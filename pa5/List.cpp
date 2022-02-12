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
	beforeCursor = nullptr;
	afterCursor = nullptr;
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
	beforeCursor = nullptr;
	afterCursor = nullptr;
	pos_cursor = 0;
	num_elements = 0;

	// load elements from L to this List
	Node* N = L.backDummy->prev;
	while(N != frontDummy) {
		this->insertAfter(N->data);
		N = N->prev;
	}
}

// Destructor
List::~List() {
	moveFront();
	while(num_elements > 0) {
		eraseAfter();
	}
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
		throw std::length_error("List: peekNext(): out of range");
	}
	return afterCursor->data;
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const {
	if(pos_cursor == 0) {
		throw std::length_error("List: peekPrev(): out of range");
	}
	return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear() {
	Node *N = backDummy->prev;
	while(N != frontDummy) {
		delete N;
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
		throw std::length_error("List: moveNext(): out of range");
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
		throw std::length_error("List: movePrev(): out of range");
	}
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor->prev;
	pos_cursor -= 1;
	return afterCursor->data;
}

// insertAfter()
// Inserts x after cursor.
