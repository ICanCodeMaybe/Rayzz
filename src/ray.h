#ifndef RAY_H
#define RAY_H

#include "math.h"

class Ray{
public:
	Point orig;
	Vec3 dir;
public:
	Ray(){}
	Ray(const Point& orig, const Vec3& dir): orig(orig), dir(dir){}

	Point at(double t) const {
		return orig + t * dir;
	}

};

#endif
