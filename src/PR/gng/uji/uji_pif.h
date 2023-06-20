#define NOP        -1
#define END_CODE 0xFE

#define CNT_TYPE   0x00
#define CNT_DATA   0x01
#define CNT_READ   0x02
#define CNT_WRITE  0x03
#define CNT_RESET  0xff
#define EEP_READ   0x04
#define EEP_WRITE  0x05
#define UNKNOWN_COMMAND -1
#define BUFFER_OVERFLOW -2
#define BUFFER_SIZE 63
#define ON 1
#define OFF 0

#define NSN_CODE 0xFF

#define MAX_CHANNEL 5
#define CONTROLL_PORT 0

typedef unsigned char uchar;
typedef signed char schar;
typedef unsigned int  uint;
typedef unsigned short ushort;
typedef unsigned long ulong;

typedef union {
  uchar data[BUFFER_SIZE+1];
  uint mm[(BUFFER_SIZE+1)/4];
} SI_PERIPHERAL;

typedef struct {
  uchar dummy[BUFFER_SIZE];
  uchar status;
} BUFFER;

typedef struct {
  BUFFER buffer;
  SI_PERIPHERAL *si_peripheral[MAX_CHANNEL];
  int  command[MAX_CHANNEL];
} SI;

typedef struct {
  SI *si;
  OSMesgQueue *queue;
  int channel;
} PFS;

/**** when use this with WriteSi(), PIf format buffer ****/
#define FORMATBIT_ON(si) ((si)->buffer.status |= 1)
#define RAW_DATA(si,channel,num) ((si)->si_peripheral[(channel)]->data[(num)])

/**** use    NonProcessFlag       ON/OFF(write only)
      use    JoyBusResetFlag      ON/OFF(write only) ****/
#define BUS_NONPROC_ON(si,channel)   (RAW_DATA((si),(channel),0) |= 0x80) 
#define BUS_NONPROC_OFF(si,channel)   (RAW_DATA((si),(channel),0) &= 0x7f) 
#define BUS_RESET_ON(si,channel)     (RAW_DATA((si),(channel),0) |= 0x40)
#define BUS_RESET_OFF(si,channel)     (RAW_DATA((si),(channel),0) &= 0xbf)

/**** return JoyBusNonconnectError      (read only)
      return JoyBusOtherError           (read only) ****/
#define BUS_ERR_NNCN(si,channel)  (RAW_DATA((si),(channel),1) & 0x80)
#define BUS_ERR_OTHRS(si,channel) (RAW_DATA((si),(channel),1) & 0x40)
#define BUS_ERR_ALL(si,channel)   (RAW_DATA((si),(channel),1) & 0xC0)

/**** follow's macros return PadData (read only) ****/
#define PAD_A(si,channel)     (RAW_DATA((si),(channel),3) & 0x80)
#define PAD_B(si,channel)     (RAW_DATA((si),(channel),3) & 0x40)
#define PAD_G(si,channel)     (RAW_DATA((si),(channel),3) & 0x20)
#define PAD_START(si,channel) (RAW_DATA((si),(channel),3) & 0x10)
#define PAD_UP(si,channel)    (RAW_DATA((si),(channel),3) & 0x08)
#define PAD_DOWN(si,channel)  (RAW_DATA((si),(channel),3) & 0x04)
#define PAD_LEFT(si,channel)  (RAW_DATA((si),(channel),3) & 0x02)
#define PAD_RIGHT(si,channel) (RAW_DATA((si),(channel),3) & 0x01)
#define PAD_JSRST(si,channel) (RAW_DATA((si),(channel),4) & 0x80)
#define PAD_L(si,channel)     (RAW_DATA((si),(channel),4) & 0x20)
#define PAD_R(si,channel)     (RAW_DATA((si),(channel),4) & 0x10)
#define PAD_E(si,channel)     (RAW_DATA((si),(channel),4) & 0x08)
#define PAD_D(si,channel)     (RAW_DATA((si),(channel),4) & 0x04)
#define PAD_C(si,channel)     (RAW_DATA((si),(channel),4) & 0x02)
#define PAD_F(si,channel)     (RAW_DATA((si),(channel),4) & 0x01)
#define PAD_X(si,channel)     (RAW_DATA((si),(channel),5))
#define PAD_Y(si,channel)     (RAW_DATA((si),(channel),6))

