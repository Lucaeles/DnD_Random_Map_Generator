#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// for (int y = 0; y < height; y++)
// {
//     for (int x = 0; x < width; x++)
//     {
//         int i = (y * width + x) * 3;

//         if (y==x)
//         {
//             pixels[i]     = 0;
//             pixels[i + 1] = 0;
//             pixels[i + 2] = 255;
//         }
//         else
//         {
//             pixels[i]     = 255;
//             pixels[i + 1] = 255;
//             pixels[i + 2] = 255;
//         }
//     }
// }
const int width = 300;
const int height = 300;
const int imageSize = width * height * 3;
const int juma = 100;
int map[height][width];
int newMap[height][width];
int countNeighbors(int y, int x)
{
    int count = 0;

    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            if (dx == 0 && dy == 0)
                continue;

            int ny = y + dy;
            int nx = x + dx;

            if (ny < 0 || nx < 0 || ny >= height || nx >= width)
                count++;
            else
                count += map[ny][nx];
        }
    }
    return count;
}

int main()
{
    srand(time(nullptr));
    //     int r=rand();
    int r2 = 50 + rand() % 20; // 40–59% land

    std::ofstream f("a.bmp", std::ios::binary);

    // BMP header (54 bytes)
    unsigned char header[54] = {
        'B', 'M',               // Signature
        0x36, 0x1E, 0x04, 0x00, // File size
        0, 0, 0, 0,             // Reserved
        54, 0, 0, 0,            // Pixel data offset
        40, 0, 0, 0,            // DIB header size
        0x2C, 0x01, 0x00, 0x00, // Width
        0x2C, 0x01, 0x00, 0x00, // Height
        1, 0,                   // Planes
        24, 0,                  // Bits per pixel
        0, 0, 0, 0,             // Compression
        0x00, 0x1E, 0x04, 0x00, // Image size
        0, 0, 0, 0,             // X ppm
        0, 0, 0, 0,             // Y ppm
        0, 0, 0, 0,             // Colors
        0, 0, 0, 0};

    f.write((char *)header, 54);

    unsigned char pixels[imageSize];

    // for (int y = 0; y < height; y++)
    // {
    //     for (int x = 0; x < width; x++)
    //     {
    //         if (x == y)
    //         {
    //             float t = (float)(x + y) / (float)((width - 1) + (height - 1));

    //             unsigned char r = (unsigned char)((1 - t) * 255);
    //             unsigned char g = 0;
    //             unsigned char b = (unsigned char)(t * 255);

    //             int i = (y * width + x) * 3;

    //             // BMP = BGR
    //             pixels[i] = b;
    //             pixels[i + 1] = g;
    //             pixels[i + 2] = r;
    //         }
    //         else
    //         {
    //             int i = (y * width + x) * 3;
    //             pixels[i] = 255;
    //             pixels[i + 1] = 255;
    //             pixels[i + 2] = 255;
    //         }
    //     }
    // }
    srand(42); // fixed seed (or time(0))

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            map[y][x] = (rand() % 100 < r2) ? 1 : 0;
        }
    }

    for (int iter = 0; iter < 5; iter++)
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                int neighbors = countNeighbors(y, x);

                if (neighbors >= 5)
                    newMap[y][x] = 1;
                else
                    newMap[y][x] = 0;
            }
        }
        for (int y = 0; y < height; y++)
            for (int x = 0; x < width; x++)
                map[y][x] = newMap[y][x];
    }

    float cx = width / 2.0f;
    float cy = height / 2.0f;
    float maxDist = sqrt(cx * cx + cy * cy);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float dx = x - cx;
            float dy = y - cy;

            float dist = sqrt(dx * dx + dy * dy);
            float t = dist / maxDist;

            float islandSize = 0.6f + (rand() % 30) / 100.0f; 

            if (t > islandSize)
                map[y][x] = 0;
        }
    }

for (int iter = 0; iter < 2; iter++)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int neighbors = countNeighbors(y, x);

            if (neighbors >= 5)
                newMap[y][x] = 1;
            else
                newMap[y][x] = 0;
        }
    }

    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
            map[y][x] = newMap[y][x];
}


    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int i = (y * width + x) * 3;

            if (map[y][x] == 1)
            {
                pixels[i] = 0;
                pixels[i + 1] = 255;
                pixels[i + 2] = 0;
            }
            else
            {
                pixels[i] = 255;
                pixels[i + 1] = 0;
                pixels[i + 2] = 0;
            }
        }
    }

    f.write((char *)pixels, imageSize);
    std::cout << "debug";
}
