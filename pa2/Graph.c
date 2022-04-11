/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA2
 * Graph.c
 * Graph ADT
 *********************************************************************************/
#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INF -7
#define NIL 0
/*** Structs ***/

// private GraphObj type
typedef struct GraphObj {
  List *adjList;
  int *color;
  int *parent;
  int *dist;
  int order;
  int size;
  int source;
} GraphObj;

/*** Constructors-Destructors ***/

// newGraph()
// Returns a Graph pointing to a newly created GraphObj representing a graph
// having n vertices and no edges.
Graph newGraph(int n) {
  Graph G = malloc(sizeof(GraphObj));
  G->adjList = (List *)calloc(n + 1, sizeof(List *));
  G->color = (int *)calloc(n + 1, sizeof(int *));
  G->parent = (int *)calloc(n + 1, sizeof(int *));
  G->dist = (int *)calloc(n + 1, sizeof(int *));
  for (int i = 1; i < n + 1; i++) {
    G->adjList[i] = newList();
    G->color[i] = 0;
    G->parent[i] = NIL;
    G->dist[i] = INF;
  }
  G->order = n;
  G->size = 0;
  G->source = NIL;
  return (G);
}

// freeGraph()
// Frees all heap memory associated with the Graph *pG, then sets the handle *pG
// to NULL.
void freeGraph(Graph *pG) {
  if (pG != NULL && *pG != NULL) {
    for (int i = 1; i < (*pG)->order + 1; i++) {
      freeList(&(*pG)->adjList[i]);
      (*pG)->adjList[i] = NULL;
    }
    free((*pG)->adjList);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->dist);
    (*pG)->adjList = NULL;
    (*pG)->color = NULL;
    (*pG)->parent = NULL;
    (*pG)->dist = NULL;

    free(*pG);
    *pG = NULL;
  }
}

/*** Access functions ***/

// getOrder()
// Returns the order of the graph.
int getOrder(Graph G) {
  if (G == NULL) {
    fprintf(stderr,
            "Graph Error: calling getOrder with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return (G->order);
}

// getSize()
// Returns the size of the graph.
int getSize(Graph G) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling getSize with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  return (G->size);
}

// getSource()
// Returns the source vertex most recently used in function BFS(), or NIL if
// BFS() has not yet been called.
int getSource(Graph G) {
  if (G == NULL) {
    fprintf(stderr,
            "Graph Error: calling getSource with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (G->source == NIL) {
    return NIL;
  }
  return (G->source);
}

// getParent()
// Return the parent of vertex u in the Breadth-First tree created by BFS(), or
// NIL if BFS() has not yet been called. Pre: 1 ≤ u ≤ getOrder(G)
int getParent(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr,
            "Graph Error: calling getParent() with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    fprintf(stderr,
            "Graph Error: calling getParent() with vertex u out of range\n");
    exit(EXIT_FAILURE);
  }
  if (G->source == NIL) {
    return NIL;
  }
  return G->parent[u];
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if
// BFS() has not yet been called. Pre: 1 ≤ u ≤ getOrder(G)
int getDist(Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr,
            "Graph Error: calling getDist() with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    fprintf(stderr,
            "Graph Error: calling getDist() with vertex u out of range\n");
    exit(EXIT_FAILURE);
  }
  if (G->source == NIL) {
    return INF;
  }
  return G->dist[u];
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u,
// or appends to L the value NIL if no such path exists. Pre: 1 ≤ u ≤
// getOrder(G), getSource(G)!=NIL
void getPath(List L, Graph G, int u) {
  if (G == NULL) {
    fprintf(stderr,
            "Graph Error: calling getPath() with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    fprintf(stderr,
            "Graph Error: calling getPath() with vertex u out of range\n");
    exit(EXIT_FAILURE);
  }
  if (G->source == NIL) {
    fprintf(stderr,
            "Graph Error: calling getPath() with unknown source vertex\n");
    exit(EXIT_FAILURE);
  }
  if (u == G->source) {
    append(L, u);
  } else if (G->parent[u] == NIL) {
    append(L, NIL);
  } else {
    getPath(L, G, G->parent[u]);
    append(L, u);
  }
}

/*** Manipulation procedures ***/

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G) {
  for (int i = 1; i < G->order + 1; i++) {
    clear(G->adjList[i]);
    G->color[i] = 0;
    G->parent[i] = NIL;
    G->dist[i] = INF;
  }
  G->size = 0;
  G->source = NIL;
}

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of
// v, and v to the adjacency List of u. Pre: u and v must be within 1 and
// getOrder(G)
void addEdge(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr,
            "Graph Error: calling addEdge() with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    fprintf(stderr,
            "Graph Error: calling addEdge() with vertex u out of range\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > getOrder(G)) {
    fprintf(stderr,
            "Graph Error: calling addEdge() with vertex v out of range\n");
    exit(EXIT_FAILURE);
  }
  int currentSize = G->size;
  addArc(G, u, v);
  addArc(G, v, u);
  if (G->size > currentSize) {
    G->size -= 1;
  }
}

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency
// List of u (but not u to the adjacency List of v). Pre: u and v must be within
// 1 and getOrder(G)
void addArc(Graph G, int u, int v) {
  if (G == NULL) {
    fprintf(stderr,
            "Graph Error: calling addArc() with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    fprintf(stderr,
            "Graph Error: calling addArc() with vertex u out of range\n");
    exit(EXIT_FAILURE);
  }
  if (v < 1 || v > getOrder(G)) {
    fprintf(stderr,
            "Graph Error: calling addArc() with vertex v out of range\n");
    exit(EXIT_FAILURE);
  }
  moveBack(G->adjList[u]);
  while ((index(G->adjList[u]) >= 0) && (v < get(G->adjList[u]))) {
    movePrev(G->adjList[u]);
  }
  if (index(G->adjList[u]) == -1) {
    prepend(G->adjList[u], v);
  } else {
    if (get(G->adjList[u]) == v) {
      fprintf(stderr, "Warning: Try to add duplicate existing arc/edge to "
                      "adjacency List\n");
      return;
    }
    insertAfter(G->adjList[u], v);
  }
  G->size += 1;
}

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color,
// distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
  if (G == NULL) {
    fprintf(stderr, "Graph Error: calling BFS() with NULL Graph reference\n");
    exit(EXIT_FAILURE);
  }
  G->source = s;
  for (int x = 1; x < G->order + 1; x++) {
    if (x == s) {
      continue;
    }
    G->color[x] = 0;
    G->dist[x] = INF;
    G->parent[x] = NIL;
  }
  G->color[s] = 1;
  G->dist[s] = 0;
  G->parent[s] = NIL;
  List Q = newList();
  append(Q, s);
  while (length(Q) > 0) {
    int x = front(Q);
    deleteFront(Q);
    if (length(G->adjList[x]) > 0) {
      for (moveFront(G->adjList[x]); index(G->adjList[x]) >= 0;
           moveNext(G->adjList[x])) {
        int y = get(G->adjList[x]);
        if (G->color[y] == 0) {
          G->color[y] = 1;
          G->dist[y] = G->dist[x] + 1;
          G->parent[y] = x;
          append(Q, y);
        }
      }
    }
    G->color[x] = 2;
  }
  freeList(&Q);
}

/*** Other operations ***/

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE *out, Graph G) {
  for (int i = 1; i < G->order + 1; i++) {
    fprintf(out, "%d: ", i);
    printList(out, G->adjList[i]);
    fprintf(out, "\n");
  }
}
