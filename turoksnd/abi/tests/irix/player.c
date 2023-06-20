/*====================================================================
 * player.c
 *
 * Synopsis:
 *
 * Player for testing of driver functions
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
 *====================================================================*/

#include "player.h"
#include <math.h>
#include <stdio.h>
#include <assert.h>

extern  ALGlobals *slg;

#define MIN_TIME        0
#define MAX_TIME        10000
#define MAX_INT         0x7fffffff
#define MAX_SHORT       0x7fff

int myRandom(int min, int max);

void nullAction(MyPlayer *p, int voice);
void allocVoice(MyPlayer *p, int voice);
void freeVoice(MyPlayer *p, int voice);
void startVoice(MyPlayer *p, int voice);
void stopVoice(MyPlayer *p, int voice);
void setVol(MyPlayer *p, int voice);
void setPan(MyPlayer *p, int voice);
void setPitch(MyPlayer *p, int voice);
void setFxMix(MyPlayer *p, int voice);
void setPriority(MyPlayer *p, int voice);
void getPriority(MyPlayer *p, int voice);

ALMicroTime _voiceHandler(void *node);

int playerHeadSize(MyPlayerConfig *c)
{
    return 0;
}

void playerNew(MyPlayer *p, MyPlayerConfig *c) 
{
    int i, w;

    _ASSERT(c->numVoices <= MAX_VOICES);
    
    p->numVoices = c->numVoices;
    p->drvr = &slg->drvr;
    
    for (i = 0; i < p->numVoices; i++) {
        p->voices[i].state = START;
        p->voices[i].voice = 0;
    }
    
    /*
     * init wavetables array
     */
    p->numWaveTables = 0;
    
    /*
     * initialize the state machine
     */
    /* START state */
    i = 0; w = 0;
    p->sm[START].vector[i].action = (StateAction)allocVoice;
    p->sm[START].vector[i].next = READY;
    p->sm[START].vector[i].count = 0;
    w += p->sm[START].vector[i++].weight = 1;
    
    p->sm[START].vector[i].action = (StateAction)nullAction;
    p->sm[START].vector[i].next = START;
    p->sm[START].vector[i].count = 0;
    w += p->sm[START].vector[i++].weight = 1;

    p->sm[START].numVectors = i;
    p->sm[START].weightTotal = w;
    
    /* READY state */
    i = 0; w = 0;
    p->sm[READY].vector[i].action = (StateAction)freeVoice;
    p->sm[READY].vector[i].next = START;
    p->sm[READY].vector[i].count = 0;
    w += p->sm[READY].vector[i++].weight = 1;

    p->sm[READY].vector[i].action = (StateAction)startVoice;
    p->sm[READY].vector[i].next = PLAY;
    p->sm[READY].vector[i].count = 0;
    w += p->sm[READY].vector[i++].weight = 3;
    
    p->sm[READY].numVectors = i;
    p->sm[READY].weightTotal = w;

    /* PLAY state */
    i = 0; w = 0;
    p->sm[PLAY].vector[i].action = (StateAction)stopVoice;
    p->sm[PLAY].vector[i].next = READY;
    p->sm[PLAY].vector[i].count = 0;
    w += p->sm[PLAY].vector[i++].weight = 1;

    p->sm[PLAY].vector[i].action = (StateAction)setVol;
    p->sm[PLAY].vector[i].next = PLAY;
    p->sm[PLAY].vector[i].count = 0;
    w += p->sm[PLAY].vector[i++].weight = 2;

    p->sm[PLAY].vector[i].action = (StateAction)setPitch;
    p->sm[PLAY].vector[i].next = PLAY;
    p->sm[PLAY].vector[i].count = 0;
    w += p->sm[PLAY].vector[i++].weight = 2;

    p->sm[PLAY].vector[i].action = (StateAction) setPan;
    p->sm[PLAY].vector[i].next = PLAY;
    p->sm[PLAY].vector[i].count = 0;
    w += p->sm[PLAY].vector[i++].weight = 2;

    p->sm[PLAY].vector[i].action = (StateAction)setFxMix;
    p->sm[PLAY].vector[i].next = PLAY;
    p->sm[PLAY].vector[i].count = 0;
    w += p->sm[PLAY].vector[i++].weight = 2;

    p->sm[PLAY].vector[i].action = (StateAction) setPriority;
    p->sm[PLAY].vector[i].next = PLAY;
    p->sm[PLAY].vector[i].count = 0;
    w += p->sm[PLAY].vector[i++].weight = 2;

    p->sm[PLAY].vector[i].action = (StateAction) getPriority;
    p->sm[PLAY].vector[i].next = PLAY;
    p->sm[PLAY].vector[i].count = 0;
    w += p->sm[PLAY].vector[i++].weight = 2;

    p->sm[PLAY].numVectors = i;
    p->sm[PLAY].weightTotal = w;

    /*
     * add ourselves to the driver
     */
    p->node.next       = NULL;
    p->node.handler    = _voiceHandler;
    p->node.clientData = p;
    alSynAddPlayer(&slg->drvr, &p->node);
}

