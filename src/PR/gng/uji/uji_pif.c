#include	<ultra64.h>
#include        "uji_pif.h"
#include	"gng.h"

uchar ssndata[32];
PFS pfs0;

extern OSMesgQueue	siMessageQ;

#undef  MAXCONTROLLERS
#define MAXCONTROLLERS 5

/***** read status all channels *****/
void InitSi(OSMesgQueue *queue, SI *si){
  int i;
  for(i = 0 ; i < MAX_CHANNEL ; i++) si->command[i] = CNT_TYPE;

  FormatSiBuffer(si);
  WriteSi(queue,si);
  ReadSi(queue,si);
}

/***** send write64byte-command to PIf *****/
void WriteSi(OSMesgQueue *queue, SI *si){
  osWritebackDCache( si, sizeof(SI));
  osRecvMesg(queue, NULL, OS_MESG_NOBLOCK);
  *(BUFFER **)( PHYS_TO_K1( SI_DRAM_ADDR_REG ) ) = &(si->buffer);
  *(u32 *)PHYS_TO_K1(SI_PIF_ADDR_WR64B_REG) = PIF_RAM_START;
  osRecvMesg(queue, NULL, OS_MESG_BLOCK);
}

/***** send read64byte-command to PIf *****/
void ReadSi(OSMesgQueue *queue, SI *si){
  osRecvMesg(queue, NULL, OS_MESG_NOBLOCK);
  *(BUFFER **)( PHYS_TO_K1(SI_DRAM_ADDR_REG) ) = &(si->buffer);
  *(u32 *)PHYS_TO_K1(SI_PIF_ADDR_RD64B_REG) = PIF_RAM_START;
  osRecvMesg(queue, NULL, OS_MESG_BLOCK);
  osInvalDCache( si, sizeof(SI));
}

/***** format SerialInterfaceBuffer *****/
int FormatSiBuffer(SI *si){
  int ch,i;
  SI_PERIPHERAL *ch_ptr;
  ch_ptr = (SI_PERIPHERAL *)&(si->buffer.dummy[0]);

  for(ch = 0; ch < MAX_CHANNEL ; ch++){
      si->si_peripheral[ch] = ch_ptr;
      switch( si->command[ch] ){
	case NOP:
	  ch_ptr = SetPeripheralNop(si,ch);
	  break;
	case CNT_TYPE:
	  ch_ptr = SetReadStatus(si,ch);
	  break;
	case CNT_DATA:
	  ch_ptr = SetReadPadButton(si,ch);
	  break;
	case CNT_READ:
	  ch_ptr = SetReadPadRam(si,ch,0);
	  break;
	case CNT_WRITE:
	  ch_ptr = SetWritePadRam(si,ch,0);
	  break;
	case CNT_RESET:
	  ch_ptr = SetPeripheralReset(si,ch);
	  break;
	case EEP_READ:
	  ch_ptr = SetReadEEProm(si, ch, 0);
	  break;
	case EEP_WRITE:
	  ch_ptr = SetWriteEEProm(si, ch, 0);
	  break;
	default:
	  return(UNKNOWN_COMMAND);
      }
      if(ch_ptr == NULL) {
	*((uchar *)si->si_peripheral[ch]) = END_CODE;
	for( ; ch < 5 ; ch++) si->command[ch] = NOP;
	return(BUFFER_OVERFLOW);
      }
    }
  si->buffer.status = 1;
  return(0);
}

/***** calculate AddressCrc *****/
uchar addr_crc5(ushort addr){
  uchar temp=0,temp2;
  int i;
  for(i = 0 ; i < 16 ; i++) {
    temp2 = ((temp & 0x10)? 0x15: 0);
    temp <<= 1;
    temp |= ((addr & 0x0400)? 1:0);
    addr <<= 1;
    temp ^= temp2;
  }
  return( 0x1f & temp );
}

/***** calculate DataCrc *****/
uchar data_crc8(uchar *data){
  uchar temp=0,temp2;
  int i,j;
  for( i = 0 ; i < 33 ; i++){
      for(j = 7 ; j > -1 ; j--){
	  temp2 = ((temp & 0x80) ? 0x85: 0);
	  temp <<= 1;
	  if(i == 32) temp |= 0;
	  else temp |= ((*data & (0x01 << j))? 1:0);
	  temp ^= temp2;
      }
      data++;
  }
  return( temp );
}
	  
