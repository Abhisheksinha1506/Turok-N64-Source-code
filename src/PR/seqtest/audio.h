#define cos(n)					cosf(n)
#define sin(n)					sinf(n)
#define sqrt(n)					sqrtf(n)
#define max(a, b)				MAX(a, b)
#define min(a, b)				MIN(a, b)
#define PRIORITY_AUDIO			12
#define PRIORITY_AUDIOLOCK		13
#define MAX_VOICES              16
#define MIN_WORLD_VOL			0
#define MAX_WORLD_VOL			32000
#define MAX_PAN_LEFT				0
#define MAX_PAN_RIGHT			127
#define	PAN_CENTER				64
#define TICKS_PER_MEASURE		1920 

#define DEBUG_TRACE				1
#define MAX_UPDATES             64
#define MAX_EVENTS              64
#define AUDIO_HEAP_SIZE         400000
#define EXTRA_SAMPLES           80
#define NUM_OUTPUT_BUFFERS      3      /* Need three of these */
#define OUTPUT_RATE             22050
#define QUIT_MSG                10

#define DMA_BUFFER_LENGTH       0x800  /* Larger buffers result in fewer DMA' but more  */
                                       /* memory being used.  */


#define NUM_ACMD_LISTS          2      /* two lists used by this example                */
#define MAX_RSP_CMDS            4096   /* max number of commands in any command list.   */
                                       /* Mainly dependent on sequences used            */

#define NUM_DMA_BUFFERS         64     /* max number of dma buffers needed.             */
                                       /* Mainly dependent on sequences and sfx's       */

#define NUM_DMA_MESSAGES        64     /* The maximum number of DMAs any one frame can  */
                                       /* have.                                         */

#define FRAME_LAG               1      /* The number of frames to keep a dma buffer.    */
                                       /* Increasing this number causes buffers to not  */
                                       /* be deleted as quickly. This results in fewer  */
                                       /* DMA's but you need more buffers.              */


#define	DEFAULT_PRIORITY		128
#define	DEFAULT_PITCH			1
#define	DEFAULT_FXMIX			0
#define	DEFAULT_PAN				64
#define	DEFAULT_VOLUME			32000
#define	DEFAULT_RADIUS			10
#define  AUDIO_STACKSIZE			0x2000
#define  MAX_SEQ_LENGTH			20000
#define  EVT_COUNT				64
#define  MAX_PITCH				1
#define	MAX_SEQ					10
#define  FADE_SEQ_UP				(1 << 0)
#define  FADE_SEQ_DOWN			(1 << 1)


typedef signed char		INT8 ;
typedef signed short	INT16 ;
typedef signed long		INT32 ;
typedef unsigned char	UINT8 ;
typedef unsigned short	UINT16 ;
typedef unsigned long	UINT32 ;


typedef struct
{
    u32       outputRate;
    u32       framesPerField;
    u32       maxACMDSize;
} amConfig;



typedef struct
{
	void			*ROMaddr;
	void			*RAMaddr;
	INT32			size;

} t_SeqInfo;



typedef struct
{
	ALBank			*sfxBank;
	u8					*sfxBankPtr;
	ALSndPlayer		Sndp;					// first sound player
	ALSndPlayer		*NextPlayer;			// pointer to any additional players allocated
	ALSndId			idlist[MAX_VOICES];		// id list of sounds allocated to this player
	INT16			SoundCount;				// sound count number of sounds allocated to this player
} t_SoundPlayer;

typedef struct
{
	INT32			Vol;
	INT32			MaxVol;
	INT16			FXmix;
	float			Pitch;
	INT16			Pan;
	INT8			Looped;
	INT8			Priority;
	INT16			SfxNum;

} t_SndPtr;


typedef struct
{
	INT32			VoiceHandle;	// VoiceHandle
	t_SndPtr		theSFX;			// the SFX
	ALSndPlayer		*SndPlayer;

} t_Channel;


typedef struct
{
	float	x;
	float	y;
	float	z;
	float	YRot;
	float	Radius;

} t_Ears;


typedef struct
{

	ALSynConfig		SynthConfig;		// info on how synth is configured
	ALSndpConfig	SPConfig;			// info on how sound player is configured
	ALGlobals		GlobalAudio;		// audio environment globals

	t_SoundPlayer	SndPlayerList;		// list of sound players
	INT16				NumPlayers;			// number of current players allocated
	INT32				SFXcounter;					// handle counter
	t_Channel		VoiceChannels[MAX_VOICES];	// audio channels

	INT16				ChannelLock;
	t_Ears			Ears;
	float				VolScaleFactor;
	float				PanScaleFactor;

} t_AudioWorld;

void	UpdateEars(t_Ears *EarLocation);
void	InitSoundGlobals(INT32 Radius);
INT16	playSFX(INT32 VoiceHandle);
INT32	initSFX(INT16	sfxnum);
INT16	GetNextVoice(void);
void	killSFX(INT32 VoiceHandle);
void	FreeVoice(ALSndPlayer *Sndp, ALSndId voiceID, INT16 Channel) ;
INT16	UpdateWorldSound(void);
void	amCreateAudioMgr(ALSynConfig *c, OSPri priority, amConfig *amc);
int		SoundHandleToChannel(INT32 VoiceHandle);
void	SetSoundPosition(INT32 VoiceHandle, float X, float Y, float Z);
void	SetSoundVolume(INT32 VoiceHandle, float Volume);
void	SetSoundPitch(INT32 VoiceHandle, float Pitch);
void	DoSound(int nSound, float X, float Y, float Z, float Volume, float Pitch);
void	SetupSeq(int seqnum);

extern u64        audYieldBuf[];
extern int		globalsfxnum;
