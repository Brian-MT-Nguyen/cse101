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


