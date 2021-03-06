#pragma once

#include "pixel.h"
#include <memory>
#include <fstream>

class Camera
{
public:
    int width;
    int height;
    std::string filename;
    std::string type;

    std::shared_ptr<Pixel> film;

    // camera borders
    double l, r, b, t;

    Camera(std::string type_) : type(type_) {}

    void set_file(int width_, int height_, std::string filename_)
    {
        width = width_;
        height = height_;
        filename = filename_;
        film = std::shared_ptr<Pixel>(new Pixel[width * height]);
    }

    int get_width() const { return width; }
    int get_height() const { return height; }

    void add(const int &x, const int &y, const Pixel &color)
    {
        if (x < width && x >= 0 && y < height && y >= 0)
            film.get()[y * width + x] = color;
    }

    Pixel &get_pixel(const int &x, const int &y)
    {
        return film.get()[y * width + x];
    }

    void write_image()
    {
        std::ofstream file(filename);

        file << "P3" << std::endl
             << width << " " << height << std::endl
             << "256" << std::endl;

        for (int y = height - 1; y >= 0; y--)
        {
            for (int x = 0; x < width; x++)
            {
                Pixel &p = get_pixel(x, y);
                file << (int)p.get_r() << " " << (int)p.get_g() << " " << (int)p.get_b() << " ";
            }
            file << std::endl;
        }

        file.close();
    }
};