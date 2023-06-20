#include <ultra64.h>
#include <ramrom.h>
#include "n64audio.h"

/*
 * Double buffered storage for wavetable data
 */
Acmd				*cmdList[2];
s16					audioSamples[3] = {0, 0, 0};
s16					*audioBuffer[3];
ALHeap				hp;
ALGlobals			g;
ALSynConfig			c;
ALSndpConfig		SPConfig;
u8					audioHeap[AUDIO_HEAP_SIZE];
s32					audioframeSize, minFrameSize; 
f32					fsize;
ALSndPlayer		    Sndp, *sndp = &Sndp;
ALSound				*snd;
ALSeqPlayer			sequencePlayer, *seqp = &sequencePlayer;
ALSeqpConfig		seqc;
ALBank				*midiBank, *sfxBank;
ALSeq				sequence, *seq = &sequence;
ALSndId				*idPtr;
ALSeqFile			*sfile;
ALInstrument		*inst; 
s32					nextAudioDMA = 0;

// external references 
extern OSTask           *tlist[];               /* global task list      */
extern OSIoMesg			dmaIOMessageBuf;
extern OSMesg			dmaMessageBuf[];
extern OSMesg			taskMessageBuf;
extern OSIoMesg			dmaIOMesgBuf[];
extern OSMesgQueue		dmaMessageQ;

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
		osPiStartDma(&dmaIOMesgBuf[nextAudioDMA++], OS_MESG_PRI_NORMAL, OS_READ,
                     (u32)addr, freeBuffer, dBuff->size, &dmaMessageQ);
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
 
    dState = (DMAState *) alHeapAlloc(&hp, 1, sizeof(DMAState));
    dState->currentBuffer = 0;
    dState->nBuffers = NBUFFERS;	// 4 buffers
    for (i=0; i<NBUFFERS; i++)
	{
        dState->buffers[i].ptr = alHeapAlloc(&hp, 1, MAX_BUFFER_LENGTH);	//MAX_BUFFER_LENGTH  = 1024
        dState->buffers[i].addr = 0;
        dState->buffers[i].len = 0;
        dState->buffers[i].size = MAX_BUFFER_LENGTH;
    }
    *state = (DMAState *) dState;

	//rmonPrintf("cbn\n");
    return dmaCallBack;
}



/*****************************************************************************
*
*	Function Title: (void) InitAudioSystem()
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
void InitAudioSystem()
{



	// Audio initialization
	//snd_status = AL_STOPPED;	
	alHeapInit(&hp, audioHeap, AUDIO_HEAP_SIZE);
    cmdList[0] = alHeapAlloc(&hp, 1, MAX_CLIST_SIZE*sizeof(Acmd));
    cmdList[1] = alHeapAlloc(&hp, 1, MAX_CLIST_SIZE*sizeof(Acmd));
    tlist[0] = alHeapAlloc(&hp, 1, sizeof(OSTask));
    tlist[1] = alHeapAlloc(&hp, 1, sizeof(OSTask));
    audioBuffer[0] = alHeapAlloc(&hp, 1, sizeof(s32)*MAX_AUDIO_LENGTH);
    audioBuffer[1] = alHeapAlloc(&hp, 1, sizeof(s32)*MAX_AUDIO_LENGTH);
    audioBuffer[2] = alHeapAlloc(&hp, 1, sizeof(s32)*MAX_AUDIO_LENGTH);


	/*
     * Audio synthesizer initialization
     */
    /* Initialize the DACs */
    c.outputRate = osAiSetFrequency(OUTPUT_RATE);
    fsize = (f32) NUM_FIELDS * c.outputRate / (f32) 60;

    audioframeSize = (s32) fsize;
    if (audioframeSize < fsize)
        audioframeSize++;
    if (audioframeSize & 0xf)
        audioframeSize = (audioframeSize & ~0xf) + 0x10;
    minFrameSize = audioframeSize - 16;

    /*
     * initialize audio synthesizer
     */
    c.maxVVoices = MAX_VOICES;
    c.maxPVoices = MAX_VOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc    = &dmaNew;
	c.fxType	 = AL_FX_SMALLROOM;
    c.heap       = &hp;

    alInit(&g, &c);

    /*
     * Initialize the soundplayer
     */
    SPConfig.maxSounds = MAX_VOICES;
    SPConfig.maxEvents = EVT_COUNT;
    SPConfig.heap  = &hp;
    alSndpNew(sndp, &SPConfig);
}



/*****************************************************************************
*
*	Function Title: static s32 nActiveSounds(ALSndPlayer *sndp, ALInstrument  *inst, ALSndId *idPtr)
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


