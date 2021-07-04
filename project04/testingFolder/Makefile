#this is the make file for project 4
#!/bin/bash

CC = g++
CXXFLAGS = -Wall -std=c++11
TARGET = compfs
SRC = main.cpp scanner.cpp fileHandling.cpp tree.cpp parser.cpp st.cpp
OBJ = main.o scanner.o fileHandling.o tree.o parser.o st.o

$TARGET: $(OBJ)
	$(CC) $(CPPFLAGS) -o $(TARGET) $(OBJ)

    %.o     : %.c

.PHONY: clean

clean:
	rm -f $(TARGET) *.o