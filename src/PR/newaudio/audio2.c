/**********************************************************************
 * audio.c
 *
 * This code implements the application audio thread. This is done
 * through an audio manager layer. The audio manager, does all of the 
 * neccessary initialization of the audio, and signs in to the scheduler.
 * At the begining of each video retrace, the scheduler sends a message
 * that wakes up the audio thread, which calls alAudioFrame to build an
 * audio task. Once this task is built, it is sent to the scheduler, that
 * will then send the task to the rsp for execution. 
 * 
 * Copyright 1993, Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *********************************************************************/
#include <ultra64.h>
#include <libaudio.h>
#include <ultralog.h>
#include <ramrom.h>
#include <rmon.h>
#include "audio.h"
#include "simple.h"

extern OSSched         sc;
extern u8 _sfxbankSegmentRomStart[], _sfxbankSegmentRomEnd[];
extern u8 _sfxtableSegmentRomStart[], _sfxtableSegmentRomEnd[];


/**** audio globals ****/
t_AudioWorld		AW;
u8					audioHeap[AUDIO_HEAP_SIZE];
ALSeqPlayer			*seqp;
static u8			*seqPtr;
static s32			seqLen;
static ALSeq		*seq;
static ALSeqMarker	seqStart;
static ALSeqMarker	seqEnd;
ALHeap				hp;
int					globalsfxnum  = 0;


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


	


    alHeapInit(&hp, audioHeap, sizeof(audioHeap));    

    /*
     * Load the bank file from ROM
     */
    bankLen = _bankSegmentRomEnd - _bankSegmentRomStart;
    bankPtr = alHeapAlloc(&hp, 1, bankLen);
    romCopy(_bankSegmentRomStart, (char *)bankPtr, bankLen);
    alBnkfNew(bankPtr, (u8 *) _tableSegmentRomStart);

    /*
     * Load the sequence file from ROM
     */
    seqLen = _seqSegmentRomEnd - _seqSegmentRomStart;
    seqPtr = alHeapAlloc(&hp, 1, seqLen);
    romCopy(_seqSegmentRomStart, (char *) seqPtr, seqLen);

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
 
    amCreateAudioMgr(&c, AUDIO_PRIORITY, &amc);
    
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

	// Intialize AudioWorld globals
	InitSoundGlobals(100);
	AW.SndPlayerList.NextPlayer = NULL;
	for(i = 0; i<MAX_VOICES;i++)
	{
		AW.VoiceChannels[i].VoiceHandle = -1;
		AW.VoiceChannels[i].theSFX.SfxNum = -1;
		AW.VoiceChannels[i].theSFX.Priority = 0;
		AW.VoiceChannels[i].SndPlayer = &AW.SndPlayerList.Sndp;
	}


	AW.SFXcounter = 0;
	AW.ChannelLock = -1;


	//load sounds
    bankLen = _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart;
    AW.SndPlayerList.sfxBankPtr = alHeapAlloc(&hp, 1, bankLen);
	romCopy(_sfxbankSegmentRomStart,  AW.SndPlayerList.sfxBankPtr, bankLen);
	alBnkfNew((ALBankFile *) AW.SndPlayerList.sfxBankPtr, _sfxtableSegmentRomStart);
    AW.SndPlayerList.sfxBank = ((ALBankFile *) AW.SndPlayerList.sfxBankPtr)->bankArray[0];


    inst =  AW.SndPlayerList.sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;  
	PlayerPtr = &AW.SndPlayerList.Sndp;
	PlayerInfo = &AW.SndPlayerList; 
	PRINTF("count:%d\n", inst->soundCount); 

#if 0

	// inst is of *ALInstrument
    inst =  SndPlayerList.sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;  
	PlayerPtr = &AW.SndPlayerList.Sndp;
	PlayerInfo = &AW.SndPlayerList; 
	//PlayerInfo->SoundCount = inst->soundCount;

    for (i=0, numAllocated = 0; i < inst->soundCount; i++)
	{	
		newsndptr = inst->soundArray[i];
		//newsndptr->envelope->decayTime = 772000;
		
        if ((idPtr[i] = alSndpAllocate(PlayerPtr, newsndptr)) != -1)
            numAllocated++;
		else
			PRINTF("alloc error!\n");
    }

	PRINTF("numAllocated:%d\n", numAllocated);

