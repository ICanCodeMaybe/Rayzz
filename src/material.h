#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "math.h"
#include "ray.h"


class Material{
public:
	virtual bool scatter( const Ray& r_in, const hit_info&, Color& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material{
public:
	Color albedo;
public:
	Lambertian(const Color& col) : albedo(col){}

	virtual bool scatter( const Ray& r_in, const hit_info& info, Color& attenuation, Ray& scattered) const{
		Vec3 scattered_dir = info.normal + random_unit_vector(); 
	
		if(scattered_dir.close_zero())
			scattered_dir = info.normal;

		scattered = Ray(info.point, scattered_dir);
		attenuation = albedo;
		return true;
	}
};

class Metal : public Material{
public:
	Color albedo;
	double fuzz;
public:
	Metal(const Color& col, double fuzzines) : albedo(col), fuzz((fuzzines > 1)? 1 : fuzzines){}

	virtual bool scatter(const Ray& r_in, const hit_info& info, Color& attenuation, Ray& scattered) const {
		Vec3 reflect_dir = reflect(unit_vector(r_in.dir), info.normal);
		scattered = Ray(info.point, reflect_dir + fuzz*random_in_unit_sphere());
		attenuation = albedo;

		return (dot(scattered.dir, info.normal) > 0); //check, so the scattered and normal arent more than 90 degrees apart;
	}
};
#endif
