#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

#include "math.h"
#include "util.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"

//--------CONSTANTS-----------
//image propreties
const auto ASPECT_RATIO = 16/9;
const int IMAGE_WIDTH = 400;
const int IMAGE_HEIGHT = IMAGE_WIDTH/ASPECT_RATIO;
const int SAMPLES_PER_PIXEL = 100;
const int MAX_DEPTH = 50;

//camera
Camera camera;


//----------------------------

Color ray_color(const Ray& r, const Hittable& world, int depth){
	hit_info info;

	if(depth <= 0)
		return Color(0, 0 ,0);

	if(world.hit(r, 0.001, infinity, info)){
		Point target = info.point + info.normal + random_in_hemisphere(info.normal); 
		return 0.5*ray_color(Ray(info.point, target - info.point), world, depth -1);
	}

	Vec3 unit = unit_vector(r.dir);
	double t = 0.5 * (unit.y() + 1);

	return (1.0-t)*Color(0.85, 0.9, 1) + t*Color(0.3, 0.35, 0.65);
}

int main(){

	//world
	HittableList world;
	world.add(std::make_shared<Sphere>(Point(0.0, 0.0, -1.0), 0.5));
	world.add(std::make_shared<Sphere>(Point(0.0, -100.5, -1.0), 100.0));
	

	std::cout << "P3\n"<< IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n256\n";
	for(int i = IMAGE_HEIGHT -1; i >= 0; i--){
		for(int k = 0; k < IMAGE_WIDTH; k++){
			Color pixel_color(0, 0, 0);
			for(int l = 0; l < SAMPLES_PER_PIXEL; l++){
				double v = (double(i) + random_double())/IMAGE_HEIGHT;
				double u = (double(k) + random_double())/IMAGE_WIDTH;
				
				Ray r = camera.get_ray(u, v);   
				pixel_color += ray_color(r, world, MAX_DEPTH);
			}
			write_color(std::cout, pixel_color, SAMPLES_PER_PIXEL);
		}
		std::cerr << "Lines remeaining: " << IMAGE_HEIGHT - i << " out of "<< IMAGE_HEIGHT << "\n" << std::flush;
	}

}

