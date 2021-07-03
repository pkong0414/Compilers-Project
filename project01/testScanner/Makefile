#this is the make file for project 1
#!/bin/bash

CC = g++
CXXFLAGS = -Wall -std=c++11
TARGET = scanner
SRC = main.cpp testScanner.cpp fileHandling.cpp
OBJ = main.o testScanner.o fileHandling.o

$TARGET: $(OBJ)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJ)

    %.o     : %.c

.PHONY: clean

clean:
	rm -f $(TARGET) *.o
	echo cleaning done