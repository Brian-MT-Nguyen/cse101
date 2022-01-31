#------------------------------------------------------------------------------
# Brian Nguyen, bnguy118
# 2022 Winter CSE 101 PA3
# Makefile
# The makefile that runs and compilies the files to run the program of PA3
# Also removes computer geneterated files, formats code, and checks for
# memory leaks in clients
#
#  make                     makes FindComponents
#  make GraphTest           makes GraphTest
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindComponents for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o $(BASE_OBJECTS)
		$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest : GraphTest.o $(BASE_OBJECTS)
		$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
		$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
		$(COMPILE) FindComponents.c

GraphTest.o : GraphTest.c $(HEADERS)
		$(COMPILE) GraphTest.c

GraphClient.o : GraphClient.c $(HEADERS)
		$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
		$(COMPILE) $(BASE_SOURCES)

clean :
		$(REMOVE) FindComponents GraphTest GraphClient FindComponents.o GraphTest.o GraphClient.o $(BASE_OBJECTS)

format:
	clang-format -i -style=file *.[ch]

checkFind : FindComponents
		$(MEMCHECK) FindComponents in8 junk8

checkClient : GraphClient
		$(MEMCHECK) GraphClient

