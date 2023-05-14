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

class Dielectric : public Material{
public:
	double index_of_refraction;
	Color m_attentuation;
public:
	Dielectric(double index_of_refraction, Color attenuation = Color(1.0, 1.0, 1.0)): index_of_refraction(index_of_refraction), m_attentuation(attenuation){}
	
	virtual bool scatter(const Ray& r_in, const hit_info& info, Color& attenuation, Ray& scattered) const override {
		attenuation = m_attentuation;
		double refract_ratio = (info.front_face)? (1.0 / index_of_refraction) : index_of_refraction; //going from air, to material. then from material to air, so its ir/1 = ir

		Vec3 unit_direction = unit_vector(r_in.dir);
		Vec3 refracted_dir = refract(unit_direction, info.normal, refract_ratio);
		
		scattered = Ray(info.point, refracted_dir);

		return true;
	}
};
#endif
