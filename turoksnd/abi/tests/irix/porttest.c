#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <miditime.h>
#include <midi.h>
#include <midiio.h>

MIport *MInewport(void);
MIconfig *MInewconfig(void);
 
main()
{
    MIport *port;
    MIconfig *c;
    MIevent e;
    
    register int i;
    int channel = 0;

    printf("Sending on MIDI channel %d\n", channel+1);
    c = MInewconfig();
    MICsetstamp(c, MIDELTASTAMP);
    
    port = MInewport();
    if (MIopen(port, "w", c) < 0) {
	perror("open");
	exit(-1);
    }

    MImakemessage(&e.mm.msgbuf, MIDI_NoteOn, channel, 0, 0);

    for (i = 48; i <= 60; i++)
    {
	MItime zero;
	MItime half;

	zero = MItimecreatemicros(0);
	half = MItimecreatemicros(500000);
	MIsetbyte1(&e.mm.msgbuf, i);
	MIsetbyte2(&e.mm.msgbuf, 0x60);
	e.dt = zero;
	e.t = MIMESSAGE;
	
	if (MIsend(port, &e, 1) < 0)
	{
	    perror("send note on");
	    exit(-1);
	}
	
	MIsetbyte1(&e.mm.msgbuf, i);
	MIsetbyte2(&e.mm.msgbuf, 0x0);
	e.dt = half;
	e.t = MIMESSAGE;
	
	if (MIsend(port, &e, 1) < 0)
	{
	    perror("send note off");
	    exit(-1);
	}
    }
    sleep(5);
}  

