#include <ultra64.h>
#include "gng.h"

#include <sptask.h>
#include <os_internal.h>
#include "rcp.h"

extern int     __osSpDeviceBusy(void);
extern s32     __osSpRawWriteIo(u32 devAddr, u32 data);
extern s32     __osSpRawReadIo(u32 devAddr, u32 *data);
extern char    *rspcodeSegment;
extern OSIoMesg	dmaIOMessageBuf;
extern char    _rspcodeSegmentRomStart[];
extern OSMesgQueue  dmaMessageQ;
extern OSMesg  dummyMessage;

int rsp(void)
{
  u32 data;
  u32 status=0;
  int errCount = 0;
  int noErrCount = 0;
  int i, j;
  int offset = 0;
  u32 rom_addr;
  char message[256];

  rom_addr = (u32) _rspcodeSegmentRomStart;
  for (j=0; j<392; j++) {
  
    /*
     * Start rom->rdram dma of RSP data (DMem) and
     * wait for it to finish.  First 64 bit word is
     * length in bytes of data.
     */

    osPiStartDma(&dmaIOMessageBuf, OS_MESG_PRI_NORMAL, OS_READ,
               rom_addr, rspcodeSegment, 0x1008, &dmaMessageQ);
    (void)osRecvMesg(&dmaMessageQ, &dummyMessage, OS_MESG_BLOCK);
    osWritebackDCacheAll();
    offset = *((u64 *) rspcodeSegment);
    rom_addr += offset + sizeof(u64);

    /* Load DMem */
    while(__osSpRawStartDma((u32) OS_WRITE,
			    (u32) SP_DMEM_START,
			    (u64 *) rspcodeSegment + 1,
			    (u32) offset) == -1)
	;
    while(__osSpDeviceBusy())
	;

    /*
     * Start rom->rdram dma of RSP code (IMem) and
     * wait for it to finish.
     */

    osPiStartDma(&dmaIOMessageBuf, OS_MESG_PRI_NORMAL, OS_READ,
               rom_addr, rspcodeSegment, 0x1008, &dmaMessageQ);
    (void)osRecvMesg(&dmaMessageQ, &dummyMessage, OS_MESG_BLOCK);
    osWritebackDCacheAll();
    offset = *((u64 *) rspcodeSegment);
    rom_addr += offset + sizeof(u64);

    /* Load IMem */
    while(__osSpRawStartDma((u32) OS_WRITE,
			    (u32) SP_IMEM_START,
			    (u64 *) rspcodeSegment + 1, 
			    (u32) SP_UCODE_SIZE) == -1)
	;
    while(__osSpDeviceBusy())
	;
    
    /*
     * Set PC and run
     */
    __osSpRawWriteIo(0x04080000, 0x00000000);   /* Initialize PC           */
    __osSpRawWriteIo(0x04040010, 0x00000005);   /* Clear break and halt    */
    
    status=0;
    while (!(status & 0x2)) {
      __osSpRawReadIo(0x04040010, &status);     /* Check break status      */
    }

    /* Check results in DMem */
    osWritebackDCacheAll();
    __osSpRawReadIo((0x04000f84), &data);
    if (data!=0x0000feed && data!=0xfeed0000) {
      errCount++;
	sprintf(message, "RSP diagnostic\nsub-test %d failed.\n", j);
	gng_report(message, 1, GNG_PASS_FAIL_BIT, 0);
    } else {
      noErrCount++;
    }
  }
  
  PRINTF("%d RSP tests out of 392 pass.\n", noErrCount);
  return(errCount);
}