/**** follow's macros return backup-ram-card status (read only) ****/
#define CARD_STATUS_ERR_ADDRCRC(si,channel)  (RAW_DATA((si),(channel),5) & 0x04)
#define CARD_STATUS_PULL_ONCE(si,channel)    (RAW_DATA((si),(channel),5) & 0x02)
#define CARD_STATUS_ATTACH(si,channel)       (RAW_DATA((si),(channel),5) & 0x01)
#define CARD_STATUS_ALL(si,channel)          RAW_DATA((si),(channel),5)

/**** next macro for checking data-crc ****/
#define CARD_CRC(si,channel)                 (data_crc8(&RAW_DATA((si),(channel),5)) \
					      == RAW_DATA((si),(channel),37) ) 

/**** follow's set up SerialInterfaceBuffer ****/
extern void InitSi(OSMesgQueue *, SI *);
extern int FormatSiBuffer(SI *);
extern void WriteSi(OSMesgQueue *, SI *);
extern void ReadSi(OSMesgQueue *, SI *);

extern SI_PERIPHERAL *SetWritePadRam(SI *si,int channel,ushort back_addr);
extern SI_PERIPHERAL *SetReadPadRam(SI *si, int channel, ushort back_addr);
extern SI_PERIPHERAL *SetReadStatus(SI *si,int channel);
extern SI_PERIPHERAL *SetPeripheralReset(SI *si,int channel);
extern SI_PERIPHERAL *SetReadPadButton(SI *si,int channel);
extern SI_PERIPHERAL *SetPeripheralNop(SI *si,int channel);
extern SI_PERIPHERAL *SetWriteEEProm(SI *si, int channel, uchar back_addr);
extern SI_PERIPHERAL *SetReadEEProm(SI *si, int channel, uchar back_addr);

/**** When use BackupRam, you need follow's routines ****/
extern uchar data_crc8(uchar *data);
extern uchar addr_crc5(ushort addr);


extern s32 SiContReset(OSMesgQueue *, OSContStatus *sdata[], SI *);
extern s32 SiContStartQuery(OSMesgQueue *, SI *);
extern s32 SiContStartRamRead(OSMesgQueue *queue, OSContRamIo *ram,
			      SI *si, int channel, ushort backup_addr);
extern s32 SiContStartRamWrite(OSMesgQueue *queue, OSContRamIo *ram, 
			      SI *si, int channel, ushort backup_addr);
extern s32 SiContStartReadData(OSMesgQueue *queue, SI *si);

extern void SiContGetQuery(SI *si,OSContStatus sdata[]);
extern void SiContGetReadData(SI *si,OSContPad rdata[]);
extern void SiContGetRamRead(SI *si,OSContRamIo *ramio, int channel,ushort backup_addr);
extern void SiContGetRamWrite(SI *si,OSContRamIo *ramio, int channel,ushort backup_addr);

/*
 * Declarations & typedefs for eeprom (joy controller 5) tests
 */
typedef struct {
	char result;
	char dat[4];
} EEPSTAT;

/*
 * Definitions for EEPSTAT.result
 */
#define EEP_OK		0x00
#define EEP_NG		0xff
#define EEP_TIMEOUT	0x80

EEPSTAT ssneepchk(EEPSTAT);
void ssnreadee(OSMesgQueue *queue,SI *si,PFS *pfs,int page,uchar* data);
char ssnwaitee(OSMesgQueue *queue,SI *si,int page,uchar* data);
void ssnwriteee(OSMesgQueue *queue,SI *si,int page,uchar* data);
extern SI si1,si2;
