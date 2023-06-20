
/* For tex[].fmt: */
#define	RGBA		0
#define	YUV		1
#define	CI 		2
#define	IA		3
#define	I		4
#define	A		5
#define	MASK		6

#define C               0
#define RAW             1
#define MIPMAP          2

#define COLOR           0
#define INTENSITY       1

struct texture {
	char	name[70];		/* Name of the array		*/
	int	index;			/* Texture index		*/
	int	width;			/* X dimention			*/
	int	height;			/* Y dimention			*/
	int	fmt;			/* RGBA, IA, I, etc.		*/
	int	siz;			/* Number of bits		*/
};

#define FLIP_FLAG 		(0x001)
#define PAD_FLAG 		(0x002)
#define XTRA_FLAG 		(0x004)
#define QUAD_FLAG 		(0x008)
#define SHUF_FLAG 		(0x010)
#define MM_SUPPLIED_FLAG 	(0x020)
#define SKIP_RAW_FLAG 		(0x040)
#define MM_HI_LEVEL 		(0x080)
#define HALF_SHIFT 		(0x100)

int readtex (char *fn, struct texture *tex, int fmt, int siz, int makestatic,
	int lr, int lg, int lb, int hr, int hg, int hb, int output, int flags,
	int shuffle_mask);

char *fmtstr (int fmt);
char *cmbstr (int fmt);
char *sizstr (int siz);
