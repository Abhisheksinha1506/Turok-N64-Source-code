//#define IG_DEBUG

#include <ultra64.h>
#include <libaudio.h>
#include <ultralog.h>
#include <ramrom.h>
#include <rmon.h>
#include "tengine.h"
#include "audio.h"

extern OSSched         sc;

extern char _sfxbankSegmentRomStart[], _sfxbankSegmentRomEnd[];
extern char _sfxtableSegmentRomStart[], _sfxtableSegmentRomEnd[];
extern char _tableSegmentRomStart[], _tableSegmentRomEnd[];
extern char _seqSegmentRomStart[], _seqSegmentRomEnd[];
extern char _bankSegmentRomStart[], _bankSegmentRomEnd[];


/**** audio globals ****/
t_AudioWorld		AW;
//u8					audioHeap[AUDIO_HEAP_SIZE];
ALSeqPlayer			*seqp;
static u8			*seqPtr;
static s32			seqLen;
static ALSeq		*seq;
static ALSeqMarker	seqStart;
static ALSeqMarker	seqEnd;
ALHeap				hp;

void initAudio(void)
{
    ALBankFile		*bankPtr;
    u32				bankLen;
    ALSynConfig		c;
    ALSeqpConfig	seqc;
    amConfig		amc;
	int				i;
    s32				numAllocated;
	ALSndId			*idPtr;
	ALSound			*newsndptr;
	ALSndPlayer		*PlayerPtr;
	t_SoundPlayer	*PlayerInfo;
	ALInstrument	*inst;

	InitSoundGlobals(DEFAULT_RADIUS);

    alHeapInit(&hp, audioHeap, AUDIO_HEAP_SIZE);

    /*
     * Load the bank file from ROM
     */
    bankLen = _bankSegmentRomEnd - _bankSegmentRomStart;
    bankPtr = alHeapAlloc(&hp, 1, bankLen);
    romcpy(_bankSegmentRomStart, (char *)bankPtr, bankLen);
    alBnkfNew(bankPtr, (u8 *) _tableSegmentRomStart);

    /*
     * Load the sequence file from ROM
     */
    seqLen = _seqSegmentRomEnd - _seqSegmentRomStart;
    seqPtr = alHeapAlloc(&hp, 1, seqLen);
    romcpy(_seqSegmentRomStart, (char *) seqPtr, seqLen);

    /*
     * Create the Audio Manager
     */
    c.maxVVoices = MAX_VOICES;
    c.maxPVoices = MAX_VOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc    = 0;                  /* audio mgr will fill this in */
    c.fxType	 = AL_FX_BIGROOM;
    c.outputRate = 0;                  /* audio mgr will fill this in */
    c.heap       = &hp;

    amc.outputRate = 44100;
    amc.framesPerField = NUM_FIELDS;
    amc.maxACMDSize = MAX_RSP_CMDS;

	// Intialize AudioWorld globals
	AW.SndPlayerList.NextPlayer = NULL;
	for(i = 0; i<MAX_VOICES;i++)
	{
		AW.VoiceChannels[i].VoiceHandle = -1;
		AW.SndPlayerList.idlist[i] = -1;
		AW.VoiceChannels[i].theSFX.SfxNum = -1;
		AW.VoiceChannels[i].theSFX.Priority = 0;
		AW.VoiceChannels[i].SndPlayer = &AW.SndPlayerList.Sndp;
	}

    amCreateAudioMgr(&c, PRIORITY_AUDIO, &amc);

    /*
     * Create the sequence and the sequence player
     */
    seqc.maxVoices      = MAX_VOICES;
    seqc.maxEvents      = MAX_EVENTS;
    seqc.maxChannels    = 16;
    seqc.heap           = &hp;
    seqc.initOsc        = 0;
    seqc.updateOsc      = 0;
    seqc.stopOsc        = 0;

    seqp = alHeapAlloc(&hp, 1, sizeof(ALSeqPlayer));
    alSeqpNew(seqp, &seqc);
    seq = alHeapAlloc(&hp, 1, sizeof(ALSeq));
    alSeqNew(seq, seqPtr, seqLen);
    //alSeqNewMarker(seq, &seqStart, 0);
    //alSeqNewMarker(seq, &seqEnd, -1);
    //alSeqpLoop(seqp, &seqStart, &seqEnd, -1);
    //alSeqpSetSeq(seqp, seq);
    //alSeqpSetBank(seqp, bankPtr->bankArray[0]);
    //alSeqpPlay(seqp);

    /*
     * Initialize the soundplayer
     */
    AW.SPConfig.maxSounds = MAX_VOICES;
    AW.SPConfig.maxEvents = EVT_COUNT;
    AW.SPConfig.heap  = &hp;
	alSndpNew(&AW.SndPlayerList.Sndp, &AW.SPConfig);


	AW.SFXcounter = 0;
	AW.ChannelLock = -1;


	//load sounds
    bankLen = _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart;
    AW.SndPlayerList.sfxBankPtr = alHeapAlloc(&hp, 1, bankLen);
	romcpy(_sfxbankSegmentRomStart,  AW.SndPlayerList.sfxBankPtr, bankLen);
	alBnkfNew((ALBankFile *) AW.SndPlayerList.sfxBankPtr, _sfxtableSegmentRomStart);
    AW.SndPlayerList.sfxBank = ((ALBankFile *) AW.SndPlayerList.sfxBankPtr)->bankArray[0];


    inst =  AW.SndPlayerList.sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;
	PlayerPtr = &AW.SndPlayerList.Sndp;
	PlayerInfo = &AW.SndPlayerList;
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
INT32 initSFX(INT16	sfxnum)
{

	int				i;
	t_SndPtr		*sndptr;
	INT16			NextVoice;
	ALSndId			*idPtr;
	ALSound			*newsndptr;
	ALSndPlayer		*PlayerPtr;
	t_SoundPlayer	*PlayerInfo;
	ALInstrument	*inst;


	NextVoice = GetNextVoice();
	
	ASSERT(AW.ChannelLock == -1);
	AW.ChannelLock = NextVoice;

	if(NextVoice < 0)
	{
		TRACE1("NextVoice:%d\n", NextVoice);
		return -1;
	}


	// allocate sound in player
	inst =  AW.SndPlayerList.sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;
	PlayerPtr = &AW.SndPlayerList.Sndp;
	PlayerInfo = &AW.SndPlayerList;

	newsndptr = inst->soundArray[sfxnum];

   ASSERT(idPtr[NextVoice] == -1);
	idPtr[NextVoice] = alSndpAllocate(PlayerPtr, newsndptr);
	if (idPtr[NextVoice] == -1)
	{
		AW.VoiceChannels[NextVoice].VoiceHandle = -1;
		AW.ChannelLock = -1;
		TRACE0("snd alloc error!\n");
		return -1;
	}
	else
   {
		PlayerInfo->SoundCount++;
		AW.VoiceChannels[NextVoice].VoiceHandle = idPtr[NextVoice];
		//AW.ChannelLock = NextVoice;
		TRACE1("v:%d\n", NextVoice);
		//TRACE1("id:%d\n", idPtr[NextVoice]);
		//TRACE1("sfx:%d\n", sfxnum);
	}



	sndptr = &AW.VoiceChannels[NextVoice].theSFX;
	//sndptr->CurrentX = 0;
	//sndptr->CurrentY = 0;
	//sndptr->CurrentZ = 0;
	sndptr->MaxVol = DEFAULT_VOLUME;
	sndptr->Vol = DEFAULT_VOLUME;
	sndptr->Pitch = DEFAULT_PITCH;
	sndptr->FXmix = DEFAULT_FXMIX;
	sndptr->Pan = DEFAULT_PAN;
	sndptr->Looped = 0;
	sndptr->Priority = DEFAULT_PRIORITY;
	//sndptr->SndState = AL_STOPPED;
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
	INT16			VoiceNum, i, Channel;
	ALSndPlayer		*Sndp;
	t_SndPtr		*sndptr;

	if(VoiceHandle == -1)
	{
		TRACE0("No voices free\n");
		return -1;
	}

	Channel = -1;
	for(i = 0; i<MAX_VOICES;i++)
	{
		if(AW.VoiceChannels[i].VoiceHandle == VoiceHandle)
		{
			Channel= i;
			break;
		}
	}

	if(Channel == -1)
	{
		TRACE0("channel:-1\n");
		return -1;
	}

	// this will eventually search sound player list
	// for the address of the player
	sndplayer = &AW.SndPlayerList;

	Sndp = AW.VoiceChannels[Channel].SndPlayer;
	sndptr = &AW.VoiceChannels[Channel].theSFX;

	if (sndptr->Vol == 0)
	{
		// will get deallocated in UpdateWorldSound()
		AW.ChannelLock = -1;
		return 0;
	}

	ASSERT(sndplayer->idlist[Channel] != -1);
	alSndpSetSound(Sndp, sndplayer->idlist[Channel]);
	if (alSndpGetState(Sndp) != AL_STOPPED)
	{
		ASSERT(FALSE);
		AW.ChannelLock = -1;
		return 0;
	}

	alSndpSetPitch(Sndp, sndptr->Pitch);
    alSndpSetFXMix(Sndp, sndptr->FXmix);
    alSndpSetPan(Sndp, sndptr->Pan);
    alSndpSetVol(Sndp, sndptr->Vol);
    alSndpPlay(Sndp);
	AW.ChannelLock = -1;
	return 0;
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
	INT16			PriorityCount, Priority;
	int				i;
	ALSndPlayer		*Sndp;
	t_SoundPlayer	*sndplayer;

	sndplayer = &AW.SndPlayerList;
	Sndp = &sndplayer->Sndp;


	// if there are sounds with duplicate priorities, it will kill the first one
	Priority = AW.VoiceChannels[0].theSFX.Priority;
	for(i = 0; i < MAX_VOICES; i++)
	{
		if((AW.VoiceChannels[i].theSFX.Priority >= Priority) || (AW.VoiceChannels[i].theSFX.Priority == 0))
			Priority = AW.VoiceChannels[i].theSFX.Priority;

		// if Priority == 0, then we have found a free channel stop looking
		if(Priority == 0)
			break;

	}

	if (i == MAX_VOICES)
	{
		i = 0;
		Priority = AW.VoiceChannels[i].theSFX.Priority;
	}

	if(Priority != 0)
	{
		// there is a sound allocated, we must kill it
		ASSERT(sndplayer->idlist[i] != -1);
		alSndpSetSound(Sndp, sndplayer->idlist[i]);
		if (alSndpGetState(Sndp) != AL_STOPPED)
		{
			alSndpStop(Sndp);

			while(alSndpGetState(Sndp) != AL_STOPPED)
			{
				TRACE0("wait kill\n");
			}
			TRACE1("voice %d killed\n", i);
		}

		alSndpDeallocate(Sndp, sndplayer->idlist[i]);
		sndplayer->idlist[i] = -1;

		AW.VoiceChannels[i].VoiceHandle = -1;
		AW.VoiceChannels[i].theSFX.SfxNum = -1;
		AW.VoiceChannels[i].theSFX.Priority = 0;
		TRACE1("sfx %d killed\n", sndplayer->idlist[i]);
	}

	return i;
}

/*****************************************************************************
*
*		Function Title:	void killSFX(INT32 VoiceHandle)
*
*****************************************************************************
*
*		Description:	this will kill the specified sound effect
*
*		Inputs:			voice handle
*
*		Outputs:		voice number
*
****************************************************************************/
void killSFX(INT32 VoiceHandle)
{
	t_SoundPlayer	*sndplayer;
	INT16			VoiceNum, i, Channel;
	ALSndPlayer		*Sndp;
	t_SndPtr		*sndptr;


	// search cheannels for voice handle
	Channel = -1;
	for(i = 0; i<MAX_VOICES;i++)
	{
		if(AW.VoiceChannels[i].VoiceHandle == VoiceHandle)
		{
			Channel = i;
			break;
		}
	}

	// if can't find  sound do nothing
	if(Channel == -1)
		return;

	sndplayer = &AW.SndPlayerList;
	Sndp = AW.VoiceChannels[Channel].SndPlayer;
	ASSERT(sndplayer->idlist[Channel] != -1);
	alSndpSetSound(Sndp, sndplayer->idlist[Channel]);
    alSndpStop(Sndp);
}


/*****************************************************************************
*
*		Function Title:	void killSFX(INT32 VoiceHandle)
*
*****************************************************************************
*
*		Description:	this will kill the specified sound effect
*
*		Inputs:			voice handle
*
*		Outputs:		voice number
*
****************************************************************************/
void killAllSFX(void)
{
	t_SoundPlayer	*sndplayer;
	INT16			VoiceNum, i, Channel;
	ALSndPlayer		*Sndp;
	t_SndPtr		*sndptr;

	Channel = -1;
	sndplayer = &AW.SndPlayerList;
	for(i = 0; i<MAX_VOICES;i++)
	{
		Sndp = AW.VoiceChannels[i].SndPlayer;
		ASSERT(sndplayer->idlist[i] != -1);
		alSndpSetSound(Sndp, sndplayer->idlist[i]);
		alSndpStop(Sndp);
	}

}


/*****************************************************************************
*
*	Function Title:  INT16 UpdateWorldSound(void);
*
******************************************************************************
*
*	Description:	This updates world sound. It keeps track of environmental
*					variables and monitors voices. It also does clean up of
*					voices that have finished playing
*
*	Inputs:			None
*
*	Outputs:		Number of active voices still playing
*
*****************************************************************************/
INT16 UpdateWorldSound(void)
{
	int				i,  nactive = 0;
	t_SoundPlayer	*sndplayer;
	ALSndPlayer		*Sndp;


	sndplayer = &AW.SndPlayerList;
	Sndp = &sndplayer->Sndp;

   for (i=0; i<MAX_VOICES; i++)
	{
		if((AW.VoiceChannels[i].VoiceHandle != -1) && (AW.ChannelLock != i))
		{
			ASSERT(sndplayer->idlist[i] != -1);
			alSndpSetSound(Sndp, sndplayer->idlist[i]);
			if (alSndpGetState(Sndp) == AL_STOPPED)
			{
				alSndpDeallocate(Sndp, sndplayer->idlist[i]);
				sndplayer->idlist[i] = -1;

				AW.VoiceChannels[i].VoiceHandle = -1;
				AW.VoiceChannels[i].theSFX.SfxNum = -1;
				AW.VoiceChannels[i].theSFX.Priority = 0;
				TRACE2("free(%d:%d)\n", sndplayer->idlist[i], i);
			}
			else	// sound is still playing
			{
				//UpdateVolume(i);
					//UpdatePitch(i);
					//UpdateFXmix(i);
				//UpdatePan(i);
				nactive++;
			}
		}
    }

    return nactive;
}

int SoundHandleToChannel(INT32 VoiceHandle)
{
	int i;

	if (VoiceHandle == -1)
		return -1;

	for (i=0; i<MAX_VOICES; i++)
		if (AW.VoiceChannels[i].VoiceHandle == VoiceHandle)
			return i;

	return -1;
}

void SetSoundVolume(INT32 VoiceHandle, float Volume)
{
	int				channel;
	t_SndPtr			*pSound;

	channel = SoundHandleToChannel(VoiceHandle);
	if (channel == -1)
		return;

	pSound = &AW.VoiceChannels[channel].theSFX;

	pSound->Vol = pSound->MaxVol = (INT32) (MAX_WORLD_VOL * max(0, min(1, Volume)));
}

void SetSoundPitch(INT32 VoiceHandle, float Pitch)
{
#if 0
	int				channel;
	t_SndPtr			*pSound;

	channel = SoundHandleToChannel(VoiceHandle);
	if (channel == -1)
		return;

	pSound = &AW.VoiceChannels[channel].theSFX;

	pSound->Pitch = Pitch;
#endif
}

void SetSoundPosition(INT32 VoiceHandle, float X, float Y, float Z)
{
	int				channel;
	//ALSndPlayer		*pPlayer;
	t_SndPtr			*pSound;
	float				dx, dy, dz,
						udx, udz,
						dist, invDist,
						rightX, rightZ,
						dot;

	channel = SoundHandleToChannel(VoiceHandle);
	if (channel == -1)
		return;

	pSound = &AW.VoiceChannels[channel].theSFX;

	dx = X - AW.Ears.x;
	dy = Y - AW.Ears.y;
	dz = Z - AW.Ears.z;

	dist = sqrt(dx*dx + dy*dy + dz*dz);
	if (dist == 0)
	{
		udx = 0;
		udz = 1;

		dot = 0;

		rightX = rightZ = 0;
	}
	else
	{
		invDist = 1/dist;

		udx = dx*invDist;
		udz = dz*invDist;

		rightX = cos(AW.Ears.YRot);
		rightZ = sin(AW.Ears.YRot);

		dot = rightX*udx + rightZ*udz;
	}

	ASSERT(AW.Ears.Radius != 0);
	pSound->Vol = (INT32) (pSound->MaxVol * max(0.0, AW.Ears.Radius - dist*0.7)/AW.Ears.Radius);

	pSound->Pan = ((char) ((dot + 1)*127)) >> 1;

	//pPlayer = &AW.SndPlayerList.Sndp;

	//alSndpSetSound(pPlayer, AW.SndPlayerList.idlist[channel]);

	//alSndpSetVol(pPlayer, pSound->Vol);
	//alSndpSetPan(pPlayer, pSound->Pan);
}

void DoSound(int nSound, float X, float Y, float Z, float Volume, float Pitch)
{
	UINT32	hSound;

	hSound = initSFX(nSound);
	
	if (Volume != 1)
		SetSoundVolume(hSound, Volume);
	if (Pitch != 1)
		SetSoundPitch(hSound, Pitch);

	SetSoundPosition(hSound, X,Y,Z);

	playSFX(hSound);
}

/*****************************************************************************
*
*	Function Title:  void InitSoundGlobals(float Radius)
*
******************************************************************************
*
*	Description:
*
*	Inputs:
*
*	Outputs:
*
*****************************************************************************/
void InitSoundGlobals(float Radius)
{
	AW.VolScaleFactor = MAX_WORLD_VOL/Radius;
	AW.Ears.Radius = Radius;
	AW.Ears.x = 0;
	AW.Ears.y = 0;
	AW.Ears.z = 0;
	AW.Ears.YRot = 0;
}

/*****************************************************************************
*
*	Function Title:  INT16 UpdateEars(void);
*
******************************************************************************
*
*	Description:	This updates world sound. It keeps track of environmental
*					variables and monitors voices. It also does clean up of
*					voices that have finished playing
*
*	Inputs:			None
*
*	Outputs:
*
*****************************************************************************/
void UpdateEars(t_Ears *EarLocation)
{
	AW.Ears.x = EarLocation->x;
	AW.Ears.y = EarLocation->y;
	AW.Ears.z = EarLocation->z;
	AW.Ears.YRot = EarLocation->YRot;
	AW.Ears.Radius = EarLocation->Radius;
}

