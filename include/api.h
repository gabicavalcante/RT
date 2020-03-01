#pragma once

#include <memory>
#include "paramset.h"
#include "camera.h"
#include "background.h"
#include <vector>
#include <sstream>

class API
{
private:
    static API *instance;
    std::shared_ptr<Camera> camera_;
    std::shared_ptr<Background> background_;

    API();

public:
    static API *get_instance();

    void camera(ParamSet ps)
    {
        int x_res, y_res;
        string filename;

        x_res = std::stoi(ps.get_attribute("x_res"));
        y_res = std::stoi(ps.get_attribute("y_res"));
        filename = ps.get_attribute("filename");

        Camera cam(x_res, y_res, filename);
        camera_ = std::make_shared<Camera>(cam);
    }

    std::shared_ptr<Camera> get_camera()
    {
        return camera_;
    }

    void background(ParamSet ps)
    {
        std::istringstream is(ps.get_attribute("color"));
        int r, g, b;
        is >> r >> g >> b;

        Pixel color(r, g, b);
        string type = ps.get_attribute("type");

        Background bg(type, color);
        background_ = std::make_shared<Background>(bg);
        ;
    }

    std::shared_ptr<Background> get_background()
    {
        return background_;
    }
};