void playerDelete(MyPlayer *p) 
{
    int i;
    
    printf("START state\n");
    for (i = 0; i < p->sm[START].numVectors; i++) {
        printf("vector %d: %d times\n", i, p->sm[PLAY].vector[i].count);
    }
    
    printf("READY state\n");
    for (i = 0; i < p->sm[READY].numVectors; i++) {
        printf("vector %d: %d times\n", i, p->sm[READY].vector[i].count);
    }
    
    printf("PLAY state\n");
    for (i = 0; i < p->sm[PLAY].numVectors; i++) {
        printf("vector %d: %d times\n", i, p->sm[PLAY].vector[i].count);
    }
    
    alSynRemovePlayer(&slg->drvr, &p->node);
}

void playerSetBank(MyPlayer *p, ALBank *bank)
{
    int i, k;
    ALInstrument *inst;
    ALSound      *sound;
    
    for (i = 0; i < bank->progCount; i++) {
        inst = bank->progArray[i];
        for (k = 0; k < inst->soundCount; k++) {
            sound = inst->soundArray[k];
            p->waves[p->numWaveTables++] = sound->wavetable[0];
            if (p->numWaveTables >= MAX_WAVES)
                return;
        }    
    }
}

ALMicroTime _voiceHandler(void *node)
{
    MyPlayer *p = (MyPlayer *)node;
    int i, v, rv, w;
    State voiceState;
    
    v = myRandom(0, p->numVoices-1);        /* pick a voice, any voice */
    
    voiceState = p->voices[v].state;

    rv = myRandom(0, p->sm[voiceState].weightTotal);
    w = 0;
    for (i = 0; i < p->sm[voiceState].numVectors; i++) {
        w += p->sm[voiceState].vector[i].weight;
        if (w >= rv)
            break;
    }
        
    (*p->sm[voiceState].vector[i].action)(p, v);

    p->sm[voiceState].vector[i].count++;
    
    p->voices[v].state = p->sm[voiceState].vector[i].next;

    return myRandom(MIN_TIME, MAX_TIME);
}

int myRandom(int min, int max) 
{
    float frand, fmin, fmax;
    static long long seed = 1;

    seed = seed * 1103515245 + 12345;
    
    frand = (float)(seed & MAX_INT)/(float)MAX_INT; /* assume int = long */
    fmin = (float)min;
    fmax = (float)max;
    frand = frand * (max - min) + min;
    
    return (int)(frand + 0.5);
}

void nullAction(MyPlayer *p, int voice)
{
}

void allocVoice(MyPlayer *p, int voice)
{
    ALVoiceConfig vc;

    vc.priority = myRandom(0, AL_MAX_PRIORITY);   /* voice priority       */
    vc.fxBus = 0;                               /* bus assignment       */
    vc.type = 0;                                /* voice type           */
    
    p->voices[voice].voice = alSynAllocVoice(p->drvr, &vc);

    assert(p->voices[voice].voice);    
}

void freeVoice(MyPlayer *p, int voice)
{
    alSynFreeVoice(p->drvr, p->voices[voice].voice);
    p->voices[voice].voice = 0;
}

void startVoice(MyPlayer *p, int v)
{
    int i;
    
    if (!p->numWaveTables)
        return;
    
    i = myRandom(0, p->numWaveTables-1);

    alSynStartVoice(p->drvr, p->voices[v].voice, p->waves[i]);
}

void stopVoice(MyPlayer *p, int voice)
{
    alSynStopVoice(p->drvr, p->voices[voice].voice);
}

void setVol(MyPlayer *p, int voice)
{
    short vol = myRandom(0, MAX_SHORT);
    ALMicroTime t = myRandom(0, MAX_SHORT);
    
    alSynSetVol(p->drvr, p->voices[voice].voice, vol, t);
}

void setPitch(MyPlayer *p, int voice)
{
    float ratio = (float)myRandom(0, MAX_INT)/(float)MAX_INT;
    alSynSetPitch(p->drvr, p->voices[voice].voice, ratio);
}

void setPan(MyPlayer *p, int voice)
{
    ALPan pan = myRandom(0, 127);
    alSynSetPan(p->drvr, p->voices[voice].voice, pan);
}

void setFxMix(MyPlayer *p, int voice)
{
    char fxmix = myRandom(0, 127);
    alSynSetFXMix(p->drvr, p->voices[voice].voice, fxmix);
}

void setPriority(MyPlayer *p, int voice) 
{
    short priority = myRandom(0, AL_MAX_PRIORITY);
    alSynSetPriority(p->drvr, p->voices[voice].voice, priority);
}

void getPriority(MyPlayer *p, int voice)
{
    alSynGetPriority(p->drvr, p->voices[voice].voice);
}

