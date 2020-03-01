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