/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA4
 * Sparse.c
 * Calculator that performs Matrix Operations on a sparse nXn matrix in List
 * representation
 *********************************************************************************/
#include "List.h"
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Initialize variables used for program and command-line parsing
  FILE *input_file, *output_file;

  // Give respective outputs based on parsed command line input
  if (argc != 3) {
    printf("Usage: %s <input file> <output file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  input_file = fopen(argv[1], "r");
  if (input_file == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  output_file = fopen(argv[2], "w");
  if (output_file == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(EXIT_FAILURE);
  }

  // Initializes variables to store input from input file
  int totalRows;
  int entriesA;
  int entriesB;
  int row;
  int column;
  double value;

  // Grabs number of successful inputs (for error handling)
  int inputTriple =
      fscanf(input_file, "%d %d %d\n\n", &totalRows, &entriesA, &entriesB);
  // Error Msg for Invalid Inputs
  if (inputTriple != 3) {
    fprintf(stderr, "Error: Invalid number of inputs");
    exit(EXIT_FAILURE);
  }

  // Make new Matrix using totalRows input
  Matrix A = newMatrix(totalRows);
  Matrix B = newMatrix(totalRows);

  // Initialize variable to grab number of successful inputs from line scan (for
  // error handling)
  int inputEntries;

  // Scan entries for the A Matrix
  for (int i = 0; i < entriesA; i++) {
    inputEntries = fscanf(input_file, "%d %d %lf\n", &row, &column, &value);
    if (inputEntries != 3) {
      fprintf(stderr, "Error: Invalid number of inputs");
      exit(EXIT_FAILURE);
    }
    changeEntry(A, row, column, value);
  }

  // Scan entries for the B Matrix
  for (int i = 0; i < entriesB; i++) {
    inputEntries = fscanf(input_file, "%d %d %lf\n", &row, &column, &value);
    if (inputEntries != 3) {
      fprintf(stderr, "Error: Invalid number of inputs");
      exit(EXIT_FAILURE);
    }
    changeEntry(B, row, column, value);
  }

  // Print A and B Matricies and their non-zero entries
  fprintf(output_file, "A has %d non-zero entries:\n", entriesA);
  printMatrix(output_file, A);
  fprintf(output_file, "\n");
  fprintf(output_file, "B has %d non-zero entries:\n", entriesB);
  printMatrix(output_file, B);
  fprintf(output_file, "\n");

  // Initialize Matrix to hold resultant matrix of operations
  Matrix C, D, E, F, G, H, I, J;

  // Print (1.5)*A
  C = scalarMult(1.5, A);
  fprintf(output_file, "(1.5)*A =\n");
  printMatrix(output_file, C);
  fprintf(output_file, "\n");

  // Print A+B
  D = sum(A, B);
  fprintf(output_file, "A+B =\n");
  printMatrix(output_file, D);
  fprintf(output_file, "\n");

  // Print A+A
  E = sum(A, A);
  fprintf(output_file, "A+A =\n");
  printMatrix(output_file, E);
  fprintf(output_file, "\n");

  // Print B-A
  F = diff(B, A);
  fprintf(output_file, "B-A =\n");
  printMatrix(output_file, F);
  fprintf(output_file, "\n");

  // Print A-A
  G = diff(A, A);
  fprintf(output_file, "A-A =\n");
  printMatrix(output_file, G);
  fprintf(output_file, "\n");

  // Print Transpose(A)
  H = transpose(A);
  fprintf(output_file, "Transpose(A) =\n");
  printMatrix(output_file, H);
  fprintf(output_file, "\n");

  // Print A*B
  I = product(A, B);
  fprintf(output_file, "A*B =\n");
  printMatrix(output_file, I);
  fprintf(output_file, "\n");

  // Print B*B
  J = product(B, B);
  fprintf(output_file, "B*B =\n");
  printMatrix(output_file, J);

  // Free all heap memory of Matricies and close files
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
  fclose(input_file);
  fclose(output_file);
}
