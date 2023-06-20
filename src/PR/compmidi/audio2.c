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
#include <assert.h>
#include <os.h>
#include "simple.h"
#include "audio.h"
//#include "/usr/turoksnd/sequences/JUNGLE.H"



extern OSSched         sc;
extern u8 _sfxbankSegmentRomStart[], _sfxbankSegmentRomEnd[];
extern u8 _sfxtableSegmentRomStart[], _sfxtableSegmentRomEnd[];
extern u8 _seqbankSegmentRomStart[],  _seqbankSegmentRomEnd[];
extern u8 _seqtableSegmentRomStart[], _seqtableSegmentRomEnd[];

extern u8 _seq1SegmentRomStart[], _seq1SegmentRomEnd[];

/**** audio globals ****/
u8							audioHeap[AUDIO_HEAP_SIZE];
int						globalsfxnum  = 0;
ALHeap					hp;
static u8				*seqPtr;
static s32				seqLen;
//ALSeqPlayer				*seqp;
ALCSPlayer				*seqp;
t_AudioWorld			AW;
//static ALSeq			*seq;
static ALCSeq			*seq;
static ALSeqMarker	seqStart;
static ALSeqMarker	seqEnd;
t_SeqInfo				SeqInfo[MAX_SEQ];
ALBankFile				*seqbankPtr;
int						SeqFlags;
int						db_channel = -1;

void SortSounds(ALInstrument	*inst);

void initAudio(void) 
{

	ALSeqpConfig			seqc;
    u32				bankLen;
    ALSynConfig		c;
    amConfig		amc;
	int				i;
    s32				numAllocated;
	ALSndId			*idPtr;
	ALSound			*newsndptr;
	ALSndPlayer		*PlayerPtr;
	t_SoundPlayer	*PlayerInfo;
	ALInstrument	*inst;
	ALWaveTable		*wavetable;
   ALADPCMWaveInfo *adpcmWave;

	InitSoundGlobals(DEFAULT_RADIUS);

    alHeapInit(&hp, audioHeap, AUDIO_HEAP_SIZE);

    // Load the bank file from ROM
    bankLen = _seqbankSegmentRomEnd - _seqbankSegmentRomStart;
    seqbankPtr = alHeapAlloc(&hp, 1, bankLen);
    romCopy(_seqbankSegmentRomStart, (char *)seqbankPtr, bankLen);
    alBnkfNew(seqbankPtr, (u8 *) _seqtableSegmentRomStart);
	 //PRINTF("instCount: %d\n", bankPtr->bankArray[0]->instCount);

	//PRINTF("soundcount: %d\n", bankPtr->bankArray[0]->instArray[0]->soundCount);
	//SortSounds(bankPtr->bankArray[0]->instArray[0]);

 	SeqInfo[0].size = _seq1SegmentRomEnd - _seq1SegmentRomStart;
	SeqInfo[0].ROMaddr = _seq1SegmentRomStart;
	SeqInfo[0].RAMaddr = alHeapAlloc(&hp, 1, SeqInfo[0].size);
	romCopy(SeqInfo[0].ROMaddr, (char *) SeqInfo[0].RAMaddr, SeqInfo[0].size);


			// Create the Audio Manager
    c.maxVVoices = MAX_VOICES;
    c.maxPVoices = MAX_VOICES;
    c.maxUpdates = MAX_UPDATES;
    c.dmaproc    = 0;                  /* audio mgr will fill this in */
    //c.fxType	 = AL_FX_BIGROOM;
	 c.fxType	 = AL_FX_NONE;
    c.outputRate = 0;                  /* audio mgr will fill this in */
    c.heap       = &hp;

    amc.outputRate = OUTPUT_RATE;
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
    //seqc.maxVoices      = MAX_VOICES;
    seqc.maxVoices      = 16;
    seqc.maxEvents      = MAX_EVENTS;
    seqc.maxChannels    = 16;
    seqc.heap           = &hp;
    seqc.initOsc        = 0;
    seqc.updateOsc      = 0;
    seqc.stopOsc        = 0;

    seqp = alHeapAlloc(&hp, 1, sizeof(ALCSPlayer));
    alCSPNew(seqp, &seqc);
    seq = alHeapAlloc(&hp, 1, sizeof(ALCSeq));

	 SetupSeq(0);

	 
    // Initialize the soundplayer
    AW.SPConfig.maxSounds = MAX_VOICES;
    AW.SPConfig.maxEvents = MAX_EVENTS;
    AW.SPConfig.heap  = &hp;
	 alSndpNew(&AW.SndPlayerList.Sndp, &AW.SPConfig);

	 	//load sounds info 
    bankLen = _sfxbankSegmentRomEnd - _sfxbankSegmentRomStart;
    AW.SndPlayerList.sfxBankPtr = alHeapAlloc(&hp, 1, bankLen);
	 romCopy(_sfxbankSegmentRomStart,  AW.SndPlayerList.sfxBankPtr, bankLen);
	 alBnkfNew((ALBankFile *) AW.SndPlayerList.sfxBankPtr, _sfxtableSegmentRomStart);
    AW.SndPlayerList.sfxBank = ((ALBankFile *) AW.SndPlayerList.sfxBankPtr)->bankArray[0];


	 AW.SFXcounter = 0;
	 AW.ChannelLock = -1;
	 AW.audio_timer = 0;

    inst =  AW.SndPlayerList.sfxBank->instArray[0];
	 idPtr = AW.SndPlayerList.idlist;
	 PlayerPtr = &AW.SndPlayerList.Sndp;
	 PlayerInfo = &AW.SndPlayerList;
	
	inst =  AW.SndPlayerList.sfxBank->instArray[0];
	//PRINTF("soundcount: %d\n", inst->soundCount);
	SortSounds(inst);

}