/***** set up WriteEEPRom-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetWriteEEProm(SI *si, int channel, uchar back_addr){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+13)) > &(si->buffer.status)) return(NULL);
  *temp++ = 10;
  *temp++ = 1;
  *temp++ = 5;
  *temp++ = back_addr;
  return( (SI_PERIPHERAL *)ret );
}

/***** set up ReadEEPRom-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetReadEEProm(SI *si, int channel, uchar back_addr){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+12)) > &(si->buffer.status)) return(NULL);
  *temp++ = 2;
  *temp++ = 8;
  *temp++ = 4;
  *temp++ = back_addr;
  return( (SI_PERIPHERAL *)ret );
}

/***** set up ReadPadRam-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetReadPadRam(SI *si, int channel, ushort back_addr){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+38)) > &(si->buffer.status)) return(NULL);
  *temp++ = 3;
  *temp++ = 33;
  *temp++ = 2;
  *temp++ = (uchar)(0xff & (back_addr >> 3));
  *temp++ = (uchar)( ((7 & back_addr) << 5) | addr_crc5(back_addr));
  return( (SI_PERIPHERAL *)ret );
}

/***** set up WritePadRam-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetWritePadRam(SI *si,int channel,ushort back_addr){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+38)) > &(si->buffer.status)) return(NULL);
  *temp++ = 35;  /* send bytes count */
  *temp++ = 1;   /* recieve bytes count */
  *temp++ = 3;
  *temp++ = (uchar)(0xff & (back_addr >> 3));
  *temp++ = (uchar)( ((7 & back_addr) << 5) | addr_crc5(back_addr));
  return( (SI_PERIPHERAL *)ret );
}

/***** set up ReadStatus-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetReadStatus(SI *si,int channel){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+6)) > &(si->buffer.status)) return(NULL);
  *temp++ = 1;
  *temp++ = 3;
  *temp++ = CNT_TYPE;
  return( (SI_PERIPHERAL *)ret );
}

/***** set up PeripheralReset-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetPeripheralReset(SI *si,int channel){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+6)) > &(si->buffer.status)) return(NULL);
  *temp++ = 1;
  *temp++ = 3;
  *temp++ = CNT_RESET;
  return( (SI_PERIPHERAL *)ret );
}

/***** set up ReadPadButton-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetReadPadButton(SI *si,int channel){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+7)) > &(si->buffer.status)) return(NULL);
  *temp++ = 1;
  *temp++ = 4;
  *temp++ = CNT_DATA;
  return( (SI_PERIPHERAL *)ret );
}

/***** set up NOP-command in SerialInterfaceBuffer *****/
SI_PERIPHERAL *SetPeripheralNop(SI *si,int channel){
  uchar *temp,*ret;
  temp = (uchar *)si->si_peripheral[channel];
  if( (ret = (temp+1)) > &(si->buffer.status)) return(NULL);
  *temp++ = 0;
  return( (SI_PERIPHERAL *)ret );
}

/********************************************************/
int GetReadPadRam(SI *si, int channel, uchar *dest_ptr){
  int i;
  if( BUS_ERR_NNCN(si,channel))  return -1;
  if( BUS_ERR_OTHRS(si,channel)) return -2;
  if( CARD_CRC(si,channel) )     return -3;
  for(i = 0 ; i < 32 ; i++) *dest_ptr++ = RAW_DATA(si,channel,5+i);
  return 0;
}

int GetReadStatus(SI *si,int channel){
  if( BUS_ERR_NNCN(si,channel))  return -1;
  if( BUS_ERR_OTHRS(si,channel)) return -2;
  if( CARD_STATUS_ERR_ADDRCRC(si,channel)) return -3;
  if( CARD_STATUS_PULL_ONCE(si,channel))   return -4;
  if( CARD_STATUS_ATTACH(si,channel))      return -5;
}

/***** set up SerialInterfaceBuffer of all-channel-reset,
  and return to OSContStatus  *****/
