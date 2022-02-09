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
	frontDummy = nullptr;
	backDummy = nullptr;
	beforeCursor = nullptr;
	afterCursor = nullptr;
	pos_cursor = 0;
	num_elements = 0;
}

// Copy constructor.
List::List(const List& L) {
	// initialize empty List
	frontDummy = nullptr;
	backDummy = nullptr;
	beforeCursor = nullptr;
	afterCursor = nullptr;
	pos_cursor = 0;
	num_elements = 0;

	// load elements from L to this List
	Node* N = L.back;
	while(N != nullptr) {
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
