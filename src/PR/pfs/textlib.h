#include	<ultra64.h>

#define LOW  1
#define HIGH 2
#define RESOLUTION HIGH
#define PATTERN_SIZE_X 8
#define PATTERN_SIZE_Y 16
#define SCREEN_SIZE_X 320*RESOLUTION
#define SCREEN_SIZE_Y 240*RESOLUTION
#define SCREEN_SIZE_VY 240*2*RESOLUTION
#define NUM_OF_X SCREEN_SIZE_X/PATTERN_SIZE_X
#define NUM_OF_Y SCREEN_SIZE_Y/PATTERN_SIZE_Y
#define NUM_OF_VY SCREEN_SIZE_VY/PATTERN_SIZE_Y

#define NUM_OF_CHAR 0x5f

extern void draw_char(int code);
extern void draw_uint( unsigned long num );
extern void draw_ushort( unsigned short num );
extern void draw_hex(int code);
extern void setcolor(int r,int g,int b);
extern void setbgcolor( int r, int g, int b);
extern void init_draw(void);
extern void clear_draw(void);
extern void draw_puts(char *s);
extern void v_sync_double_buffer(OSMesgQueue *queue);

