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

    void camera(ParamSet ps);
    std::shared_ptr<Camera> get_camera();

    void background(ParamSet ps);
    std::shared_ptr<Background> get_background();
};

API *API::instance = 0;

API::API() {}

void API::camera(ParamSet ps)
{
    int x_res, y_res;
    std::string filename;

    x_res = std::stoi(ps.get_attribute("x_res"));
    y_res = std::stoi(ps.get_attribute("y_res"));
    filename = ps.get_attribute("filename");

    Camera cam(x_res, y_res, filename);
    API::camera_ = std::make_shared<Camera>(cam);
}

std::shared_ptr<Camera> API::get_camera()
{
    return API::camera_;
}

void API::background(ParamSet ps)
{
    std::istringstream is(ps.get_attribute("color"));
    int r, g, b;
    is >> r >> g >> b;

    Pixel color(r, g, b);
    std::string type = ps.get_attribute("type");

    Background bg(type, color);
    API::background_ = std::make_shared<Background>(bg);
}

std::shared_ptr<Background> API::get_background()
{
    return API::background_;
}

API *API::get_instance()
{
    if (instance == 0)
    {
        instance = new API();
    }

    return instance;
}