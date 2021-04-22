#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average;
    for(int i=0; i<height; i++)
    {
            for (int j=0; j<width; j++)
            {
                //printf("pixel of %i height and %i width is %d %d %d\n",i, j, image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
                average= (image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen)/3;
                image[i][j].rgbtBlue=average;
                image[i][j].rgbtRed=average;
                image[i][j].rgbtGreen=average;

            }

    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
     for(int i=0; i<height; i++)
    {
            for (int j=0; j<(width-1)/2; j++)
            {
                temp.rgbtBlue=image[i][j].rgbtBlue;
                temp.rgbtRed=image[i][j].rgbtRed;
                temp.rgbtGreen=image[i][j].rgbtGreen;
                image[i][j].rgbtBlue=image[i][width-j-1].rgbtBlue;
                image[i][j].rgbtRed=image[i][width-j-1].rgbtRed;
                image[i][j].rgbtGreen=image[i][width-j-1].rgbtGreen;
                image[i][width-j-1].rgbtBlue=temp.rgbtBlue;
                image[i][width-j-1].rgbtRed=temp.rgbtRed;
                image[i][width-j-1].rgbtGreen=temp.rgbtGreen;
            }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempArray[height][width];
    long tempBlue;
    long tempRed;
    long tempGreen;
    for(int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            tempBlue = image[i][j].rgbtBlue;
            tempRed=image[i][j].rgbtRed;
            tempGreen=image[i][j].rgbtGreen; ;
            int counter=1;
            // printf("int temp blue is %d\n", image[i][j].rgbtBlue);
            // printf("int temp red is %d\n", image[i][j].rgbtRed);
            // printf("int temp green is %d\n", image[i][j].rgbtGreen);
            if (i>0)
            {
                tempBlue+= image[i-1][j].rgbtBlue;
                tempRed+=image[i-1][j].rgbtRed;
                tempGreen+=image[i-1][j].rgbtGreen;
                counter +=1;
            }
            if (j>0)
            {
                tempBlue+=image[i][j-1].rgbtBlue;
                tempRed+=image[i][j-1].rgbtRed;
                tempGreen+=image[i][j-1].rgbtGreen;
                counter +=1;
            }
            if (i<height-1)
            {
                tempBlue+=image[i+1][j].rgbtBlue;
                tempRed+=image[i+1][j].rgbtRed;
                tempGreen+=image[i+1][j].rgbtGreen;
                counter +=1;
            }
            if (j<width-1)
            {
                tempBlue+= image[i][j+1].rgbtBlue;
                tempRed+=image[i][j+1].rgbtRed;
                tempGreen+=image[i][j+1].rgbtGreen;
                counter +=1;
            }
            if (i>0 && j>0)
            {
                tempBlue+= image[i-1][j-1].rgbtBlue;
                tempRed+=image[i-1][j-1].rgbtRed;
                tempGreen+=image[i-1][j-1].rgbtGreen;
                counter +=1;
            }
            if (i>0 && j<width-1)
            {
                tempBlue+= image[i-1][j+1].rgbtBlue;
                tempRed+=image[i-1][j+1].rgbtRed;
                tempGreen+=image[i-1][j+1].rgbtGreen;
                counter +=1;
            }
            if (i<height-1 && j>0)
            {
                tempBlue+= image[i+1][j-1].rgbtBlue;
                tempRed+=image[i+1][j-1].rgbtRed;
                tempGreen+=image[i+1][j-1].rgbtGreen;
                counter +=1;
            }
            if (i<height-1 && j<width-1)
            {
                tempBlue+= image[i+1][j+1].rgbtBlue;
                tempRed+=image[i+1][j+1].rgbtRed;
                tempGreen+=image[i+1][j+1].rgbtGreen;
                counter +=1;
            }
            //change
            tempArray[i][j].rgbtBlue= round(tempBlue/counter);
            tempArray[i][j].rgbtRed= round(tempRed/counter);
            tempArray[i][j].rgbtGreen= round(tempGreen/counter);
        }
    }
    for(int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            image[i][j]=tempArray[i][j];
        }
    }
    return;
}

//Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //X kernel
    int Gx[3][3];
        Gx[0][0]=-1;
        Gx[0][1]=0;
        Gx[0][2]=1;
        Gx[1][0]=-2;
        Gx[1][1]=0;
        Gx[1][2]=2;
        Gx[2][0]=-1;
        Gx[2][1]=0;
        Gx[2][2]=1;
    // Y kernel
    int Gy[3][3];
        Gy[0][0]=-1;
        Gy[0][1]=-2;
        Gy[0][2]=-1;
        Gy[1][0]=0;
        Gy[1][1]=0;
        Gy[1][2]=0;
        Gy[2][0]=1;
        Gy[2][1]=2;
        Gy[2][2]=1;

    //output array
    RGBTRIPLE array[height][width];
    // for (int i=0; i<height-1; i++)
    // {
    //     for(int j=0; j<width-1; j++)
    //     {
    //         array[i][j].rgbtBlue=image[i][j].rgbtBlue;
    //         array[i][j].rgbtRed=image[i][j].rgbtRed;
    //         array[i][j].rgbtGreen=image[i][j].rgbtGreen;
    //     }
    // }

    for(int i=0; i<height-1; i++)
    {
        for (int j=0; j<width-1; j++)
        {
            float GxSumBlue=0;
            float GySumBlue=0;
            float GxSumRed=0;
            float GySumRed=0;
            float GxSumGreen=0;
            float GySumGreen=0;

            int index=0;
            for (int x=i-1;x<=i+1; x++)
            {
                int j_index=0;
                for (int y=j-1; y<=j+1; y++)
                {
                    if(x<0 || y<0 || i>height-1 || j>width-1)
                    {
                        j_index++;
                    }
                    else
                    {
                        //printf("indeces are %i %i\n", index, j_index);
                        GxSumBlue+=(Gx[index][j_index]*image[x][y].rgbtBlue);
                        GySumBlue+=(Gy[index][j_index]*image[x][y].rgbtBlue);
                        GxSumRed+=(Gx[index][j_index]*image[x][y].rgbtRed);
                        GySumRed+=(Gy[index][j_index]*image[x][y].rgbtRed);
                        GxSumGreen+=(Gx[index][j_index]*image[x][y].rgbtGreen);
                        GySumGreen+=(Gy[index][j_index]*image[x][y].rgbtGreen);

                        j_index++;
                    }

                }
                index++;
            }
            //blue
            float imagetemp= pow(GxSumBlue,2)+pow(GySumBlue,2);
            imagetemp= sqrt(imagetemp);
            imagetemp= round(imagetemp);
            if(imagetemp>255)
            {
                imagetemp=255;
            }
            array[i][j].rgbtBlue=imagetemp;
            //red
            imagetemp= pow(GxSumRed,2)+pow(GySumRed,2);
            imagetemp= sqrt(imagetemp);
            imagetemp= round(imagetemp);
            if(imagetemp>255)
            {
                imagetemp=255;
            }
            array[i][j].rgbtRed=imagetemp;
            //green
            imagetemp= pow(GxSumGreen,2)+pow(GySumGreen,2);
            imagetemp= sqrt(imagetemp);
            imagetemp= round(imagetemp);
            if(imagetemp>255)
            {
                imagetemp=255;
            }
            array[i][j].rgbtGreen=imagetemp;
            }
        }
    for (int i=0; i<height-1; i++)
    {
        for(int j=0; j<width-1; j++)
        {
            image[i][j].rgbtBlue=array[i][j].rgbtBlue;
            image[i][j].rgbtRed=array[i][j].rgbtRed;
            image[i][j].rgbtGreen=array[i][j].rgbtGreen;
        }

    }
    return;
}
