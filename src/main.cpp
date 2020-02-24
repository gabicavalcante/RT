#include "RTParser.h"

#include "float.h"
#include "hittable_list.h"
#include "sphere.h"

// blends white and blue depending on the up/downess of the y coordinate
// linear_interpolation: blendedValue = (1 - t) * startValue + t * endValue
vec3 color(const ray &r, hittable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0, MAXFLOAT, rec))
	{
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

void parser(string file_path)
{
	std::cout << "creating parser to read: ";
	std::cout << "\n";

	auto parser = RTParser::create(file_path);
	parser->read_file();
}

int main(int argc, char const *argv[])
{
	//parser(argv[1])
	int nx = 200;
	int ny = 100;
	std::cout << "P3\n"
			  << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	hittable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hittable *world = new hittable_list(list, 2);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + (u * horizontal) + (v * vertical));

			vec3 p = r.point_at_parameter(2.0);
			vec3 col = color(r, world);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			std::cout << ir << " " << ig << " " << ib << "\n";
		}
	}
}
