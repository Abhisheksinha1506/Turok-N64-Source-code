#ifndef __TLB_H__
#define	__TLB_H__

#ident	"IP22diags/tlb/tlb.h:  $Revision: 1.1 $"

#include "uif.h"

#define PAGESIZE	(1 << TLBHI_VPNSHIFT)

/*
 * Primitive TLB operations: get and set key/value, lookup, and invalidate.
 *	unsigned int	index;
 *	unsigned int	pid, vpn;
 *	unsigned int	key;
 *	unsigned int	value;
 * NB: tlbmatch() returns -1 if the key formed from pid and vpn isn't found.
 */

unsigned int	get_tlbhi(/* index */);
unsigned int	get_tlblo0(/* index */);
unsigned int	get_tlblo1(/* index */);
void		tlbwired(/* index, tlbpid, vaddr, pte, pte2 */);
int		probe_tlb(/* vpn, pid */);
void		invaltlb(/* index */);
void		tlbpurge(/* void */);

/*
 * Test functions.  They share a common interface consisting of the following
 * arguments (some are unused by certain tests) and a return value
 * which signals success (0) or failure (!0).
 *	unsigned int	pt[NTLBENTRIES];	// test page table
 *	unsigned int	*uncachedp;		// K1seg ptr to mapped mem
 *	unsigned int	*cachedp;		// K0seg ptr to mapped mem
 */
int	tlbglobal(/* pt */);
int	tlbmod(/* pt */);
int	tlbnocache(/* pt, uncachedp, cachedp */);
int	tlbvalid(/* pt */);
int	tlbmem(/* pt */);
int	tlbprobe(/* pt */);
int	tlbpid(/* pt */);
int	tlbtranslate(/* pt, uncachedp */);

#endif	/* __TLB_H__ */
