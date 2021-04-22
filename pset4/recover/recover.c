#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int main(int argc, char *argv[])
{
    //prompt user if more than one command-line argument is given
    if (argc != 2)
    {
        printf("Usage...\n");
        return 1;
    }
    //create unsigned int structure 
    typedef uint8_t BYTE;
    //create array of BYTES
    BYTE buffer[512];
    //pointer to source file
    FILE *ptr= fopen(argv[1], "r");
    //allocate memory for filenames
    char *filename=malloc(8);
    //counter for number of jpegs
    int counter=0;
    //stream for destination files starts here
    FILE *img;
    //loop through entire card
    while (fread(buffer,512, 1, ptr)>0)
    {
        //boolean statement to fine start of jpegs
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer [2]== 0xff && (buffer[3] & 0xf0)==0xe0)
        {
            //boolean statement for first jpeg
            if(counter==0)
            {
                //prints name of file to each destination file
                sprintf(filename, "%03i.jpg", counter);
                //opens file for writing, then writes to file, initializes count
                img=fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                counter++;
            }
            else //boolean statement for start of non-first jpegs
            {
                
                fclose(img);
                sprintf(filename, "%03i.jpg", counter);
                fopen(filename, "w");
                fwrite(buffer, 512, 1, img);
                counter++;
            }
        }
        else if (counter !=0)//boolean statement for body of jpegs
        {
            fwrite(buffer, 512, 1, img);
        }
       
    }
    //free malloc memory
    free (filename);
}