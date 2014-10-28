/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace. Heavily based on
 * old MP4 by CS225 Staff, Fall 2010.
 * 
 * @author Chase Geigle
 * @date Fall 2012
 */
#include "filler.h"

animation filler::dfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
			solidColorPicker p = solidColorPicker(fillColor);
			return fill(img, x, y, p, tolerance, frameFreq);
}

animation filler::dfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
			gridColorPicker p = gridColorPicker(gridColor, gridSpacing);
			return fill(img, x, y, p, tolerance, frameFreq);
}

animation filler::dfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
			gradientColorPicker p = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);
			return fill(img, x, y, p, tolerance, frameFreq);
}

animation filler::dfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
			return filler::fill<Stack>(img, x, y, fillColor, tolerance, frameFreq);
}

animation filler::bfs::fillSolid( PNG & img, int x, int y, 
        RGBAPixel fillColor, int tolerance, int frameFreq ) {
			solidColorPicker p = solidColorPicker(fillColor);
			return fill(img, x, y, p, tolerance, frameFreq);
}

animation filler::bfs::fillGrid( PNG & img, int x, int y, 
        RGBAPixel gridColor, int gridSpacing, int tolerance, int frameFreq ) {
			gridColorPicker p = gridColorPicker(gridColor, gridSpacing);
			return fill(img, x, y, p, tolerance, frameFreq);
}

animation filler::bfs::fillGradient( PNG & img, int x, int y, 
        RGBAPixel fadeColor1, RGBAPixel fadeColor2, int radius, 
        int tolerance, int frameFreq ) {
			gradientColorPicker p = gradientColorPicker(fadeColor1, fadeColor2, radius, x, y);
			return fill(img, x, y, p, tolerance, frameFreq);
}

animation filler::bfs::fill( PNG & img, int x, int y, 
        colorPicker & fillColor, int tolerance, int frameFreq ) {
			return filler::fill<Queue>(img, x, y, fillColor, tolerance, frameFreq);
}

template <template <class T> class OrderingStructure>
animation filler::fill( PNG & img, int x, int y,
        colorPicker & fillColor, int tolerance, int frameFreq ) {
			//image dimensions
			int width  = img.width();
			int height = img.height();
			
			//image starting points 
			//GOES RGB
			
			int sRed = (int) (img(x,y)->red);
			int sGreen = (int) (img(x,y)->green);
			int sBlue = (int) (img(x,y)->blue);
			
			//set up the animation
			animation gif;
			
			//set up the list for x and y
			OrderingStructure<int> xList;
			OrderingStructure<int> yList;
			xList.add(x);
			yList.add(y);
			
			//number of frames added
			int framesAdded = 0;
			
			//marked as processed 
			//make a vector of vectors???
			//hey it works
			std::vector< vector<bool> > marked(width, vector<bool>(height));
			//set all the stuff inside marked to false 
			for (int i = 0; i<width; i++) {
				for (int j = 0; j<height; j++) {
					marked[i][j] = false;
				}
			} 
			
			while(!xList.isEmpty() && !yList.isEmpty()) {
				int currentX = xList.remove();
				int currentY = yList.remove();
				//tolerence
				
				int toleranceCurrent = 0;
				toleranceCurrent += pow(img(currentX, currentY)->red - sRed, 2);
				toleranceCurrent += pow(img(currentX, currentY)->green - sGreen, 2);
				toleranceCurrent += pow(img(currentX, currentY)-> blue - sBlue, 2);
				
				//if the current is NOT marked and if the tolerance is less than the given tolerance
				if(!marked[currentX][currentY] && toleranceCurrent <= tolerance) {
					
					framesAdded++;
					
					//sets the pointee of the the image to the fill color
					*img(currentX, currentY) = fillColor(currentX, currentY);
					marked[currentX][currentY] = true;
					
					
					//adds the animation
					if(framesAdded % frameFreq == 0) {
						gif.addFrame(img);
					}
					
					//check out of bounds
					//TRUE if out of bounds, FALSE if in bounds
					bool rightoob = currentX+1 >= width;
					bool downoob = currentY+1 >= height;
					bool leftoob = currentX-1 < 0;
					bool topoob = currentY-1 < 0;
					
					if(!rightoob) {
						xList.add(currentX + 1);
						yList.add(currentY);
					}
					if(!downoob) {
						xList.add(currentX);
						yList.add(currentY + 1);
					}
					if (!leftoob) {
						xList.add(currentX - 1);
						yList.add(currentY);
					}
					if (!topoob) {
						xList.add(currentX);
						yList.add(currentY-1);
					}
					
				}
			}
    return gif;
}

	
	