s32 SiContReset(OSMesgQueue *queue, OSContStatus *sdata[], SI *si){
  int channel;
  for(channel = 0; channel < MAXCONTROLLERS ; channel++)
    si->command[channel] = CNT_RESET;
  FormatSiBuffer(si);
  WriteSi(queue,si);
  ReadSi(queue,si);

  for(channel = 0 ; channel < MAXCONTROLLERS ; channel++) {
    sdata[channel]->type = ((u16)RAW_DATA(si,channel,3) << 8);
    sdata[channel]->type += (u16)RAW_DATA(si,channel,4);
    sdata[channel]->status = RAW_DATA(si,channel,5);
    sdata[channel]->errno = ( (RAW_DATA(si,channel,1)) & 0xC0 );
  }
  return(0);
}

s32 SiContStartQuery(OSMesgQueue *queue, SI *si){
  int channel;
  for(channel = 0; channel < MAXCONTROLLERS ; channel++)
    si->command[channel] = CNT_TYPE;
  FormatSiBuffer(si);
  WriteSi(queue,si);
  ReadSi(queue,si);
  return(0);
}

s32 SiContStartRamRead(OSMesgQueue *queue, OSContRamIo *ram,
		       SI *si, int channel, ushort back_addr){
  int i;
  for(i = 0; i < MAXCONTROLLERS ; i++) {
    if( i == channel ) si->command[i] = CNT_READ;
    else si->command[i] = NOP;
  }
  FormatSiBuffer(si);
  SetReadPadRam( si, channel, back_addr);
  WriteSi(queue,si);
  ReadSi(queue,si);
  return(0);
}

s32 SiContStartRamWrite(OSMesgQueue *queue, OSContRamIo *ram,
			SI *si, int channel,ushort back_addr){
  int i;
  for(i = 0; i < MAXCONTROLLERS ; i++) {
    if( i == channel ) si->command[i] = CNT_WRITE;
    else si->command[i] = NOP;
  }
  FormatSiBuffer(si);
  SetWritePadRam(si,channel,back_addr);

  for(i = 0 ; i < 32 ; i++) RAW_DATA(si,channel,i+5) =  ram->databuffer[i];
  WriteSi(queue,si);
  ReadSi(queue,si);
  return(0);
}

s32 SiContStartReadData(OSMesgQueue *queue, SI *si){
  int channel;
  for(channel = 0; channel < MAXCONTROLLERS ; channel++)
    si->command[channel] = CNT_DATA;

	/*si->command[0]=NOP;*/
		/* sasano add */

  FormatSiBuffer(si);
  WriteSi(queue,si);
  ReadSi(queue,si);
  return(0);
}

void SiContGetQuery(SI *si,OSContStatus sdata[]){
  int channel;
  for(channel = 0 ; channel < MAXCONTROLLERS ; channel++) {
    sdata[channel].type = (u16)RAW_DATA(si,channel,3) << 8;
    sdata[channel].type += (u16)RAW_DATA(si,channel,4);
    sdata[channel].status = RAW_DATA(si,channel,5);
    sdata[channel].errno = RAW_DATA(si,channel,1) & 0xC0 ;
  }
}

void SiContGetRamRead(SI *si,OSContRamIo *ramio, int channel,ushort backup_addr){
  int i;
  ramio->errno = RAW_DATA(si,channel,1) & 0xC0;
  ramio->addressCrc = RAW_DATA(si,channel,4) & 0x1f;
  for(i = 0 ; i < 32 ; i++) ramio->databuffer[i] = RAW_DATA(si,channel,i+5);
  ramio->dataCrc = RAW_DATA(si,channel,37);
}

void SiContGetRamWrite(SI *si,OSContRamIo *ramio, int channel,ushort backup_addr){
  int i;
  ramio->errno = RAW_DATA(si,channel,1) & 0xC0;
  ramio->addressCrc = RAW_DATA(si,channel,4) & 0x1f;
  ramio->dataCrc = RAW_DATA(si,channel,37);
}

void SiContGetReadData(SI *si,  OSContPad rdata[]){
  int channel;
  for(channel = 0 ; channel < MAXCONTROLLERS ; channel++) {
    rdata[channel].button = (u16)RAW_DATA(si,channel,3) << 8;
    rdata[channel].button += (u16)RAW_DATA(si,channel,4);
    rdata[channel].stick_x = RAW_DATA(si,channel,5);
    rdata[channel].stick_y = RAW_DATA(si,channel,6);
    rdata[channel].errno =  RAW_DATA(si,channel,1) & 0xC0 ;
  }
}

