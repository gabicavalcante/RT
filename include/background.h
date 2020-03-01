#pragma once

#include "pixel.h"

class Background
{
public:
    string type;
    Pixel color;

    Background(string type_, Pixel color_) : type(type_), color(color_)
    {
    }

    Pixel
    sample(float r_, float g_, float b_ = 0.2)
    {
        float r = r_;
        float g = g_;
        float b = b_;

        //255.99
        int ir = int(color.get_r() * r);
        int ig = int(color.get_g() * g);
        int ib = int(color.get_b() * b);

        Pixel col(ir, ig, ib);
        return col;
    }
};