void SetupSeq(int seqnum)
{
	u8				*seqPtr = SeqInfo[seqnum].RAMaddr;
	//u8				*seqPtr;
	int			seqLen = SeqInfo[seqnum].size;

	//seqPtr = (u8 *)&__junglemidi;
	assert(seqPtr);

	alCSPStop(seqp);
	alCSeqNew(seq, seqPtr);
   alCSPSetSeq(seqp, seq);
   alCSPSetBank(seqp, seqbankPtr->bankArray[0]);
	alCSPPlay(seqp);


}



/*****************************************************************************
*
*	Function Title: void SortSounds(ALInstrument	*inst)
*
******************************************************************************
*
*	Description:	This is a lovely insertion sort that sorts 
*						the addresses of instruments
*
*	Inputs:			
*
*	Outputs:		
*
*****************************************************************************/
void SortSounds(ALInstrument	*inst)
{
	int				i, j;
	ALSound			*temp;





	for(i = 0; i < inst->soundCount; i++)
	{
		for(j = i+1; j < inst->soundCount; j++)
		{
			if(inst->soundArray[j] < inst->soundArray[i])
			{
				temp = inst->soundArray[i]; 
				inst->soundArray[i] = inst->soundArray[j];
				inst->soundArray[j] = temp; 
			}
		}
	}
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
INT32 initSFX(INT16	sfxnum, INT16 Priority)
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
	
	assert(AW.ChannelLock == -1);
	if(NextVoice < 0)
	{
		//TRACE1("NextVoice:%d\n", NextVoice);
		return -1;
	}

	AW.ChannelLock = NextVoice;

	// allocate sound in player
	inst =  AW.SndPlayerList.sfxBank->instArray[0];
	idPtr = AW.SndPlayerList.idlist;
	PlayerPtr = &AW.SndPlayerList.Sndp;
	PlayerInfo = &AW.SndPlayerList;

	newsndptr = inst->soundArray[sfxnum];

   assert(idPtr[NextVoice] == -1);
	idPtr[NextVoice] = alSndpAllocate(PlayerPtr, newsndptr);
	if (idPtr[NextVoice] == -1)
	{
		AW.VoiceChannels[NextVoice].VoiceHandle = -1;
		AW.ChannelLock = -1;
		//TRACE0("snd alloc error!\n");
		return -1;
	}
	else
   {
		PlayerInfo->SoundCount++;
		AW.VoiceChannels[NextVoice].VoiceHandle = idPtr[NextVoice];
	}



	sndptr = &AW.VoiceChannels[NextVoice].theSFX;

	if(sfxnum == 0)
		db_channel = NextVoice;

	sndptr->MaxVol = DEFAULT_VOLUME;
	sndptr->Vol = DEFAULT_VOLUME;
	sndptr->Pitch = DEFAULT_PITCH;
	sndptr->FXmix = DEFAULT_FXMIX;
	sndptr->Pan = DEFAULT_PAN;
	sndptr->Looped = 0;
	sndptr->Priority = Priority;
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
		//TRACE0("No voices free\n");
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
		//TRACE0("channel:-1\n");
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

	assert(sndplayer->idlist[Channel] != -1);
	alSndpSetSound(Sndp, sndplayer->idlist[Channel]);
	if (alSndpGetState(Sndp) != AL_STOPPED)
	{
		assert(FALSE);
		AW.ChannelLock = -1;
		return 0;
	}

	alSndpSetPitch(Sndp, sndptr->Pitch);
   alSndpSetFXMix(Sndp, sndptr->FXmix);
   alSndpSetPan(Sndp, sndptr->Pan);
   alSndpSetVol(Sndp, sndptr->Vol);
   alSndpPlay(Sndp);
	AW.ChannelLock = -1;

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
		//if((AW.VoiceChannels[i].theSFX.Priority >= Priority) || (AW.VoiceChannels[i].theSFX.Priority == 0))
		Priority = AW.VoiceChannels[i].theSFX.Priority;

		// if Priority = 0, then we have found a free channel stop looking
		if(Priority == 0)
			break;

	}

	if (i == MAX_VOICES)
	{
		//i = 0;
		i = -1;
		Priority = AW.VoiceChannels[i].theSFX.Priority;
	}

