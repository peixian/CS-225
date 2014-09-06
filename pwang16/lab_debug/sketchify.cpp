#include <cstdlib>
#include "png.h"
#include <iostream>
using namespace std;
//
// sets up the output image
PNG * setupOutput(int w, int h)
{
	PNG * image = new PNG(w, h);
	return image;
}


// Returns my favorite color
RGBAPixel * myFavoriteColor(int intensity)
{
	RGBAPixel * color = new RGBAPixel();
	color->red   = 0;
	color->green = intensity/2;
	color->blue  = intensity;
	return color;
}


void sketchify()
{
	// Load in.png
	PNG * original = new PNG();
	cout << "Reached " << __LINE__ << endl;
	
	original->readFromFile("in.png");
	cout << "Reached " << __LINE__ << endl;
	int width  = original->width();
	cout << "Reached " << __LINE__ << endl;
	int height = original->height();
	cout << "Reached " << __LINE__ << endl;
	// Create out.png
	PNG * output;
	output = setupOutput(width, height);	

	// Loud our favorite color to color the outline
	RGBAPixel * myPixel = myFavoriteColor(192);
	cout << "WIDTH IS " << width << endl;
	cout << "HEIGHT IS " << height << endl;
	// Go over the whole image, and if a pixel differs from that to its upper
	// left, color it my favorite color in the output
	for (int y = 1; y < height; y++)
	{
		cout << "REACHED " << __LINE__ << endl;
		for (int x = 1; x < width; x++)
		{
			cout << "AT POSITION " << x << ", " << y << endl;
			// Calculate the pixel difference
			
			RGBAPixel * prev = (*original)(x-1, y-1);
			RGBAPixel * curr = (*original)(x  , y  );
			int diff = abs(curr->red  - prev->red  ) +
					   abs(curr->green - prev->green) +
					   abs(curr->blue  - prev->blue );
			cout << "DIFFERENCE IS " << diff << endl;
			// If the pixel is an edge pixel,
			// color the output pixel with my favorite color
			
			RGBAPixel * currOutPixel = (*output)(x,y);
			if (diff > 100) {
				cout << "DIFFERENCE CALLED" << endl;
				*currOutPixel = *myPixel;
			}
				
		}
	}
	cout << "REACHED " << __LINE__ << endl;
	// Save the output file
	output->writeToFile("out.png");
	cout << "REACHED " << __LINE__ << endl;
	// Clean up memory
	delete myPixel;
	delete output;
	delete original;
	
}
