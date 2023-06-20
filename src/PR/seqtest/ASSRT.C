#define IG_DEBUG
#define TRAP_ON_ASSERT

#ifdef IG_DEBUG

#ifdef TRAP_ON_ASSERT
#define ASSERT(expr) (expr) ? ((void)0) : igAssert(TRUE, __FILE__, __LINE__)
#else
#define ASSERT(expr) (expr) ? ((void)0) : igAssert(FALSE, __FILE__, __LINE__)
#endif

#else	// !IG_DEBUG

#ifdef TRAP_ON_ASSERT
#define ASSERT(expr) (expr) ? ((void)0) : igAssert(TRUE, __FILE__, __LINE__)
#else
#define ASSERT(expr)
#endif

#endif

void igAssert(BOOL Trap, const char *szFile, int nLine)
{
#ifndef MAKE_CART
	rmonPrintf("\r\n\r\nASSERTION FAILED!  file:%s, line:%d\r\n\r\n", szFile, nLine);

	if (Trap)
		*((char*)(NULL)) = 0;
#endif
}

