
#include "textlib.h"

extern u16      *bitmap_buf;
extern u16      bitmap_buf1[];
extern u16      bitmap_buf2[];

unsigned int x_pos=0;
unsigned int y_pos=0;
unsigned int scroll_top=0;
unsigned int scroll_x=0;
unsigned int scroll_y=0;
extern u8 patterns[NUM_OF_CHAR][PATTERN_SIZE_Y];
u16 color;
u16 bg_color=0;

void v_sync_double_buffer(OSMesgQueue *queue)
{
  static int toggle=0;

  osWritebackDCache(bitmap_buf, sizeof(u16) * SCREEN_SIZE_X * SCREEN_SIZE_Y);

  if (MQ_IS_FULL(queue))
    (void)osRecvMesg(queue, NULL, OS_MESG_BLOCK);
  (void)osRecvMesg(queue, NULL, OS_MESG_BLOCK);


  osViSwapBuffer( bitmap_buf );

  toggle ^= 1;
  if( toggle == 1 )
    bitmap_buf = bitmap_buf2;
  else
    bitmap_buf = bitmap_buf1;
}

void setcolor( int r, int g, int b)
{
  color = GPACK_RGBA5551(r,g,b,1);
}

void setbgcolor( int r, int g, int b)
{
  bg_color = GPACK_RGBA5551(r,g,b,1);
}

void init_draw(void)
{
  int mode=RESOLUTION;
  int i;
  u16 *r;
  bitmap_buf = bitmap_buf1;
  if(mode == LOW)
    osViSetMode(&osViModeTable[OS_VI_NTSC_LPF1]);
  else
    osViSetMode(&osViModeTable[OS_VI_NTSC_HPF1]);
  osViSwapBuffer( bitmap_buf );

  r = bitmap_buf1;
  for (i = 0; i < SCREEN_SIZE_X * SCREEN_SIZE_Y; i ++)
    *r++  = bg_color;
  r = bitmap_buf2;
  for (i = 0; i < SCREEN_SIZE_X * SCREEN_SIZE_Y; i ++)
    *r++  = bg_color;
}

void clear_draw(void)
{
  int i;
  u16 *r;
  r = bitmap_buf;
  for (i = 0; i < SCREEN_SIZE_X * SCREEN_SIZE_Y; i ++)
    *r++  = bg_color;
}

void draw_char( int in_code )
{
  int i,j;
  int code;
  switch( in_code )
    {
    case '\n':
      x_pos = 0;
      if( ++y_pos >= NUM_OF_Y )
	{
	  y_pos=0;
	}
      break;
    case '\r':
      x_pos = 0;
      break;
    case '\t':
                   x_pos += 8;
      if( x_pos  >= NUM_OF_X )
	{
	  x_pos = 0;
	  if( ++y_pos >= NUM_OF_Y )
	    {
	      y_pos=0;
	    }
	}
      break;
    case '\f':
      y_pos = 0;
      x_pos = 0;
      break;
    default:
      if( 0 > ( code = in_code - 0x20 ))
	code = 0x1f;
      else if( 0x5f < code)
	code = 0x1f;

      for(i = 0 ; i < PATTERN_SIZE_Y ; i++)
	for(j = 0 ; j < PATTERN_SIZE_X ; j++)
	  bitmap_buf[ (y_pos * PATTERN_SIZE_Y + i) * SCREEN_SIZE_X +
		     (x_pos * PATTERN_SIZE_X + j) ]
		       = ( ((patterns[code][i]>>(7-j)) & 0x01)? color:bg_color);
      if( ++x_pos >= NUM_OF_X )
	{
	  x_pos = 0;
	  if( ++y_pos >= NUM_OF_Y )
	    {
	      y_pos=0;
	    }
	}
      break;
    }
}  



void draw_uint( unsigned long num )
{
  int i;
  for(i = 0 ; i < 4; i++)
    draw_hex( num >> (8 * (3 - i)) );
}

void draw_ushort( unsigned short num )
{
  int i;
  for(i = 0 ; i < 2; i++)
    draw_hex( num >> (8 * (1 - i)) );
}

          
void draw_hex( int num )
{
  int lo,hi;
  lo = num & 0x0f;
  hi = (num >> 4) & 0x0f;
  if(hi >= 10)
    draw_char('a' + hi -10);
  else
    draw_char('0' + hi);
  if(lo >= 10)
    draw_char('a' + lo -10);
  else
    draw_char('0' + lo);
}


void draw_puts(char *s)
{
  while( *s )
    draw_char( *s++ );
}
