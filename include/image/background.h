#pragma once

#include "image/pixel.h"
#include "png/lodepng.h"
#include <iostream>

class Background
{
public:
    std::string type, mapping;
    Pixel color;
    std::vector<unsigned char> image; //the raw pixels
    unsigned width, height;

    Background(std::string type_, Pixel color_, std::string mapping_, std::string filename) : type(type_), color(color_), mapping(mapping_)
    {
        if (mapping_ == "screen")
            decodeOneStep(filename.c_str());
    }

    //Decode from disk to raw pixels with a single function call
    void decodeOneStep(const char *filename)
    {
        unsigned error = lodepng::decode(image, width, height, filename);
        std::cout << width << ", " << height << std::endl;

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

    Pixel
    sample_image(int x, int y)
    {

        //unsigned char p[3];
        unsigned char *p = NULL;
        std::cout << x << ", " << y << std::endl;
        if (x < width && y > 0 && y < height)
        {
            p[0] = image[4 * y * width + 4 * x + 0];
            p[1] = image[4 * y * width + 4 * x + 1];
            p[2] = image[4 * y * width + 4 * x + 2];
            Pixel col(p[0], p[1], p[2]);
            return col;
        }

        Pixel col(255, 255, 255);
        return col;
    }
};