#ifndef UTILS_H
#define UTILS_H

//frequently used standart libary files
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

//constatns
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265;

//Utility functions

inline double degrees_to_radians(double degrees){
	return degrees * pi/180;
}

inline double radians_to_degrees(double radians){
	return radians * 180/pi;
}

inline double random_double(){
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max){
	return min + (max - min)*random_double();
}

inline double clamp(double x, double min, double max){
	if(x < min) return min;
	if(x > max) return max;
	return x;
}

#endif

