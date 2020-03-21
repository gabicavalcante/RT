#pragma once

#include <memory>
#include <fstream>

#include "image/pixel.h"
#include "math/vec3.h"
#include "image/ray.h"
#include "png/lodepng.h"

class Camera
{
public:
    int width;
    int height;

    std::string output_filename;
    std::vector<unsigned char> image;

    std::string type;

    vec3 v_up;
    point3 position; // look_from
    point3 target;   // look_at

    std::shared_ptr<Pixel> film;

    // camera vectors
    vec3 w_vec, u_vec, v_vec;

    // camera borders
    double l, r, b, t;

    Camera(std::string type_) : type(type_)
    {
        calculate_camera_borders();
        calc_camera_vectors();
    }

    Camera(std::string type_, double l_, double r_, double b_, double t_) : type(type_)
    {
        l = l_;
        r = r_;
        b = b_;
        t = t_;
    }

    void set_film(int width_, int height_, std::string output_filename_)
    {
        width = width_;
        height = height_;
        output_filename = output_filename_;

        film = std::shared_ptr<Pixel>(new Pixel[width * height]);

        image.resize(width * height * 4);
    }

    void set_look_at(float *look_from, float *look_at, float *up)
    {
        position = point3{look_from[0], look_from[1], look_from[2]};
        target = point3{look_at[0], look_at[1], look_at[2]};
        v_up = vec3{up[0], up[1], up[2]};
    }

    int get_width() const { return width; }
    int get_height() const { return height; }

    ray generate_ray(float i, float j)
    {
        double u = l + ((r - l) * (i + 0.5)) / width;
        double v = b + ((t - b) * (j + 0.5)) / height; 

        point3 origin = position + (u * u_vec) + (v * v_vec);
        vec3 direction = -w_vec;
        return ray(origin, direction);
    }

    void calc_camera_vectors()
    {
        vec3 gaze = target - position;

        // left-hand orientation
        w_vec = unit_vector(gaze);
        u_vec = unit_vector(cross(v_up, w_vec));
        v_vec = unit_vector(cross(w_vec, u_vec));
    }

    void calculate_camera_borders()
    {
        double min_dimention = width, max_dimention = height;
        if (height < min_dimention)
        {
            min_dimention = height;
            max_dimention = width;
        }

        l = -max_dimention / min_dimention;
        r = max_dimention / min_dimention;
        b = -1;
        t = 1;
    }

    void add(const int &x, const int &y, const Pixel &color)
    {
        if (x < width && x >= 0 && y < height && y >= 0)
            film.get()[y * width + x] = color;
    }

    void add_texture(const int &x, const int &y, Pixel &color)
    {
        if (x < width && x >= 0 && y < height && y >= 0)
        {
            image[4 * y * width + 4 * x + 0] = color.get_r();
            image[4 * y * width + 4 * x + 1] = color.get_g();
            image[4 * y * width + 4 * x + 2] = color.get_b();
            image[4 * y * width + 4 * x + 3] = 255;
        }
    }

    Pixel &get_pixel(const int &x, const int &y)
    {
        return film.get()[y * width + x];
    }

    //The image argument has width * height RGBA pixels or width * height * 4 bytes
    void encodeOneStep()
    {
        //Encode the image
        unsigned error = lodepng::encode(output_filename, image, width, height);

        //if there's an error, display it
        if (error)
            std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    }

    void write_image()
    {
        std::ofstream file(output_filename);

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