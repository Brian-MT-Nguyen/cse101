/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA4
 * ListTest.c
 * Test Client for List ADT
 *********************************************************************************/
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  // Testing Constructors
  fprintf(stdout, "Testing Construction of List: newList() and Empty index() & "
                  "length():\n");
  List A = newList();
  List B = newList();

  fprintf(stdout,
          "Used newList()...\nindex(): %d | Expected Value: -1\nlength(): %d | "
          "Expected Value: 0\n",
          index(A), length(B));
  fprintf(stdout, "\n");

  char X[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
              'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

  // Testing Append to List A
  fprintf(stdout, "Testing append() with char array data type:\n");
  for (int i = 0; i <= 25; i++) {
    append(A, &X[i]);
  }

  // Printing List A from front to back
  fprintf(stdout, "Testing moveFront(), moveNext(), Non-empty index(), and "
                  "get() by Printing List A: (Expected Result = full alphabet "
                  "a-z)\n");
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    fprintf(stdout, "%c ", *(char *)get(A));
  }
  fprintf(stdout, "\n\n");

  // Testing Prepend to List B
  fprintf(stdout, "Testing prepend() with same alphabet array:\n");
  for (int i = 0; i <= 25; i++) {
    prepend(B, &X[i]);
  }
  fprintf(stdout, "Printing List B: (Expected Result = full alphabet z-a)\n");
  for (moveFront(B); index(B) >= 0; moveNext(B)) {
    fprintf(stdout, "%c ", *(char *)get(B));
  }
  fprintf(stdout, "\n\n");

  // Printing both Lists from back to front
  fprintf(stdout, "Testing moveBack() by Printing Lists from back to front: "
                  "(Expected Result is z-a and a-z respectively)\n");
  for (moveBack(A); index(A) >= 0; movePrev(A)) {
    fprintf(stdout, "%c ", *(char *)get(A));
  }
  fprintf(stdout, "\n");
  for (moveBack(B); index(B) >= 0; movePrev(B)) {
    fprintf(stdout, "%c ", *(char *)get(B));
  }
  fprintf(stdout, "\n\n");

  // Testing deleteFront(), deleteBack(), delete()
  fprintf(stdout, "Testing deleteFront(), deleteBack(), and delete() from List "
                  "A: (Expected Result: p)\n");
  deleteFront(A);
  deleteBack(A);
  for (int i = 0; i < 14; i++) {
    moveFront(A);
    delete (A);
  }
  for (int i = 0; i < 9; i++) {
    moveFront(A);
    moveNext(A);
    delete (A);
  }
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    fprintf(stdout, "%c ", *(char *)get(A));
  }
  fprintf(stdout, "\n\n");

  // Testing InsertBefore and InsertAfter
  fprintf(stdout, "Testing insertBefore() and insertAfter() with List A: "
                  "(Expected Result: p u s h p b r o)\n");
  moveBack(A);
  insertBefore(A, &X[15]);
  insertBefore(A, &X[20]);
  insertBefore(A, &X[18]);
  insertBefore(A, &X[7]);
  moveBack(A);
  insertAfter(A, &X[14]);
  insertAfter(A, &X[17]);
  insertAfter(A, &X[1]);
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    fprintf(stdout, "%c ", *(char *)get(A));
  }
  fprintf(stdout, "\n\n");

  // Testing set()
  moveFront(B);
  set(B, &X[1]);
  fprintf(stdout, "Testing set() with List B: (Expected Result: b)\n");
  fprintf(stdout, "%c ", *(char *)get(B));
  fprintf(stdout, "\n\n");

  // Test freeList()
  fprintf(stdout, "Testing freeList() Check Valgrind\n");
  freeList(&A);
  freeList(&B);
  return (EXIT_SUCCESS);
}
