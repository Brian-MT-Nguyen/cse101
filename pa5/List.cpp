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
	beforeCursor = nullptr;
	afterCursor = nullptr;
	pos_cursor = 0;
	num_elements = 0;

	// load elements from L to this List
	Node* N = L.backDummy;
	while(N != frontDummy) {
		N = N->prev;
		this->insertAfter(N->data);
	}
}

// Destructor
List::~List() {
	moveFront();
	while(num_elements > 0) {
		eraseAfter();
	}
}
