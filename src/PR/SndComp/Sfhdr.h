/*****************************************************************************
*   Data Structures
*****************************************************************************/
//      WAV FORMAT
typedef struct
{
    	char 	ID[4];                 	// chunckID
	INT32 	size;              	// chunck size in bytes

}RIFFCHUNK;

typedef struct
{
    	INT16 FormatTag;            	// WAVE format code
	INT16 nChannels;          	// number of channels
	INT32 nSamplesPerSec;    	// sampling Rate
	INT32 nAvgBytesPerSec;   	// nBlockAlign * nSamplesPerSec
	INT16 nBlockAlign;        	// nChannels * nBitsPerSample / 8
	INT16 samplesize;

} WAVEHEADER;

typedef struct	s_WAV_HDR
{
   RIFFCHUNK 	ck;             // RIFF chunck structure
	char 		formID[4];      // 'W' 'A' 'V' 'E'
	RIFFCHUNK 	fmtck;        	// format chunck header structure
	WAVEHEADER 	wavhdr;      	// waveheader structure
	RIFFCHUNK 	datack;       	// data chunck header structure

} t_WAV_HDR;

////////////     AIFF FORMAT
typedef struct s_AIFF_HDR
{
    char        FORM_ID[4] ;    /* Text 'FORM' */
    INT32       FORM_Length ;   /* Length of file (bytes) */
    char        Type[4] ;       /* Text '????' IFF file type */
    char        COMM_ID[4] ;    /* Text 'COMM' */
    INT32       COMM_Length ;   /* Length of chunk (bytes) */
    INT16       numChannels;    /* number of channels */
    UINT32      NumSampleFrames;
    UINT16      sampleSize;     /* sample width in bits */
    UINT8       sampleRate[8];
    char        SSND_ID[4] ;    /* Text 'SSND' */
    INT32       SSND_Length ;   /* Length of chunk (bytes) */
    INT32       offset ;        /* offset to sound data */
    INT32       blockSize ;     /* size of alignment blocks */

} t_AIFF_HDR ;



typedef struct s_COMM_CHUNK
{
    char        COMM_ID[4] ;    /* Text 'COMM' */
    INT32       COMM_Length ;   /* Length of chunk (bytes) */
    INT16       numChannels;    /* number of channels */
    UINT32      NumSampleFrames;
    UINT16      sampleSize;     /* sample width in bits */
    UINT8       sampleRate[10];

} t_COMM_CHUNK ;