EEPSTAT ssneepchk(EEPSTAT eepstat){
        ssndata[0]=0x55;
        ssndata[1]=0xaa;
        ssnwriteee(&siMessageQ,&si1,0,ssndata);
        if (ssnwaitee(&siMessageQ,&si1,0,ssndata)==0){
          ssnreadee(&siMessageQ,&si1,&pfs0,0,ssndata);
          eepstat.dat[0]=ssndata[0];
          eepstat.dat[1]=ssndata[1];
/*
          sprintf(s0,"%02x %02x",eepstat.dat[0],eepstat.dat[1]);
*/

          ssndata[0]=0xaa;
          ssndata[1]=0x55;
          ssnwriteee(&siMessageQ,&si1,0,ssndata);
          if (ssnwaitee(&siMessageQ,&si1,0,ssndata)==0){
            ssnreadee(&siMessageQ,&si1,&pfs0,0,ssndata);
            eepstat.dat[2]=ssndata[0];
            eepstat.dat[3]=ssndata[1];
/*
            sprintf(s1,"%s %02x %02x",s0,eepstat.dat[2],eepstat.dat[3]);
*/

            if((eepstat.dat[0]==0x55)&&(eepstat.dat[1]==0xaa)&&(eepstat.dat[2]=0xaa)&&(eepstat.dat[3]=0x55)){
/*
              sprintf(seeprom,"%s \\c5OK",s1);
*/
							eepstat.result=EEP_OK;
						} else {
/*
							sprintf(seeprom,"%s \\c1NG",s1);
*/
							eepstat.result=EEP_NG;
						}
          } else {
/*
						sprintf(seeprom,"\\c2NG Time out#2");
*/
						eepstat.result=EEP_TIMEOUT;
					}
        } else {
/*
					sprintf(seeprom,"\\c2NG Time out#1");
*/
					eepstat.result=EEP_TIMEOUT;
				}
	return(eepstat);
}

char ssnwaitee(OSMesgQueue *queue,SI *si,int page,uchar* data){
  int i;
	char c,j;

	for(j=0;j<0xff;j++){
	  for(i = 0; i < MAXCONTROLLERS ; i++) si->command[i] = NOP;
	  si->command[4] = CNT_TYPE;

		FormatSiBuffer(si);
	  SetReadStatus(si,4);
	  WriteSi(queue,si);
		ReadSi(queue,si);
		c=RAW_DATA(si,4,5)&0x80;
		if (c == 0) return(0);
	}
	return(-1);
}

void ssnreadee(OSMesgQueue *queue,SI *si,PFS *pfs,int page,uchar* data){
  int i;

  pfs->channel = 4;
  pfs->queue = queue;
  pfs->si=si;
  InitSi(pfs->queue, pfs->si);

  for(i = 0; i < MAXCONTROLLERS ; i++) si->command[i] = NOP;
  si->command[4] = EEP_READ;

  FormatSiBuffer(si);
  SetReadEEProm(si,4,page);
  WriteSi(queue,si);
  ReadSi(queue,si);
  for(i = 0 ; i < 8 ; i++) data[i]=RAW_DATA(si,4,i+4);
}

void ssnwriteee(OSMesgQueue *queue,SI *si,int page,uchar* data){
  int i;

  for(i = 0; i < MAXCONTROLLERS ; i++) si->command[i] = NOP;
  si->command[4] = EEP_WRITE;

  FormatSiBuffer(si);
  SetWriteEEProm(si,4,page);
  for(i = 0 ; i < 8 ; i++) RAW_DATA(si,4,i+4)=data[i];

  WriteSi(queue,si);
  ReadSi(queue,si);
}

/******** [50P EXTJOY] 検査 *********/
/******** [50P EXTJOY] check*********/
/*
 * External joy controller check (writes to an eeprom mapped into joy channel 5)
 */
int
chk50PExtjoy( void ) {

    EEPSTAT state, dummy;

    /*
     * Assume everything is OK if no Zaru OR if we are running from ramrom.
     */
    if ( (!zaruexists) || (!runningFromRom) )
	return GNG_TEST_SUCCESS;

    state = ssneepchk( dummy );   /* 笹野さんのプログラムから検査結果を得る */

    if (state.result == EEP_OK) {
	return GNG_TEST_SUCCESS;
    } else {
	return GNG_TEST_FAILURE;
    }
}
