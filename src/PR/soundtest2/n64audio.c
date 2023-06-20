#include <ultra64.h>
#include <ramrom.h>
#include "n64audio.h"

/*
 * Double buffered storage for wavetable data
 */
Acmd				*cmdList[2];
s16					audioSamples[3] = {0, 0, 0};
s16					*audioBuffer[3];
s32					audioframeSize, minFrameSize, samplesLeft = 0; 
f32					fsize;
ALBank				*sfxBank;
ALInstrument		*inst;




INT8 audio_yield_buffer[OS_YIELD_AUDIO_SIZE+15];
u64 *audio_yield_buffer_ptr;
t_AudioWorld		AW;

// external references 
extern OSTask			*theadp;
extern OSTask			*tlistp;
extern OSTask           *tlist[];               /* global task list      */
extern OSIoMesg			dmaIOMessageBuf;
extern OSMesg			AudioDmaMessageBuf[];
extern OSMesg			AudioTaskMessageBuf;
extern OSIoMesg			dmaIOMesgBuf[];
extern OSMesgQueue		AudioTaskMessageQ, AudioRetraceMessageQ, retraceMessageQ;
extern s32				curBuf;
extern u8 _seqSegmentRomStart[], _seqSegmentRomEnd[];
extern u8 _sfxbankSegmentRomStart[], _sfxbankSegmentRomEnd[];
extern u8 _sfxtableSegmentRomStart[], _sfxtableSegmentRomEnd[];
extern u8 _midibankSegmentRomStart[], _midibankSegmentRomEnd[];
extern u8 _miditableSegmentRomStart[], _miditableSegmentRomEnd[];
extern char		*yield_bufferptr;



/*****************************************************************************
*
*	Function Title: s32 dmaCallBack(s32 addr, s32 len, void *state)
*
******************************************************************************
*
*	Description:	This will calculate the address of the next transfer.
*					If that address is outside of the audio buffers. It 
*					will send get the next chunk of audio data from the
*					cartridge.	 
*
*	Inputs:			
*
*	Outputs:		
*
*****************************************************************************/
s32 dmaCallBack(s32 addr, s32 len, void *state)
{
    void        *freeBuffer;
    DMAState    *dState = state;
    s32         delta = 0;
    u32         bStartAddr;
    u32         bEndAddr;
    DMABuffer   *dBuff = &dState->buffers[dState->currentBuffer];
	/*
     * Is it in the last buffer
     */
    bStartAddr = (u32) dBuff->addr;
    bEndAddr = (u32) bStartAddr + dBuff->len;

    if ((addr >= bStartAddr) && (addr+len <= bEndAddr))
	{
        freeBuffer = dBuff->ptr + addr - dBuff->addr;
    } 
	else
	{
        if (++dState->currentBuffer >= dState->nBuffers )	// wrap arround
            dState->currentBuffer = 0;
        dBuff = &dState->buffers[dState->currentBuffer];
        freeBuffer = dBuff->ptr;
        delta = addr & 0x1;	// make sure address is even
        addr -= delta;
        dBuff->addr = addr;
        dBuff->len = dBuff->size;	 // size = 1024
		osPiStartDma(&dmaIOMesgBuf[AW.nextAudioDMA++], OS_MESG_PRI_NORMAL, OS_READ,
                     (u32)addr, freeBuffer, dBuff->size, &AW.AudioDmaMessageQ);
	}

    return (s32) osVirtualToPhysical(freeBuffer) + delta;
}


/*****************************************************************************
*
*	Function Title: ALDMAproc dmaNew(DMAState **state)
*
******************************************************************************
*
*	Description:	This will initialize a voice in the sound player. It also 
*					sets the call back routines for DMA transfers.	
*
*	Inputs:			DMA stat
*
*	Outputs:		address of callback routine
*
*****************************************************************************/
ALDMAproc dmaNew(DMAState **state)
{
    s32         i;
    DMAState    *dState;
 
    dState = (DMAState *) alHeapAlloc(&AW.hp, 1, sizeof(DMAState));
    dState->currentBuffer = 0;
    dState->nBuffers = NBUFFERS;	// 4 buffers
    for (i=0; i<NBUFFERS; i++)
	{
        dState->buffers[i].ptr = alHeapAlloc(&AW.hp, 1, MAX_BUFFER_LENGTH);	//MAX_BUFFER_LENGTH  = 1024
        dState->buffers[i].addr = 0;
        dState->buffers[i].len = 0;
        dState->buffers[i].size = MAX_BUFFER_LENGTH;
    }
    *state = (DMAState *) dState;

	//TRACE(("cbn\n"));
    return dmaCallBack;
}



