/*********************************************************************************
* Brian Nguyen, bnguy118
* 2022 Winter CSE101 PA2
* Graph.c
* Graph ADT
*********************************************************************************/
#include "List.h"
#include "Graph.h"
#include <stdio.h>
#include <stdbool.h>
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
// Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adjList = (List *) calloc(n+1, sizeof(List *));
	G->color = (int *) calloc(n+1, sizeof(int *));
	G->parent = (int *) calloc(n+1, sizeof(int *));
	G->dist = (int *) calloc(n+1, sizeof(int *));
	for (int i = 1; i < n+1; i++) {
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
// Frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG) {
	if(pG != NULL && *pG != NULL) {
		for(int i = 1; i < (*pG)->order+1; i++) {
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
	if(G == NULL) {
		fprintf(stderr, "Graph Error: calling getOrder with NULL Graph reference\n");
	}
	return(G->order);
}

// getSize()
// Returns the size of the graph.
int getSize(Graph G) {
	if(G == NULL) {
                fprintf(stderr, "Graph Error: calling getSize with NULL Graph reference\n");
        }
	return(G->size);
}

// getSource()
// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G) {
	if(G == NULL) {
                fprintf(stderr, "Graph Error: calling getSource with NULL Graph reference\n");
        }
	if(G->source == NIL) {
		return NIL;
	}
	return(G->source);
}

// getParent()
// Return the parent of vertex u in the Breadth-First tree created by BFS(), or NIL if BFS() has not yet been called.
// Pre: 1 ≤ u ≤ getOrder(G)
int getParent(Graph G, int u) {	
	if(G == NULL) {
                fprintf(stderr, "Graph Error: calling getParent() with NULL Graph reference\n");
        }
	if(u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Graph Error: calling getParent() with vertex u out of range\n");
	}
	if(G->source == NIL) {
		return NIL;
	}
	return G->parent[u];
}

// getDist()
// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
// Pre: 1 ≤ u ≤ getOrder(G)
int getDist(Graph G, int u) {
	if(G == NULL) {
                fprintf(stderr, "Graph Error: calling getDist() with NULL Graph reference\n");
        }
	if(u < 1 || u > getOrder(G)) {
                fprintf(stderr, "Graph Error: calling getDist() with vertex u out of range\n");
        }
	if(G->source == NIL) {
		return INF;
	}
        return G->dist[u];	
}

// getPath()
// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
// Pre: 1 ≤ u ≤ getOrder(G), getSource(G)!=NIL
void getPath(List L, Graph G, int u) {
	if(G == NULL) {
		fprintf(stderr, "Graph Error: calling getPath() with NULL Graph reference\n");
	}
	if(u < 1 || u > getOrder(G)) {
                fprintf(stderr, "Graph Error: calling getPath() with vertex u out of range\n");
        }
        if(G->source == NIL) {
                fprintf(stderr, "Graph Error: calling getPath() with unknown source vertex\n");
	}
	if(u == G->source) {
		append(L, u);
	}
	else if(G->parent[u] == NIL) {
		append(L, NIL);
	}
	else {
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}

/*** Manipulation procedures ***/

// makeNull()
// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

// addEdge()
// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
// Pre: u and v must be within 1 and getOrder(G)
void addEdge(Graph G, int u, int v);

// addArc()
// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
// Pre: u and v must be within 1 and getOrder(G)
void addArc(Graph G, int u, int v);

// BFS()
// Runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s);

/*** Other operations ***/

// printGraph()
// Prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G);
