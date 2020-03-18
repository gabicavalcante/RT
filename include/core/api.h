#pragma once

#include <memory>
#include <vector>
#include <sstream>

#include "core/paramset.h"
#include "camera/camera.h"
#include "camera/orthographic_camera.h"
#include "image/background.h"

class API
{
private:
    static API *instance;
    static std::shared_ptr<Camera> camera_;
    static std::shared_ptr<Background> background_;

    API();

public:
    static API *get_instance();

    static void camera(ParamSet ps);
    static std::shared_ptr<Camera> get_camera();

    static void film(ParamSet ps);

    static void background(ParamSet ps);
    static std::shared_ptr<Background> get_background();
};

API *API::instance = 0;
std::shared_ptr<Camera> API::camera_ = 0;
std::shared_ptr<Background> API::background_ = 0;

API::API() {}

API *API::get_instance()
{
    if (instance == 0)
    {
        instance = new API();
    }
    return instance;
}

void API::camera(ParamSet ps)
{
    std::string type, screen_window;

    type = ps.get_attribute("type");

    if (type == "orthographic")
    {
        std::istringstream is(ps.get_attribute("screen_window"));
        int l, r, b, t;
        is >> l >> r >> b >> t;

        OrthographicCamera cam(l, r, b, t);

        API::camera_ = std::make_shared<Camera>(cam);
    }
}

void API::film(ParamSet ps)
{
    int x_res, y_res;
    std::string output_filename;

    x_res = std::stoi(ps.get_attribute("x_res"));
    y_res = std::stoi(ps.get_attribute("y_res"));
    output_filename = ps.get_attribute("filename");

    API::camera_->set_film(x_res, y_res, output_filename);
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

std::shared_ptr<Camera> API::get_camera()
{
    return API::camera_;
}

std::shared_ptr<Background> API::get_background()
{
    return API::background_;
}