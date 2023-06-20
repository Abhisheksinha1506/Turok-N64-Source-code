// mattable.h

#ifndef _INC_MATTABLE
#define _INC_MATTABLE


#include "defs.h"
#include "lists.h"


/////////////////////////////////////////////////////////////////////////////
// Structures
/////////////////////////////////////////////////////////////////////////////

typedef struct CAnimationMtxs_t
{
	INT16		m_MtxsFree ;		// Current matrices free for allocation
	Mtx		*m_pmFreeMtx ;		// Ptr to current free matrix
	INT32		m_MtxsRequested ;	// Matrices requested last frame
} CAnimationMtxs ;


/////////////////////////////////////////////////////////////////////////////
// Function prototypes
/////////////////////////////////////////////////////////////////////////////

void CAnimationMtxs__Construct(void) ;
void CAnimationMtxs__Update(void) ;
Mtx *CAnimationMtxs__RequestMtxTable(INT32 Size) ;


/////////////////////////////////////////////////////////////////////////////

#endif // _INC_MATTABLE