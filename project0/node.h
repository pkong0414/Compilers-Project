//node.h

#include <string>
#include <set>
#ifndef NODE_H
#define NODE_H

struct Node{
    std::set<std::string> characters;
    std::string indents;
    std::string firstLetter;
    int depth;
    int strLength;
    Node *left;
    Node *right;
	 
};

#endif
