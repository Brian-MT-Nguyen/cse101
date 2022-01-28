/*********************************************************************************
* Brian Nguyen, bnguy118
* 2022 Winter CSE101 PA3
* Graph.h
* Header file for Graph ADT
*********************************************************************************/
#pragma once

#include "List.h"
#include <stdio.h>

#define UNDEF -7
#define NIL 0

// Exported type
typedef struct GraphObj *Graph;

// Constructors-Destructors

// newGraph()
// Return a reference to a new graph object containing n vertices and no edges.
Graph newGraph(int n);

// freeGraph()
// Frees all heap memory associated with a graph and sets its Graph argument to NULL.
void freeGraph(Graph* pG);

// Access functions

// getOrder()
// Returns the number of vertices in G.
int getOrder(Graph G);

// getSize()
// Returns the size of the graph.
int getSize(Graph G);

// getParent()
// Returns the parent of the vertex.
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u);

// getDiscover()
// Returns iteration at which the vetex was discovered by DFS().
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u);

// getFinish()
// Returns iteration at which the vetex was finished by DFS().
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u);

// Manipulation procedures

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency
// List of u (but not u to the adjacency List of v).
// Pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v);

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of
// v, and v to the adjacency List of u.
// Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v);

// DFS()
// Perform the depth first search algorithm on G.
// Pre: length(S)==getOrder(G)
void DFS(Graph G, List S);

// Other Functions

// transpose()
// Returns a reference to a new graph object representing the transpose of G.
Graph transpose(Graph G);

// copyGraph()
// Returns a reference to a new graph that is a copy of G.
Graph copyGraph(Graph G);

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out , Graph G);
