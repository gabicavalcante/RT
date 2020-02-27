#pragma once

#include "ray.h"
#include "vec3.h"
#include "pixel.h"
#include <memory>
#include <memory>

class Camera
{
public:
    Camera(int _width, int _height) : width(_width),
                                      height(_height)
    {
        film = std::shared_ptr<Pixel>(new Pixel[_width * _height]);

        lower_left_corner = vec3(-2.0, -1.0, -1.0);
        horizontal = vec3(4.0, 0.0, 0.0);
        vertical = vec3(0.0, 2.0, 0.0);
        origin = vec3(0.0, 0.0, 0.0);
    }

    ray get_ray(float u, float v)
    {
        return ray(origin,
                   lower_left_corner + u * horizontal + v * vertical - origin);
    }

    int get_width() const { return width; }
    int get_height() const { return height; }

    void add(vec3 color)
    {
        int ir = int(255.99 * color[0]);
        int ig = int(255.99 * color[1]);
        int ib = int(255.99 * color[2]);

        Pixel p(ir, ig, ib);
        //std::cout << ir << " " << ig << " " << ib << "\n";
    }

    get color()
    {
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;

    int width;
    int height;

    std::shared_ptr<Pixel> film;

    // camera borders
    double l, r, b, t;
};