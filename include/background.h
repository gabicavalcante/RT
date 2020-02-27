#pragma once
#include "pixel.h"
#include "vec3.h"

class Background
{
public:
    Background(){};

    vec3 sample(float r_, float g_)
    {
        float r = i;
        float g = g;
        float b = 0.2;

        vec3 col(r, g, b);
        return col;
    }
};