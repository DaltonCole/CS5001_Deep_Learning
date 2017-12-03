#ifndef POINT_H
#define POINT_H

#include <iostream>
using namespace std;

enum Direction {north=0, east=1, south=2, west=3};

enum Type {empty=0, tile=1, wall=2, donut=3};

struct Point {
	int x;
	int y;
	float value[4];
	Type type;

	Point(int a, int b) {
		// Set x and y
		x = a;
		y = b;

		// Initalize value
		for(int i = 0; i < 4; i++) {
			value[i] = 0;
		}

		// Initalize type
		type = empty;
	}

	void set_type(const Type& t) {
		type = t;
	}

	float max_value() {
		// Find max value
		float max_value = value[0];
		for(int i = 1; i < 4; i++) {
			if(max_value < value[i]) {
				max_value = value[i];
			}
		}
		return max_value;
	} 

	Direction max_dir() {
		// Find direction
		float max_value = value[0];
		int index = 0;
		for(int i = 1; i < 4; i++) {
			if(max_value < value[i]) {
				max_value = value[i];
				index = i;
			}
		}
		return static_cast<Direction>(index);
	}
};

#endif