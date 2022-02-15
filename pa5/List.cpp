/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA5
 * List.cpp
 * List ADT
 *********************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x) {
	data = x;
	next = nullptr;
	prev = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
List::List() {
	frontDummy = new Node(7);
	backDummy = new Node(16);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
	// initialize empty List
	frontDummy = new Node(7);
	backDummy = new Node(16);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;

	// load elements from L to this List
	Node* N = L.backDummy->prev;
	while(N != L.frontDummy) {
		this->insertAfter(N->data);
		N = N->prev;
	}
}

// Destructor
List::~List() {
	Node *N = backDummy->prev;
	while(N != nullptr) {
		delete N->next;
		N = N->prev;
	}
	delete frontDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const {
	return num_elements;
}

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const {
	if(num_elements == 0) {
		throw std::length_error("List: front(): empty List");
	}
	return frontDummy->next->data;
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const {
	if(num_elements == 0) {
		throw std::length_error("List: back(): empty List");
	}
	return backDummy->prev->data;
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const {
	return pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const {
	if(pos_cursor == num_elements) {
		throw std::range_error("List: peekNext(): out of range");
	}
	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	if(pos_cursor == 0) {
		throw std::range_error("List: peekPrev(): out of range");
	}
	return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	Node *N = backDummy->prev->prev;
	while(N != nullptr) {
		delete N->next;
		N = N->prev;
	}
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	num_elements = 0;
	pos_cursor = 0;
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront() {
	if(num_elements == 0) {
		return;
	}
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;
	pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack() {
	if(num_elements == 0) {
		return;
	}
	beforeCursor = backDummy->prev;
	afterCursor = backDummy;
	pos_cursor = num_elements;
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
// pre: position()<length()
ListElement List::moveNext() {
	if(pos_cursor == num_elements) {
		throw std::range_error("List: moveNext(): out of range");
	}
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	pos_cursor += 1;
	return beforeCursor->data;
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
// pre: position()>0
ListElement List::movePrev() {
	if(pos_cursor == 0) {
		throw std::range_error("List: movePrev(): out of range");
	}
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor->prev;
	pos_cursor -= 1;
	return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x) {
	Node *N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements += 1;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x) {
	Node *N = new Node(x);
	N->prev = beforeCursor;
	N->next = afterCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	pos_cursor += 1;
	num_elements += 1;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x) {
	if(pos_cursor == num_elements) {
		throw std::range_error("List: setAfter(): out of range");
	}
	afterCursor->data = x;
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x) {
	if(pos_cursor == 0) {
		throw std::range_error("List: setBefore(): out of range");
	}
	beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter() {
	if(pos_cursor == num_elements) {
		throw std::range_error("List: eraseAfter(): out of range");
	}
	beforeCursor->next = afterCursor->next;
	afterCursor->next->prev = beforeCursor;
	delete afterCursor;
	afterCursor = beforeCursor->next;
	num_elements -= 1;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore() {
	if(pos_cursor == 0) {
		throw std::range_error("List: eraseBefore(): out of range");
	}
	afterCursor->prev = beforeCursor->prev;
	beforeCursor->prev->next = afterCursor;
	delete beforeCursor;
	beforeCursor = afterCursor->prev;
	num_elements -= 1;
	pos_cursor -= 1;
}

// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position length(), and returns -1.
int List::findNext(ListElement x) {
	int found = -1;
	while (afterCursor != backDummy) {
		if(moveNext() == x) {
			found = pos_cursor;
			break;
		}
	}
	return found;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor
// at position 0, and returns -1.
int List::findPrev(ListElement x) {
	int found = -1;
	while (beforeCursor != frontDummy) {
		if(movePrev() == x) {
			found = pos_cursor;
			break;
		}
	}
	return found;
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() {
	Node *S = frontDummy->next;
	Node *D;
	bool stillBefore;
	bool nowAfter = false;
	while(S != backDummy) {
		D = S;
		stillBefore = true;
		if(S == afterCursor) {
			nowAfter = true;
		}
		while(D->next != backDummy) {
			if(D->next->data == S->data) {
				if(stillBefore == true && nowAfter == false) {
					if(D->next == beforeCursor) {
						beforeCursor = beforeCursor->prev;
						stillBefore = false;
					}
					pos_cursor -= 1;
				}
				if(D->next == afterCursor) {
					afterCursor = afterCursor->next;
				}
				Node *DEL = D->next;
				D->next->next->prev = D;
				D->next = D->next->next;
				delete DEL;
				num_elements -= 1;
			}
			else {
				if(D->next == beforeCursor) {
					stillBefore = false;
				}
				D = D->next;
			}
		}
		S = S->next;
	}
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const {
	List K;
	Node *T = this->frontDummy->next;
	Node *N = L.frontDummy->next;
	while(T != this->backDummy) {
		K.insertBefore(T->data);
		T = T->next;
	}
	while(N != L.backDummy) {
		K.insertBefore(N->data);
		N = N->next;
	}
	K.moveFront();
	return K;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const {
	Node *N = nullptr;
	std::string s = "(";
	for(N = frontDummy->next; N != backDummy->prev; N = N->next){
		s += std::to_string(N->data)+ ", ";
	}
	s += std::to_string(N->data)+ ")";
	return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const {
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = (this->num_elements == R.num_elements);
	N = this->frontDummy->next;
	M = R.frontDummy->next;
	while(eq && N != backDummy){
		eq = (N->data == M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) {
	return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ) {
	return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ) {
	if( this != &L ){ // not self assignment
		// make a copy of L
  		List temp = L;

		// then swap the copy's fields with fields of this
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
	}

	   // return this with the new data installed
	   return *this;
}
