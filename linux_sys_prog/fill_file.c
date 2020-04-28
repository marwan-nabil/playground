/*
    This program fills a file with repititions of a
    small number (0-255) input by the user.
    
    USAGE:
            fill BLOCSIZE COUNT CONTENT FILENAME
    BLOCKSIZE   -the malloced buffer size
    COUNT       -how many times the buffer is pasted to the file
    CONTENT     -an integer between 0 and 255 to fill the file with
    FILENAME    -the name of the resulting file

    NOTE: the final file size would be BLOCKSIZE*COUNT bytes.
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *buffer, *filename;
    int  size, count, i, content;
    FILE *fd;

    if (argc != 5){
        printf("\nUsage: fill BLOCKSIZE COUNT CONTENT FILENAME\n");
        exit(1);
    }

    size  = atoi(argv[1]);
    count = atoi(argv[2]);
    content = atoi(argv[3]);
    filename = argv[4];
    
    fd = fopen(filename, "w");

    // buffer size is the blocksize provided by user
    buffer = malloc(size);
    // filling the buffer with content
    for (i=0; i<size; i++)
        buffer[i] = (unsigned char) content;

    // pasting buffer into file
    for (i=0; i<count; i++) {
	   fwrite(buffer, size, 1, fd);
    }

    close(fd);
}
