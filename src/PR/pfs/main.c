
#include	<ultra64.h>
#include	"thread.h"
#include        "textlib.h"
#ifdef FORMAT 
#include        "controller.h"
#endif

extern u16      *bitmap_buf;
extern u16      bitmap_buf1[];
extern u16      bitmap_buf2[];

extern u8 backup_buffer[];
extern void eep_test(void);
extern	s32 __osDumpInode(OSPfs *);
extern s32 __osDumpId(OSPfs *);

OSPfs pfs0;

#define NUM_MESSAGE 1

static int err_handlaer(int, OSPfs *);

OSMesgQueue  pifMesgQueue;
OSMesg       dummyMessage, pifMesgBuf[NUM_MESSAGE];
static OSContStatus     sdata[MAXCONTROLLERS];
static OSContPad        rdata[MAXCONTROLLERS];

extern OSMesgQueue retraceMessageQ;

#define NUM_OF_FILE 64

u16 c_code[NUM_OF_FILE]={  0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
			   0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,
			   0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
			   0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20,
			   0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
			   0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,0x10,
			   0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,
			   0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,0x20
			   };
u32 g_code[NUM_OF_FILE]={0x11111111,0x22222222,0x33333333,0x44444444,
			 0x55555555,0x66666666,0x77777777,0x8888888,
			   0x9999999,0xaaaaaaa,0xbbbbbbb,0xccccccc,0xddddddd,
			   0xeeeeeee,0xfffffff,0x1231234,
			   0x0001,0x0002,0x0003,0x0004,0x0005,0x0006,0x0007,0x0008,
			   0x0009,0x000a,0x000b,0x000c,0x000d,0x000e,0x000f,0x0010,
			   0x0111,0x0222,0x0333,0x0444,0x0555,0x0666,0x0777,0x0888,
			   0x0999,0x0aaa,0x0bbb,0x0ccc,0x0ddd,0x0eee,0x0fff,0x0234,
			   0x1001,0x1002,0x1003,0x1004,0x1005,0x1006,0x1007,0x1008,
			   0x1009,0x100a,0x100b,0x100c,0x100d,0x100e,0x100f,0x1010
			   };
char gname[NUM_OF_FILE][17]= {  
				  "Autofill        ", "Curve           ",
				  "Blockmonkey     ", "Drive           ",
				  "Bumpmap         ", "Trafic          ",
				  "Chrome          ", "Solid view      ",
				  "Ci8fb           ", "Sky Fly         ",
				  "Detail          ", "Rolo 3D         ",
				  "Ginv            ", "Snoop           ",
				  "Ground          ", "Quake           ",
				  "Gtdemo          ", "Present         ",
				  "Hostio          ", "Newton          ",
				  "Lights          ", "Insect          ",
				  "Mipmap          ", "Ideas           ",
				  "Morphcube       ", "1942            ",
				  "1943            ", "i3Dm            ",
				  "Morphfaces      ", "Fractal         ",
				  "Onetri          ", "E2              ",
				  "Overlay         ", "Go Fish         ",
				  "Playseq         ", "Worm            ",
				  "Polyline        ", "Sea Haven       ",
				  "Simple          ", "donkey kong     ",
				  "Soundmonkey     ", "Drip            ",
				  "Spin            ", "Back Trace      ",
				  "Texlight        ", "yoshi island    ",
				  "Tile Rect2D     ", "Areas           ",
				  "Tile Rect3D     ", "Bounce          ",
				  "Topgun          ", "Arena           ",
				  "Tron            ", "Dragon          ",
				  "Turbomonkey     ", "Close Up        ",
				  "Fast Track      ", "Liquid          ",
				  "Fast Shadows !  ", "Wave            ",
				  "Flight          ", "Sphere          ",
				  "Chess            ", "Magic Cube     "
				};

u8 ename[NUM_OF_FILE][5] = { "rich","karn","jon ","joan","phil","rob ","chip","vic ",
				 "bill","lynn","ann ","jeff","mike","don ","mark","Adam",
				 "bob ","jim ","jun ","kris","joan","dave ","joe ","paul",
				 "doug","eric","ron ","lili","marc","jean","roy ","joe ",
				 "jan","jack","tina","lupe","ken ","kay ","dean","rene",
				 "tien","pat ","andy","erin","donn","reg ","tim ","gary",
				 "nacy","hank","ben ","ian ","beth","kim ","elke","pam ",
				 "nora","mary","rose","flip","tony","ina ","ed  ","tom "
				 };

