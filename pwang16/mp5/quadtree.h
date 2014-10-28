// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"
#include <vector>
class Quadtree
{
	public:
	
		Quadtree();
		
		Quadtree(const PNG &source, int resolution);
		
		Quadtree(Quadtree const &other);
		
		~Quadtree();
		
		Quadtree const& operator=(Quadtree const &other);
		
		void buildTree(PNG const &source, int resolution);
		
		RGBAPixel getPixel(int x, int y) const;
		
		PNG decompress() const;
		
		void clockwiseRotate();
		
		void prune(int tolerance);
		
		int pruneSize(int tolerance) const;
		
		int idealPrune(int numLeaves) const;
		
		
	
	
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
		class QuadtreeNode
		{
			public:
			QuadtreeNode* nwChild;  // pointer to northwest child
			QuadtreeNode* neChild;  // pointer to northeast child
			QuadtreeNode* swChild;  // pointer to southwest child
			QuadtreeNode* seChild;  // pointer to southeast child
    	
			RGBAPixel element;  // the pixel stored as this node's "data"
			
			QuadtreeNode(RGBAPixel &pixel) {
				element = pixel;
				nwChild = NULL;
				neChild = NULL;
				swChild = NULL;
				seChild = NULL;
			}
			
			QuadtreeNode() {
				nwChild = NULL;
				neChild = NULL;
				swChild = NULL;
				seChild = NULL;
			}
			
			bool isLeaf() const {
				if (nwChild == NULL && neChild == NULL && swChild == NULL && seChild == NULL) {
					return true;
				}
				return false;
			}
			
		};
		
		void buildTree(PNG const &source, int resolution, int x, int y, QuadtreeNode* &leaves);
		
		std::vector<int> average(QuadtreeNode* node);
		
		RGBAPixel getPixel(QuadtreeNode* leaves, int x, int y, int resolution) const;
		
		void clear();

		void copy(Quadtree const &other);

		void copy(QuadtreeNode* &here, QuadtreeNode* const &other);

		void clockwiseRotate(QuadtreeNode* &node);

		void clear(QuadtreeNode* &node);

		void prune(QuadtreeNode* &node, int tolerance);
		
		//clears the node
		void pruneRemove(QuadtreeNode* &node);
		
		//true if it falls within tolerance, false if it doesn'
		bool pruneCheck(QuadtreeNode* const &node, QuadtreeNode* const &subnode, int tolerance) const;
		
		int pruneSize(QuadtreeNode* const &node, int tolerance) const;
		
		int idealPrune(int numLeaves, int min, int max) const;
		
		int res;
		
		QuadtreeNode* root;    // pointer to root of quadtree		
		/**** Functions added for testing/grading                ****/
		/**** Do not remove this line or copy its contents here! ****/
		#include "quadtree_given.h"
};

#endif
