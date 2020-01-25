//
// Created by Yona Appletree on 1/24/20.
//

#include "util.h"
#include "math.h"

double mapd(double x, double in_min, double in_max, double out_min, double out_max) {
	double divisor = (in_max - in_min);
	if(divisor == 0){
		return (out_min + out_max) / 2;
	}
	return (x - in_min) * (out_max - out_min) / divisor + out_min;
}

double mapdClamp(double x, double in_min, double in_max, double out_min, double out_max) {
	double divisor = (in_max - in_min);
	if(divisor == 0){
		return (out_min + out_max) / 2;
	}
	if (x < in_min) return out_min;
	if (x > in_max) return out_max;

	return (x - in_min) * (out_max - out_min) / divisor + out_min;
}


double triangle(double input) {
	input = fmod(1 + fmod(input, 1.0), 1);

	return input < 0.5
	       ? input / 0.5
	       : 1 - (input - 0.5) / 0.5;
}
