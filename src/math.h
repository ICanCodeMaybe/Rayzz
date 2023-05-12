#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <cmath>

class Vec3;
using Color = Vec3;
using Point = Vec3;

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


	Vec3 operator-() const { return Vec3(-data[0], -data[1], -data[2]); };
	double operator[](int i) const { return data[i]; };
	double& operator[](int i) { return  data[i]; };

	Vec3& operator+(const double t){
		data[0] += t;
		data[1] += t;
		data[2] += t;
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


void write_color(std::ostream &out, Color pixel_color){
	out 	<< int(pixel_color.x() * 255.999) << " "
		<< int(pixel_color.y() * 255.999) << " "
		<< int(pixel_color.z() * 255.999) << "\n";
}
#endif
