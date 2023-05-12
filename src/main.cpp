#include <iostream>

#include "math.h"

const int IMAGE_WIDTH = 256;
const int IMAGE_HEIGHT = 256;

int main(){
	std::cout << "P3\n"<< IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n256\n";

	for(int i = 0; i < IMAGE_HEIGHT; i++){
		for(int k = 0; k < IMAGE_WIDTH; k++){
			Color pixel_color(double(i)/IMAGE_HEIGHT, double(k)/IMAGE_WIDTH, 0.5);
			write_color(std::cout, pixel_color);
		}
		std::cerr << "Lines remeaining: " << IMAGE_HEIGHT - i << " out of "<< IMAGE_HEIGHT << "\n";
	}

}
