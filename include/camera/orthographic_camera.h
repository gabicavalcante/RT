#pragma once

#include "camera/camera.h"

class OrthographicCamera : public Camera
{
public:
    OrthographicCamera(double l_, double r_, double b_, double t_) : Camera("orthographic")
    {
        l = l_;
        r = r_;
        b = b_;
        t = t_;
    }
};