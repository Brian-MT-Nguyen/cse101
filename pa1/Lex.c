#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <stdio.h>

int main( int argc, char *argv[] )  {
	FILE *input_file, *output_file;
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
}
