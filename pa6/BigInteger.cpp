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

// BigInteger Arithmetic Helper functions ----------------------------------

// negateList()
// Changes the sign of each integer in List L.
// Used by normalize().
void negateList(List& L) {
	L.moveFront();
	while(L.position() < L.length()) {
		long element = L.moveNext();
		L.setBefore(-element);
	}
}

// sumList()
// Overwrites the state of S with signA*A + sgnB*B (considered as vectors).
// Used by both sum().
void sumList(List& S, List A, List B, int sgnA, int sgnB) {
	// clear list in case
	if(S.length() > 0) {
		S.clear();
	}
	// start adding from back to front
	A.moveBack();
	B.moveBack();
	while((A.position() > 0) && (B.position() > 0)) {
		// add elements and insert in list
		long AElement = (sgnA)*A.movePrev();
		long BElement = (sgnB)*B.movePrev();
		S.insertAfter(AElement + BElement);
	}
	// if remaining elements still in list then insert remaining
	while(A.position() > 0) {
		long AElement = (sgnA)*A.movePrev();
		S.insertAfter(AElement);
	}
	while(B.position() > 0) {
		long BElement = (sgnB)*B.movePrev();
		S.insertAfter(BElement);
	}
}

// subList()
// Overwrites the state of S with sgnA*A - sgnB*B (considered as vectors).
// Used by sub().
void subList(List &S, List A, List B, int sgnA, int sgnB) {
	// clear list in case
	if(S.length() > 0) {
		S.clear();
	}
	// start subtracting from back to front
	A.moveBack();
	B.moveBack();
	while((A.position() > 0) && (B.position() > 0)) {
		// subtract elements and insert in list
		long AElement = (sgnA)*A.movePrev();
		long BElement = (sgnB)*B.movePrev();
		S.insertAfter(AElement - BElement);
	}
	// if remaining elements still in list then insert remaining
	while(A.position() > 0) {
		long AElement = (sgnA)*A.movePrev();
		S.insertAfter(AElement);
	}
	while(B.position() > 0) {
		long BElement = (sgnB)*B.movePrev();
		// special case needs to be negative BElement
		S.insertAfter(-BElement);
	}
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
int normalizeList(List& L) {
	// check for negation case when non-normalized list is negative
	int sign = 1;
	if(L.front() < 0) {
		negateList(L);
		sign = -1;
	}
	// start normalizing from back to front
	L.moveBack();
	long carbor = 0;
	while(L.position() > 0) {
		// if there is a carry/borrow then apply to borrowed from digit
		if(carbor != 0) {
			L.setBefore(L.peekPrev() + carbor);
			carbor = 0;
		}
		// if number is not from 0 to base-1 then normalize
		long element = L.movePrev();
		if(element < 0) {
			carbor = (element/base)-1;
			L.setAfter(element-(base*carbor));
		}
		else if(element >= base) {
			carbor = (element/base);
			L.setAfter(element-(base*carbor));
		}
	}
	// if carry/borrow still exist then add to front of list
	if(carbor > 0) {
		L.insertBefore(carbor);
		L.movePrev();
	}
	// remove leading zeros
	while(L.position() < L.length()) {
		if(L.peekNext() == 0) {
			L.eraseAfter();
		}
		else {
			break;
		}
	}
	// detect signs based on most significant digit
	if(L.length() == 0) {
		sign = 0;
	}
	else if(L.peekNext() < 0) {
		sign = -1;
	}
	else if((sign != -1) && (L.peekNext() > 0)) {
		sign = 1;
	}
	return sign;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p) {
	L.moveBack();
	for(int i = 0; i < p; i++) {
		L.insertAfter(0);
	}
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m) {
	L.moveBack();
	while (L.position() > 0) {
		long element = L.movePrev();
		L.setAfter(m * element);
	}
}

// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
	BigInteger S;
	List T = this->digits;
	List L = N.digits;
	List Sum;
	sumList(Sum, T, L, this->signum, N.signum);
	int sign = normalizeList(Sum);
	S.signum = sign;
	S.digits = Sum;
	return S;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
	BigInteger D;
	List T = this->digits;
	List L = N.digits;
	List Diff;
	subList(Diff, T, L, this->signum, N.signum);
	int sign = normalizeList(Diff);
	D.signum = sign;
	D.digits = Diff;
	return D;
}

// mult()
// Returns a BigInteger representing the product of this and N.
BigInteger BigInteger::mult(const BigInteger& N) const {
	BigInteger M;
	List T = this->digits;
	if(this->signum == -1) {
		negateList(T);
	}
	List L = N.digits;
	List Prod;

	L.moveBack();
	int shiftCounter = 0;
	int sign = 0;
	while(L.position() > 0) {
		List Copy = T;
		long element = (N.signum)*L.movePrev();
		scalarMultList(Copy, element);
		shiftList(Copy, shiftCounter);
		normalizeList(Copy);
		List PCopy = Prod;
		sumList(Prod, Copy, PCopy, 1, 1);
		normalizeList(Prod);
		shiftCounter += 1;
	}
	if((this->signum == -1 && N.signum == 1) || (this->signum == 1 && N.signum == -1)) {
		M.signum = -1;
	} else {
		M.signum = 1;
	}
	if(Prod.length() == 0) {
		M.signum = 0;
	}
	M.digits = Prod;
	return M;
}

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

// operator+()
// Returns the sum A+B.
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
	return A.BigInteger::add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
	A = A.BigInteger::add(B);
	return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
	return A.BigInteger::sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
	A = A.BigInteger::sub(B);
	return A;
}

// operator*()
// Returns the product A*B.
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
	return A.BigInteger::mult(B);
}

// operator*=()
// Overwrites A with the product A*B.
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
	A = A.BigInteger::mult(B);
	return A;
}
