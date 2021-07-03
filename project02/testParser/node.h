//node.h

#include <string>
#include <set>
#ifndef NODE_H
#define NODE_H

struct Node{
    //characters will be changed to strings in order to accomodate the parser.

    //nodeString will store Operators,IDs, Numbers in the node.
    std::string nodeName;
    std::set<struct Node *> children;
    std::string indents;
    bool nonterminal;
    int depth;
    int childCount;

};

#endif
