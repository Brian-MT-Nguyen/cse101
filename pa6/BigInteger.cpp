/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA6
 * BigInteger.cpp
 * BigInteger ADT
 *********************************************************************************/
#include<iostream>
#include<stdexcept>
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
		int feLength = (c.length() % power);
		std::string e = c.substr(0, feLength);
		long firstEntry = std::stol(e);
		digits.insertBefore(firstEntry);
		c.erase(0, feLength);
	}
	while(c.length() > 0) {
		std::string e = c.substr(0, (power));
		long Entry = std::stol(e);
		digits.insertBefore(Entry);
		c.erase(0, (power));
	}
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
	//Copy N's state
	signum = N.signum;
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
	if((T.length() > L.length()) && (this->signum == 1)) {
		comp = 1;
	}
	else if((T.length() > L.length()) && (this->signum == -1)) {
		comp = -1;
	}
	else if((T.length() < L.length()) && (N.signum == 1)) {
		comp = -1;
	}
	else if((T.length() < L.length()) && (N.signum == -1)) {
		comp = 1;
	}

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

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
	std::string s = "";
	if(this->signum == 0) {
		s += "0";
		return s;
	}
	if(this->signum == -1) {
		s += "-";
	}
	List L = this->digits;
	L.moveFront();
	s+= std::to_string(L.moveNext());
	while(L.position() < L.length()) {
		std::string pad = std::to_string(L.moveNext());
		pad.insert(pad.begin(), 9 - pad.length(), '0');
		s += pad;
	}
	return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==( const BigInteger& A, const BigInteger& B ) {
	if(A.compare(B) == 0) {
		return true;
	}
	return false;
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<( const BigInteger& A, const BigInteger& B ) {
	if(A.compare(B) == -1) {
		return true;
	}
	return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=( const BigInteger& A, const BigInteger& B ) {
	if(A.compare(B) <= 0) {
		return true;
	}
	return false;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>( const BigInteger& A, const BigInteger& B ) {
	if(A.compare(B) == 1) {
		return true;
	}
	return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=( const BigInteger& A, const BigInteger& B ) {
	if(A.compare(B) >= 0) {
		return true;
	}
	return false;
}
