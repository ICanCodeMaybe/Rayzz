#include <cmath>
#include <iostream>
#include <memory>
#include <ostream>

#include "util.h"
#include "math.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"
#include "material.h"

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
		Ray scattered;
		Color attenuation;
		if(info.material->scatter(r, info, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth -1);
		return Color(0 , 0, 0);
	}

	Vec3 unit = unit_vector(r.dir);
	double t = 0.5 * (unit.y() + 1);

	return (1.0-t)*Color(0.85, 0.9, 1) + t*Color(0.3, 0.35, 0.65);
}

int main(){
	//materials
	auto red_scatt = std::make_shared<Lambertian>(Color(0.9, 0.15, 0.1));
	auto green_scatt = std::make_shared<Lambertian>(Color(0.15, 0.9, 0.1));
	auto pink_scatt = std::make_shared<Lambertian>(Color(0.8, 0.3, 0.7));
	auto white_metal = std::make_shared<Metal>(Color(0.94, 0.93, 0.9), 0.5);
	auto blue_metal = std::make_shared<Metal>(Color(0.4, 0.5, 0.9), 0.05);
	auto glass = std::make_shared<Dielectric>(1.5, Color(1.0, 1.0, 1.0));


	//world
	HittableList world;
	world.add(std::make_shared<Sphere>(Point(0.0, 0.0, -2.0), 0.5, pink_scatt));
	world.add(std::make_shared<Sphere>(Point(0.0, -100.5, -2.0), 100.0, green_scatt));
	world.add(std::make_shared<Sphere>(Point(-1.25, 0.0, -3.0), 0.5, blue_metal));
	world.add(std::make_shared<Sphere>(Point(1.0, 0.0, -2.0), 0.5, white_metal));
	world.add(std::make_shared<Sphere>(Point(-1.5, 0.0, -1.5), 0.5, red_scatt));
	world.add(std::make_shared<Sphere>(Point(0.0, 0.0, -1), 0.5, glass));

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

