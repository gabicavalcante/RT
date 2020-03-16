#pragma once

#include <memory>
#include <fstream>

#include "image/pixel.h"
#include "math/vec3.h"
#include "image/ray.h"

class Camera
{
public:
    int width;
    int height;
    std::string filename;
    std::string type;

    vec3 v_up;
    point3 position;
    point3 target;

    std::shared_ptr<Pixel> film;

    // camera vectors
    vec3 w_vec, u_vec, v_vec;

    // camera borders
    double l, r, b, t;

    Camera(std::string type_) : type(type_)
    {
        calc_camera_vectors();
    }

    void set_film(int width_, int height_, std::string filename_)
    {
        width = width_;
        height = height_;
        filename = filename_;
        film = std::shared_ptr<Pixel>(new Pixel[width * height]);
    }

    int get_width() const { return width; }
    int get_height() const { return height; }

    ray generate_ray(float i, float j)
    {
        double u = l + ((r - l) * (i + 0.5)) / width;
        double v = b + ((t - b) * (j + 0.5)) / height;

        std::cout << u << ", " << v << std::endl;

        point3 origin = position + (u * u_vec) + (v * v_vec);
        vec3 direction = -w_vec;
        return ray(origin, direction);
    }

    void calc_camera_vectors()
    {
        vec3 gaze = target - position;

        w_vec = unit_vector(-gaze);
        u_vec = unit_vector(cross(v_up, w_vec));
        v_vec = unit_vector(cross(w_vec, u_vec));
    }

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