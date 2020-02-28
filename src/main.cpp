#include "rtparser.h"
#include "camera.h"
#include "background.h"

#include <iostream>

void parser(string file_path)
{
	auto parser = RTParser::create(file_path);

	auto camera = parser->read_object("camera");
	auto film = parser->read_object("film");

	camera.print();
	film.print();
}

// TODO: read background data from input file
std::shared_ptr<Background> dummy_init_bg()
{
	Background bg;
	return std::make_shared<Background>(bg);
}

// TODO: read camera data from input file
std::shared_ptr<Camera> dummy_init_camera(int w, int h)
{
	Camera cam(w, h);
	return std::make_shared<Camera>(cam);
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		parser(argv[1]);
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
	else
	{
		std::cout << "Please, enter a valid input" << std::endl;
	}
}