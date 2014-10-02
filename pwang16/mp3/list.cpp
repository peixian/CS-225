/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
	ListNode * removed = tail;
	while (removed != NULL) 
	{
	    tail = tail->prev;
	    delete removed;
	    removed = tail;
	    length--;
	}
	tail = NULL;
	head = NULL;
	removed = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    ListNode *node;
    node = new ListNode(ndata);
    node->next = head;
    if (head != NULL) {
         head->prev = node;
    }
    else {
        tail = node;
    }
    head = node;
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
  ListNode* node;
  node = new ListNode(ndata);
  if (tail != NULL) {
     tail->next = node;
     node->prev = tail;
  }
  else {
    head = node;
  }
  tail = node;
  length++;
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    //default cases if the input is bad
    if (length == 0 || startPoint == NULL || endPoint == NULL)
        return;

    //temporary variables set to be used later. tempBefore and tempAfter are there to reanchor our list after we futz around with it
    ListNode * temp = NULL;
    ListNode * tempBefore = NULL;
    ListNode * tempAfter = NULL;

    //finds the previous and next pointers around the blocked that needs to be reversed, and nulls them
    if (startPoint->prev != NULL) {
        tempBefore = startPoint->prev;
        tempBefore->next = NULL;
        startPoint->prev = NULL;
    }
    if (endPoint->next != NULL) {
        tempAfter = endPoint->next;
        tempAfter->prev = NULL;
        endPoint->next = NULL;
    }

    //makes a temp variable that clones the start point, then goes from each one (we set the previous node to the next node, then set the next node to the previous node)
    //then sets the temp variable to the "next" (node that's been already reversed)
    ListNode * tempMove = startPoint;
    while (tempMove != NULL && tempMove != endPoint->next) {
        
        temp = tempMove->prev;
        tempMove->prev = tempMove->next;
        tempMove->next = temp;
        tempMove = tempMove->prev;
    
    }
    
    //swaps the startpoint and end point with a temp variable
    temp = endPoint;
    endPoint = startPoint;
    startPoint = temp;

    //if reverse function didn't get called over the entire List, we need to set the previous and end points back to where they were orginally
    if (tempBefore != NULL) {
        startPoint->prev = tempBefore;
        tempBefore->next = startPoint;
    }

    if (tempAfter != NULL) {
        tempAfter->prev = endPoint;
        endPoint->next = tempAfter;
    }
    
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    //this function is dukkha overload

    //initates the start and end of the search blocks
    if (head == NULL || tail == NULL || length == 0) 
        return;
    if (n > length) {
        reverse(head, tail);
        return;
    }

    //creates the start and end of the nodes to be reversed
    ListNode * start = head;
    ListNode * end = head;

    //since we're going to go through the entire list anyways, we'll just stop at the tail
    while(end->next != NULL) {
        //finds the next block to be reversed, we use n-1 since we're starting from 0 and n starts from 1
        for (int i = 0; i<n-1; i++) {
            if (end->next != NULL) {
                end = end->next;
            }
        }
        reverse(start, end);
        //MOVE TO THE NEXT BLOCK YOU DUMBASS (allows the stupid thing to actually move forward)
        if (end->next != NULL) {
            end = end->next;
            start = end; 
        }
    } 

    //once done, we need to actually reset the head and tail, these loop through it and find it
    while(head->prev != NULL) {
        head = head->prev;
    }
    while (tail->next != NULL) {
        tail = tail->next;
    }

}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    if (head == NULL || tail == NULL || length == 1)
        return;
    ListNode * temp = head;
    ListNode * tempBefore = NULL;
    ListNode * tempAfter = NULL;
    while (temp->next != tail) {
            tempBefore = temp;


            temp = temp->next;
            tempAfter = temp->next;
            
            temp->next = NULL;
            temp->prev = NULL;

            tail->next = temp;
            temp->prev = tail;

            tempBefore->next = tempAfter;
            tempAfter->prev = tempBefore;
        tail = tail->next;
        temp = tempAfter;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    if (length == 0 || splitPoint == 0) {
        return start;
    }
    ListNode * temp = start;
    ListNode * nextTemp;
    for (int i = 0; i<splitPoint; i++) {
        temp = temp->next;
    }

    nextTemp = temp->prev;
    temp->prev = NULL;
    nextTemp->next = NULL;
    return temp;

}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    if (first == NULL || second == NULL) {
        if (first == NULL) {
            return second;
        }
        else 
            return first;
    }
    ListNode * temp = first;
    if (first->data < second->data) {
        first = first->next;
    }
    else {
        temp = second;
        second = second->next;
    }
    while (first != NULL && second != NULL) {
        if (first->data < second->data) {
            temp->next = first;
            first->prev = temp;
            first = first->next;
        }
        else {
            temp->next = second;
            second->prev = temp;
            second = second->next;
        }
        temp = temp->next;
    }
    if (first == NULL) {
        temp->next = second;
        second->prev = temp;
    }
    if (second == NULL) {
        temp->next = first;
        first->prev = temp;
    }
    while (temp->prev != NULL) {
        temp = temp->prev;
    }
    return temp;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    if (chainLength <= 1) {
        return start;
    }
    ListNode * tempStart1 = start;
    ListNode * tempStart2 = split(start, chainLength/2);
    ListNode * array1 = mergesort(tempStart1, chainLength/2);
    ListNode * array2 = mergesort(tempStart2, chainLength - chainLength/2);
    return merge(array1, array2);
}
