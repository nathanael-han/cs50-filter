#include "helpers.h"
#include <math.h>
#include <stdio.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Finds average of rgb values
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.00);

            // Applies average value to RGB in image
            image[i][j].rgbtRed = average;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)

            // Calculates sepia filter values
        {
            int Red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int Blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            int Green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);

            // Caps value
            if (Red > 255)
            {
                Red = 255;
            }

            if (Blue > 255)
            {
                Blue = 255;
            }

            if (Green > 255)
            {
                Green = 255;
            }

            // Assigns new sepia value
            image[i][j].rgbtRed = Red;
            image[i][j].rgbtBlue = Blue;
            image[i][j].rgbtGreen = Green;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor(width / 2); j++)
        {
            // Saves left side value
            int temp_red = image[i][j].rgbtRed;
            int temp_green = image[i][j].rgbtGreen;
            int temp_blue = image[i][j].rgbtBlue;

            // Assigns left pixel to its mirror
            image[i][j].rgbtRed =  image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            // Assigns right pixel to its mirror
            image[i][width - 1 - j].rgbtRed = temp_red;
            image[i][width - 1 - j].rgbtGreen = temp_green;
            image[i][width - 1 - j].rgbtBlue = temp_blue;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Creates arrays to find boxes around a pixel
    int x[3] = { -1, 0, 1};
    int y[3] = { -1, 0, 1};

    const int SIZE = 3;   // size of x and y array

    float red = 0;
    float green = 0;
    float blue = 0;

    int num = 0; // number of boxes around a pixel

    RGBTRIPLE blurry[height][width]; // RGBTRIPLE to fill in

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int k = 0; k < SIZE; k++)
            {
                for (int l = 0; l < SIZE; l++)
                {
                    if (i + x[k] >= 0 && j + y[l] >= 0 && i + x[k] < height  && j + y[l] < width)
                    {
                        // keeps count of number of boxes around the pixel (including the pixel itself)
                        num ++;

                        // adds values
                        red += image[i + x[k]][j + y[l]].rgbtRed;
                        green += image[i + x[k]][j + y[l]].rgbtGreen;
                        blue += image[i + x[k]][j + y[l]].rgbtBlue;
                    }
                }
            }

            //In a new struct, assigns the average value of boxes around pixel
            blurry[i][j].rgbtRed =  round(red / num);
            blurry[i][j].rgbtGreen = round(green / num);
            blurry[i][j].rgbtBlue = round(blue / num);

            // resets values for next pixel
            red = 0;
            green = 0;
            blue = 0;
            num = 0;

        }

    }
    // Assigns values in "blurry" to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j].rgbtRed = blurry[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurry[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurry[i][j].rgbtBlue;

        }
    }
    return;


}

