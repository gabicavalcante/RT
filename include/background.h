#pragma once
#include "pixel.h"

class Background
{
public:
    Pixel sample(float r_, float g_)
    {
        float r = r_;
        float g = g_;
        float b = 0.2;

        int ir = int(255.99 * r);
        int ig = int(255.99 * g);
        int ib = int(255.99 * b);

        Pixel col(ir, ig, ib);
        return col;
    }
};