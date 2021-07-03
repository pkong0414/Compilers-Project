//tree.cpp

#include "node.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "tree.h"

void Tree::buildTree( std::string input ){
    //This function will contain functions that handle the string comparison operation
    //as well as set up new nodes to be inserted into the tree.

	 if( input.find("\r") != std::string::npos ){
	 	input.erase( input.find("\r") );
	 }
	 if( input.find("\n") != std::string::npos ){
	 	input.erase( input.find("\n") );
	 }

	 printf( "input: %s\n", input.c_str() );

    int inputLen = input.length();
    

	 
	 //test output
    std::cout << "inputLen is: " << inputLen << std::endl;
	
	 //if the tree does not have a root we will immediately attach a node to root.
    if( !root ) {
        Node *newNode;
        newNode = new Node;
        newNode->indents = "";
        newNode->strLength = inputLen;
        newNode->firstLetter.append( 1, input.at(0) );
        newNode->depth = 0;
        newNode->left = newNode->right = nullptr;			//setting up left and right pointer to null
        insert( root, newNode, input );
    }
    //if we cannot find a comparable string from any of the nodes
    //then we will make a new node to attach to the tree.
    if( searchNode( input ) == false ){
        //if search node returns false it means we've found nothing.
        //this means we will make a new node to insert.

        Node *newNode;
        newNode = new Node;
		newNode->indents = "";
        newNode->strLength = inputLen;
        newNode->firstLetter.append( 1, input.at(0) );
        newNode->depth = 0;
        newNode->left = newNode->right = nullptr;			//setting up left and right pointer to null

        //TODO we need to change the nature of the insertion for adding nodes
        insert( root, newNode, input );
    }


}

void Tree::insert( Node *& nodePtr, Node *& newNode, std::string input ){
    //This function will handle the insertion of nodes.

	 //inserting the new node
    if(!nodePtr) {
        newNode->characters.insert( input );
        nodePtr = newNode;
    }
	 //traversing the BST to attach the new node
    else if(newNode->firstLetter < nodePtr->firstLetter) {
        newNode->depth += 1;
		newNode->indents.append( "--" );
        insert(nodePtr->left, newNode, input);
    }
    else if(newNode->firstLetter > nodePtr->firstLetter) {
        newNode->depth += 1;
		newNode->indents.append( "--" );
		insert(nodePtr->right, newNode, input);
    }
}

void Tree::printInOrder( Node *nodePtr, std::ofstream &file, std::string fileName ) const{
    //In Order node traversal:
    //left
    //root
    //right
	 
	 if( nodePtr ){
        printInOrder( nodePtr->left, file, fileName );
        std::set<std::string>::iterator it = nodePtr->characters.begin();
        file << "\n" << nodePtr->indents << nodePtr->firstLetter << ": ";
        while( it != nodePtr->characters.end() ) {
            std::cout << *it << " depth: " << nodePtr->depth << std::endl;
            file << *it << " ";
            it++;
        }
        printInOrder( nodePtr->right, file, fileName );
    }
}

void Tree::printPreOrder( Node *nodePtr, std::ofstream &file, std::string fileName ) const{
    //Pre Order node traversal:
    //root
    //left
    //right
    
	 if( nodePtr ){
        std::set<std::string>::iterator it = nodePtr->characters.begin();
        file << "\n" << nodePtr->indents << nodePtr->firstLetter << ": ";
		while( it != nodePtr->characters.end() ) {
          std::cout << *it << " depth: " << nodePtr->depth << std::endl;
          file << *it << " ";
          it++;
        }
        printPreOrder( nodePtr->left, file, fileName );
        printPreOrder( nodePtr->right, file, fileName );
    }
}

void Tree::printPostOrder( Node *nodePtr, std::ofstream &file, std::string fileName ) const{
    //Post Order node traversal:
    //left
    //right
    //root

    std::set<std::string> nodeList;
	 if( nodePtr ){
        printPostOrder( nodePtr->left, file, fileName );
        printPostOrder( nodePtr->right, file, fileName );
        std::set<std::string>::iterator it = nodePtr->characters.begin();
        file << "\n" << nodePtr->indents << nodePtr->firstLetter << ": ";
        while( it != nodePtr->characters.end() ) {
            std::cout << *it << " depth: " << nodePtr->depth << std::endl;
            file << *it << " ";
            it++;
        }
    }
}

bool Tree::searchNode( std::string input ){
    // This function will making comparison of the strings lengths.
	 // If the string length matches any node's string length, it will attach to the set.
	 // Since sets only allow unique strings, any matches will be rejected.

    // 3 cases:
    // - 1. we found a node with equal string comparison and matching string literals. - returns true
    // - 2. we found a node with equal string comparison and no matching string literals. - returns true
    // - 3. we found nothing at all - returns false

    Node *nodePtr = root;
    std::string inputFrontLetter;
    inputFrontLetter.append( 1, input.at(0) );
    std::cout << "inputFrontLetter: " << inputFrontLetter << std::endl;
    while( nodePtr ){
        //condition that the correct node's strLength and input's length matches is found.
        //std::cout << "strLen: " << strLen << std::endl;
        //std::cout << "nodePtr strLength: " << nodePtr->strLength << std::endl;
        std::cout << "node front letter: " << nodePtr->firstLetter << std::endl;
        if( nodePtr->firstLetter.compare( inputFrontLetter ) == 0 ) {
            std::cout << "first letter matches!" << std::endl;
            std::cout << "input string: " << input << std::endl;
            nodePtr->characters.insert( input );
            return true;
        }
        else {
            if( nodePtr->firstLetter.compare( inputFrontLetter ) < 0 )
                nodePtr = nodePtr->right;
            else
                nodePtr = nodePtr->left;
        }
    }
    return false;
}