/*****************************************************************************
*
*	Function Title: (void) InitAudioSystem(void)
*
******************************************************************************
*
*	Description:	This will init sound player and allocate the memory 
*					for sound buffers.	
*
*	Inputs:			none
*
*	Outputs:		none
*
*****************************************************************************/
void InitAudioSystem(void)
{

	int			i;

	// Audio initialization
	//snd_status = AL_STOPPED;	
	alHeapInit(&AW.hp, AW.audioHeap, AUDIO_HEAP_SIZE);
    cmdList[0] = alHeapAlloc(&AW.hp, 1, MAX_CLIST_SIZE*sizeof(Acmd));
    cmdList[1] = alHeapAlloc(&AW.hp, 1, MAX_CLIST_SIZE*sizeof(Acmd));
    tlist[0] = alHeapAlloc(&AW.hp, 1, sizeof(OSTask));
    tlist[1] = alHeapAlloc(&AW.hp, 1, sizeof(OSTask));
    audioBuffer[0] = alHeapAlloc(&AW.hp, 1, sizeof(s32)*MAX_AUDIO_LENGTH);
    audioBuffer[1] = alHeapAlloc(&AW.hp, 1, sizeof(s32)*MAX_AUDIO_LENGTH);
    audioBuffer[2] = alHeapAlloc(&AW.hp, 1, sizeof(s32)*MAX_AUDIO_LENGTH);


	/*
     * Audio synthesizer initialization
     */
    /* Initialize the DACs */
    AW.SynthConfig.outputRate = osAiSetFrequency(OUTPUT_RATE);
    fsize = (f32) NUM_FIELDS * AW.SynthConfig.outputRate / (f32) 60;

    audioframeSize = (s32) fsize;
    if (audioframeSize < fsize)
        audioframeSize++;
    if (audioframeSize & 0xf)
        audioframeSize = (audioframeSize & ~0xf) + 0x10;
    minFrameSize = audioframeSize - 16;

    /*
     * initialize audio synthesizer
     */
    AW.SynthConfig.maxVVoices = MAX_VOICES;
    AW.SynthConfig.maxPVoices = MAX_VOICES;
    AW.SynthConfig.maxUpdates = MAX_UPDATES;
    AW.SynthConfig.dmaproc    = &dmaNew;
	AW.SynthConfig.fxType	 = AL_FX_BIGROOM;
    AW.SynthConfig.heap       = &AW.hp;

    alInit(&AW.GlobalAudio, &AW.SynthConfig);

    /*
     * Initialize the soundplayer
     */
    AW.SPConfig.maxSounds = MAX_VOICES;
    AW.SPConfig.maxEvents = EVT_COUNT;
    AW.SPConfig.heap  = &AW.hp;
	alSndpNew(&AW.SndPlayerList.Sndp, &AW.SPConfig);

	// Intialize AudioWorld globals
	AW.SndPlayerList.NextPlayer = NULL;
	for(i = 0; i<MAX_VOICES;i++)
	{
		AW.VoiceChannels[i].VoiceHandle = -1;
		AW.VoiceChannels[i].theSFX.SfxNum = -1;
		AW.VoiceChannels[i].theSFX.Priority = 0;
		AW.VoiceChannels[i].SndPlayer = &AW.SndPlayerList.Sndp;
	}

	AW.SFXcounter = 0;
}



/*****************************************************************************
*
*	Function Title: static s32 nActiveSounds(ALSndPlayer *sndp, ALInstrument  *inst, ALSndId *idPtr)
*
******************************************************************************
*
*	Description:	This finds the number of active sounds that are being played
*
*	Inputs:			none
*
*	Outputs:		none
*
*****************************************************************************/
static s32 nActiveSounds(ALSndPlayer *sndp, ALInstrument  *inst, ALSndId *idPtr)

{
    s32		i,  nactive = 0;

    for (i=0; i<sndp->maxSounds; i++)
	{
        alSndpSetSound(sndp, idPtr[SFX_NUM]);
        if (alSndpGetState(sndp) != AL_STOPPED)
            nactive++;
    }
    return nactive;
}

