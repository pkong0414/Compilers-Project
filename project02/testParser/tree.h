#include "node.h"
#include <iostream>
#include <string>
#include <fstream>

#ifndef TREE_H
#define TREE_H

/*  This file will be reconstructed in order to accommodate the parser. Goal is to generate a parse tree that will
 *  output in preorder.
 *
 */

//struct Node *buildTree(struct node *nodePoint,string fileName);
struct Node *nodeConstruct( std::string word, std::string currentIndents );
struct Node *insertNode( struct Node *nodePtr, std::string input, std::string indent );

//void printToken(ofstream &file, int level, set<string> token);
//void printInorder(struct Node *root);
void printPreorder(struct Node *root);
//void printPostorder(ofstream &file, struct node *root);


#endif
