/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA3
 * GraphTest.c
 * Test Client to test functionality of Graph ADT
 *********************************************************************************/
#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int n = 8;
  Graph G = newGraph(n);
  List S = newList();
  for (int i = 1; i <= n; i++) {
    append(S, i);
  }

  // Test if order and size is accurate + constructs correctly
  fprintf(stdout, "Testing constructor of graph:\n");
  fprintf(stdout, "Test_Order: %d (Expected: 8)\n", getOrder(G));
  fprintf(stdout, "Test_Size: %d (Expected: 0)\n", getSize(G));
  fprintf(stdout, "Test_Parent: %d (Expected: NIL/0)\n", getParent(G, 3));
  fprintf(stdout, "Test_Discover: %d (Expected: UNDEF/-7)\n",
          getDiscover(G, 3));
  fprintf(stdout, "Test_Finish: %d (Expected: UNDEF/-7)\n", getFinish(G, 3));

  // Testing addArc and adjacency Lists
  addArc(G, 1, 2);
  addArc(G, 1, 5);
  addArc(G, 2, 5);
  addArc(G, 2, 6);
  addArc(G, 3, 2);
  addArc(G, 3, 4);
  addArc(G, 3, 6);
  addArc(G, 3, 7);
  addArc(G, 3, 8);
  addArc(G, 6, 5);
  addArc(G, 6, 7);
  addArc(G, 8, 4);
  addArc(G, 8, 7);

  // Should be a connected triangle graph from
  fprintf(stdout, "\nTesting addArc, printGraph(), and adjacency lists:\n");
  fprintf(stdout, "Test_printGraph: (Expected: 1: 2 5, 2: 5 6, 3: 2 4 6 7 8, "
                  "4: , 5: , 6: 5 7, 7: , 8: 4 7)\n");
  printGraph(stdout, G);
  fprintf(stdout, "\n");

  // Testing DFS()
  DFS(G, S);

  // Testing Discover, Finish, Parent
  fprintf(stdout, "Test DFS:\n");
  fprintf(stdout, "Test_Graph_Parent: %d (Expected: 6)\n", getParent(G, 7));
  fprintf(stdout, "Test_Graph_Discover: %d (Expected: 11)\n",
          getDiscover(G, 3));
  fprintf(stdout, "Test_Graph_Finish: %d (Expected: 15)\n", getFinish(G, 8));

  // Testing tranpose() and copyGraph()
  Graph T = transpose(G);
  Graph C = copyGraph(G);
  fprintf(stdout, "\nTesting tranpose() and copyGraph():\n");
  fprintf(stdout, "Test_Graph_transpose: (Expected: 1: , 2: 1 3, 3: , 4: 3 8, "
                  "5: 1 2 6, 6: 2 3, 7: 3 6 8, 8: 3)\n");
  printGraph(stdout, T);
  fprintf(stdout, "\nTest_Graph_copyGraph: (Expected: 1: 2 5, 2: 5 6, 3: 2 4 6 "
                  "7 8, 4: , 5: , 6: 5 7, 7: , 8: 4 7)\n");
  printGraph(stdout, C);

  // Testing freeGraph()
  fprintf(stdout, "\nTesting freeGraph(): Check valgrind for mem leaks\n");
  freeGraph(&G);
  freeGraph(&T);
  freeGraph(&C);
  freeList(&S);
}
