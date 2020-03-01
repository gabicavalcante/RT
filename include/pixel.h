#pragma once

#include <string>

using color_t = unsigned char;

class Pixel
{
private:
    color_t colors[3];

public:
    Pixel(color_t r = 0, color_t g = 0, color_t b = 0)
    {
        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
    }

    int get_r() { return colors[0]; }
    int get_g() { return colors[1]; }
    int get_b() { return colors[2]; }
};