/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA6
 * Arithmetic.cpp
 * Calculator that performs arithmetic operations on arbitrarily large signed
 * integers.
 *********************************************************************************/
#include "List.h"
#include "BigInteger.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
	ifstream in;
	ofstream out;
	string number;
	// check command line for correct number of arguments
	if( argc != 3 ) {
 		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	}

	// open files for reading and writing
	in.open(argv[1]);
	if( !in.is_open() ){
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	}

	out.open(argv[2]);
	if( !out.is_open() ){
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	}

	getline(in, number);
	BigInteger A = number;
	getline(in, number);
	getline(in, number);
	BigInteger B = number;

	out << A << endl << endl;
	out << B << endl << endl;

	BigInteger C = A + B;
	out << C << endl << endl;

	BigInteger D = A - B;
	out << D << endl << endl;

	BigInteger E = A - A;
	out << E << endl << endl;

	BigInteger F = A + A + A;
	BigInteger G = B + B;
	BigInteger FS = F-G;
	out << FS << endl << endl;

	BigInteger FM = A * B;
	out << FM << endl << endl;

	BigInteger ExpA = A * A;
	out << ExpA << endl << endl;

	BigInteger ExpB = B * B;
	out << ExpB << endl << endl;

	BigInteger CExpA = A * A * A * A;
	BigInteger CExpB = B * B * B * B * B;
	BigInteger AddA = CExpA + CExpA + CExpA + CExpA + CExpA + CExpA + CExpA + CExpA + CExpA;
	BigInteger AddB = CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB + CExpB;
	BigInteger R = AddA + AddB;
	out << R << endl << endl;

	in.close();
	out.close();
	return(EXIT_SUCCESS);
}
