/*
	This program copies a file using 3 different implementations.
	
	USAGE: copy METHOD SOURCE DESTINATION
	METHOD  -specifies the underlying copying mechanism, 1 for using system calls directly,
			 2 for using the standard library way, 3 for using memory mapping of the files.
	SOURCE	-specifies the source file name.
	DESTINATION		-specifies the destination file name.
*/
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BSIZE 16384		// 16 kilobyte blocks

/* makes a copy using linux system calls directly */
void syscalls_copy(char *src, char* dest)
{
	int infd, outfd, count;
	char buf[BSIZE];

	// check if we can open source file
	if ((infd = open(src, O_RDONLY)) < 0) {
    	perror(src);
    	exit(1);
  	}
  	// check if we can make the destination file
  	if ((outfd = open(dest, O_WRONLY | O_CREAT, 0644)) < 0) {
    	perror(dest);
    	exit(2);
  	}

  	while ((count = read(infd, buf, BSIZE)) > 0)
    	write(outfd, buf, count);
	
	// unnecessary cleanup
  	close(infd);
  	close(outfd);
}

void stdio_copy(char *src, char* dest)
{
	// FILE is an opaque type used by stdio.h
	FILE *infile, *outfile;
    char buf[BSIZE];
    int count;

    if ((infile = fopen(src, "r")) < 0){
    	perror(src);
    	exit(2);
    }
    if ((outfile = fopen(dest, "w")) < 0){
    	perror(dest);
    	exit(2);
    }

    while ((count = fread(buf, 1, BSIZE, infile)) > 0)
        fwrite(buf, 1, count, outfile);

    fclose(infile);
    fclose(outfile);
}

void mmap_copy(char *src, char* dest)
{
	char *srcp, *dstp;
    int infd, outfd;
    size_t size;

    // open the source file and check for errors
    infd = open(src, O_RDONLY);
    if (infd < 0) {
        perror(src);
        exit(1);
    }

    // quick way to get the source file size
    size = lseek(infd, 0, SEEK_END);

    // memory map the source file
    srcp = mmap(NULL, size, PROT_READ, 	// protection mode
     					   MAP_PRIVATE,	// sharing mode
     					   infd, 0);
    if (srcp == MAP_FAILED) {
        perror("mmap");
        exit(2);
    }

    // open the destination file (or create it), truncating if necessary, and check errors
    outfd = open(dest, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outfd < 0) {
        perror(dest);
        exit(1);
    }
    if (ftruncate(outfd, size) == -1) {
        perror("ftruncate");
        exit(3);
    }

	// memory map the destination file
	dstp = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, outfd, 0);
    if (dstp == MAP_FAILED) {
        perror("mmap");
        exit(2);
    }

    // copy memory from source to destination file maps
    memcpy(dstp, srcp, size);

    // sync the output file (save to disk)
    if (msync(dstp, size, MS_SYNC) == -1) {
        perror("msync");
        exit(4);
    }

    close(infd);
  	close(outfd);
    exit(0);
}

void main(int argc, char *argv[])
{
	char *source, *destination;

	// error checking
	if (argc !=4){
		printf("\nUSAGE: copy METHOD SOURCE DESTINATION\n");
		exit(1);
	}
	
	switch(*argv[1]){
	case '1':
		printf("\ncopying file using the syscalls_copy method\n");
		syscalls_copy(argv[2], argv[3]);
		break;
	
	case '2':
	printf("\ncopying file using the stdio_copy method\n");
		stdio_copy(argv[2], argv[3]);
		break;

	case '3':
	printf("\ncopying file using the mmap_copy method\n");
		mmap_copy(argv[2], argv[3]);
		break;
	
	default:
		printf("\nMETHOD should be 1, 2 or 3.\n");
		exit(1);
		break;	
	}
}
