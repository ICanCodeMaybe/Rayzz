#ifndef SPHERE_H
#define SPHERE_H

#include "util.h"
#include "math.h"
#include "ray.h"
#include "material.h"
#include "hittable.h"

class Sphere : public Hittable{
public:
	Point center;
	double radius;
	std::shared_ptr<Material> m_material;
public:
	Sphere(){}
	Sphere(Point center, double radius, std::shared_ptr<Material> material): center(center), radius(radius), m_material(material){}

	virtual bool hit(const Ray& r, double t_min, double t_max, hit_info& hit_in) const override;
};

bool Sphere::hit(const Ray &r, double t_min, double t_max, hit_info &hit_in) const{
	Vec3 oc = r.orig - center;
	double a = r.dir.lenght_squared();
	double b_half = dot(oc, r.dir);
	double c = oc.lenght_squared() - radius * radius;
	double discriminant = b_half*b_half - a*c;

	if(discriminant < 0) return false;

	double sqrtd = sqrt(discriminant);
	
	double root = (-b_half-sqrtd)/a;
	if( t_min > root || t_max < root){
		root = (-b_half + sqrtd)/a;
		if( t_min > root || t_max < root)
			return false;
	}

	hit_in.t = root;
	hit_in.point = r.at(root);
	hit_in.set_face_normal(r, (hit_in.point - center) / radius);
	hit_in.material = m_material;

	return true;
}

#endif

