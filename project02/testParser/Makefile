#this is the make file for project 2
#!/bin/bash

CC = g++
CXXFLAGS = -Wall -std=c++11
TARGET = frontEnd
SRC = main.cpp scanner.cpp fileHandling.cpp tree.cpp parser.cpp
OBJ = main.o scanner.o fileHandling.o tree.o parser.o

$TARGET: $(OBJ)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJ)

    %.o     : %.c

.PHONY: clean

clean:
	rm -f $(TARGET) *.o
	echo cleaning done