/*****************************************************************************
*
*	Function Title: void updateAudio()
*
******************************************************************************
*
*	Description:	This will build the audio task list that will be sent to the RCP and
*					swaps the audio buffers.	
*
*	Inputs:			none
*
*	Outputs:		none
*
*****************************************************************************/
void updateAudio(void)
{	

	s32			buf, yielded;
	int			i;

	/*
	 * Build the audio task
	 */
	tlistp->t.type = M_AUDTASK;
	tlistp->t.flags = 0x0;
	tlistp->t.ucode_boot = (u64 *) rspbootTextStart;
	tlistp->t.ucode_boot_size = ((s32)rspbootTextEnd -
								 (s32)rspbootTextStart);
	tlistp->t.ucode = (u64 *) aspMainTextStart;
	tlistp->t.ucode_data = (u64 *) aspMainDataStart;
	tlistp->t.ucode_size = 4096;
	tlistp->t.ucode_data_size = sizeof(u64)*(aspMainDataEnd - aspMainDataStart);
	tlistp->t.data_ptr = (u64 *) cmdList[curBuf];
	tlistp->t.data_size = (AW.cmdlp - cmdList[curBuf]) * sizeof(Acmd);
	tlistp->t.data_ptr = 
	tlistp->t.yield_data_ptr = audio_yield_buffer_ptr;
	tlistp->t.yield_data_size = OS_YIELD_AUDIO_SIZE;

	TRACE(("atask:%x\n", audio_yield_buffer));


	/*
	 * Video does nothing - just syncs up on the frame boundary.
	 */
	//(void)osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);

	/*
	 * Find out how many samples left in the currently running
	 * audio buffer
	 */
	samplesLeft = IO_READ(AI_LEN_REG)>>2;

	/*
	 * The last task should have finished before the frame message
	 * so this just clears the message queue
	 */
	//(void)osRecvMesg(&AudioTaskMessageQ, NULL, OS_MESG_BLOCK);

	/*
	 * Stick the task output in files - or to the DAC
	 */
	buf = (AW.curAudioBuf-1) % 3;
	osAiSetNextBuffer(audioBuffer[buf], audioSamples[buf]<<2);

	/*
	 * Empty the dma queue to make sure all DMAs have completed
	 */
	for (i=0; i<AW.nextAudioDMA; i++)
		osRecvMesg(&AW.AudioDmaMessageQ, NULL, OS_MESG_BLOCK);

	osWritebackDCacheAll();



#if 1

	// empty audio queue
	while (!MQ_IS_EMPTY(&AudioTaskMessageQ))
		osRecvMesg(&AudioTaskMessageQ, NULL, OS_MESG_BLOCK);

	// save state of RSP and suspend RSP task
	osSpTaskYield();
	//osInvalDCache(theadp, sizeof(OSTask));
	osInvalDCache(yield_bufferptr, OS_YIELD_DATA_SIZE);
	yielded = osSpTaskYielded(theadp);
		TRACE(("y:%d\n", yielded));

	osWritebackDCacheAll();
	osSpTaskStart(tlistp);
	TRACE(("TaskStart\n"));

	while(MQ_IS_EMPTY(&AudioTaskMessageQ));
	osRecvMesg(&AudioTaskMessageQ, NULL, OS_MESG_BLOCK);
	// restore  previous state, and start task

	TRACE(("Taskfinished\n"));

	if (yielded == OS_TASK_YIELDED)
	{
		osWritebackDCacheAll();
		osSpTaskStart(theadp);
	}

#endif

	// Swap buffers for wavetable storage and output
	curBuf ^= 1;
	AW.curAudioBuf++;
	AW.nextAudioDMA = 0;
}

/*****************************************************************************
*
*		Function Title:	void allocateSFX
*
*****************************************************************************
*
*		Description:	will allocate and load sound effetcs
*
*		Inputs:			
*
*		Outputs:		
*
****************************************************************************/
s32	 allocateSFX(void)
{
	s32				bankLen, numAllocated;
    u8				*sfxBankPtr;
	ALSndId			*idPtr;
	INT16			i;
	ALSound			*newsndptr;
	ALSndPlayer		*PlayerPtr;

    bankLen = _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart;
    sfxBankPtr = alHeapAlloc(&AW.hp, 1, bankLen);
    osWritebackDCacheAll();
    osPiStartDma(&dmaIOMessageBuf, OS_MESG_PRI_NORMAL, OS_READ,
                 (u32)_sfxbankSegmentRomStart, sfxBankPtr,
                 bankLen, &AW.AudioDmaMessageQ);
    (void) osRecvMesg(&AW.AudioDmaMessageQ, NULL, OS_MESG_BLOCK);

	
    inst = sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;  
	PlayerPtr = &AW.SndPlayerList.Sndp;

    for (i=0, numAllocated = 0; i < inst->soundCount; i++)
	{	
		newsndptr = inst->soundArray[i];
        if ((idPtr[i] = alSndpAllocate(PlayerPtr, newsndptr)) != -1)
            numAllocated++;
		else
			rmonPrintf("alloc error!\n");
    }


	return numAllocated;

}



