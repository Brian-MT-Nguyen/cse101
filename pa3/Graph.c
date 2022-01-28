/*********************************************************************************
* Brian Nguyen, bnguy118
* 2022 Winter CSE101 PA3
* Graph.c
* Graph ADT
*********************************************************************************/
#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNDEF -7
#define NIL 0

// Structs

// private GraphObj type
typedef struct GraphObj {
    List *adjList;
    int *color;
    int *discoverTime;
    int *finishTime;
    int *parent;
    int order;
    int size;
} GraphObj;

// Constructors-Destructors

// newGraph()
// Return a reference to a new graph object containing n vertices and no edges.
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->adjList = (List *)calloc(n + 1, sizeof(List *));
    G->color = (int *)calloc(n + 1, sizeof(int *));
    G->discoverTime = (int *)calloc(n + 1, sizeof(int *));
    G->finishTime = (int *)calloc(n + 1, sizeof(int *));
    G->parent = (int *)calloc(n + 1, sizeof(int *));
    for (int i = 1; i < n + 1; i++) {
        G->adjList[i] = newList();
        G->color[i] = 0;
        G->discoverTime[i] = UNDEF;
        G->finishTime[i] = UNDEF;
        G->parent[i] = NIL;
    }
    G->order = n;
    G->size = 0;
    return (G);
}

// freeGraph()
// Frees all heap memory associated with a graph and sets its Graph argument to NULL.
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i < (*pG)->order + 1; i++) {
            freeList(&(*pG)->adjList[i]);
            (*pG)->adjList[i] = NULL;
        }
        free((*pG)->adjList);
        free((*pG)->color);
        free((*pG)->discoverTime);
        free((*pG)->finishTime);
        free((*pG)->parent);
        (*pG)->adjList = NULL;
        (*pG)->color = NULL;
        (*pG)->discoverTime = NULL;
        (*pG)->finishTime = NULL;
        (*pG)->parent = NULL;

        free(*pG);
        *pG = NULL;
    }
}

// Access functions

// getOrder()
// Returns the number of vertices in G.
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() with NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->order);
}

// getSize()
// Returns the size of the graph.
int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() with NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    return (G->size);
}

// getParent()
// Returns the parent of the vertex.
// Pre: 1<=u<=n=getOrder(G)
int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() with NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getParent() with vertex u out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}
// getDiscover()
// Returns iteration at which the vetex was discovered by DFS().
// Pre: 1<=u<=n=getOrder(G)
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() with NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getDiscover() with vertex u out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->discoveredTime[u];
}

// getFinish()
// Returns iteration at which the vetex was finished by DFS().
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() with NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getFinish() with vertex u out of range\n");
        exit(EXIT_FAILURE);
    }
    return G->finishTime[u];
}

// Manipulation procedures

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency
// List of u (but not u to the adjacency List of v).
// Pre: 1<=u<=n, 1<=v<=n
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() with NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addArc() with vertex u out of range\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addArc() with vertex v out of range\n");
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
            fprintf(stderr, "Warning: Try to add duplicate existing edge to adjacency List");
            return;
        }
        insertAfter(G->adjList[u], v);
    }
    G->size += 1;
}

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of
// v, and v to the adjacency List of u.
// Pre: 1<=u<=n, 1<=v<=n
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() with NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() with vertex u out of range\n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() with vertex v out of range\n");
        exit(EXIT_FAILURE);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size -= 1;
}

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
void printGraph(FILE* out , Graph G) {
    for (int i = 1; i < G->order + 1; i++) {
        fprintf(out, "%d: ", i);
        printList(out, G->adjList[i]);
        fprintf(out, "\n");
    }
}
