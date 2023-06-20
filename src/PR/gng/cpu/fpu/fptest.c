
#include <ultra64.h>
#include <os_internal.h>
#include <osint.h>
#include <fpu.h>
#include "cpu.h"


int
fpTest()
{
	extern int fpmem();
	extern int fpregs();
	extern int faddsubd();
	extern int faddsubs();
	extern int fmulsubd();
	extern int fmulsubs();
	extern int fmuldivd();
	extern int fmuldivs();
	extern int fdivzero();
	extern int finexact();
	extern int finvalid();
	extern int foverflow();
	extern int funderflow();
	extern int fpcmput();

	u32 stat = 0;
	u32 i = 0;
	int errcount = 0;

	struct fp_table {
		int	(*fp_func)();
		char	*fp_name;
	};
	static struct fp_table fp_diag[] = {
		{fpmem,		"general registers"},
		{fpregs,	"control registers"},
		{faddsubd,	"double precision addition/subtraction"},
		{faddsubs,	"single precision addition/subtraction"},
		{fmulsubd,	"double precision multiplication/subtraction"},
		{fmulsubs,	"single precision multiplication/subtraction"},
		{fmuldivd,	"double precision multiplication/division"},
		{fmuldivs,	"single precision multiplication/division"},
		{fdivzero,	"dividing by zero"},
		{finexact,	"inexact result"},
		{foverflow,	"overflow result"},
/*
		{finvalid,	"invalid result"},
		{funderflow,	"underflow result"},
*/
		{0,		0},
	};
	struct fp_table *fp;
	
	XDEBUG(PRINTF("Floating point unit test\n"));

	stat = 0;
	errcount = 0;
	for (i = 0, fp = fp_diag; fp->fp_name; fp++, i++) {
		if ((*fp->fp_func)()) {
			stat |= (1 << i);
			++errcount;
			PRINTF("FPU %s test FAILED, error=%d\n", fp->fp_name,
				errcount);
		}
	}
	
	if (stat != 0) {
	    PRINTF("FPU result=0x%x, %d errors\n", stat, errcount);
	}

	return errcount;
}

