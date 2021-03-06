#include "rtparser.h"
#include "camera.h"
#include "background.h"
#include "api.h"

#include <iostream>

int main(int argc, char **argv)
{
	auto api = API::get_instance();
	if (argc == 2)
	{
		auto parser = RTParser::create(argv[1]);
		parser->run();

		auto cam = api->get_camera();
		int width = cam->get_width();
		int height = cam->get_height();

		auto background = api->get_background();

		for (int y = height - 1; y >= 0; y--)
		{
			for (int x = 0; x < width; x++)
			{
				auto color = background->sample(float(x) / float(width), float(y) / float(height));
				cam->add(x, y, color);
			}
		}
		cam->write_image();
	}
	else
	{
		std::cout << "Please, enter a valid input" << std::endl;
	}
}