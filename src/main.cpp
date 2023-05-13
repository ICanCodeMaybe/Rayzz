#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

#include "math.h"
#include "util.h"

#include "sphere.h"
#include "hittable_list.h"

//--------CONSTANTS-----------
//image propreties
const auto ASPECT_RATIO = 16/9;
const int IMAGE_WIDTH = 900;
const int IMAGE_HEIGHT = IMAGE_WIDTH/ASPECT_RATIO;

//camera propreties
const auto VIEWPORT_HEIGHT = 2.0;
const auto VIEWPORT_WIDTH = VIEWPORT_HEIGHT * ASPECT_RATIO;
const auto FOCAL_LENGHT = 1.0;

Point origin(0,0,0);
Vec3 horizontal(VIEWPORT_WIDTH, 0, 0);
Vec3 vertical(0, VIEWPORT_HEIGHT, 0);
Point lower_left_corn = origin - horizontal/2 - vertical/2 - Vec3(0, 0, FOCAL_LENGHT);
//----------------------------

Color ray_color(const Ray& r, const Hittable& world){
	hit_info info;
	if(world.hit(r, 0, infinity, info)){
		return 0.5*(info.normal + Color(1, 1, 1));
	}

	Vec3 unit = unit_vector(r.dir);
	double t = 0.5 * (unit.y() + 1);

	return (1.0-t)*Color(0.3, 0.4, 0.65) + t*Color(0.75, 0.85, 0.9);
}

int main(){

	//world
	HittableList world;
	world.add(std::make_shared<Sphere>(Point(0.0, 0.0, -1.0), 0.5));
	world.add(std::make_shared<Sphere>(Point(0.0, -100.5, -1.0), 100.0));
	

	std::cout << "P3\n"<< IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n256\n";
	for(int i = IMAGE_HEIGHT -1; i >= 0; i--){
		for(int k = 0; k < IMAGE_WIDTH; k++){
			double u = double(i)/IMAGE_HEIGHT;
			double v = double(k)/IMAGE_WIDTH;
			
			Ray r(origin, (lower_left_corn + u*vertical + v*horizontal - origin));   
			Color pixel_color = ray_color(r, world);
			
			write_color(std::cout, pixel_color);
		}
		std::cerr << "Lines remeaining: " << IMAGE_HEIGHT - i << " out of "<< IMAGE_HEIGHT << "\n" << std::flush;
	}

}

