#include "RTParser.h"
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "background.h"

#include <iostream>

// blends white and blue depending on the up/downess of the y coordinate
// t = 1.0 -> blue
// t = 0.0 -> white
// linear_interpolation: blendedValue = (1 - t) * startValue + t * endValue
vec3 color(const ray &r)
{
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

void parser(string file_path)
{
	std::cout << "creating parser to read: ";
	std::cout << "\n";

	auto parser = RTParser::create(file_path);
	parser->read_file();
}

std::shared_ptr<Background> dummy_init_bg()
{
	Background b;
	return std::make_shared<Background>(b);
}

std::shared_ptr<Camera> dummy_init_camera()
{
	Camera cam(200, 100);
	return std::make_shared<Camera>(cam);
}

int main()
{
	auto cam = dummy_init_camera();
	int w = cam->get_width();
	int h = cam->get_height();

	auto background = dummy_init_bg();

	for (int j = h - 1; j >= 0; j--)
	{
		for (int i = 0; i < w; i++)
		{
			auto color = background->sample(float(i) / float(w), float(j) / float(h));
			cam->add(j, i, color);
		}
	}
	cam->write_image("output");
}