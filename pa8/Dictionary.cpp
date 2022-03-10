/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA8
 * Dictionary.cpp
 * Dictionary ADT
 *********************************************************************************/
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
	color = 0;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const {
	if(R == nil) {
		return;
	}
	inOrderString(s, R->left);
	s += R->key + " : " + std::to_string(R->val) + "\n";
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
	s += R->key + "\n";
	preOrderString(s, R->left);
	preOrderString(s, R->right);
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N) {
	if((R == N) || (R == nil)) {
		return;
	}
	setValue(R->key, R->val);
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
	if((R == nil) || (R->key.compare(k) == 0)) {
		return R;
	}
	else if(R->key.compare(k) < 0) {
		return search(R->right, k);
	}
	else {
		return search(R->left, k);
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

// RBT Helper Functions (Optional) -----------------------------------------

// LeftRotate()
void Dictionary::LeftRotate(Node* N) {
	Node *Y = N->right;

	N->right = Y->left;
	if(Y->left != nil) {
		Y->left->parent = N;
	}

	Y->parent = N->parent;
	if(N->parent == nil) {
		root = Y;
	}
	else if(N == N->parent->left) {
		N->parent->left = Y;
	}
	else {
		N->parent->right = Y;
	}

	Y->left = N;
	N->parent = Y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N) {
	Node *Y = N->left;

	N->left = Y->right;
	if(Y->right != nil) {
		Y->right->parent = N;
	}

	Y->parent = N->parent;
	if(N->parent == nil) {
		root = Y;
	}
	else if(N == N->parent->right) {
		N->parent->right = Y;
	}
	else {
		N->parent->left = Y;
	}

	Y->right = N;
	N->parent = Y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N) {
	while(N->parent->color == 0) {
		if(N->parent == N->parent->parent->left) {
			Node *Y = N->parent->parent->right;
			if(Y->color == 0) {
				N->parent->color = 1;
				Y->color = 1;
				N->parent->parent->color = 0;
				N = N->parent->parent;
			}
			else {
				if(N == N->parent->right) {
					N = N->parent;
					LeftRotate(N);
				}
				N->parent->color = 1;
				N->parent->parent->color = 0;
				RightRotate(N->parent->parent);
			}
		}
		else {
			Node *Y = N->parent->parent->left;
			if(Y->color == 0) {
				N->parent->color = 1;
				Y->color = 1;
				N->parent->parent->color = 0;
				N = N->parent->parent;
			}
			else {
				if(N == N->parent->left) {
					N = N->parent;
					RightRotate(N);
				}
				N->parent->color = 1;
				N->parent->parent->color = 0;
				LeftRotate(N->parent->parent);
			}
		}
	}
	root->color = 1;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v) {
	if(u->parent == nil) {
		root = v;
	}
	else if(u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N) {
	while((N != root) && (N->color == 1)) {
		if(N == N->parent->left) {
			Node *W = N->parent->right;
			if(W->color == 0) {
				W->color = 1;
				N->parent->color = 0;
				LeftRotate(N->parent);
				W = N->parent->right;
			}
			if((W->left->color == 1) && (W->right->color == 1)) {
				W->color = 0;
				N = N->parent;
			}
			else {
				if(W->right->color == 1) {
					W->left->color = 1;
					W->color = 0;
					RightRotate(W);
					W = N->parent->right;
				}
				W->color = N->parent->color;
				N->parent->color = 1;
				W->right->color = 1;
				LeftRotate(N->parent);
				N = root;
			}
		}
		else {
			Node *W = N->parent->left;
			if(W->color == 0) {
				W->color = 1;
				N->parent->color = 0;
				RightRotate(N->parent);
				W = N->parent->left;
			}
			if((W->right->color == 1) && (W->left->color = 1)) {
				W->color = 0;
				N = N->parent;
			}
			else {
				if(W->left->color == 1) {
					W->right->color = 1;
					W->color = 0;
					LeftRotate(W);
					W = N->parent->left;
				}
				W->color = N->parent->color;
				N->parent->color = 1;
				W->left->color = 1;
				RightRotate(N->parent);
				N = root;
			}
		}
	}
	N->color = 1;
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N) {
	Node *Y = N;
	int y_og_color = Y->color;
	Node *X;
	if(N->left == nil) {
		X = N->right;
		RB_Transplant(N, N->right);
	}
	else if(N->right == nil) {
		X = N->left;
		RB_Transplant(N, N->left);
	}
	else {
		Y = findMin(N->right);
		y_og_color = Y->color;
		X = Y->right;
		if(Y->parent == N) {
			X->parent = Y;
		}
		else {
			RB_Transplant(Y, Y->right);
			Y->right = N->right;
			Y->right->parent = Y;
		}
		RB_Transplant(N, Y);
		Y->left = N->left;
		Y->left->parent = Y;
		Y->color = N->color;
	}
	if(y_og_color == 1) {
		RB_DeleteFixUp(X);
	}
}

// Class Constructors & Destructors ----------------------------------------

Dictionary::Dictionary() {
	nil = new Node("\7", 16);
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	nil->color = 1;
	root = nil;
	current = nil;
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) {
	// initialize empty dictionary
	nil = new Node("\7", 16);
	nil->left = nil;
	nil->right = nil;
	nil->parent = nil;
	nil->color = 1;
	root = nil;
	current = nil;
	num_pairs = 0;

	// copy dictionary of D to this dictionary
	preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() {
	postOrderDelete(root);
	delete nil;
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
	Node *S = search(root, k);
	return (S != nil);
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
	Node *S = search(root, k);
	if(S == nil) {
		throw std::logic_error("Dictionary: getValue(): key \""+ k +"\" does not exist");
	}
	return S->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false
// otherwise.
bool Dictionary::hasCurrent() const {
	return (current != nil);
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent()
keyType Dictionary::currentKey() const {
	if(current == nil) {
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	return current->key;
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
	if(current == nil) {
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	}
	return current->val;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
	postOrderDelete(root);
	current = nil;
	root = nil;
	num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v,
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
	Node *Y = nil;
	Node *X = root;
	while(X != nil) {
		Y = X;
		if(k.compare(X->key) < 0) {
			X = X->left;
		}
		else if(k.compare(X->key) == 0) {
			X->val = v;
			return;
		}
		else {
			X = X->right;
		}
	}
	Node *Z = new Node(k, v);
	Z->parent = Y;
	num_pairs += 1;
	if(Y == nil) {
		root = Z;
	}
	else if(Z->key.compare(Y->key) < 0) {
		Y->left = Z;
	}
	else {
		Y->right = Z;
	}
	Z->left = nil;
	Z->right = nil;
	Z->color = 0;
	RB_InsertFixUp(Z);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
	Node *S = search(root, k);
	if(S == nil) {
		throw std::logic_error("Dictionary: remove(): key \""+ k +"\" does not exist");
	}
	if(current == S) {
		current = nil;
	}
	RB_Delete(S);
	delete S;
	num_pairs -= 1;
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::begin() {
	if(num_pairs == 0) {
		return;
	}
	current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing.
void Dictionary::end() {
	if(num_pairs == 0) {
		return;
	}
	current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current
// to the next pair (as defined by the order operator < on keys). If
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
	if(current == nil) {
		throw std::logic_error("Dictionary: next(): current undefined");
	}
	current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to
// the previous pair (as defined by the order operator < on keys). If
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
	if(current == nil) {
		throw std::logic_error("Dictionary: prev(): current undefined");
	}
	current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value
// are separated by the sequence space-colon-space " : ". The pairs are arranged
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
	std::string s;
	inOrderString(s, root);
	return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const {
	std::string s;
	preOrderString(s, root);
	return s;
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
	return ((this->pre_string() == D.pre_string()) && this->to_string() == D.to_string());
}

// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
	return stream << D.Dictionary::to_string();
}


// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals().
bool operator==( const Dictionary& A, const Dictionary& B ) {
	return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
	if(this != &D) {
		Dictionary temp = D;

		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	}
	return *this;
}
