#ifndef UTILS_H
#define UTILS_H

//frequently used standart libary files
#include <cmath>
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

//headers
#include "ray.h"
#include "math.h"

#endif

