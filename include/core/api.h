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
    static void look_at(ParamSet ps);

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
    double l, r, b, t;

    if (ps.has_attribute("screen_window"))
    {
        std::istringstream is(ps.get_attribute("screen_window"));
        is >> l >> r >> b >> t;
        Camera cam(type, l, r, b, t);
        API::camera_ = std::make_shared<Camera>(cam);
    }
    else
    {
        Camera cam(type);
        API::camera_ = std::make_shared<Camera>(cam);
    }

}

void API::film(ParamSet ps)
{
    // TODO:
    // - crop_window
    // - img_type
    // - gamma_corrected
    int x_res, y_res;
    std::string output_filename;

    x_res = std::stoi(ps.get_attribute("x_res"));
    y_res = std::stoi(ps.get_attribute("y_res"));
    output_filename = ps.get_attribute("filename");

    API::camera_->set_film(x_res, y_res, output_filename);
}

void API::look_at(ParamSet ps)
{
    float look_from[3];
    float look_at[3];
    float up[3];

    std::istringstream is_look_from(ps.get_attribute("look_from"));
    is_look_from >> look_from[0] >> look_from[1] >> look_from[2];

    std::istringstream is_look_at(ps.get_attribute("look_at"));
    is_look_at >> look_at[0] >> look_at[1] >> look_at[2];

    std::istringstream is_up(ps.get_attribute("up"));
    is_up >> up[0] >> up[1] >> up[2];

    API::camera_->set_look_at(look_from, look_at, up);
}

void API::background(ParamSet ps)
{
    std::istringstream is(ps.get_attribute("color"));
    int r, g, b;
    is >> r >> g >> b;

    Pixel color(r, g, b);
    std::string type = ps.get_attribute("type");
    std::string mapping = ps.get_attribute("mapping");
    std::string filename = ps.get_attribute("filename");
    
    Background bg(type, color, mapping, filename);
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