#include "image.h"
void Image::flipleft() {
	int width = this->width();
	int height = this->height();
	for (int x = 0; x<width/2; x++) {
		for (int y = 0; y<height; y++) {
			RGBAPixel* temp = new RGBAPixel();
			*temp  = *this->operator()(x,y);
			*this->operator()(x,y) = *this->operator()(width-1-x, y);
			*this->operator()(width-1-x, y) = *temp;
		}
	}	
}
void Image::adjustbrightness(int r, int g, int b) {
	int width = this->width();
	int height = this->height();
	for (int x = 0; x<width; x++) {
		for (int y = 0; y< height; y++) {
			int red = (*this)(x,y)->red + r;
			int green = (*this)(x,y)->green + g;
			int blue = (*this)(x,y)->blue + b;
			if (red > 255) {
				red = 255;
			}
			else if (red < 0) {
				red = 0;
			}
			if (green > 255) {
				green = 255;
			}
			else if (green < 0) {
				green = 0;
			}
			if (blue > 255)
			{
				blue = 255;
			}
			else if (blue < 0) {
				blue = 0;			
			}
			(*this)(x,y)->red = red;
			(*this)(x,y)->green = green;
			(*this)(x,y)->blue = blue;
		}
	}
	
}
void Image::invertcolors () {
	int width = this->width();
	int height = this->height();
	for (int x = 0; x<width; x++) {
		for(int y = 0; y<height; y++) {
			(*this)(x,y)->red = 255-(*this)(x,y)->red;
			(*this)(x,y)->green = 255-(*this)(x,y)->green;
			(*this)(x,y)->blue = 255-(*this)(x,y)->blue;
		}
	}
}
