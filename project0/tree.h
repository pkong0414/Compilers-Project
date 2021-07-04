#include "node.h"
#include <iostream>
#include <string>
#include <fstream>

#ifndef TREE_H
#define TREE_H

class Tree{
private:

    Node *root;											 //head of the node
	
    void insert(Node *&, Node *&, std::string);					 //inserting node
    void printInOrder(Node *, std::ofstream &, std::string ) const;		    	 //print nodes in order
    void printPreOrder(Node *, std::ofstream &, std::string ) const;           //print nodes in Pre Order
    void printPostOrder(Node *, std::ofstream &, std::string ) const;          //print nodes in Post Order
public:

    Tree()										//constructor
    { root = nullptr; }

    void buildTree(std::string);

	 void printInOrder(std::ofstream &file, std::string fileName) const{
		 printInOrder(root, file, fileName);
	 }

	 void printPreOrder(std::ofstream &file, std::string fileName) const{
		 printPreOrder(root, file, fileName);
		 
    }

    void printPostOrder(std::ofstream &file, std::string fileName) const{
		 printPostOrder(root, file, fileName);
    }

    bool searchNode(std::string);
	
};


#endif
