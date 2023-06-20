#define         NBUFFERS        10

#define MAX_UPDATES             80
#define MAX_EVENTS              20
#define AUDIO_HEAP_SIZE         64000

#define MAX_VOICES              8

#define NUM_SMPL_PER_FRAME      1280
#define DMA_BUFFER_LENGTH       0x600  /* Larger buffers result in fewer DMA' but more  */
                                       /* memory being used.  */


#define NUM_ACMD_LISTS          2      /* two lists used by this example                */
#define MAX_RSP_CMDS            1024   /* max number of commands in any command list.   */
                                       /* Mainly dependent on sequences used            */

#define NUM_DMA_BUFFERS         8      /* max number of dma buffers needed.             */
                                       /* Mainly dependent on sequences and sfx's       */

#define NUM_DMA_MESSAGES        8      /* The maximum number of DMAs any one frame can  */
                                       /* have.                                         */

#define FRAME_LAG               2      /* The number of frames to keep a dma buffer.    */
                                       /* Increasing this number causes buffers to not  */
                                       /* be deleted as quickly. This results in fewer  */
                                       /* DMA's but you need more buffers.              */

typedef struct 
{
    ALLink      node;
    int         startAddr;
    u32         lastFrame;
    char        *ptr;
} DMABuffer;

typedef struct 
{
    u8          initialized;
    DMABuffer   *firstUsed;
    DMABuffer   *firstFree;

} DMAState;

extern u8 _subwaySegmentRomStart[], _subwaySegmentRomEnd[];
extern u8 _seq1SegmentRomStart[], _seq1SegmentRomEnd[];
extern u8 _seq2SegmentRomStart[], _seq2SegmentRomEnd[];
extern u8 _seq3SegmentRomStart[], _seq3SegmentRomEnd[];
extern u8 _bankSegmentRomStart[], _bankSegmentRomEnd[];
extern u8 _tableSegmentRomStart[], _tableSegmentRomEnd[];

