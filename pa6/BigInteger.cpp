/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA6
 * BigInteger.cpp
 * BigInteger ADT
 *********************************************************************************/
#include<iostream>
#include<string>
#include"List.h"
#include"BigInteger.h"

//Define global constants used in program
const long base = 1000000000;
const int power = 9;

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:
// signum=0, digits=().
BigInteger::BigInteger() {
	signum = 0;
	List digits;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
	if (s.length() == 0) {
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	if(s.length() == 1 && (s[0] == '-' || s[0] == '+')) {
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
	}
	for(unsigned long i = 0; i < s.length(); i++) {
		if(s[0] == '-' || s[0] == '+') {
			continue;
		}
		if(std::isdigit(s[i]) == 0) {
			throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
		}
	}

	std::string c = s;
	signum = 1;
	if(c[0] == '+') {
		c.erase(0,1);
	}
	else if(c[0] == '-') {
		signum = -1;
		c.erase(0,1);
	}
	if(c.length() % power != 0) {
		int feLength = (c.length() % power) - 1;
		long firstEntry = std::stol(c.substr(0, feLength), nullptr, base);
		digits.insertBefore(firstEntry);
		c.erase(0, feLength);
	}
	while(c.length() > 0) {
		long Entry = std::stol(c.substr(0, (power - 1)), nullptr, base);
		digits.insertBefore(Entry);
		c.erase(0, (power - 1));
	}
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
	//make empty state
	signum = 0;
	List digits;

	//load N's digits into this digits
   	digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,
// negative or 0, respectively.
int BigInteger::sign() const {
	return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
	int comp = 0;
	List T = this->digits;
	List L = N.digits;
	T.moveFront();
	L.moveFront();

	while((comp == 0) && (T.position() < T.length()) && (L.position() < L.length())) {
		int thisElement = T.moveNext()*(this->signum);
		int LElement = L.moveNext()*(N.signum);
		if((thisElement - LElement) > 0) {
			comp = 1;
		}
		else if((thisElement - LElement) < 0) {
			comp = -1;
		}
	}
	if((T.position() < T.length()) && (this->signum == 1)) {
		comp = 1;
	}
	else if((T.position() < T.length()) && (this->signum == -1)) {
		comp = -1;
	}
	else if((L.position() < L.length()) && (N.signum == 1)) {
		comp = -1;
	}
	else if((L.position() < L.length()) && (N.signum == -1)) {
		comp = 1;
	}
	return comp;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
	signum = 0;
	digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of
// this BigInteger positive <--> negative.
void BigInteger::negate() {
	signum = -signum;
}

// BigInteger Arithmetic operations ----------------------------------------

// Other Functions ---------------------------------------------------------

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
	return stream << N.digits;
}
