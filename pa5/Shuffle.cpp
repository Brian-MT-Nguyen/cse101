/*********************************************************************************
 * Brian Nguyen, bnguy118
 * 2022 Winter CSE101 PA5
 * Shuffle.cpp
 * Determines how many shuffles are necessary to bring a List back into its
 * original order based on List size using the List ADT.
 *********************************************************************************/
#include "List.h"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void shuffle(List &D) {
  // Initialize variables to use for Lists and lengths
  List A;
  List B;
  int lengthD = D.length();
  int lengthA = lengthD / 2;
  int lengthB = lengthD - lengthA;

  // Appends D to A and B
  D.moveFront();
  for (int i = 0; i < lengthA; i++) {
    A.insertBefore(D.moveNext());
  }
  A.moveFront();

  for (int i = 0; i < lengthB; i++) {
    B.insertBefore(D.moveNext());
  }
  B.moveFront();

  // Appends A and B in alternating order to a empty D list
  D.clear();
  for (int i = 0; i < lengthA; i++) {
    D.insertBefore(B.moveNext());
    D.insertBefore(A.moveNext());
  }

  // Check if n is odd then add one more B to finish
  if (lengthD % 2 != 0) {
    D.insertBefore(B.moveNext());
  }
  D.moveFront();
}

int main(int argc, char *argv[]) {
  // Initialize variable to store input
  int deckSize;

  // Parse command-line and check for invalid arguments
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <number of decks>" << endl;
    return (EXIT_FAILURE);
  }
  // Set deckSize to argv[1] for the List
  deckSize = atoi(argv[1]);
  if (deckSize <= 0) {
    cerr << "Invalid Deck Size" << endl;
    exit(EXIT_FAILURE);
  }

  // Initialize Lists and variable for shuffle
  int shuffleCounter = 1;
  List Deck;
  List Copy;

  // Start Table (String Output)
  cout << "deck size       shuffle count" << endl;
  cout << "------------------------------" << endl;

  // Start outer loop to shuffle deck size of i
  for (int i = 1; i <= deckSize; i++) {
    // Fill List with 0 to i-1
    for (int j = 0; j < i; j++) {
      Deck.insertBefore(j);
    }
    // Set Copy to Deck to check if equal when shuffled
    Copy = Deck;

    // Shuffle the deck until Copy equals Deck
    shuffle(Deck);
    while (!(Deck == Copy)) {
      shuffle(Deck);
      shuffleCounter += 1;
    }

    // Output shuffling data
    cout << setw(2) << left << i << "              " << setw(2) << left
         << shuffleCounter << endl;

    // Reset vars for next iteration
    Deck.clear();
    Copy.clear();
    shuffleCounter = 1;
  }
}
