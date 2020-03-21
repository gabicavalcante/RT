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

    Background(std::string type_, Pixel color_, std::string mapping_, std::string filename) : type(type_), mapping(mapping_), color(color_)
    {
        if (mapping_ == "screen")
            decodeOneStep(filename.c_str());
    }

    //Decode from disk to raw pixels with a single function call
    void decodeOneStep(const char *filename)
    {
        std::cout << "decode image" << std::endl;
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
    sample_image(const float &x_, const float &y_)
    {
        float x = x_ * width;
        float y = y_ * height;
        // std::cout << x << ", " << y << std::endl;

        unsigned char *data = &(image[y * width + x]);
        // std::cout << int(data[0]) << int(data[1]) << int(data[2]) << std::endl;

        Pixel col(data[0], data[1], data[2]);
        return col;
    }
};