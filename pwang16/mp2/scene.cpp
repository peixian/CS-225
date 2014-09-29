#include "scene.h"
using namespace std;
Scene::Scene(int max)
{
	x = new int[max];
	y = new int[max];
	imageNumber = max;
	images = new Image*[max];
	
	for (int i = 0; i<max; i++) {
		images[i] = NULL;
	}
}
Scene::~Scene() {
	clear();
}
Scene::Scene(const Scene &source) {
	copy(source);
}
const Scene& Scene::operator=(const Scene &source) {
	if (this != &source) {
		clear();
		copy(source);
	}
	return *this;
}

void Scene::changemaxlayers(int newmax) {
	Image ** newMaxLayerImage = new Image * [newmax];
	if (newmax < imageNumber) {
		for (int i = newmax; i < imageNumber; i++) {
			if (images[i] != NULL) {
				cout << "invalid newmax" << endl;
				return;
			}
		}
	}
	for (int i = 0; i < imageNumber; i++) {
		*newMaxLayerImage[i] = *images[i];	
	}
	images = newMaxLayerImage;
	delete newMaxLayerImage;
}

void Scene::addpicture(const char *FileName, int index, int xInput, int yInput) {
	if (index > imageNumber || index < 0) {
		cout << "index out of bounds" << endl;
		return;
	}
	x[index] = xInput;
	y[index] = yInput;
	if (images[index] != NULL) {
		delete images[index];
	}
	images[index] = new Image();
	images[index]->readFromFile(FileName);
}

void Scene::changelayer(int index, int newindex) {
	if (index == newindex) {
		return;
	}
	if (index > imageNumber || index < 0) {
		cout << "invalid index" << endl;
		return;
	}
	delete images[newindex];
	images[newindex] = images[index];
	x[newindex] = x[index];
	y[newindex] = y[index];
	images[index] = NULL;
}

void Scene::translate(int index, int xcoord, int ycoord) {
	if (index > imageNumber || index < 0) {
		cout << "invalid index" << endl;
		return;
	}
	x[index] = xcoord;
	y[index] = ycoord;

}

void Scene::deletepicture(int index) {
	if (index > imageNumber || index < 0) {
		cout << "invalid index" << endl;
		return;
	}
	delete images[index];
	images[index] = NULL;
}

Image*  Scene::getpicture(int index) const {
	if (index > imageNumber || index < 0) {
		cout << "invalid index" << endl;
		return NULL;
	}
	return (images[index]);
}

Image  Scene::drawscene() const {
	int maxX = 0;
	int maxY = 0;
	
	for (int i = 0; i<imageNumber; i++) {
		if (images[i] != NULL) {		
			if (maxX < (images[i]->width() + x[i])) {
				maxX = images[i]->width() + x[i];		
			}
			if (maxY < (images[i]->height() + y[i])) {
				maxY = images[i]->height() + y[i];
			}
		}
	}
	Image total;
	total.resize(maxX, maxY);	
	for (int i = 0; i < imageNumber; i++) {
		if (images[i] != NULL) {
			for (int j = 0; j<images[i]->width(); j++) {
				for (int k = 0; k<images[i]->height(); k++) {
					*(total)(x[i]+j, y[i]+k) = *(*images[i])(j,k);				
				}			
			}
		}
	}
	return total;
}



void Scene::clear() {
	for (int i = 0; i<imageNumber; i++) {
		delete images[i];
	}
	delete [] images;
	delete [] x;
	delete [] y;	
}

void Scene::copy(const Scene &original) {
	imageNumber = original.imageNumber;
	x = new int[original.imageNumber];
	y = new int[original.imageNumber];
	images = new Image*[original.imageNumber];
	
	for (int i = 0; i<original.imageNumber; i++) {
		if (original.images[i] != NULL) {		
			x[i] = original.x[i];
			y[i] = original.y[i];
			images[i] = new Image();
			*images[i] = *(original.images[i]);
		}
		else {
			images[i] = NULL;
		}
	}
}
