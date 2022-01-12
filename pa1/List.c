#include "List.h"
#include <stdio.h>
#include <stdbool.h>

// structs --------------------------------------------------------------------
// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
	int data;
	Node prev;
	Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj {
	Node front;
	Node cursor;
	Node back;
	int index;
	int length;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes prev, next, and data
// fields.
Node newNode(int data)
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->prev = NULL;
	N->next = NULL;
	return (N);
}

// freeNode()
// Frees all heap memory pointed to by *pN
void freeNode(Node* pN)
{
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Returns reference to new empty List object.
List newList(void)
{
	List L = malloc(sizeof(List));
	L->front = NULL;
	L->cursor = NULL;
	L->back = NULL;
	L->index = -1;
	L->length = 0;
	return (L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL)
{
	if (pL != NULL && *pL != NULL) {
		if (length(*pL) > 0) {
			clear(*pL);
		}
		free(*pL);
		*pQ = NULL;
	}
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L
int length(List L) {
	if(L == NULL) {
		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
      		exit(EXIT_FAILURE);
   	}
	return (L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L) {
	if(L == NULL) {
        	fprintf(stderr, "List Error: calling index() on NULL List reference\n");
                exit(EXIT_FAILURE);
	}
	return (L->index);
}

// front()
// Returns front element of L
// Pre: length()>0
int front(List L) {
	if(L == NULL) {
        	fprintf(stderr, "List Error: calling front() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling front() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->front->data);
}

// back()
// Returns back element of L
// Pre: length()>0
int back(List L) {
	if(L == NULL) {
                fprintf(stderr, "List Error: calling back() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling back() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->back->data);
}

// get()
// Returns cursor element of L
// Pre: length()>0, index()>=0
int get(List L) {
	if(L == NULL) {
                fprintf(stderr, "List Error: calling get() on NULL List reference\n");
                exit(EXIT_FAILURE);
        }
	if (length(L) == 0) {
		fprintf(stderr, "List Error: calling get() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) == -1) {
		fprintf(stderr, "List Error: calling get() with undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	return (L->cursor->data);
}

// equals()
// Returns true iff Lists A and B are in same state, and returns false otherwise
bool equals(List A, List B) {
	if(A == NULL || B == NULL) {
		fprintf(stderr, "List Error: calling equals() on at least one NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node tempA = A->front;
	Node tempB = B->front;
	while (tempA != NULL && tempB != NULL) {
		if (tempA->data != tempB->data) {
			return false;
		}
		tempA = A->next;
		tempB = B->next;
	}
	return (tempA == NULL && tempB == NULL);
}
