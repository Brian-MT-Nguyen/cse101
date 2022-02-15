#------------------------------------------------------------------------------
# Brian Nguyen, bnguy118
# 2022 Winter CSE 101 PA5
# Makefile
# The makefile that runs and compilies the files to run the program of PA5
# Also removes computer geneterated files, formats code, and checks for
# memory leaks in clients
#
#  make                makes Shuffle
#  make ListTest       make ListTest
#  make clean          removes binary files
#  make check1         runs valgrind on ListClient
#  make check2         runs valgrind on Shuffle with CLA 35
#------------------------------------------------------------------------------

Shuffle : Shuffle.o List.o
		g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o

Shuffle.o : List.h Shuffle.cpp
		g++ -std=c++17 -Wall -c Shuffle.cpp

ListTest : ListTest.o List.o
		g++ -std=c++17 -Wall -o ListTest ListTest.o List.o

ListTest.o : List.h ListTest.cpp
		g++ -std=c++17 -Wall -c ListTest.cpp

List.o : List.h List.cpp
		g++ -std=c++17 -Wall -c List.cpp

clean :
		rm -f Shuffle Shuffle.o ListTest ListTest.o List.o

check1 : ListClient
		valgrind --leak-check=full ListTest

check2 : Shuffle
		valgrind --leak-check=full Shuffle 35
