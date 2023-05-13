#ifndef HITTABLE_H
#define HITTABLE_H

#include "math.h"
#include "ray.h"

struct hit_info{
	Point point;
	Vec3 normal;
	double t;

	bool front_face;

	inline void set_face_normal(const Ray& r, const Vec3& outward_normal){
		front_face = dot(r.dir, outward_normal) > 0.0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class Hittable{
public:
	virtual bool hit(const Ray& r, double t_min, double t_max, hit_info& hit_in) const = 0;
};

#endif

