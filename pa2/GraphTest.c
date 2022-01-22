/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA2
 * GraphTest.c
 *
 *********************************************************************************/
#define NIL 0
#define INF -7
#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n = 4;
  Graph G = newGraph(n);
  List P = newList();

  // Test if order and size is accurate + constructs correctly
  fprintf(stdout, "Testing constructor of graph:\n");
  fprintf(stdout, "Test_Order: %d (Expected: 4)\n", getOrder(G));
  fprintf(stdout, "Test_Size: %d (Expected: 0)\n", getSize(G));
  fprintf(stdout, "Test_Source: %d (Expected: NIL/0)\n", getSource(G));
  fprintf(stdout, "Test_Parent: %d (Expected: NIL/0)\n", getParent(G, 3));
  fprintf(stdout, "Test_Distance: %d (Expected: INF/-7)\n\n", getDist(G, 3));

  // Add edges(calls arc anyways so checks arc too) and check adjacency List +
  // check new Parent/Dists
  addEdge(G, 1, 2);
  addEdge(G, 2, 3);
  addEdge(G, 3, 1);

  // Should be a connected triangle graph from 1-2-3-1
  fprintf(stdout, "Testing addArc, addEdge() and printGraph():\n");
  fprintf(stdout, "Test_printGraph: (Expected: 1: 2 3, 2: 1 3, 3: 1 2, 4: )\n");
  printGraph(stdout, G);
  fprintf(stdout, "\n");
  // Call BFS to make Paths
  BFS(G, 1);

  // Check source and parents and dist and size
  fprintf(stdout, "Test BFS part1:\n");
  fprintf(stdout, "Test_Graph_Parent: %d (Expected: 1)\n", getParent(G, 3));
  fprintf(stdout, "Test_Graph_Dist: %d (Expected: 1)\n", getDist(G, 2));
  fprintf(stdout, "Test_Graph_Size: %d (Expected: 3)\n", getSize(G));
  fprintf(stdout, "Test_Graph_Source: %d (Expected: 1)\n\n", getSource(G));

  // Add another edge and check path (should be 1 to 3 to 4)
  addEdge(G, 3, 4);
  BFS(G, 1);
  getPath(P, G, 4);
  fprintf(stdout, "Testing BFS part2 + getPath():\n");
  fprintf(stdout, "Test_getPath: ");
  printList(stdout, P);
  fprintf(stdout, "| (Expected: 1 3 4)\n\n");

  // Checks makeNULL
  fprintf(stdout, "Testing makeNull() reverting Graph to OG state:\n");
  makeNull(G);
  fprintf(stdout, "Test_Graph_Parent: %d (Expected: NIL/0)\n", getParent(G, 3));
  fprintf(stdout, "Test_Graph_Dist: %d (Expected: INF/-7)\n", getDist(G, 3));
  fprintf(stdout, "Test_Graph_Size: %d (Expected: 0)\n", getSize(G));
  fprintf(stdout, "Test_Graph_Source: %d (Expected: NIL/0)\n\n", getSource(G));

  // free Graph (check valgrind)
  fprintf(stdout, "Testing freeGraph(): Check valgrind for mem leaks\n");
  freeGraph(&G);
  freeList(&P);
}
