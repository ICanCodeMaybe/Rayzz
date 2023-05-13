#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"
#include "ray.h"
#include "util.h"

class Camera{
private:
	Point origin;
	Point lower_left_corn;
	Vec3 horizontal;
	Vec3 vertical;

public:
	Camera(){
		auto aspect_ration = 16/9;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * aspect_ration;
		auto focal_lenght = 1.0;

		origin = Point(0,0,0);
		horizontal = Point(viewport_width, 0 , 0);
		vertical = Point(0, viewport_height, 0);
		lower_left_corn = origin - horizontal/2 - vertical/2 - Point(0, 0, focal_lenght);
	}
	Ray get_ray(double u, double v) const {
		return Ray(origin, lower_left_corn + u*horizontal + v*vertical - origin);
	}
};

#endif
