/*
 * Layout of attributes of each tests for checksums
 */

typedef struct {
	int	avoidtest;
	int	pixtype;
	int	width;
	int	height;
	int	onePrim;
} ChecksumAttrib_t;

extern unsigned long long testChecksums[];
extern ChecksumAttrib_t checksumAttrib[];
