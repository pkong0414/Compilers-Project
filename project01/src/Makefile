#this is the make file for project 1
#!/bin/bash

CC = g++
CXXFLAGS = -Wall -std=c++11
TARGET = scanner
SRC = main.cpp scanner.cpp fileHandling.cpp
OBJ = main.o scanner.o fileHandling.o

$TARGET: $(OBJ)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp
scanner.o: scanner.cpp
fileHandling.o: fileHandling.cpp


.PHONY: clean

clean:
	rm -f $(TARGET) *.o
	echo cleaning done