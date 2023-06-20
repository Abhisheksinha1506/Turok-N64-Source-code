/*
	Fonts: Definitions and externals.
*/

#include <PR/sp.h>

typedef struct sp_font_struct {
    char *index_string;
    Bitmap *bitmaps;
    char *img;
} Font;


void text_sprite( Sprite *, char *, Font *, int , int );

