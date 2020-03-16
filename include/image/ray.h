#pragma once

#include "math/vec3.h"

class ray
{
private:
    point3 origin;  // ray origin
    vec3 direction; // ray direction

public:
    ray() {}
    ray(const point3 &origin_, const vec3 &direction_) : origin(origin_), direction(direction_) {}

    point3 get_origin() const { return origin; }
    vec3 get_direction() const { return direction; }

    // ray function. p(t) moves the point along the ray / point_at_parameter
    point3 operator()(float t) const { return origin + (t * direction); }

    friend std::ostream &operator<<(std::ostream &os, const ray &r)
    {
        os << "(o =" << r.origin << ", d =" << r.direction << ")";
        return os;
    }
};