u8 dsize[NUM_OF_FILE] = {     16,16, 16,  16, 7, 21,  1,  8, 10,  1,  6,  3,  4, 10,  2, 8,
			         8, 79,114, 24,  8, 8,  1,  8, 42,  1, 63,  8, 54, 40,  2, 20,
			        18, 19,  4, 24,  7, 21,  1,  8, 10, 11,  1,  3,  4, 10,  2, 8,
			         4,  9,1, 1, 1, 1,  1,  16, 32,  8,  8, 8, 8, 8,  16, 124
			       };

u16 data_status[NUM_OF_FILE]={ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
				    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

void	
mainproc(void *arg)
{	
	int i;
	int j;
	int cont_no=0;
	int toggle = 1;
	s32 file_no=0;
	s32 no, last_file=0;
	u16 number;
	u32 total_size;
	int error;
	char *s;
	u32 data_no=0;
	int draw_count = 0;
	int cursor=0;
	u32 ret, eep;
	u8 p;
	u16 button;
	int bytes;
	OSPfsState state, state1;
	u8 tmp_data[BLOCKSIZE];
	char label[BLOCKSIZE]= "Memory Pack 2 ";
	int len;
	s32 free;
	s32 max_files, files_used;
#ifdef FORMAT 
	u16 index[4];
	__OSPackId *id;
  	u8 id_data[BLOCKSIZE]= {1,9,9,6,0,1,2,4,0,8,1,5,3,2,10,24,
                        'N','i','n','t','e','n','d','o',0,0,0,0,0,0,0,0};
#endif 
	
	osCreateMesgQueue(&pifMesgQueue, pifMesgBuf, NUM_MESSAGE);
	osSetEventMesg(OS_EVENT_SI, &pifMesgQueue, dummyMessage);
	init_draw();
	draw_char('n');
	osContInit(&pifMesgQueue, &p, &sdata[0]);
	eep = osEepromProbe(&pifMesgQueue);
	if (eep)
		eep_test();
	osPfsIsPlug(&pifMesgQueue, &p);
	if (p == 0){
		while(1) {
			/* no memory pack */
			eep = osEepromProbe(&pifMesgQueue);
			draw_puts("\f\n\n\n\n\n\teep:");
			draw_ushort(eep);
			draw_puts("\n");
			if (eep)
				eep_test();
		}
	}
	for (i = 0; i < MAXCONTROLLERS; i++) {
		if (p & (1<<i)){
			cont_no = i;
			break;
		}
	}
#ifdef FORMAT
	
	id = (__OSPackId *)id_data;
	id->version = 1;
	id->deviceid = 1;
	id->banks = 1;
	__osIdCheckSum((u16 *)id, &(id->checksum), &(id->inverted_checksum));

	index[0] = PFS_ID_0AREA;
        index[1] = PFS_ID_1AREA;
        index[2] = PFS_ID_2AREA;
        index[3] = PFS_ID_3AREA;

	for (i=0; i < 4; i++) {
		__osContRamWrite(&pifMesgQueue, cont_no, index[i], (u8 *)id, 1);
	}

	for(j = 0; j < BLOCKSIZE ; j++)
		tmp_data[j] = 0;
	__osContRamWrite(&pifMesgQueue, cont_no, PFS_LABEL_AREA, tmp_data, 1);
  	ret = osPfsReFormat(&pfs0, &pifMesgQueue, cont_no);
	if (ret == PFS_ERR_NOPACK)
		for (;;);
#endif /* FORMAT */

	ret = osPfsInit(&pifMesgQueue, &pfs0, cont_no);
	if ((ret == PFS_ERR_NOPACK) || (ret == PFS_ERR_ID_FATAL) || 
		(ret == PFS_ERR_DEVICE))
		for (;;);
	osPfsSetLabel(&pfs0, label);
	
	if (pfs0.status & PFS_CORRUPTED)
		draw_puts("\f\n\n\n\tfile system has been repaired\n");

#ifdef CREATE
	ret = osPfsNumFiles(&pfs0, &max_files, &files_used);
	for(no = 0 ; max_files ; no++) {
		bytes = dsize[no]*BLOCKSIZE*PFS_ONE_PAGE;
		ret = osPfsAllocateFile(&pfs0, c_code[no], g_code[no], 
			gname[no], ename[no], bytes, &file_no);
		if (ret == 0) {
			for (i = 0 ; i < (int)(dsize[no]*BLOCKSIZE*PFS_ONE_PAGE);
				i++)
				backup_buffer[i] = file_no;
			ret = osPfsReadWriteFile(&pfs0, file_no, PFS_WRITE, 0,
				bytes, backup_buffer);
			if (ret)
				err_handlaer(ret, &pfs0);
		}else  if ((ret == PFS_DIR_FULL) || (ret == PFS_DATA_FULL))
			break;
		else
			err_handlaer(ret, &pfs0);
	}
#endif /* CREATE */

	while(1) {
		osContStartReadData(&pifMesgQueue);
	    
	    	osRecvMesg(&pifMesgQueue, NULL, OS_MESG_BLOCK);
		osContGetReadData(&rdata[0]);
		button = rdata[cont_no].button;

		if (button & CONT_UP) {
	      		cursor--;
	    	}
	    	else if (button & CONT_DOWN) {
		      cursor++;
		}
	    	else if(button & CONT_LEFT) {
		      data_no--;
	    	}
	    	else if (button & CONT_RIGHT) {
	      		data_no++;
	    	} 
	    	else if (button & CONT_A) {
			ret = osPfsFindFile(&pfs0, state1.company_code, 
		state1.game_code, state1.game_name, state1.ext_name, &no);
			if (ret == 0) {
		  		error = 0;
		  		setcolor(0x20,0x90,0x90);
				ret = osPfsReadWriteFile(&pfs0, no, PFS_READ,
				0, state1.file_size, backup_buffer);
				if (ret == 0) {
		    			j = 0;
		    			while(1) {
						if( state1.game_code == g_code[j] )
							break;
		      				j++;
		    			}
		    			for(i = 0 ; i < state1.file_size; i++) {
		      			     if( backup_buffer[i] !=  j ){
							error++;
					     }
		    			}
		    			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		    			draw_puts( gname[j] );
		    			if( error == 0)
		      				draw_puts(" read success");
		    			else
		      				draw_puts(" read error");
		    			v_sync_double_buffer(&retraceMessageQ);
		    			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		    			draw_puts( gname[j] );
		    			if( error == 0)
		      				draw_puts(" read success");
		    			else
		      				draw_puts(" read error");
				}
		  		else {
					err_handlaer(ret, &pfs0);
		    			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		    			draw_puts( state1.game_name);
		    			draw_puts(" read failure");
					draw_uint(ret);
		    			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		    			draw_puts( state1.game_name);
		    			draw_puts(" read failure");
					draw_uint(ret);
		  		}	    
			} else
			err_handlaer(ret, &pfs0);
	    	}
	    	else if  (button & CONT_B) {
	      		setcolor(0x20,0x90,0x90);
			ret = osPfsFindFile(&pfs0, state1.company_code, 
		state1.game_code, state1.game_name, state1.ext_name, &no);
			if (ret == 0) {
		  		error = 0;
		  		setcolor(0x20,0x90,0x90);
				j = 0;
				while(1) {
					if( state1.game_code == g_code[j] )
						break;
					j++;
				}
		  		for(i = 0 ; i < state1.file_size ;i++)
		    			backup_buffer[i] = j;
				ret = osPfsReadWriteFile(&pfs0, no, PFS_WRITE,
				0, state1.file_size, backup_buffer);
				if (ret != 0) {
					err_handlaer(ret, &pfs0);
		    			draw_puts("\f\n\n\n\n\t");
		    			draw_puts( gname[j] );
		    			draw_puts("write file failure");
					draw_uint(ret);
				}
		  		else {
		    			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		    			draw_puts( gname[j] );
		    			draw_puts("write file success");
		    			v_sync_double_buffer(&retraceMessageQ);
		    			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		    			draw_puts( gname[j] );
		    			draw_puts("write file success");
		  		}
			} else
				err_handlaer(ret, &pfs0);
	    	}
	    else if (button & CONT_C) {
	      for(i = 0 ; i < (int)(256*dsize[data_no]) ;i++)
		backup_buffer[i] = data_no;
	ret = osPfsNumFiles(&pfs0, &max_files, &files_used);
		ret = osPfsFreeBlocks(&pfs0, &free);
		if ((osPfsNumFiles(&pfs0, &max_files, &files_used) != 0)
		 || (osPfsFreeBlocks(&pfs0, &free) != 0)) {
			err_handlaer(ret, &pfs0);
                        draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
                        draw_puts("osPfsFreeBlocks fail");
                        v_sync_double_buffer(&retraceMessageQ);
                        draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
                        draw_puts("osPfsFreeBlocks fail");
		} else if ((int)free < 256*dsize[data_no]) {
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("no free space");
			v_sync_double_buffer(&retraceMessageQ);
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("no free space");
		} else if (max_files <= files_used) {
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("directory full");
			v_sync_double_buffer(&retraceMessageQ);
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("directory full");
		} else {
		   ret = osPfsAllocateFile(&pfs0, c_code[data_no], 
			g_code[data_no], gname[data_no], ename[data_no], 
			256*dsize[data_no], &no);
		   if (ret == 0) {
			ret = osPfsReadWriteFile(&pfs0, no, PFS_WRITE,
			0, 256*dsize[data_no], backup_buffer);
			if (ret != 0) {
		  		draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  		draw_puts("write file failure");
				draw_uint(ret);
		  		v_sync_double_buffer(&retraceMessageQ);
		  		draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  		draw_puts("write file failure");
				draw_uint(ret);
			} else {
				err_handlaer(ret, &pfs0);
		  		draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  		draw_puts("create file success");
		  		v_sync_double_buffer(&retraceMessageQ);
		  		draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  		draw_puts("create file success");
			}
	    	} else {
		  if ((ret == PFS_DIR_FULL) || (ret == PFS_DATA_FULL)) {
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("file system full");
			v_sync_double_buffer(&retraceMessageQ);
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("file system full");
		   } else {
			err_handlaer(ret, &pfs0);
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("create file failure");
			v_sync_double_buffer(&retraceMessageQ);
			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
			draw_puts("create file failure");
		    }
		}
	      }
	    } else if (button & CONT_D) {
	     	setcolor(0xa0,0x20,0x80);
		ret = osPfsDeleteFile(&pfs0, state1.company_code, 
		state1.game_code, state1.game_name, state1.ext_name);
		if (ret != 0) {
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("delete file failure");
			draw_uint(ret);
		  	v_sync_double_buffer(&retraceMessageQ);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("delete file failure");
			draw_uint(ret);
		} else {
			err_handlaer(ret, &pfs0);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("delete file success");
		  	v_sync_double_buffer(&retraceMessageQ);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("delete file success");
		}
	    } else if (button & CONT_E) {
	     	setcolor(0xa0,0x20,0x80);
		ret = osPfsChecker(&pfs0);
		if (ret != 0) {
			err_handlaer(ret, &pfs0);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system failure");
			draw_uint(ret);
		  	v_sync_double_buffer(&retraceMessageQ);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system failure");
			draw_uint(ret);
		} else {
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system success");
		  	v_sync_double_buffer(&retraceMessageQ);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system success");
		}
	    } else if (button & CONT_L) {
			ret = osPfsReSizeFile(&pfs0, state1.company_code, 
			state1.game_code, state1.game_name, state1.ext_name, 
			state1.file_size-BLOCKSIZE*PFS_ONE_PAGE);
		   	if (ret != 0) {
				err_handlaer(ret, &pfs0);
				draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
				draw_puts("Truncate file failure");
				v_sync_double_buffer(&retraceMessageQ);
				draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
				draw_puts("Truncate file failure");
			    }
	    } else if (button & CONT_R) {
			ret = osPfsReSizeFile(&pfs0, state1.company_code, 
			state1.game_code, state1.game_name, state1.ext_name, 
			state1.file_size+BLOCKSIZE*PFS_ONE_PAGE);
		   	if (ret == 0) {
				j = 0;
				while(1) {
                                        if( state1.game_code == g_code[j] )
                                                break;
                                        j++;
                                }
                                for(i = 0 ; i < BLOCKSIZE*PFS_ONE_PAGE ;i++)
                                        backup_buffer[i] = j;
				ret = osPfsReadWriteFile(&pfs0, last_file, PFS_WRITE,
		state1.file_size, BLOCKSIZE*PFS_ONE_PAGE,backup_buffer);
				if (ret != 0) {
					draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
					draw_puts("write partial file failure");
					draw_uint(ret);
					v_sync_double_buffer(&retraceMessageQ);
					draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
					draw_puts("write partial file failure");
					draw_uint(ret);
				} else {
					err_handlaer(ret, &pfs0);
					draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
					draw_puts("Resize file success");
		  			v_sync_double_buffer(&retraceMessageQ);
		  			draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  			draw_puts("Resize file success");
				}
	    	    	} else {
			  if (ret == PFS_DATA_FULL) {
				draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
				draw_puts("Grow file failure");
				v_sync_double_buffer(&retraceMessageQ);
				draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
				draw_puts("Grow file failure");
			   } else {
				err_handlaer(ret, &pfs0);
				draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
				draw_puts("Grow file failure");
				v_sync_double_buffer(&retraceMessageQ);
				draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
				draw_puts("Grow file failure");
			    }
			}
	    } else if (button & CONT_F) {
	     	setcolor(0xa0,0x20,0x80);
		ret = osPfsReFormat(&pfs0, &pifMesgQueue, cont_no);
		if (ret != 0) {
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system failure");
			draw_uint(ret);
		  	v_sync_double_buffer(&retraceMessageQ);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system failure");
			draw_uint(ret);
		} else {
			err_handlaer(ret, &pfs0);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system success");
		  	v_sync_double_buffer(&retraceMessageQ);
		  	draw_puts("\f\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t");
		  	draw_puts("check file system success");
		}
	    } else if (button & CONT_START) {
	      	toggle ^= 1;
	    }
	    
	    data_no &= 0x3f;

	    draw_count= 0;
	    total_size = 0;
	    draw_puts("\f\n\n");
	    ret = osPfsGetLabel(&pfs0, tmp_data, &len);
	    if (ret != 0)
		err_handlaer(ret, &pfs0);
	    s = tmp_data;
	    draw_puts("		");
	    setcolor(0xa0,0xf0,0x80);
	    draw_puts("LABEL: ");
	    for(j = 0; j < len ; j++)
	      draw_char( *s++ );
	    draw_char(' ');
	    draw_puts("\n");
	    number=0;
	    eep = osEepromProbe(&pifMesgQueue);
	    if (eep)
		eep_test();
	    for(i = 0 ; i < NUM_OF_FILE ; i++) { 
		      ret = osPfsFileState(&pfs0, i, &state);
	      if (ret == 0) {
		  number++;
		  setcolor(0xa0,0x20,0x80);
		  draw_puts("	  ");
		  draw_ushort(number);
		  if( draw_count == cursor ) {
		    draw_puts("    * ");
		    last_file = i;
		    state1.file_size = state.file_size;
		    state1.company_code = state.company_code;
		    state1.game_code = state.game_code;
		    for (j = 0; j < PFS_FILE_NAME_LEN; j++)
			state1.game_name[j] = state.game_name[j];
		    for (j = 0; j < PFS_FILE_EXT_LEN; j++)
			state1.ext_name[j] = state.ext_name[j];
		  }
		  else
		    draw_puts("      ");
		  s = state.game_name;
		  draw_char(' ');
		  setcolor(0xf0,0xf0,0);
		  for(j = 0; j < PFS_FILE_NAME_LEN ; j++)
		      draw_char( *s++ );
		  draw_char(' ');
		  setcolor(0x80,0x60,0x80);
		  s = state.ext_name;
		  for(j = 0; j < PFS_FILE_EXT_LEN ; j++)
		      draw_char( *s++ );
		  setcolor(0x20,0x70,0xf0);
		  draw_puts("  size = ");
		  draw_uint(state.file_size);
		    
		  draw_char('\n');
		  draw_count++;
		  total_size += state.file_size;
		}  else
			err_handlaer(ret, &pfs0);
	    }
	
	    if( cursor < 0 )
	      cursor = draw_count-1;
	    else if( cursor >= draw_count )
	      cursor = 0;

	    draw_puts("\f\\n\nn\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	    setcolor(0x30,0xf0,0x20);
	    draw_puts("		");
	    draw_puts("total_size = ");
	    draw_uint( total_size );
	    draw_puts(" \n\n");
	    setcolor(0xa0,0x20,0x80);
	    draw_char('\t');
	    draw_hex(data_no);
	    draw_char(' ');
	    draw_puts( gname[data_no] ); 
	    draw_puts("size = ");
	    draw_uint( dsize[data_no]*BLOCKSIZE*PFS_ONE_PAGE);
	    v_sync_double_buffer(&retraceMessageQ);
	    clear_draw();
	  }

	  for (;;);
}

static int
err_handlaer(int error, OSPfs *pfs)
{
	switch(error) {

	case PFS_ERR_NEW_PACK:
		osPfsInit(pfs->queue, pfs, pfs->channel);
		break;

	case PFS_ERR_INCONSISTENT:
		osPfsChecker(&pfs0);
		break;

	default:
		break;
	}
	return(0);
}