#if 0
	if(Priority != 0)
	{
		// there is a sound allocated, we must kill it
		assert(sndplayer->idlist[i] != -1);
		alSndpSetSound(Sndp, sndplayer->idlist[i]);
		if (alSndpGetState(Sndp) != AL_STOPPED)
		{
			alSndpStop(Sndp);
			
			while(alSndpGetState(Sndp) != AL_STOPPED)
			{
				//TRACE0("wait kill\n");
			}
			//TRACE1("voice %d killed\n", i);
		}

		alSndpDeallocate(Sndp, sndplayer->idlist[i]);
		sndplayer->idlist[i] = -1;

		AW.VoiceChannels[i].VoiceHandle = -1;
		AW.VoiceChannels[i].theSFX.SfxNum = -1;
		AW.VoiceChannels[i].theSFX.Priority = 0;
		//TRACE1("sfx %d killed\n", sndplayer->idlist[i]);
	}
#endif
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
	assert(sndplayer->idlist[Channel] != -1);
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
			assert(sndplayer->idlist[i] != -1);
			alSndpSetSound(Sndp, sndplayer->idlist[i]);
			if (alSndpGetState(Sndp) == AL_STOPPED)
			{
				alSndpDeallocate(Sndp, sndplayer->idlist[i]);
				sndplayer->idlist[i] = -1;

				AW.VoiceChannels[i].VoiceHandle = -1;
				AW.VoiceChannels[i].theSFX.SfxNum = -1;
				AW.VoiceChannels[i].theSFX.Priority = 0;

				if(i == db_channel)
					db_channel = -1;

				//TRACE2("free(%d:%d)\n", sndplayer->idlist[i], i);
			}
			else	// sound is still playing
			{
				nactive++;
			}
		}
   }

	AW.audio_timer++;

	if((AW.audio_timer%60) == 0)
	{
		if(db_channel != -1)
		{
			alSndpSetSound(Sndp, sndplayer->idlist[db_channel]);
			if (alSndpGetState(Sndp) == AL_STOPPED)
				PRINTF("state: STOPPED\n");
			else if (alSndpGetState(Sndp) == AL_STOPPING)				
				PRINTF("state: STOPPING\n");
			else if (alSndpGetState(Sndp) == AL_PLAYING)				
				PRINTF("state: PLAYING\n");
			else
				PRINTF("state: UNKOWN\n");

		}			
	}

   return nactive;

}

/*****************************************************************************
*
*	Function Title:  int SoundHandleToChannel(INT32 VoiceHandle)

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

/*****************************************************************************
*
*	Function Title:  void SetSoundVolume(INT32 VoiceHandle, float Volume)

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


/*****************************************************************************
*
*	Function Title:  void SetSoundPitch(INT32 VoiceHandle, float Pitch)
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
void SetSoundPitch(INT32 VoiceHandle, float Pitch)
{
	int				channel;
	t_SndPtr			*pSound;

	channel = SoundHandleToChannel(VoiceHandle);
	if (channel == -1)
		return;

	pSound = &AW.VoiceChannels[channel].theSFX;

	pSound->Pitch = Pitch;
}


/*****************************************************************************
*
*	Function Title:  void SetSoundPosition(INT32 VoiceHandle, float X, float Y, float Z)
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

	assert(AW.Ears.Radius != 0);
	pSound->Vol = (INT32) (pSound->MaxVol * max(0.0, AW.Ears.Radius - dist*0.7)/AW.Ears.Radius);

	pSound->Pan = ((char) ((dot + 1)*127)) >> 1;

	//pPlayer = &AW.SndPlayerList.Sndp;

	//alSndpSetSound(pPlayer, AW.SndPlayerList.idlist[channel]);

	//alSndpSetVol(pPlayer, pSound->Vol);
	//alSndpSetPan(pPlayer, pSound->Pan);
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
	SeqFlags = 0;
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
*	Outputs:		Number of active voices still playing	
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
