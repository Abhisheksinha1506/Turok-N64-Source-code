#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#define	BUFSIZE	1024*256/sizeof(unsigned short)

unsigned short	buf[BUFSIZE];

main()
{
    int			fid;
    unsigned long	i;
    unsigned short	*bufp=buf;

    fid = open("NumberSequence", O_RDWR | O_CREAT | O_TRUNC, 0664); 
    if (fid == -1) {
	fprintf(stderr, "can't open pidata.raw\n");
	exit(EXIT_FAILURE);
    }

    for (i=0; i<BUFSIZE; i++)
	*bufp++ = i & 0xffff;

    write(fid, buf, BUFSIZE*sizeof(unsigned short));
    close(fid);
    exit(EXIT_SUCCESS);
}
