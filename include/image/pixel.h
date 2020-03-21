#pragma once

#include <string>

using color_t = unsigned char;

class Pixel
{
    //private:
    //    color_t colors[3];

public:
    color_t colors[3];

    Pixel(color_t r = 255, color_t g = 255, color_t b = 255)
    {
        colors[0] = r;
        colors[1] = g;
        colors[2] = b;
    }

    int get_r() { return colors[0]; }
    int get_g() { return colors[1]; }
    int get_b() { return colors[2]; }

    friend std::ostream &operator<<(std::ostream &os, const Pixel &p)
    {
        os << "(r: " << int(p.colors[0]) << " | g: " << int(p.colors[1]) << " | b: " << int(p.colors[2]) << ")";
        return os;
    }
};