/*****************************************************************************
*
*	Function Title: INT16 GetNextVoice()
*
******************************************************************************
*
*	Description:	This will return the voice number of the next available voice.
*					
*	Inputs:			none
*
*	Outputs:		voice number
*
*****************************************************************************/
INT16 GetNextVoice(void)
{
	INT16	PriorityCount, Priority;
	int		i;


	Priority = AW.VoiceChannels[0].theSFX.Priority;
	for(i = 0; i < MAX_VOICES; i++)
	{	
		if(AW.VoiceChannels[i].theSFX.Priority > Priority)
			Priority = AW.VoiceChannels[i].theSFX.Priority;

	}

	return Priority;

}
/*****************************************************************************
*
*	Function Title: INT32 InitSFX(INT16	sfxnum)
*
******************************************************************************
*
*	Description:	This will init sfx and fill in the t_SndPtr structure with 
*					default values. If the requested song is already being played 
*					another soundplayer will be allocated. 
*	Inputs:			sfx num
*
*	Outputs:		sound handle.
*
*****************************************************************************/
INT32 InitSFX(INT16	sfxnum)
{
	
	int				i;
	t_SndPtr		*sndptr;
	INT16			NextVoice;					


	NextVoice = GetNextVoice();

	if(NextVoice < 0)
		return -1;

	// this should be
	//AW.VoiceChannels[NextVoice].SndPlayer = GetSndPlayer(); 
	AW.VoiceChannels[NextVoice].SndPlayer = &AW.SndPlayerList.Sndp;
	AW.VoiceChannels[NextVoice].VoiceHandle = AW.SFXcounter++;;
	sndptr = &AW.VoiceChannels[NextVoice].theSFX;
	sndptr->CurrentX = 0;
	sndptr->CurrentY = 0;	
	sndptr->CurrentZ = 0;	
	sndptr->Vol = DEFAULT_VOLUME;
	sndptr->Pitch = DEFAULT_PITCH;
	sndptr->FXmix = DEFAULT_FXMIX;
	sndptr->Pan = DEFAULT_PAN;
	sndptr->Looped = 0;
	sndptr->Priority = DEFAULT_PRIORITY;
	sndptr->SndState = AL_STOPPED;
	sndptr->SfxNum = sfxnum;

	return AW.VoiceChannels[NextVoice].VoiceHandle;

}

/*****************************************************************************
 *
 *		Function Title:	INT16 playSFX(INT32 VoiceHandle)
 *
 *****************************************************************************
 *
 *		Description:	this will play the specified sound effect at x,y,z
 *
 *		Inputs:			voice handle
 *
 *		Outputs:		voice number
 *
 ****************************************************************************/
