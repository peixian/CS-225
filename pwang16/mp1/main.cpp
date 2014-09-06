#include <iostream>
#include "png.h"
using namespace std;
int main() {
	//makes the png and reads the size 
	PNG input = PNG("in.png");
	size_t x = input.width();
	size_t y = input.height();
	//makes a new png
	PNG out = PNG(x, y);
	for (size_t i = 0; i< x; i++) {
		for (size_t j = 0; j<y; j++) {
			//loops over the input png, then copies the the pixel to the corresponding pixel on the other side of the image
			*out(x-1-i, y-1-j) =  *input(i,j);
		}
	}
	//writes to the file
	out.writeToFile("out.png");
};