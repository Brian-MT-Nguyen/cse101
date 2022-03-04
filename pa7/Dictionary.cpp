#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

// Private Constructor -----------------------------------------------------

// Node constructor
Dictionary::Node::Node(keyType k, valType v) {
	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}

// Private Helper Functions ------------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if(R == nil) {
		return;
	}
	inOrderString(s, R->left);
	s += R->key;
	inOrderString(s, R->right);
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const {
	if(R == nil) {
		return;
	}
	s += R->key;
	preOrderString(s, R->left);
	preOrderString(s, R->right);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
	if(R == N || R == nil) {
		return;
	}
	this->setValue(R->key, R->val);
	preOrderCopy(R->left, N);
	preOrderCopy(R->right, N);
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R) {
	if(R == nil) {
		return;
	}
	postOrderDelete(R->left);
	postOrderDelete(R->right);
	delete R;
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	if(R == nil || R->key.compare(k) == 0) {
		return R;
	}
	else if(R->key.compare(k) < 0) {
		return search(R->left, k);
	}
	else if(R->key.compare(k) > 0) {
		return search(R->right, k);
	}
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R) {
	if(R == nil) {
		return nil;
	}
	Node *C = R;
	while(C->left != nil) {
		C = C->left;
	}
	return C;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R) {
	if(R == nil) {
		return nil;
	}
	Node *C = R;
	while(C->right != nil) {
		C = C->right;
	}
	return C;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findNext(Node* N) {
	if(N->right != nil) {
		return findMin(N->right);
	}
	Node *P = N->parent;
	while(P != nil && N == P->right) {
		N = P;
		P = P->parent;
	}
	return P;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N) {
	if(N->left != nil) {
		return findMax(N->left);
	}
	Node *P = N->parent;
	while(P != nil && N == P->left) {
		N = P;
		P = P->parent;
	}
	return P;
}

// Class Constructors & Destructors ----------------------------------------

Dictionary::Dictionary() {
	nil = new Node("\7", 16);
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
	// initialize empty dictionary
	nil = new Node("\7", 16);
	root = nil;
	current = nil;
	num_pairs = 0;

	// copy dictionary of D to this dictionary
	this->preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
	this->postOrderDelete(this->root);
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
	return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {

}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {

}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const {

}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {

}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {

}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {

}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {

}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {

}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {

}



