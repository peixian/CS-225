/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K & key) const
{
	return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node * subtree, const K & key) const
{
	if (subtree == NULL)
		return V();
	else if (key == subtree->key)
		return subtree->value;
	else
	{
		if (key < subtree->key)
			return find(subtree->left, key);
		else
			return find(subtree->right, key);
	}
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	Node* n = t;
	t = t->right;
	n->right = t->left;
	t->left = n;
	
	n->height = max(heightOrNeg1(n->left), heightOrNeg1(n->right)) + 1;
	t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
	
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	// Implemented for you:
	rotateLeft(t->left);
	rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
	
	Node* n = t;
	t = t->left;
	n->left = t->right;
	t->right = n;
	
	n->height = max(heightOrNeg1(n->left), heightOrNeg1(n->right)) + 1;
	t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node * & t)
{
	*_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
	insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node* & subtree, const K & key, const V & value)
{
	if (subtree == NULL) {
		subtree = new Node(key, value);
		subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
		return;
	}
	
	//goes to the left
	if (key <= subtree->key) {
		insert(subtree->left, key, value);
		insertCheck(subtree, 0);
	}
	//goes to the right 
	else if (key > subtree->key){
		insert(subtree->right, key, value);
		insertCheck(subtree, 1);
	}
	subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}
//0 for left , 1 for right
template <class K, class V>
void AVLTree<K, V>::insertCheck(Node* & subtree, int side) {
	int difference  = heightOrNeg1(subtree->left) - heightOrNeg1(subtree->right);
	subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
	if (side == 0) {
		int innerDifference = heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->left->right);
		if (difference == 2) {
			if (innerDifference == 1) {
				rotateRight(subtree);
			}
			else {
				rotateLeftRight(subtree);
			}
		}
	}
	else if (side == 1) {
		int innerDifference = heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->right->right);
		if (difference == -2) {
//			std::cout << diff << std::endl;
			if (innerDifference == -1) {
				rotateLeft(subtree);
			}
			else {
				rotateRightLeft(subtree);
			}
		}
	}
}
