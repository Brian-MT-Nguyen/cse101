/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA3
 * FindComponents.c
 * Finds the strongest component(s) of a graph using Depth-First Search and
 * adjacency lists of vertices
 *********************************************************************************/

#include "Graph.h"
#include "List.h"
#include <stdbool.h>
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
  int source;
  int dest;
  int total_vertices;

  // Grabs number of successfully inputted vertex from line scan (for error
  // handling)
  int input_vertices = fscanf(input_file, "%d\n", &total_vertices);
  // Error Msg for Invalid Vertices
  if (input_vertices != 1) {
    fprintf(stderr, "Error: Invalid number of vertices");
    exit(EXIT_FAILURE);
  }

  // Make new graph to store vertices/edges for program tasks
  Graph G = newGraph(total_vertices);

  // Initialize variable to grab number of successfully inputted vertices from
  // line scan (for error handling)
  int input_doubles;

  // Scans through all lines that contain the two integer format and adds arcs
  // to graph
  while (((input_doubles = fscanf(input_file, "%d %d\n", &source, &dest)) !=
          EOF) &&
         (source != 0 && dest != 0)) {
    if (input_doubles != 2) {
      fprintf(stderr, "Error: Invalid number of vertices");
      exit(EXIT_FAILURE);
    }
    addArc(G, source, dest);
  }

  // Prints the Adjacency List Rep. of G
  fprintf(output_file, "Adjacency list representation of G:\n");
  printGraph(output_file, G);
  fprintf(output_file, "\n");

  // Make a List S containing all the verticies in Graph G to perform DFS()
  List S = newList();
  for (int i = 1; i <= total_vertices; i++) {
    append(S, i);
  }

  // Call DFS() on G
  DFS(G, S);

  // Make Transpose of G, T
  Graph T = transpose(G);

  // Call DFS() on T using updated S
  DFS(T, S);

  // Get Amount of Strong Components in Graph
  int total_sc = 0;
  for (moveFront(S); index(S) >= 0; moveNext(S)) {
    if (getParent(T, get(S)) == NIL) {
      total_sc += 1;
    }
  }

  // Print Strong Components of Graph
  List SC = newList();
  fprintf(output_file, "G contains %d strongly connected components:\n",
          total_sc);
  int component_counter = 1;
  for (moveBack(S); index(S) >= 0; movePrev(S)) {
    prepend(SC, get(S));
    if (getParent(T, get(S)) == NIL) {
      fprintf(output_file, "Component %d: ", component_counter);
      printList(output_file, SC);
      fprintf(output_file, "\n");
      clear(SC);
      component_counter += 1;
    }
  }

  // Frees heap memory
  freeGraph(&G);
  freeGraph(&T);
  freeList(&S);
  freeList(&SC);
}
