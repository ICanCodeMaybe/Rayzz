#ifndef MATH_H
#define MATH_H

#include "util.h"
#include <iostream>
#include <cmath>
#include <ostream>

class Vec3;
using Color = Vec3;
using Point = Vec3;

inline Vec3 unit_vector(Vec3 v); 
inline double dot(const Vec3 &u, const Vec3 &v); 

class Vec3{
public:
	double data[3];
public:
	Vec3() : data{0, 0 ,0}{
	}

	Vec3(double x, double y, double z) : data{x,y,z} {
	}

	double x() const { return data[0]; }
	double y() const { return data[1]; }
	double z() const { return data[2]; }


	inline static Vec3 random(){
		return Vec3(random_double(), random_double(), random_double());
	}

	inline static Vec3 random(double min, double max){
		return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

	Vec3 operator-() const { return Vec3(-data[0], -data[1], -data[2]); };
	double operator[](int i) const { return data[i]; };
	double& operator[](int i) { return  data[i]; };

	Vec3& operator+(const double t){
		data[0] += t;
		data[1] += t;
		data[2] += t;
		return *this;
	}
	Vec3& operator+=(const Vec3& t){
		data[0] += t[0];
		data[1] += t[1];
		data[2] += t[2];
		return *this;
	}
	
	
	Vec3& operator *=(const double t){
		data[0] *= t;
		data[1] *= t;
		data[2] *= t;
		return *this;
	}
	Vec3& operator/=(const double t){
		return *this *= 1/t;
	}

	double lenght_squared() const {
		return data[0] * data[0] + data[1] * data[1] + data[2] * data[2];
	}

	double length() const {
		return sqrt(lenght_squared());
	}

};
	// vec3 Utility Functions

	Vec3 random_in_unit_sphere(){
		while(true){
			Vec3 point = Vec3::random(-1, 1);
			if(point.lenght_squared() >= 1) continue;
			return point;
		}
	}

	Vec3 random_unit_vector(){
		return unit_vector(random_in_unit_sphere());
	}

	Vec3 random_in_hemisphere(const Vec3& normal){
		Vec3 in_unit_sphere = random_in_unit_sphere();
		if(dot(in_unit_sphere, normal) > 0){ // is in same hemisphere
			return in_unit_sphere;
		}
		else
			return -in_unit_sphere;
	}

	inline std::ostream& operator<<(std::ostream &out, const Vec3 &v) {
	    return out << v.data[0] << ' ' << v.data[1] << ' ' << v.data[2];
	}
	
	inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
	    return Vec3(u.data[0] + v.data[0], u.data[1] + v.data[1], u.data[2] + v.data[2]);
	}
	
	inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
	    return Vec3(u.data[0] - v.data[0], u.data[1] - v.data[1], u.data[2] - v.data[2]);
	}
	
	inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
	    return Vec3(u.data[0] * v.data[0], u.data[1] * v.data[1], u.data[2] * v.data[2]);
	}
	
	inline Vec3 operator*(double t, const Vec3 &v) {
	    return Vec3(t*v.data[0], t*v.data[1], t*v.data[2]);
	}
	
	inline Vec3 operator*(const Vec3 &v, double t) {
	    return t * v;
	}
	
	inline Vec3 operator/(Vec3 v, double t) {
	    return (1/t) * v;
	}
	
	inline double dot(const Vec3 &u, const Vec3 &v) {
	    return u.data[0] * v.data[0]
	         + u.data[1] * v.data[1]
	         + u.data[2] * v.data[2];
	}
	
	inline Vec3 cross(const Vec3 &u, const Vec3 &v) {
	    return Vec3(u.data[1] * v.data[2] - u.data[2] * v.data[1],
	                u.data[2] * v.data[0] - u.data[0] * v.data[2],
	                u.data[0] * v.data[1] - u.data[1] * v.data[0]);
	}
	
	inline Vec3 unit_vector(Vec3 v) {
	    return v / v.length();
	}


void write_color(std::ostream &out, Color pixel_color, int num_of_samples){
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	auto scale = 1.0/num_of_samples;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);


	out 	<< int(clamp(r, 0.0, 0.999) * 256) << " "
		<< int(clamp(g, 0.0, 0.999) * 256) << " "
		<< int(clamp(b, 0.0, 0.999) * 256) << "\n";
}
#endif
