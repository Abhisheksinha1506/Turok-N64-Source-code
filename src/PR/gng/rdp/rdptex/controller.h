extern OSMesgQueue	controllerMsgQ;
extern OSMesg		controllerMsgBuf;

extern OSContStatus     statusdata[MAXCONTROLLERS];
extern OSContPad        controllerdata[MAXCONTROLLERS];

extern int initControllers(void);
extern void readController(int);

extern int	controlFrame;
