#include "rgbapixel.h"
#include <stdint.h>
//Default Constructor
RGBAPixel::RGBAPixel() {
	red = 255;
	blue = 255;
	green = 255;
	alpha = 255;
}
//Constuctor with Options 
RGBAPixel::RGBAPixel(uint8_t r, uint8_t g, uint8_t b) {
	red = r;
	green = g;
	blue = b;
	alpha = 255;
}
