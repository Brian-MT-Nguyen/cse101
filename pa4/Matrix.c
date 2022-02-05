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
  M->size = n;
  M->nnz = 0;
  return (M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix *pM) {
  if (pM != NULL && *pM != NULL) {
    makeZero(*pM);
    for (int i = 1; i <= (*pM)->size; i++) {
      freeList(&(*pM)->rows[i]);
      (*pM)->rows[i] = NULL;
    }
    free((*pM)->rows);
    (*pM)->rows = NULL;

    free(*pM);
    *pM = NULL;
  }
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
    fprintf(stderr, "Matrix Error: calling equals() with at least one NULL "
                    "Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A == B) {
    return 1;
  }
  if ((A->size != B->size) || (A->nnz != B->nnz)) {
    return 0;
  }
  for (int i = 1; i <= A->size; i++) {
    List LA = A->rows[i];
    List LB = B->rows[i];
    moveFront(LA);
    moveFront(LB);
    while (index(LA) >= 0 && index(LB) >= 0) {
      Entry entryA = get(LA);
      Entry entryB = get(LB);
      if ((entryA->column != entryB->column) ||
          (entryA->value != entryB->value)) {
        return 0;
      }
      moveNext(LA);
      moveNext(LB);
    }
    if (index(LA) >= 0 || index(LB) >= 0) {
      return 0;
    }
  }
  return 1;
}

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
  if (M == NULL) {
    fprintf(stderr,
            "Matrix Error: calling makeZero() with NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i <= M->size; i++) {
    for (moveFront(M->rows[i]); index(M->rows[i]) >= 0; moveNext(M->rows[i])) {
      Entry E = (Entry)get(M->rows[i]);
      freeEntry(&E);
    }
    clear(M->rows[i]);
  }
  M->nnz = 0;
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
  if (M == NULL) {
    fprintf(stderr,
            "Matrix Error: calling changeEntry() with NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (i < 1 || i > M->size) {
    fprintf(stderr,
            "Matrix Error: calling changeEntry() with out of range row\n");
    exit(EXIT_FAILURE);
  }
  if (j < 1 || j > M->size) {
    fprintf(stderr,
            "Matrix Error: calling changeEntry() with out of range column\n");
    exit(EXIT_FAILURE);
  }
  moveBack(M->rows[i]);
  while ((index(M->rows[i]) >= 0) && (((Entry)get(M->rows[i]))->column > j)) {
    movePrev(M->rows[i]);
  }
  if (index(M->rows[i]) == -1) {
    if (x != 0) {
      Entry E = newEntry(j, x);
      prepend(M->rows[i], E);
      M->nnz += 1;
    }
  } else if ((((Entry)get(M->rows[i]))->column < j) && (x == 0)) {
    return;
  } else if ((((Entry)get(M->rows[i]))->column < j) && (x != 0)) {
    Entry E = newEntry(j, x);
    insertAfter(M->rows[i], E);
    M->nnz += 1;
  } else if ((((Entry)get(M->rows[i]))->column == j) && (x == 0)) {
    Entry E = (Entry)get(M->rows[i]);
    freeEntry(&E);
    delete (M->rows[i]);
    M->nnz -= 1;
  } else if ((((Entry)get(M->rows[i]))->column == j) && (x != 0)) {
    ((Entry)get(M->rows[i]))->value = x;
  }
}

// Matrix Arithmetic operations

// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
  Matrix C = newMatrix(A->size);
  for (int i = 1; i <= A->size; i++) {
    for (moveFront(A->rows[i]); index(A->rows[i]) >= 0; moveNext(A->rows[i])) {
      changeEntry(C, i, ((Entry)get(A->rows[i]))->column,
                  ((Entry)get(A->rows[i]))->value);
    }
  }
  return (C);
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
  Matrix T = newMatrix(A->size);
  for (int i = 1; i <= A->size; i++) {
    for (moveFront(A->rows[i]); index(A->rows[i]) >= 0; moveNext(A->rows[i])) {
      changeEntry(T, ((Entry)get(A->rows[i]))->column, i,
                  ((Entry)get(A->rows[i]))->value);
    }
  }
  return (T);
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
  if (A == NULL) {
    fprintf(stderr,
            "Matrix Error: calling scalarMult() with NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  Matrix R = newMatrix(A->size);
  if (x != 0) {
    for (int i = 1; i <= A->size; i++) {
      for (moveFront(A->rows[i]); index(A->rows[i]) >= 0;
           moveNext(A->rows[i])) {
        changeEntry(R, i, ((Entry)get(A->rows[i]))->column,
                    x * (((Entry)get(A->rows[i]))->value));
      }
    }
  }
  return (R);
}

// addList()
// Adds 2 matrix row lists and appends to Matrix.
// Private helper function
void addList(Matrix M, List A, List B, int i) {
  moveFront(A);
  moveFront(B);
  while (index(A) >= 0 && index(B) >= 0) {
    if (((Entry)get(A))->column < ((Entry)get(B))->column) {
      Entry entryA = newEntry(((Entry)get(A))->column, ((Entry)get(A))->value);
      append(M->rows[i], entryA);
      M->nnz += 1;
      moveNext(A);
    } else if (((Entry)get(B))->column < ((Entry)get(A))->column) {
      Entry entryB = newEntry(((Entry)get(B))->column, ((Entry)get(B))->value);
      append(M->rows[i], entryB);
      M->nnz += 1;
      moveNext(B);
    } else if (((Entry)get(A))->column == ((Entry)get(B))->column) {
      if ((((Entry)get(A))->value + ((Entry)get(B))->value) != 0) {
        Entry entryS =
            newEntry(((Entry)get(A))->column,
                     (((Entry)get(A))->value + ((Entry)get(B))->value));
        append(M->rows[i], entryS);
        M->nnz += 1;
      }
      moveNext(A);
      moveNext(B);
    }
  }
  while (index(A) >= 0) {
    Entry entryA = newEntry(((Entry)get(A))->column, ((Entry)get(A))->value);
    append(M->rows[i], entryA);
    M->nnz += 1;
    moveNext(A);
  }
  while (index(B) >= 0) {
    Entry entryB = newEntry(((Entry)get(B))->column, ((Entry)get(B))->value);
    append(M->rows[i], entryB);
    M->nnz += 1;
    moveNext(B);
  }
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Matrix Error: calling sum() with at least one NULL "
                    "Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size) {
    fprintf(stderr, "Matrix Error: calling sum() when Matrix A and B "
                    "dimensions do not match\n");
    exit(EXIT_FAILURE);
  }
  if (A == B) {
    return (scalarMult(2, A));
  }
  Matrix R = newMatrix(A->size);
  for (int i = 1; i <= A->size; i++) {
    addList(R, A->rows[i], B->rows[i], i);
  }
  return (R);
}

// subList()
// Subtracts 2 matrix row lists and appends to Matrix.
// Private helper function
void subList(Matrix M, List A, List B, int i) {
  moveFront(A);
  moveFront(B);
  while (index(A) >= 0 && index(B) >= 0) {
    if (((Entry)get(A))->column < ((Entry)get(B))->column) {
      Entry entryA = newEntry(((Entry)get(A))->column, ((Entry)get(A))->value);
      append(M->rows[i], entryA);
      M->nnz += 1;
      moveNext(A);
    } else if (((Entry)get(B))->column < ((Entry)get(A))->column) {
      Entry entryB = newEntry(((Entry)get(B))->column, ((Entry)get(B))->value);
      append(M->rows[i], entryB);
      M->nnz += 1;
      moveNext(B);
    } else if (((Entry)get(A))->column == ((Entry)get(B))->column) {
      if ((((Entry)get(A))->value - ((Entry)get(B))->value) != 0) {
        Entry entryS =
            newEntry(((Entry)get(A))->column,
                     (((Entry)get(A))->value - ((Entry)get(B))->value));
        append(M->rows[i], entryS);
        M->nnz += 1;
      }
      moveNext(A);
      moveNext(B);
    }
  }
  while (index(A) >= 0) {
    Entry entryA = newEntry(((Entry)get(A))->column, ((Entry)get(A))->value);
    append(M->rows[i], entryA);
    M->nnz += 1;
    moveNext(A);
  }
  while (index(B) >= 0) {
    Entry entryB = newEntry(((Entry)get(B))->column, -((Entry)get(B))->value);
    append(M->rows[i], entryB);
    M->nnz += 1;
    moveNext(B);
  }
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Matrix Error: calling diff() with at least one NULL "
                    "Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size) {
    fprintf(stderr, "Matrix Error: calling diff() when Matrix A and B "
                    "dimensions do not match\n");
    exit(EXIT_FAILURE);
  }
  Matrix R = newMatrix(A->size);
  if (A == B) {
    return R;
  }
  for (int i = 1; i <= A->size; i++) {
    subList(R, A->rows[i], B->rows[i], i);
  }
  return (R);
}

