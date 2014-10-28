// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <vector>
#include <math.h>

Quadtree::Quadtree() {
	root = NULL;
	res = 0;
}

Quadtree::Quadtree(const PNG &source, int resolution) {
	root = NULL;
	res = resolution;
	buildTree(source, resolution);
}

Quadtree::Quadtree(Quadtree const &other) {
	root = NULL;
	res = 0;
	copy(other);
}


Quadtree::~Quadtree() {
	clear();
}

void Quadtree::clear() {
	clear(root);
}
//helper
void Quadtree::clear(QuadtreeNode* &current) {
	if (current == NULL) {
		return;
	}
	clear(current->neChild);
	clear(current->seChild);
	clear(current->swChild);
	clear(current->nwChild);
	
	delete current;
	
	current = NULL;
}

Quadtree const& Quadtree::operator=(Quadtree const &other) {
	if (&other == this)
	{
		return *this;
	}
	clear();
	copy(other);
	return *this;
}

void Quadtree::copy(Quadtree const &other) {
	res = other.res;
	copy(root, (other.root));
}
//helper
void Quadtree::copy(QuadtreeNode* &here, QuadtreeNode* const &other)  {
	if (other == NULL) {
		return;
	}
	here = new QuadtreeNode(other->element);
	copy(here->seChild, other->seChild);
	copy(here->neChild, other->neChild);
	copy(here->swChild, other->swChild);
	copy(here->nwChild, other->nwChild);

}

void Quadtree::buildTree(PNG const &source, int resolution) {
	res = resolution;
	buildTree(source, res, 0, 0, root);
}

//helper
void Quadtree::buildTree(PNG const &source, int resolution, int x, int y, QuadtreeNode* &leaves) {
	
	leaves = new QuadtreeNode();
	
	//builds the leaf
	if (resolution == 1) {

		leaves->element = *source(x,y);
		//std::cout << (int) leaves->element.red << endl;
		return;
	}
	int newRes = resolution/2;
	buildTree(source, newRes, x + newRes, y + newRes, leaves->seChild);
	buildTree(source, newRes, x + newRes, y, leaves->neChild);
	buildTree(source, newRes, x, y + newRes, leaves->swChild);
	buildTree(source, newRes, x, y, leaves->nwChild);
	
	std::vector<int> colors = average(leaves);
	leaves->element.red = colors[0];
	leaves->element.green = colors[1];
	leaves->element.blue = colors[2];
	
}
//average helper
std::vector<int> Quadtree::average(QuadtreeNode* node) {
	std::vector<int> colors(3);
	
	int avg = node->seChild->element.red;
	avg += node->swChild->element.red;
	avg += node->neChild->element.red;
	avg += node->nwChild->element.red;
	colors[0]= avg/4;
	
	avg = node->seChild->element.green;
	avg += node->swChild->element.green;
	avg += node->neChild->element.green;
	avg += node->nwChild->element.green;
	colors[1] = avg/4;
	
	avg = node->seChild->element.blue;
	avg += node->swChild->element.blue;
	avg += node->neChild->element.blue;
	avg += node->nwChild->element.blue;
	colors[2] = avg/4;
	
	return colors;
	
}

RGBAPixel Quadtree::getPixel(int x, int y) const{
	if (x >= res || y >= res || root == NULL) {
		return RGBAPixel();
	}
	
	return getPixel(root, x, y, res);
} 
//helper
RGBAPixel Quadtree::getPixel(QuadtreeNode* leaves, int x, int y, int resolution) const {
	//if the resolution 1 is or the children are NULL
	if (resolution == 1 || leaves->isLeaf()) {
		return leaves->element;
	}
	else {
		int newRes = resolution/2;
		//if x is greater than resolution, it has to be a east child
		if (x >= newRes) {
			//if y is greater than res, it has to be south, if y is less than res, it has to be north
			if (y >= newRes) {
				return getPixel(leaves->seChild, x - newRes, y - newRes, newRes); //SE
			}
			else {
				return getPixel(leaves->neChild, x - newRes, y, newRes); //NE
			}
		}
		//if x is less than resolution, it has to be a west child
		else {
			//if y is greater than res, it has to be a south child
			if (y >= newRes) {
				return getPixel(leaves->swChild, x, y - newRes, newRes); //SW
			}
			//if y is less than res, it has to be a north child
			else  {
				return getPixel(leaves->nwChild, x, y, newRes); //NW
			}
		}
		
	}
}
PNG Quadtree::decompress() const {
	if (root == NULL) {
		return PNG(res, res);
	}
	PNG decompressed(res, res);
	for (int i = 0; i<res; i++) {
		for (int j = 0; j<res; j++) {
			*decompressed(i,j) = getPixel(i, j);
		}
	}
	return decompressed;
}