#endif

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

	if(NextVoice < 0)
	{	
		PRINTF("NextVoice:%d\n", NextVoice);
		return -1;
	}


	// allocate sound in player
	inst =  AW.SndPlayerList.sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;  
	PlayerPtr = &AW.SndPlayerList.Sndp;
	PlayerInfo = &AW.SndPlayerList; 

	newsndptr = inst->soundArray[sfxnum];
	PRINTF("newsndptr:%x\n", newsndptr);


    if ((idPtr[NextVoice] = alSndpAllocate(PlayerPtr, newsndptr)) != -1)
    {
		PlayerInfo->SoundCount++;
		AW.VoiceChannels[NextVoice].VoiceHandle = idPtr[NextVoice];
		AW.ChannelLock = NextVoice;
		//PRINTF("v:%d\n", NextVoice,idPtr[NextVoice]);
		//PRINTF("id:%d\n", idPtr[NextVoice]);
		//PRINTF("sfx:%d\n", sfxnum);

	}
	else
	{
		PRINTF("snd alloc error!\n");
		return -1;
	}

	

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


	
	if(VoiceHandle == -1)
	{
		PRINTF("No voices free\n");
		return -1;
	}



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
		PRINTF("channel:-1\n");
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

	alSndpSetSound(Sndp, sndplayer->idlist[Channel]);
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
		alSndpSetSound(Sndp, sndplayer->idlist[i]);
		if (alSndpGetState(Sndp) != AL_STOPPED)
		{
			alSndpStop(Sndp);

			while(alSndpGetState(Sndp) != AL_STOPPED)
			{
				PRINTF("wait kill\n");
			}
			PRINTF("voice %d killed\n", i);
			alSndpDeallocate(Sndp, sndplayer->idlist[i]);
			AW.VoiceChannels[i].VoiceHandle = -1;
			AW.VoiceChannels[i].theSFX.SfxNum = -1;
			AW.VoiceChannels[i].theSFX.Priority = 0;
			PRINTF("sfx %d killed\n", sndplayer->idlist[i]);
		}
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
	INT16			VoiceNum, i, Channel = -1;
	ALSndPlayer		*Sndp;
	t_SndPtr		*sndptr;


	// search cheannels for voice handle
	for(i = 0; i<MAX_VOICES;i++)
	{
		if(AW.VoiceChannels[i].VoiceHandle == VoiceHandle)
		{
			Channel= i;
			break;
		}
	}

	// if can't find  sound do nothing 
	if(Channel == MAX_VOICES)
		return;

	sndplayer = &AW.SndPlayerList;
	Sndp = AW.VoiceChannels[Channel].SndPlayer;
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
	INT16			VoiceNum, i, Channel = -1;
	ALSndPlayer		*Sndp;
	t_SndPtr		*sndptr;

	sndplayer = &AW.SndPlayerList;
	for(i = 0; i<MAX_VOICES;i++)
	{
		Sndp = AW.VoiceChannels[i].SndPlayer;
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
			alSndpSetSound(Sndp, sndplayer->idlist[i]);
			if (alSndpGetState(Sndp) == AL_STOPPED)
			{
				alSndpDeallocate(Sndp, sndplayer->idlist[i]);
				AW.VoiceChannels[i].VoiceHandle = -1;
				AW.VoiceChannels[i].theSFX.SfxNum = -1;
				AW.VoiceChannels[i].theSFX.Priority = 0;
				//PRINTF("free(%d:%d)\n", sndplayer->idlist[i], i);
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


/*****************************************************************************
*
*	Function Title:  void UpdateVolume(INT32 Voicenum)
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
void UpdateVolume(INT32 Voicenum)
{

	
	INT32		dist, newvol;
	t_SndPtr	sndptr;
	t_SoundPlayer	*sndplayer;
	ALSndPlayer		*Sndp;


#if 0

	sndplayer = &AW.SndPlayerList;
	Sndp = &sndplayer->Sndp;
	sndptr = &AW.VoiceChannels[Voicenum].theSFX;
	AW.dx = abs(sndptr->CurrentX - AW.Ears.x);
	AW.dy = abs(sndptr->CurrentY - AW.Ears.y);
	AW.dz = abs(sndptr->CurrentZ - AW.Ears.z);

	dist = AW.dx;
	if(AW.dy > dist)
		dist = AW.dx;
	if(AW.dz > dist)
		dist = AW.dz;

	newvol = (INT32)(dist * AW.VolScaleFactor);
    alSndpSetVol(Sndp, newvol);

#endif

}

/*****************************************************************************
*
*	Function Title:  void UpdatePan(INT32 Voicenum)
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
void UpdatePan(INT32 Voicenum)
{
	float			rightX, rightZ,
					distance, invDistance,
					dot;
	char			pan;
	t_SndPtr		sndptr;
	t_SoundPlayer	*sndplayer;
	ALSndPlayer		*Sndp;


#if 0
	sndplayer = &AW.SndPlayerList;
	Sndp = &sndplayer->Sndp;
	sndptr = &AW.VoiceChannels[Voicenum].theSFX;
	rightX = cos(AW.Ears.YRot);
	rightZ = sin(AW.Ears.YRot);
	distance = sqrt(AW.Ears.dx*AW.Ears.dx + AW.Ears.dz*AW.Ears.dz);
	if (distance == 0)
	{
		dot = 0;
	}
	else
	{
		invDistance = 1/distance;
		dot = rightX*AW.Ears.dx*invDistance + rightZ*AW.Ears.dx*invDistance;
	}

	//pan = ((char) (dot + 1)*127)) >> 1;
    //alSndpSetPan(Sndp, pan);

#endif

}

/*****************************************************************************
*
*	Function Title:  void InitSoundObjects(void); 
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
void InitSoundGlobals(INT32 Radius)
{
	AW.VolScaleFactor = MAX_WORLD_VOL/Radius;
	AW.Ears.Radius = Radius;
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
*	Outputs:		Number of active voices still playing	
*
*****************************************************************************/
INT16 UpdateEars(t_Ears *EarLocation)
{
	AW.Ears.x = EarLocation->x;
	AW.Ears.y = EarLocation->y;
	AW.Ears.z = EarLocation->z;
	AW.Ears.YRot = EarLocation->YRot;
}