// vectorDot()
// Returns a resultant list from multiplying 2 matrix row lists.
// Private helper function
double vectorDot(List A, List B) {
  double dotProduct = 0;
  moveFront(A);
  moveFront(B);
  while (index(A) >= 0 && index(B) >= 0) {
    if (((Entry)get(A))->column < ((Entry)get(B))->column) {
      moveNext(A);
    } else if (((Entry)get(B))->column < ((Entry)get(A))->column) {
      moveNext(B);
    } else if (((Entry)get(A))->column == ((Entry)get(B))->column) {
      dotProduct += (((Entry)get(A))->value * ((Entry)get(B))->value);
      moveNext(A);
      moveNext(B);
    }
  }
  return (dotProduct);
}

// product()
// Returns a reference to a new Matrix object representing AB.
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    fprintf(stderr, "Matrix Error: calling product() with at least one NULL "
                    "Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (A->size != B->size) {
    fprintf(stderr, "Matrix Error: calling product() when Matrix A and B "
                    "dimensions do not match\n");
    exit(EXIT_FAILURE);
  }
  Matrix R = newMatrix(A->size);
  Matrix T = transpose(B);
  for (int i = 1; i <= A->size; i++) {
    if (length(A->rows[i]) == 0) {
      continue;
    }
    for (int j = 1; j <= T->size; j++) {
      changeEntry(R, i, j, vectorDot(A->rows[i], T->rows[j]));
    }
  }

  freeMatrix(&T);
  return (R);
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE *out, Matrix M) {
  for (int i = 1; i <= M->size; i++) {
    if (length(M->rows[i]) > 0) {
      fprintf(out, "%d:", i);
      for (moveFront(M->rows[i]); index(M->rows[i]) >= 0;
           moveNext(M->rows[i])) {
        fprintf(out, " (%d, %.1f)", ((Entry)get(M->rows[i]))->column,
                ((Entry)get(M->rows[i]))->value);
      }
      fprintf(out, "\n");
    }
  }
}
