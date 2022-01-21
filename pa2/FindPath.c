/*********************************************************************************
* Brian Nguyen, bnguy118
* 2022 Winter CSE101 PA2
* FindPath.c
* Finds the shortest path(s) of a graph using Breadth First Search and adjacency lists of vertices
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

    //Initializes variables to store input from input file
    int source;
    int dest;
    int total_vertices;

    //Grabs number of successfully inputted vertex from line scan (for error handling)
    int input_vertices = fscanf(input_file, "%d\n", &total_vertices);
    //Error Msg for Invalid Vertices
    if (input_vertices != 1) {
        fprintf(stderr, "Error: Invalid number of vertices");
        exit(EXIT_FAILURE);
    }

    //Make new graph to store vertices/edges for program tasks
    Graph G = newGraph(total_vertices);

    //Make List to store Paths for program tasks
    List P = newList();

    //Initialize variable to grab number of successfully inputted vertices from line scan (for error handling)
    int input_doubles;

    //scans through all lines that contain the two integer format and adds edges to graph
    while(((input_doubles = fscanf(input_file, "%d %d\n", &source, &dest)) != EOF) && (source != 0 && dest != 0)) {
        if(input_doubles != 2) {
            fprintf(stderr, "Error: Invalid number of vertices");
            exit(EXIT_FAILURE);
        }
        addEdge(G, source, dest);
    }
    printGraph(output_file, G);
    fprintf(output_file, "\n");

    //scans through all lines that contain the two integer format and prints their paths via BFS
    while(((input_doubles= fscanf(input_file, "%d %d\n", &source, &dest)) != EOF) && (source != 0 && dest != 0)) {
        if(input_doubles != 2) {
            fprintf(stderr, "Error: Invalid number of vertices");
            exit(EXIT_FAILURE);
        }
        //uses BFS to discovered vertices/path and stores the path in P via getPath()
        BFS(G, source);
        getPath(P, G, dest);

        //Prints distance and path to output files based on if real or infinite/non-existent
        if(getDist(G, dest) == INF) {
            fprintf(output_file, "The distance from %d to %d is infinity\n", source, dest);
            fprintf(output_file, "No %d-%d path exists", source, dest);
        }
        else {
            fprintf(output_file, "The distance from %d to %d is %d\n", source, dest, getDist(G, dest));
            fprintf(output_file, "A shortest %d-%d path is: ", source, dest);
            printList(output_file, P);
        }
        fprintf(output_file, "\n");
        fprintf(output_file, "\n");

        //Clears path to get ready to store next one
        clear(P);
    }
    freeGraph(&G);
    freeList(&P);
}
