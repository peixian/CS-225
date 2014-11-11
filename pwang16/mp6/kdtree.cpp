/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    if (curDim > Dim) {
    	return false;
    }
	if (second[curDim] == first[curDim]) {
		return (first > second);
	}
	else {
		return second[curDim] > first[curDim];
	}
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    //REMEMBER TO MAKE THAT EUCLIDIAN DISTANCE FUNCTION AND CALL THAT
	//check the distance between the target and potential
	
	//check the distance between currentBest and potenial
	
	//if they're the same, break the tie (aka return) with potential < currentBest
	
	
    return false;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	//build root first
    //build with recursive helper functions
	//probably want to make a buildTree function
	//watch out for recursive functions's with ###
	
	//###findMedian() to get the two split dimensions
	//call the findMedian function until we split to nothing
	//###splitfunction
	
	//even number of points => median goes to left
	
	//store it in the vector points (neatly a vector of points)
	
	//recur with build after splitting is done to add in the points
	//recur needs to be done with (currentDimension + 1) % k
	
}

//probably want to  make the stupid quickselect fxn
/*
	on a vector of {7,3,4,1,9}
	quickSelect(2) =>
		gets 3rd (index value) element of the array => 4
		then puts everything smaller on the left, and everything bigger on the right
		hence => {3,1,4,9,7}
	Quickselect = Select + Partition
	
	Partition = partition(int pivotIndex)
		pull out the element at pivotIndex from the array
		then put everything smaller on the left iterating through the array =>=> for everything from 0 to pivotIndex and for everyhing from pivotIndex + 1 to size
			swap the pivot(median) and the first element of the array
			keep a counter for how many swaps occur to denote the position of where the next swap should go (aka start with swapPosition = 1)
			iterate through the indexes 1 to end, and if the the point i is smaller than the value (use smallerDimVal) swap them and increase the counter
			then swap back index 0 and first element
			*NOTE*: We're not actually recuring because the select will be doing that

	Select = select(left, right, K) 
		basically a binary search for K
		set the medium equal to (high + low)/2
		get the pivotIndex after sorting
		if the pivotIndex is equal to K, return it
		else we're gonna have to do some recurring
			(binary search time)
			if (mid < pivotIndex); the thing is on the left side
			else the thing is on the right side of the array
	
	Swap = swap(int a, int b)
		change the pointers you fucktard 
*/

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
   return Point<Dim>();
}
