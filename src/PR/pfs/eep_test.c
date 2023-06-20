
#include	<ultra64.h>
#include	"thread.h"
#include        "textlib.h"

extern OSMesgQueue retraceMessageQ;
extern OSMesgQueue  pifMesgQueue;


void	
eep_test(void)
{	
	s32 ret = 0;
	int i;
	u8 long_buffer[EEPROM_MAXBLOCKS * EEPROM_BLOCK_SIZE];
	int error;


	setcolor(0xa0,0xf0,0x80);
	for (i  = 0; i < EEPROM_BLOCK_SIZE * EEPROM_MAXBLOCKS; i++) {
		long_buffer[i] = i & 0xff;
	}
	ret = osEepromLongWrite(&pifMesgQueue, 0, long_buffer, EEPROM_BLOCK_SIZE * EEPROM_MAXBLOCKS);
	if (ret == 0) {
		setcolor(0xa0,0x20,0x80);
		draw_puts("\f\n\n\\n\t long write success \n");
	} else {
		setcolor(0xa0,0x20,0x80);
		draw_puts("\f\n\n\n\t long write fail: \n");
	}
	ret = osEepromLongRead(&pifMesgQueue, 0, long_buffer,EEPROM_BLOCK_SIZE * EEPROM_MAXBLOCKS);
	if (ret == 0) {
		error = 0;
		for (i = 0; i < EEPROM_BLOCK_SIZE * EEPROM_MAXBLOCKS; i++) {
			if (long_buffer[i] != (i & 0xff)) {
				error++;
			}
		}
		setcolor(0xa0,0x20,0x80);
		if (error == 0)
			draw_puts("\t long read success \n");
		else
			draw_puts("\t long read error \n");
			
	} else {
		setcolor(0xa0,0x20,0x80);
		draw_puts("\t long read fail: \n");
	}
#ifdef jean
	for(no = 0 ; no < EEPROM_MAXBLOCKS ; no++) {
		for (i = 0 ; i < EEPROM_BLOCK_SIZE; i++)
			test_buffer[i] = no;
		ret = osEepromWrite(&pifMesgQueue, no, 
				test_buffer);
		if (ret == 0) {
			setcolor(0xa0,0x20,0x80);
			draw_puts("\t\t\twrite success: ");
			draw_ushort(no);
			draw_char('\n');
		} else {
			setcolor(0xa0,0x20,0x80);
			draw_puts("\t\t\twrite fail: ");
			draw_ushort(no);
			draw_char('\n');
		}
	}
	for(no = 0 ; no < EEPROM_MAXBLOCKS ; no++) {
		int error = 0;

		ret = 0;
		ret = osEepromRead(&pifMesgQueue, no, 
				test_buffer);
		if (ret == 0) {
			error = 0;
			for (i = 0 ; i < EEPROM_BLOCK_SIZE; i++){
				if (test_buffer[i] != no) {
					error++;
				}
			}
			setcolor(0xa0,0x20,0x80);
			if (error == 0) {
				draw_puts("\t\t\t\t\t\tread success: ");
				draw_ushort(no);
				draw_char('\n');
			} else {
				draw_puts("\t\t\t\t\t\tread error: ");
				draw_ushort(no);
				draw_char('\n');
			}
		} else {
			setcolor(0xa0,0x20,0x80);
			draw_puts("\t\t\t\t\t\t\read fail: ");
			draw_ushort(no);
			draw_char('\n');
		}
	}
#endif
	draw_puts("\t\n");
}

