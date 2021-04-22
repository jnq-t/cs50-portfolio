#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int main(int argc, char *argv[])
{
    //creating data type BYTE, which is unsigned 8-bit char
    typedef uint8_t BYTE;
    //creating buffer
    BYTE buffer[512];
    //opening command line argument
    FILE *f = fopen(argv[1], "r");
    FILE *img;
    //initializing jpeg count
    int counter=0;
    int i=0;
    //initializing string filename
    char *filename[8];

    //loop through buffer
    while(fread(buffer, sizeof(buffer),512, f)>0)
    {
        i++;
        //bool to find begining of files
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer [2]== 0xff && (buffer[3] & 0xf0)==0xe0)
        {
            //bool if first jpeg
            if(counter==0)
            {
                sprintf(filename, "%03i.jpg", counter);
                printf("%s is a jpeg\n", filename);
                img= fopen(filename, "w");
                fwrite(buffer, 512, 1, img);


                counter++;
            }
            //bool for begning of non-first jpeg
            else
            {
                //fclose(img);
                // sprintf(filename, "%03i.jpg", counter);
                // printf("%s is a jpeg\n", filename);
                // FILE *img= fopen(filename, "w");
                // fwrite(buffer, 1, 512, img);
                // counter++;
                break;
            }
        }
        //bool for writing body of jpeg
        else if (counter != 0)
        {
            img= fopen(filename, "a");
            fwrite(buffer, 512, 1, img);
            // printf("i is %i\n", i);
        }
    }
}
