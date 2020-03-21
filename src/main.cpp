#include "parser/rtparser.h"
#include "camera/camera.h"
#include "image/background.h"
#include "core/api.h"

#include <iostream>

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Please, enter a valid input" << std::endl;
		return 1;
	}

	auto api = API::get_instance();
	auto parser = RTParser::create(argv[1]);
	parser->run();

	auto cam = api->get_camera();
	int width = cam->get_width();
	int height = cam->get_height();

	auto background = api->get_background();

	// Traverse all pixels to shoot rays from.
	for (int y = height - 1; y >= 0; y--)
	{
		for (int x = 0; x < width; x++)
		{
			// Generate ray with the view plane frame method.
			ray r = cam->generate_ray(float(x), float(y));
			//std::cout << r << std::endl;

			//auto color = background->sample(float(x) / float(width), float(y) / float(height));
			auto color = background->sample_image(x, y);
			cam->add_texture(x, y, color);
			// Pixel p = Li(r1, scene, sampler);
			// film->setPixel(i, j, p);
		}
	}
	cam->encodeOneStep();
	//cam->write_image();
}