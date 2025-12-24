#include <iostream>
#include <fstream>
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

int main()
{
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

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == y)
            {
                float t = (float)(x + y) / (float)((width - 1) + (height - 1));

                unsigned char r = (unsigned char)((1 - t) * 255);
                unsigned char g = 0;
                unsigned char b = (unsigned char)(t * 255);

                int i = (y * width + x) * 3;

                // BMP = BGR
                pixels[i] = b;
                pixels[i + 1] = g;
                pixels[i + 2] = r;
            }
            else
            {
                int i = (y * width + x) * 3;
                pixels[i] = 255;
                pixels[i + 1] = 255;
                pixels[i + 2] = 255;
            }
        }
    }
    f.write((char *)pixels, imageSize);
    std::cout << "debug";
}
