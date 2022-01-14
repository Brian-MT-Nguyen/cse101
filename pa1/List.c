#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
// Returns reference to new Node object. Initializes prev, next, and data fields.
Node newNode(int data)
{
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->prev = NULL;
	N->next = NULL;
	return (N);
}

// freeNode()
// Frees all heap memory pointed to by *pN.
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
	List L = malloc(sizeof(ListObj));
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
		*pL = NULL;
	}
}

// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling length() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling index() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	return (L->index);
}

// front()
// Returns front element of L.
// Pre: length()>0
int front(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling front() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling front() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->front->data);
}

// back()
// Returns back element of L.
// Pre: length()>0
int back(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling back() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling back() on empty List\n");
		exit(EXIT_FAILURE);
	}
	return (L->back->data);
}

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling get() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling get() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1) {
		fprintf(stderr, "List Error: calling get() with undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	return (L->cursor->data);
}

// equals()
// Returns true iff Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B)
{
	if (A == NULL || B == NULL) {
		fprintf(stderr, "List Error: calling equals() on at least one NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node tempA = A->front;
	Node tempB = B->front;
	while (tempA != NULL && tempB != NULL) {
		if (tempA->data != tempB->data) {
			return false;
		}
		tempA = tempA->next;
		tempB = tempB->next;
	}
	return (tempA == NULL && tempB == NULL);
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	while (L->front != NULL) {
		deleteFront(L);
	}
	L->length = 0;
	L->index = -1;
}

// set()
// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, int x)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling set() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling set() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1) {
		fprintf(stderr, "List Error: calling set() with undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	L->cursor->data = x;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		return;
	}
	L->cursor = L->front;
	L->index = 0;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		return;
	}
	L->cursor = L->back;
	L->index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing.
void movePrev(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling movePrev() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		return;
	}
	if (L->index == 0) {
		L->cursor = NULL;
		L->index -= 1;
	} else {
		L->cursor = L->cursor->prev;
		L->index -= 1;
	}
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing.
void moveNext(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == NULL) {
		return;
	}
	if (L->index == (L->length - 1)) {
		L->cursor = NULL;
		L->index = -1;
	} else {
		L->cursor = L->cursor->next;
		L->index += 1;
	}
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		Node N = newNode(x);
		L->front = N;
		L->back = N;
		L->length += 1;
	} else {
		Node N = newNode(x);
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
		if (L->index >= 0) {
			L->index += 1;
		}
		L->length += 1;
	}
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, int x)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling append() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		Node N = newNode(x);
		L->front = N;
		L->back = N;
		L->length += 1;
	} else {
		Node N = newNode(x);
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
		L->length += 1;
	}
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int x)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling insertBefore() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1) {
		fprintf(stderr, "List Error: calling insertBefore() with undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == 0) {
		prepend(L, x);
	} else {
		Node N = newNode(x);
		N->next = L->cursor;
		N->prev = L->cursor->prev;
		L->cursor->prev->next = N;
		L->cursor->prev = N;
		L->index += 1;
		L->length += 1;
	}
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int x)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling insertAfter() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1) {
		fprintf(stderr, "List Error: calling insertAfter() with undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == (L->length - 1)) {
		append(L, x);
	} else {
		Node N = newNode(x);
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next->prev = N;
		L->cursor->next = N;
		L->length += 1;
	}
}

// deleteFront()
// Delete the front element.
// Pre: length()>0
void deleteFront(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling deleteFront() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 1) {
		freeNode(&L->front);
		L->front = NULL;
		L->cursor = NULL;
		L->back = NULL;
		L->index = -1;
		L->length -= 1;
	} else {
		L->front = L->front->next;
		freeNode(&L->front->prev);
		L->index -= 1;
		L->length -= 1;
	}
}

// deleteBack()
// Delete the back element.
// Pre: length()>0
void deleteBack(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling deleteBack() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 1) {
		freeNode(&L->back);
		L->front = NULL;
		L->cursor = NULL;
		L->back = NULL;
		L->index = -1;
		L->length -= 1;
	} else {
		L->back = L->back->prev;
		freeNode(&L->back->next);
		L->length -= 1;
		if (L->index == L->length) {
			L->cursor = NULL;
			L->index = -1;
		}
	}
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete (List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	if (L->length == 0) {
		fprintf(stderr, "List Error: calling delete() on empty List\n");
		exit(EXIT_FAILURE);
	}
	if (L->index == -1) {
		fprintf(stderr, "List Error: calling delete() with undefined cursor.");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->front) {
		deleteFront(L);
	} else if (L->cursor == L->back) {
		deleteBack(L);
	} else {
		L->cursor->prev->next = L->cursor->next;
		L->cursor->next->prev = L->cursor->prev;
		freeNode(&L->cursor);
		L->cursor = NULL;
		L->index = -1;
		L->length -= 1;
	}
}

// Other operations -----------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	Node tempL = L->front;
	while (tempL != NULL) {
		fprintf(out, "%d ", tempL->data);
		tempL = tempL->next;
	}
}

// copyList()
// Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L)
{
	if (L == NULL) {
		fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
		exit(EXIT_FAILURE);
	}
	List nL = newList();
	Node tempL = L->front;
	while (tempL != NULL) {
		append(nL, tempL->data);
		tempL = tempL->next;
	}
	return (nL);
}
