/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA4
 * Matrix.c
 * Matrix ADT
 *********************************************************************************/
#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// Structs

// private Entry type
typedef struct EntryObj *Entry;

// private EntryObj type
typedef struct EntryObj {
  int column;
  double value;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj {
  List *rows;
  int size;
  int nnz;
} MatrixObj;

// Constructors-Destructors

// newEntry()
// Returns reference to new Entry object. Initializes column and value fields.
Entry newEntry(int column, double value) {
  Entry E = malloc(sizeof(EntryObj));
  E->column = column;
  E->value = value;
  return (E);
}

// freeEntry()
// Frees all heap memory pointed to by *pE.
void freeEntry(Entry *pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    *pE = NULL;
  }
}

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));
  M->rows = (List *)calloc(n + 1, sizeof(List *));
  for (int i = 1; i <= n; i++) {
    M->rows[i] = newList();
  }
  M->size = 0;
  M->nnz = 0;
  return (M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM) {
  for (int i = 1; i <= (*pM)->size; i++) {
    for (moveFront((*pM)->rows[i]); index((*pM)->rows[i]) >= 0; moveNext((*pM)->rows[i])) {
      freeEntry(get((*pM)->rows[i]));
    }
    freeList(&(*pM)->rows[i]);
    (*pM)->rows[i] = NULL;
  }
  free((*pM)->rows);
  (*pM)->rows = NULL;

  free(*pM);
  *pM = NULL;
}

// Access functions

// size()
// Return the size of square Matrix M.
int size(Matrix M) {
  if (M == NULL) {
    fprintf(stderr,
            "Matrix Error: calling size() with NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return (M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
  if (M == NULL) {
    fprintf(stderr, "Matrix Error: calling NNZ() with NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return (M->nnz);
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Matrix Error: calling equals() with at least one NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }

  if ((A->size != B->size) || (A->nnz != B->nnz)) {
      return 0;
  }

  for (int i = 1; i <= A->size; i++) {
      moveFront(A->rows[i]);
      moveFront(B->rows[i]);
      while(index(A->rows[i]) >= 0) {
          if(get(A->rows[i]) != get(B->rows[i])) {
              return 0;
          }
          moveNext(A->rows[i]);
          moveNext(B->rows[i]);
      }
  }
  return 1;
}

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M);

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x);

// Matrix Arithmetic operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A);

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A);

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A);

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE *out, Matrix M);
