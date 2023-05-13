#include <iostream>
#include <ostream>

#include "math.h"
#include "ray.h"
#include "sphere.h"

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

double hit_sphere(const Point& center, const double radius, const Ray& r);

Color ray_color(const Ray& r){
	double t = hit_sphere({0, 0, -1}, 0.5, r);
	if(t > 0){
		Vec3 N = unit_vector(r.at(t) - Point(0, 0, -1));
		return (1-t)*Color(N.x()+1, N.y() + 1, N.z()+1);
	}
	Vec3 unit_dir = unit_vector(r.dir);
	t = (unit_dir.y() + 1)/2;
	return (1-t)*Color(0.3, 0.4, 0.65) + t*Color(0.75, 0.85, 0.9);
}

int main(){
	std::cout << "P3\n"<< IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n256\n";

	for(int i = 0; i < IMAGE_HEIGHT; i++){
		for(int k = 0; k < IMAGE_WIDTH; k++){
			double u = double(i)/IMAGE_HEIGHT;
			double v = double(k)/IMAGE_WIDTH;
			
			Ray r(origin, (lower_left_corn + u*vertical + v*horizontal - origin));   
			Color pixel_color = ray_color(r);
			
			write_color(std::cout, pixel_color);
		}
		std::cerr << "Lines remeaining: " << IMAGE_HEIGHT - i << " out of "<< IMAGE_HEIGHT << "\n" << std::flush;
	}

}


double hit_sphere(const Point& center, const double radius, const Ray& r){
//discriminant, explenantion is in book(it does make good sence)

	Vec3 oc = r.orig - center;
	double a = r.dir.lenght_squared();
	double half_b =  dot(oc, r.dir);
	double c = oc.lenght_squared() - radius*radius;

	double discriminant = half_b*half_b - a * c;
	if(discriminant < 0)
		return -1;
	else{
		return (-half_b - sqrt(discriminant))/(a); //solving the quadratic equation
	}

}
