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
            int average =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp;
            tmp = image[i][width - (1 + j)];
            image[i][width - (1 + j)] = image[i][j];
            image[i][j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Copy the original image to avoid overwriting
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Apply box blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0, totalBlue = 0, totalGreen = 0;
            float count = 0.0;

            // Iterate through the 3x3 grid centered on (i, j)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newRow = i + di;
                    int newCol = j + dj;

                    // Check if the neighbor is within bounds
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        totalRed += copy[newRow][newCol].rgbtRed;
                        totalBlue += copy[newRow][newCol].rgbtBlue;
                        totalGreen += copy[newRow][newCol].rgbtGreen;
                        count++;
                    }
                }
            }

            // Update the pixel in the original image with the averaged values
            image[i][j].rgbtRed = round(totalRed / count);
            image[i][j].rgbtBlue = round(totalBlue / count);
            image[i][j].rgbtGreen = round(totalGreen / count);
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Copy the original image to avoid overwriting
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Apply box blur
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRedGx = 0, totalBlueGx = 0, totalGreenGx = 0;
            int totalRedGy = 0, totalBlueGy = 0, totalGreenGy = 0;

            // Iterate through the 3x3 grid centered on (i, j)
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newRow = i + di;
                    int newCol = j + dj;

                    // Check if the neighbor is within bounds
                    if (newRow >= 0 && newRow < height && newCol >= 0 && newCol < width)
                    {
                        totalRedGx += copy[newRow][newCol].rgbtRed * gx[1 + di][1 + dj];
                        totalBlueGx += copy[newRow][newCol].rgbtBlue * gx[1 + di][1 + dj];
                        totalGreenGx += copy[newRow][newCol].rgbtGreen * gx[1 + di][1 + dj];

                        totalRedGy += copy[newRow][newCol].rgbtRed * gy[1 + di][1 + dj];
                        totalBlueGy += copy[newRow][newCol].rgbtBlue * gy[1 + di][1 + dj];
                        totalGreenGy += copy[newRow][newCol].rgbtGreen * gy[1 + di][1 + dj];
                    }
                }
            }

            if (round(sqrt(pow(totalRedGx, 2) + pow(totalRedGy, 2))) > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(sqrt(pow(totalRedGx, 2) + pow(totalRedGy, 2)));
            }

            if (round(sqrt(pow(totalGreenGx, 2) + pow(totalGreenGy, 2))) > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(sqrt(pow(totalGreenGx, 2) + pow(totalGreenGy, 2)));
            }

            if (round(sqrt(pow(totalBlueGx, 2) + pow(totalBlueGy, 2))) > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(sqrt(pow(totalBlueGx, 2) + pow(totalBlueGy, 2)));
            }
        }
    }

    return;
}
