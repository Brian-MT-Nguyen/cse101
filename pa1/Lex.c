#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEN 300
int main(int argc, char *argv[])  {
	//Initialize variables used for program and command-line parsing
	FILE *input_file, *output_file;
	char buffer[MAX_LEN];
	char newline_checker;
	int line_amount = 0;
	char **strings;
	
	//Give respective outputs based on parsed command line input
	if(argc != 3) {
      		printf("Usage: %s <input file> <output file>\n", argv[0]);
      		exit(EXIT_FAILURE);
	}
	
	input_file = fopen(argv[1], "r");
	if(input_file == NULL) {
      		printf("Unable to open file %s for reading\n", argv[1]);
      		exit(EXIT_FAILURE);
   	}
	
	output_file = fopen(argv[2], "w");
   	if(output_file == NULL) {
      		printf("Unable to open file %s for writing\n", argv[2]);
      		exit(EXIT_FAILURE);
   	}

	//Count total lines of input file
	while((newline_checker = fgetc(input_file)) != EOF) {
		if(newline_checker == '\n') {
			line_amount += 1;
		}
	}
	
	//Allocate string array and add strings to string array
	strings = (char **) calloc(line_amount, sizeof(char *));
	rewind(input_file);
	int i = 0;
	while(fgets(buffer, MAX_LEN, input_file) != NULL) {
		//Removes trailing newline
		buffer[strcspn(buffer, "\n")] = 0;
		
		//Allocates memory for each scanned string
		strings[i] = malloc((strlen(buffer) + 1) * sizeof(char *));
		strcpy(strings[i], buffer);
		i += 1;
	}

	//Indirectly sort array by adding indices to L with insertion sort algorithm
	List L = newList();
	prepend(L, 0);
	for(int i = 1; i < line_amount; i++) {
		moveBack(L);
		while((index(L) >= 0) && (strcmp(strings[i], strings[get(L)]) < 0)) {
			movePrev(L);
		}
		if(index(L) == -1) {
			prepend(L, i);
		}
		else {
			insertAfter(L, i);
		}
	}
	
	//Print array in lexicographic order
	for(moveFront(L); index(L) < length(L); moveNext(L)) {
		fprintf(output_file, "%s\n", strings[get(L)]);
		if(index(L) == (length(L) - 1)) {
			break;
		}
	}	
	
	//Free all memory
	for(int i = 0; i < line_amount; i++) {
		free(strings[i]);
	}
	free(strings);
	freeList(&L);
	fclose(input_file);
	fclose(output_file);
}
