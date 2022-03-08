/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA8
 * Order.cpp
 * Alphabetizes the lines in a file and prints its key(line) : value(line number)
 * pairs in alphabetical order along with a key-only preorder representation
 * using Dictionary ADT
 *********************************************************************************/
#include"Dictionary.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(int argc, char * argv[]) {
	ifstream in;
	ofstream out;
	string key;

	// check command line for correct number of arguments
	if(argc != 3) {
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}

	// open files for reading and writing
	in.open(argv[1]);
	if(!in.is_open()) {
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}

	out.open(argv[2]);
	if(!out.is_open()) {
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}

	// initialize empty Dictionary
	Dictionary D;

	// read each line of input file and add keys and its line number to Dictionary
	size_t line_number = 1;
	while(getline(in, key)) {
		D.setValue(key, line_number);
		line_number += 1;
	}

	// Print out Keys/Values in order (alphabetical)
	out << D << endl;

	// Print out keys in pre-order
	out << D.pre_string() << endl;

	// close files
	in.close();
	out.close();

	return(EXIT_SUCCESS);
}
