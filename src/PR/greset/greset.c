/*
 * Program to simulate pressing and releasing the RESET switch on the
 * Ultra 64.
 *
 */
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/u64gio.h>
#include <PR/R4300.h>

#define GIOBUS_BASE     0x1f400000
#define GIOBUS_SIZE     0x200000        /* 2 MB */

main(int argc, char *argv[]) 
{
    int mmemFd;
    unsigned char *mapbase;
    struct u64_board *pBoard;
    int sleeptime;

    if (argc != 1) {
	sleeptime = atoi(argv[1]);
	if (sleeptime == -1) {
	    sleeptime = 0;
	}
    } else {
	sleeptime = 0;
    }

    if ((mmemFd = open("/dev/mmem", 2)) < 0) {
        perror("open of /dev/mmem failed");
        return(1);
    }

    if ((mapbase = (unsigned char *)mmap(0, GIOBUS_SIZE, PROT_READ|PROT_WRITE,
      (MAP_PRIVATE), mmemFd,
      PHYS_TO_K1(GIOBUS_BASE))) == (unsigned char *)-1) {
        perror("mmap");
        return(1);
    }

    pBoard = (struct u64_board *)(mapbase);
    pBoard->reset_control = _U64_RESET_CONTROL_NMI;
    sginap(10);
    if (sleeptime)
	sleep(sleeptime);
    pBoard->reset_control = 0;
}
