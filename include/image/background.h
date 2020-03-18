#pragma once

#include "image/pixel.h"
#include "png/lodepng.h"
#include <iostream>

class Background
{
public:
    std::string type;
    Pixel color;
    std::vector<unsigned char> image; //the raw pixels

    Background(std::string type_, Pixel color_) : type(type_), color(color_)
    {
    }

    //Decode from disk to raw pixels with a single function call
    void decodeOneStep(const char *filename)
    {
        // std::vector<unsigned char> image;
        unsigned width, height;

        //decode
        unsigned error = lodepng::decode(image, width, height, filename);

        //if there's an error, display it
        if (error)
            std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA...
    }

    Pixel
    sample(float r_, float g_, float b_ = 0.2)
    {
        float r = r_;
        float g = g_;
        float b = b_;

        int ir = int(color.get_r() * r);
        int ig = int(color.get_g() * g);
        int ib = int(color.get_b() * b);

        Pixel col(ir, ig, ib);
        return col;
    }
};