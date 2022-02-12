#------------------------------------------------------------------------------
#  Makefile for List ADT
#
#  make                makes Shuffle
#  make ListClient     make ListClient
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
		g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o

Shuffle.o : List.h Shuffle.cpp
		g++ -std=c++17 -Wall -c Shuffle.cpp

ListClient : ListClient.o List.o
		g++ -std=c++17 -Wall -o ListClient ListClient.o List.o

ListClient.o : List.h ListClient.cpp
		g++ -std=c++17 -Wall -c ListClient.cpp

List.o : List.h List.cpp
		g++ -std=c++17 -Wall -c List.cpp

clean :
		rm -f Shuffle Shuffle.o ListClient ListClient.o List.o

check1 : ListClient
		valgrind --leak-check=full ListClient

check2 : Shuffle
		valgrind --leak-check=full Shuffle 35
format:
	clang-format -i -style=file *.[ch]
