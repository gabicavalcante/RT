#include "RTParser.h"
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "background.h"

#include <iostream>

void parser(string file_path)
{
	std::cout << "creating parser to read: ";
	std::cout << "\n";

	auto parser = RTParser::create(file_path);
	parser->read_file();
}

// TODO: read background data from input file
std::shared_ptr<Background> dummy_init_bg()
{
	Background b;
	return std::make_shared<Background>(b);
}

// TODO: read camera data from input file
std::shared_ptr<Camera> dummy_init_camera(int w, int h)
{
	Camera cam(w, h);
	return std::make_shared<Camera>(cam);
}

int main()
{
	auto cam = dummy_init_camera(200, 100);
	int width = cam->get_width();
	int height = cam->get_height();

	auto background = dummy_init_bg();

	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			auto color = background->sample(float(x) / float(width), float(y) / float(height));
			cam->add(x, y, color);
		}
	}
	cam->write_image("output");
}