void Quadtree::clockwiseRotate() {
	if (root == NULL) {
		return;
	}
	clockwiseRotate(root);
}

void Quadtree::clockwiseRotate(QuadtreeNode* &node) {
	if (node->isLeaf()) {
		return;
	}

	QuadtreeNode* tempSE = node->seChild;
	QuadtreeNode* tempSW = node->swChild;
	QuadtreeNode* tempNE = node->neChild;
	QuadtreeNode* tempNW = node->nwChild;
	
	node->swChild = tempSE;
	node->nwChild = tempSW;
	node->seChild = tempNE;
	node->neChild = tempNW;
	
	clockwiseRotate(node->neChild);
	clockwiseRotate(node->seChild);
	clockwiseRotate(node->swChild);
	clockwiseRotate(node->nwChild);

}

void Quadtree::prune(int tolerance) {
	if (root == NULL) {
		return;
	}
	prune(root, tolerance);
}

void Quadtree::prune(QuadtreeNode* &node, int tolerance) {
	if (node->isLeaf()) {
		return;
	}
	if (pruneCheck(node, node, tolerance)) {
		pruneRemove(node);
	}
	else {
		prune(node->seChild, tolerance);
		prune(node->swChild, tolerance);
		prune(node->neChild, tolerance);
		prune(node->nwChild, tolerance);
	}
	
}

void Quadtree::pruneRemove(QuadtreeNode* &node) {
	clear(node->seChild);
	clear(node->swChild);
	clear(node->neChild);
	clear(node->nwChild);
}

bool Quadtree::pruneCheck(QuadtreeNode*  const &node, QuadtreeNode* const &subnode, int tolerance) const {
	if (subnode->isLeaf()) {
		int tot = pow(node->element.red - subnode->element.red, 2);
		tot += pow(node->element.green - subnode->element.green, 2);
		tot += pow(node->element.blue - subnode->element.blue, 2);
		if (tot <= tolerance) {
			return true;
		}
		else {
			return false;
		}
	}
	bool pCheckSE = pruneCheck(node, subnode->seChild, tolerance);
	bool pCheckSW = pruneCheck(node, subnode->swChild, tolerance);
	bool pCheckNE = pruneCheck(node, subnode->neChild, tolerance);
	bool pCheckNW = pruneCheck(node, subnode->nwChild, tolerance);
	return pCheckSE && pCheckSW && pCheckNE && pCheckNW;
}

int Quadtree::pruneSize(int tolerance) const {
	if (root == NULL) {
		return 0;
	}
	return pruneSize(root, tolerance);
}

int Quadtree::pruneSize(QuadtreeNode* const &node, int tolerance) const {
	if (node == NULL) {
		return 0;
	}
	if (pruneCheck(node, node, tolerance)) {
		return 1;
	}
	else {
		return pruneSize(node->seChild, tolerance) + pruneSize(node->swChild, tolerance) + pruneSize(node->neChild, tolerance) + pruneSize(node->nwChild, tolerance);
	}
}

int Quadtree::idealPrune(int numLeaves) const {
	if (root == NULL) {
		return 0;
	}
	return idealPrune(numLeaves, 0, 195075);
}

int Quadtree::idealPrune(int numLeaves, int min, int max) const {
	int mid = (min+max)/2;
	if (min == max) {
		return mid;
	}
	//if the prunesize for the medium is smaller than the number, we need to idealprune it with a medium between min and current mid
	if (pruneSize(mid) > numLeaves) {
		return idealPrune(numLeaves, mid+1, max);
	}
	else {
		return idealPrune(numLeaves, min, mid);
	}
}