/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA4
 * MatrixTest.c
 * Test Client for the Matrix ADT
 *********************************************************************************/
#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n = 100000;
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  Matrix C, D, E, F, G, H, I, J, K, L;

  // Test changeEntry()
  changeEntry(A, 1, 1, 1);
  changeEntry(B, 1, 1, 1);
  changeEntry(A, 1, 2, 2);
  changeEntry(B, 1, 2, 0);
  changeEntry(A, 1, 3, 3);
  changeEntry(A, 1, 3, 7);
  changeEntry(A, 1, 3, 3);
  changeEntry(B, 1, 3, 1);
  changeEntry(A, 2, 1, 4);
  changeEntry(B, 2, 1, 0);
  changeEntry(A, 2, 2, 5);
  changeEntry(B, 2, 2, 1);
  changeEntry(A, 2, 3, 6);
  changeEntry(B, 2, 3, 0);
  changeEntry(A, 3, 1, 7);
  changeEntry(B, 3, 1, 1);
  changeEntry(B, 3, 1, 0);
  changeEntry(B, 3, 1, 6);
  changeEntry(B, 3, 1, 1);
  changeEntry(A, 3, 2, 8);
  changeEntry(B, 3, 2, 1);
  changeEntry(A, 3, 3, 9);
  changeEntry(B, 3, 3, 1);

  // Test NNZ()
  fprintf(stdout,
          "Testing NNZ(A): %d | Expected: 9\nTesting printMatrix(A): Expected: "
          "1: (1, 1.0) (2, 2.0) (3, 3.0), 2: (1, 4.0) (2, 5.0) (3, 6.0), 3: "
          "(1, 7.0) (2, 8.0) (3, 9.0)\n",
          NNZ(A));
  printMatrix(stdout, A);
  fprintf(stdout, "\n");

  fprintf(stdout,
          "Testing NNZ(B): %d | Expected: 6\nTesting printMatrix(B): Expected: "
          "1: (1, 1.0) (3, 1.0), 2: (2, 1.0), 3: (1, 1.0) (2, 1.0) (3, 1.0)\n",
          NNZ(B));
  printMatrix(stdout, B);
  fprintf(stdout, "\n");

  // Test scalarMult()
  fprintf(stdout, "Testing scalarMult(A): Expected: 1: (1, 1.5) (2, 3.0) (3, "
                  "4.5), 2: (1, 6.0) (2, 7.5) (3, 9.0), 3: (1, 10.5) (2, 12.0) "
                  "(3, 13.5)\n");
  C = scalarMult(1.5, A);
  printMatrix(stdout, C);
  fprintf(stdout, "\n");

  // Testing sum()
  fprintf(stdout, "Testing sum(A, B): Expected: 1: (1, 2.0) (2, 2.0) (3, 4.0), "
                  "2: (1, 4.0) (2, 6.0) (3, 6.0), 3: (1, 8.0) (2, 9.0) (3, "
                  "10.0)\n");
  D = sum(A, B);
  printMatrix(stdout, D);
  fprintf(stdout, "\n");

  fprintf(stdout, "Testing sum(A, A): Expected: 1: (1, 2.0) (2, 4.0) (3, 6.0), "
                  "2: (1, 8.0) (2, 10.0) (3, 12.0), 3: (1, 14.0) (2, 16.0) (3, "
                  "18.0)\n");
  I = sum(A, A);
  printMatrix(stdout, I);
  fprintf(stdout, "\n");

  // Testing diff()
  fprintf(stdout, "Testing diff(A, B): Expected: 1: (2, 2.0) (3, 2.0), 2: (1, "
                  "4.0) (2, 4.0) (3, 6.0), 3: (1, 6.0) (2, 7.0) (3, 8.0)\n");
  J = diff(A, B);
  printMatrix(stdout, J);
  fprintf(stdout, "\n");

  fprintf(stdout, "Testing diff(B, A): Expected: 1: (2, -2.0) (3, -2.0), 2: "
                  "(1, -4.0) (2, -4.0) (3, -6.0), 3: (1, -6.0) (2, -7.0) (3, "
                  "-8.0)\n");
  K = diff(B, A);
  printMatrix(stdout, K);
  fprintf(stdout, "\n");

  fprintf(stdout, "Testing diff(A, A): Expected: Nothing\n");
  E = diff(A, A);
  printMatrix(stdout, E);
  fprintf(stdout, "\n");

  // Testing transpose()
  fprintf(stdout, "Testing transpose(B): Expected: 1: (1, 1.0) (3, 1.0), 2: "
                  "(2, 1.0) (3, 1.0), 3: (1, 1.0) (3, 1.0)\n");
  F = transpose(B);
  printMatrix(stdout, F);
  fprintf(stdout, "\n");

  // Testing product()
  fprintf(stdout, "Testing product(A,B): Expected: 1: (2, -2.0) (3, -2.0), 2: "
                  "(1, -4.0) (2, -4.0) (3, -6.0), 3: (1, -6.0) (2, -7.0) (3, "
                  "-8.0)\n");
  L = product(A, B);
  printMatrix(stdout, K);
  fprintf(stdout, "\n");

  fprintf(stdout, "Testing product(B,B): Expected: 1: (1, 2.0) (2, 1.0) (3, "
                  "2.0), 2: (2, 1.0), 3: (1, 2.0) (2, 2.0) (3, 2.0)\n");
  G = product(B, B);
  printMatrix(stdout, G);
  fprintf(stdout, "\n");

  // Testing copy()
  fprintf(stdout, "Testing copy(A): Expected: 1: (1, 1.0) (2, 2.0) (3, 3.0), "
                  "2: (1, 4.0) (2, 5.0) (3, 6.0), 3: (1, 7.0) (2, 8.0) (3, "
                  "9.0)\n");
  H = copy(A);
  printMatrix(stdout, H);
  fprintf(stdout, "\n");

  // Testing equals()
  fprintf(stdout, "Testing equals(): Expected: true, false, true\n");
  fprintf(stdout, "%s\n", equals(A, H) ? "true" : "false");
  fprintf(stdout, "%s\n", equals(A, B) ? "true" : "false");
  fprintf(stdout, "%s\n", equals(A, A) ? "true" : "false");
  fprintf(stdout, "\n");

  // Testing makeZero()
  fprintf(stdout, "Testing makeZero(A): Expected NNZ(A) = 0, Prints Nothing\n");
  makeZero(A);
  fprintf(stdout, "NNZ(A): %d\n", NNZ(A));
  printMatrix(stdout, A);
  fprintf(stdout, "\n");

  // Testing freeMatrix()
  fprintf(stdout, "Testing freeMatrix(): Check Valgrind\n");
  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&E);
  freeMatrix(&F);
  freeMatrix(&G);
  freeMatrix(&H);
  freeMatrix(&I);
  freeMatrix(&J);
  freeMatrix(&K);
  freeMatrix(&L);
  return EXIT_SUCCESS;
}
