#include <stdio.h>                            /* Standard IO routines */

int main(void) {
    FILE *data_ptr;
    int count;
  
    /* Print the header */
    printf("Content-type: text/plain\n\n");
    
    /* Open the data file if you can't say so and exit with errlevel 1 */
    if (!(data_ptr=fopen("tcount.dat","r"))) {
        printf("Error opening tcount.dat for reading!\n");
        printf("Error 001: Exiting.\n");
        return 1;
    } else {                                /* Obviously the datafile
                                               opened fine so read it. */
        fscanf(data_ptr,"%i\n",&count);
        printf("%i\n",++count);             /* print the counter and */ 
        fclose(data_ptr);                   /* increment */
  
        /* Open the same file for writing, if you can't say so and exit with 
           errorlevel 2. */
        if (!(data_ptr=fopen("tcount.dat","w"))) {        
            printf("Error opening tcount.dat for writing!\n");
            printf("Error 002: Exiting.\n");
            return 2;
        } else                              /* You got write access */
            fprintf(data_ptr,"%i\n",count); /* write the new access count
                                               to the datafile */
    }
    return 0;
} 