INT16 playSFX(INT32 VoiceHandle)
{
	t_SoundPlayer	*sndplayer;
	INT16			VoiceNum, i, Channel = -1;
	ALSndPlayer		*Sndp;
	t_SndPtr		*sndptr;


	for(i = 0; i<MAX_VOICES;i++)
	{
		if(AW.VoiceChannels[i].VoiceHandle == VoiceHandle)
		{
			Channel= i;
			break;
		}
	}

	if(Channel == MAX_VOICES)
	{
		TRACE(("channel:-1\n"));
		return -1;
	}

	// this will eventually search sound player list 
	// for the address of the player
	sndplayer = &AW.SndPlayerList;

	Sndp = AW.VoiceChannels[Channel].SndPlayer;
	sndptr = &AW.VoiceChannels[Channel].theSFX;
	sndptr->CurrentX = 0;
	sndptr->CurrentY = 0;	
	sndptr->CurrentZ = 0;	
	sndptr->Vol = DEFAULT_VOLUME;
	sndptr->Pitch = DEFAULT_PITCH;
	sndptr->FXmix = DEFAULT_FXMIX;
	sndptr->Pan = DEFAULT_PAN;
	sndptr->Looped = 0;
	sndptr->Priority = DEFAULT_PRIORITY;
	sndptr->SndState = AL_STOPPED;

	alSndpSetSound(Sndp, sndplayer->idlist[sndptr->SfxNum]);
	alSndpSetPitch(Sndp, sndptr->Pitch);
    alSndpSetFXMix(Sndp, sndptr->FXmix);
    alSndpSetPan(Sndp, sndptr->Pan);
    alSndpSetVol(Sndp, sndptr->Vol);
    alSndpPlay(Sndp);

	return 0;
#if 0
		//if ((nActiveSounds(sndp, inst, idPtr) == 0) && (delay_counter > SFX_DELAY))
		if (nActiveSounds(sndp, inst, idPtr) == 0) 
        {
            alSndpSetSound(sndp, idPtr[SFX_NUM]);
			pitch = 15;
            alSndpSetPitch(sndp, pitch);
            fxmix = 64;	//range: (0, 127)
            alSndpSetFXMix(sndp, fxmix);
            pan = 64;	//range: (0, 127)
            alSndpSetPan(sndp, pan);
            vol = 32000;	//range: (0, 32000); 
            alSndpSetVol(sndp, vol);
            alSndpPlay(sndp);
			delay_counter = 0;
        }
		
		if (nActiveSounds(sndp, inst, idPtr) != 0)	
		{
            nTries = 0;
            do 
			{
                if (nTries++ > MAX_TRIES)
                    break;
                
                alSndpSetSound(sndp, idPtr[SFX_NUM]);
            } while (alSndpGetState(sndp) != AL_PLAYING);
            if (nTries < MAX_TRIES)
                alSndpStop(sndp);
        }
    
		delay_counter++;
#endif

}


/*****************************************************************************
 *
 *		Function Title:	void GetSFXinfo(t_SndPtr *sndptr)
 *
 *****************************************************************************
 *
 *		Description:	this will copy the SFX parameters into the structure
 *
 *		Inputs:			sound ptr
 *
 *		Outputs:		
 *
 ****************************************************************************/
INT16 GetSFXinfo(INT16 VoiceHandle, t_SndPtr *infoptr)
{
	int		i;
	t_SndPtr		*sndptr;
	
	for(i = 0; i<MAX_VOICES;i++)
	{
		if(AW.VoiceChannels[i].VoiceHandle == VoiceHandle)
			break;
	}

	if(i == MAX_VOICES)
		return -1;

	sndptr = &AW.VoiceChannels[i].theSFX;
	infoptr->CurrentX = sndptr->CurrentX;
	infoptr->CurrentY = sndptr->CurrentY;
	infoptr->CurrentZ = sndptr->CurrentZ;
	infoptr->Vol = sndptr->Vol;
	infoptr->Pitch = sndptr->Pitch;
	infoptr->FXmix = sndptr->FXmix;
	infoptr->Pan = sndptr->Pan;
	infoptr->Looped = sndptr->Looped;
	infoptr->Priority = sndptr->Priority;
	infoptr->SndState = sndptr->SndState;
	return 0;

}

/*****************************************************************************
 *
 *		Function Title:	void SetSFXinfo(t_SndPtr *sndptr)
 *
 *****************************************************************************
 *
 *		Description:	this will set SFX parameters
 *
 *		Inputs:			sound ptr 
 *
 *		Outputs:		none
 *
 ****************************************************************************/
INT16 SetSFXinfo(INT16 VoiceHandle, t_SndPtr *infoptr)
{
	int		i;
	t_SndPtr		*sndptr;

	
	for(i = 0; i<MAX_VOICES;i++)
	{
		if(AW.VoiceChannels[i].VoiceHandle == VoiceHandle)
			break;
	}

	if(i == MAX_VOICES)
		return -1;

	sndptr = &AW.VoiceChannels[i].theSFX;
	sndptr->CurrentX = infoptr->CurrentX;
	sndptr->CurrentY = infoptr->CurrentY;
	sndptr->CurrentZ = infoptr->CurrentZ;
	sndptr->Vol = infoptr->Vol;
	sndptr->Pitch = infoptr->Pitch;
	sndptr->FXmix = infoptr->FXmix;
	sndptr->Pan = infoptr->Pan;
	sndptr->Looped = infoptr->Looped;
	sndptr->Priority = infoptr->Priority;
	sndptr->SndState = infoptr->SndState;
	return 0;
}

 /*****************************************************************************
 *
 *		Function Title:	void UpdateWorldSound()
 *
 *****************************************************************************
 *
 *		Description:	this will set the priority of the sound
 *
 *		Inputs:			sound ptr and priority
 *
 *		Outputs:		none
 *
 ****************************************************************************/
//void UpdateWorldSound()
// {
// }
