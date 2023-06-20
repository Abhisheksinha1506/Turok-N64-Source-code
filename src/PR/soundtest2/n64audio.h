#ifndef	__N64AUDIO_H
#define	__N64AUDIO_H

// *********Audio defines******** 
#define DEBUG_TRACE			1
#define	DEFAULT_PRIORITY	128
#define	DEFAULT_PITCH		1
#define	DEFAULT_FXMIX		0 
#define	DEFAULT_PAN			64 
#define	DEFAULT_VOLUME		32000 
#define SFX_NUM				4
#define SFX_DELAY			1000 
#define ACTIVE_SOUNDS		1
#define MAX_PITCH			1
#define MAX_INT				0x7fffffff
#define MAX_TRIES			20
#define MAX_VOICES			32
#define MAX_SOUNDS			32
#define MAX_UPDATES			64
#define DMA_QUEUE_SIZE		50
#define EVT_COUNT			32
#define EXTRA_SAMPLES		80
#define OUTPUT_RATE			44100
#define NUM_FIELDS			1
#define MAX_AUDIO_LENGTH	2048
#define MAX_CLIST_SIZE		4096
#define MAX_BUFFER_LENGTH	1024
#define FX_BUFFER_SIZE		8192
#define AUDIO_HEAP_SIZE		307200
#define NBUFFERS			4
#define VOICE_SIZE			4168

#if DEBUG_TRACE
#define TRACE(x) rmonPrintf x
#else
#define TRACE(x)
#endif

typedef signed char		INT8 ;
typedef signed short	INT16 ;
typedef signed long		INT32 ;
typedef unsigned char	UINT8 ;
typedef unsigned short	UINT16 ;
typedef unsigned long	UINT32 ;


// *********Audio Structures********
typedef struct 
{
    u32         addr;
    u32         len;
    u32         size;
    u8        *ptr;
} DMABuffer;

typedef struct 
{
    u32         nBuffers;
    u32         currentBuffer;
    DMABuffer   buffers[NBUFFERS];
} DMAState;


typedef struct 
{
	ALSndPlayer	Sndp;			// first sound player 
	ALSndPlayer	*NextPlayer;	// pointer to any additional players allocated
	ALSndId		idlist[MAX_SOUNDS];	// id list of sounds allocated to this player
	INT16		SoundCount;			// sound count number of sounds allocated to this player
} t_SoundPlayer;

typedef struct 
{
	INT32			CurrentX;	
	INT32			CurrentY;	
	INT32			CurrentZ;	
	INT32			Vol;
	INT16			FXmix;
	float			Pitch;
	INT16			Pan;
	INT8			Looped;
	INT8			Priority;
	INT16			SndState;
	INT16			SfxNum;

} t_SndPtr;


typedef struct 
{
	INT32		VoiceHandle;	// VoiceHandle
	t_SndPtr	theSFX;			// the SFX
	ALSndPlayer	*SndPlayer;

} t_Channel;
 
typedef struct 
{

	ALSynConfig		SynthConfig;		// info on how synth is configured
	ALSndpConfig	SPConfig;			// info on how sound player is configured
	ALGlobals		GlobalAudio;		// audio environment globals

	t_SoundPlayer	SndPlayerList;		// list of sound players
	INT16			NumPlayers;			// number of current players allocated
	INT32			SFXcounter;					// handle counter
	t_Channel		VoiceChannels[MAX_VOICES];	// audio channels
	
	ALHeap			hp;	
	u8				audioHeap[AUDIO_HEAP_SIZE];
	s32				nextAudioDMA;
	s32				curAudioBuf;
	Acmd			*cmdlp;
	OSTask			*tlistp;
	OSMesgQueue		AudioDmaMessageQ; 



} t_AudioWorld;	

//*********Function Prototypes********
static s32 nActiveSounds(ALSndPlayer *sndp, ALInstrument  *inst, ALSndId *id);
s32 dmaCallBack(s32 addr, s32 len, void *state);
ALDMAproc dmaNew(DMAState **state);
void InitAudioSystem(void);
void updateAudio(void);
INT32 InitSFX(INT16	sfxnum);
INT16 playSFX(INT32 VoiceHandle);
INT16 GetNextVoice(void);
INT16 GetSFXinfo(INT16 VoiceHandle, t_SndPtr *infoptr);
INT16 SetSFXinfo(INT16 VoiceHandle, t_SndPtr *infoptr);

//*********External Variable Delarations***********
extern Acmd				*cmdList[];
extern s16				audioSamples[];
extern s16				*audioBuffer[];
extern ALHeap			hp;
extern s32				audioframeSize, minFrameSize, samplesLeft; 
extern f32				fsize;
extern ALBank			*sfxBank;
extern ALInstrument		*inst; 
extern OSTask			*tlistp;
extern t_AudioWorld		AW;
extern INT8				audio_yield_buffer[];
extern u64				*audio_yield_buffer_ptr; 
 
#endif	// __N64AUDIO_H

