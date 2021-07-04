//tree.cpp

#include "node.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "tree.h"

//Function for building nodes
struct Node *nodeConstruct( std::string word, std::string currentIndents ) {
    struct Node *newNode = new struct Node;
    newNode->nodeName = word;
    newNode->depth = 0;
    newNode->indents = currentIndents;
    return newNode;
}

//Function for inserting nodes properly.
struct Node *insertNode(struct Node *nodePtr, std::string input, std::string indent ) {
/*      if(thisNode == NULL) {
                return buildNode(level, value, word);
        } else if(value.compare(thisNode->value) > 0) {
                if(nodePtr->length > word.length()) {
                        thisNode->length > word.length();
                }
                thisNode->right = insertNode(thisNode->right, length, level++, value, word);
        } else if(value.compare(thisNode->value) < 0) {
                /->left = insertNode(thisNode->left, level++, value, words);
                if(nodePtr->length < word.length()) {
                        nodePtr->length < word.length();
                }
                nodePtr->left = insertNode(nodePtr->left, length, level++, value, word);
        } else if(value.compare(thisNode->value) == 0) {
                nodePtr->words.insert(word);
        }*/

    if(!nodePtr) {
        //if a node doesn't exist
        struct Node *newNode;
        newNode = nodeConstruct( input, indent );
        return newNode;
    } else {

        struct Node *newNode;
        newNode = nodeConstruct( input, indent );
        nodePtr->children.insert( newNode );
//        std::cout << newNode->indents << newNode->nodeName << std::endl;

    }

//    if(newNode->stringLength < nodePtr->stringLength) {
//        cout << "newNode Length is smaller, let's traverse left" << endl;
//        newNode->level++;
//        nodePtr->left = insertNode(nodePtr->left, newNode);
//
//    } else if(newNode->stringLength > nodePtr->stringLength) {
//        cout << "newNode Length is bigger, let's traverse right" << endl;
//        newNode->level++;
//        nodePtr->right = insertNode(nodePtr->right, newNode);
//    }
//
//    //due to the nature of the parser a more direct method will be needed
//
//    //rather than using string length,
//    //the method should be looking at current nodePtr and moving towards right child.
//
    return nodePtr;
}

////Defining method to print Preorder traversal
void printPreorder( struct Node* root ) {
//    std::cout << "inside printPreorder function" << std::endl;

    if( root )
    {
        std::cout << root->indents << root->nodeName << std::endl;
        std::set<struct Node*>::iterator move = root->children.begin();
        printPreorder(*move);
        while( move != root->children.end() ) {
            move++;

            if( move == root->children.end() ){
                return;
            }

            printPreorder(*move);

        }
    }

    return;
}


/* These are commented out since they are unnecessary */

//void Tree::printPreOrder( Node *nodePtr, std::ofstream &file, std::string fileName ) const{
//    //Pre Order node traversal:
//    //root
//    //left
//    //right
//
//	 if( nodePtr ){
//        std::set<std::string>::iterator it = nodePtr->characters.begin();
//        file << "\n" << nodePtr->indents << nodePtr->firstLetter << ": ";
//		while( it != nodePtr->characters.end() ) {
//          std::cout << *it << " depth: " << nodePtr->depth << std::endl;
//          file << *it << " ";
//          it++;
//        }
//        printPreOrder( nodePtr->left, file, fileName );
//        printPreOrder( nodePtr->right, file, fileName );
//    }
//}
//
//void Tree::printPostOrder( Node *nodePtr, std::ofstream &file, std::string fileName ) const{
//    //Post Order node traversal:
//    //left
//    //right
//    //root
//
//    std::set<std::string> nodeList;
//	 if( nodePtr ){
//        printPostOrder( nodePtr->left, file, fileName );
//        printPostOrder( nodePtr->right, file, fileName );
//        std::set<std::string>::iterator it = nodePtr->characters.begin();
//        file << "\n" << nodePtr->indents << nodePtr->firstLetter << ": ";
//        while( it != nodePtr->characters.end() ) {
//            std::cout << *it << " depth: " << nodePtr->depth << std::endl;
//            file << *it << " ";
//            it++;
//        }
//    }
//}
//
//bool Tree::searchNode( std::string input ){
//    // This function will making comparison of the strings lengths.
//	 // If the string length matches any node's string length, it will attach to the set.
//	 // Since sets only allow unique strings, any matches will be rejected.
//
//    // 3 cases:
//    // - 1. we found a node with equal string comparison and matching string literals. - returns true
//    // - 2. we found a node with equal string comparison and no matching string literals. - returns true
//    // - 3. we found nothing at all - returns false
//
//    Node *nodePtr = root;
//    std::string inputFrontLetter;
//    inputFrontLetter.append( 1, input.at(0) );
//    std::cout << "inputFrontLetter: " << inputFrontLetter << std::endl;
//    while( nodePtr ){
//        //condition that the correct node's strLength and input's length matches is found.
//        //std::cout << "strLen: " << strLen << std::endl;
//        //std::cout << "nodePtr strLength: " << nodePtr->strLength << std::endl;
//        std::cout << "node front letter: " << nodePtr->firstLetter << std::endl;
//        if( nodePtr->firstLetter.compare( inputFrontLetter ) == 0 ) {
//            std::cout << "first letter matches!" << std::endl;
//            std::cout << "input string: " << input << std::endl;
//            nodePtr->characters.insert( input );
//            return true;
//        }
//        else {
//            if( nodePtr->firstLetter.compare( inputFrontLetter ) < 0 )
//                nodePtr = nodePtr->right;
//            else
//                nodePtr = nodePtr->left;
//        }
//    }
//    return false;
//}

