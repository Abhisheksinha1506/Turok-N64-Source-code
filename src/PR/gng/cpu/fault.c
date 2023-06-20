
#include <ultra64.h>
#include "cpu.h"



#define THREAD_HIT_BREAK	1
#define THREAD_HIT_FAULT	2
#define THREAD_HIT_TLB		4

extern OSThread *__osGetActiveQueue(void);
extern OSThread *__osRunningThread;


/*
 * Find faulted thread in the active queue
 * The exception handler sets the thread "flags" when it detects a fault.
 */
OSThread * 
FindFaultedThread( void )
{
    register OSThread * tptr = __osGetActiveQueue();

    while ( tptr->priority != -1 ) {

        /* This thread either hit a breakpoint or fault */
        if ( tptr->flags & (THREAD_HIT_BREAK|THREAD_HIT_FAULT|THREAD_HIT_TLB)) {
	/*
            XDEBUG(PRINTF( "Brk/Fault in thread %d @ %08x\r\n",
                tptr->id, tptr->context.pc));
	*/
            return(tptr);
        }
        tptr = tptr->tlnext;
    }  /* while */

    return((OSThread *)NULL);

}  /* __osFindFaultedThread */


void
RegisterNoFault(u32 *buf)
{
    __osFault.nofault = buf;
    __osFault.thread  = __osRunningThread;
}


void
ClearNoFault(void)
{
    __osFault.nofault = 0;
    __osFault.thread  = (OSThread *)NULL;
}

