#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            int avg = round((float) (blue + green + red) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int green = 0;
    int blue = 0;
    int red = 0;
    int count = 0;
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {

            for (int m = k - 1; m < k + 2; m++)
            {
                for (int n = l - 1; n < l + 2; n++)
                {
                    if (m >= 0 && m < height && n >= 0 && n < width)
                    {
                        red += image[m][n].rgbtRed;
                        green += image[m][n].rgbtGreen;
                        blue += image[m][n].rgbtBlue;
                        count += 1;
                    }
                }
            }
            temp[k][l].rgbtRed = round((float) red / count);
            temp[k][l].rgbtGreen = round((float) green / count);
            temp[k][l].rgbtBlue = round((float) blue / count);
            green = 0;
            blue = 0;
            red = 0;
            count = 0;
        }
    }
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            image[x][y] = temp[x][y];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    int gx_red = 0;
    int gx_green = 0;
    int gx_blue = 0;
    int gy_red = 0;
    int gy_green = 0;
    int gy_blue = 0;
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {

            for (int m = k - 1; m < k + 2; m++)
            {
                for (int n = l - 1; n < l + 2; n++)
                {
                    int q = 0;
                    int r = 0;
                    if (m >= 0 && m < height && n >= 0 && n < width)
                    {
                        q = m - k + 1;
                        r = n - l + 1;

                        if (r >= 0 && r < 3 && q >= 0 && q < 3)
                        {

                            gx_red += temp[m][n].rgbtRed * gx[q][r];
                            gy_red += temp[m][n].rgbtRed * gy[q][r];

                            gx_green += temp[m][n].rgbtGreen * gx[q][r];
                            gy_green += temp[m][n].rgbtGreen * gy[q][r];

                            gx_blue += temp[m][n].rgbtBlue * gx[q][r];
                            gy_blue += temp[m][n].rgbtBlue * gy[q][r];
                        }
                    }
                }
            }
            int kernel_red = pow(gx_red, 2) + pow(gy_red, 2);
            kernel_red = round(sqrt(kernel_red));
            int kernel_green = pow(gx_green, 2) + pow(gy_green, 2);
            kernel_green = round(sqrt(kernel_green));
            int kernel_blue = pow(gx_blue, 2) + pow(gy_blue, 2);
            kernel_blue = round(sqrt(kernel_blue));

            image[k][l].rgbtRed = kernel_red > 255 ? 255 : kernel_red;
            image[k][l].rgbtGreen = kernel_green > 255 ? 255 : kernel_green;
            image[k][l].rgbtBlue = kernel_blue > 255 ? 255 : kernel_blue;

            gx_red = 0;
            gx_green = 0;
            gx_blue = 0;
            gy_red = 0;
            gy_green = 0;
            gy_blue = 0;
        }
    }
    return;
}
