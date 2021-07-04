//tree.cpp

#include "node.h"
#include "scanner.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <fstream>
#include <stack>
#include "tree.h"
#include "st.h"

//This will count the number of loops in a program.
int loopCount = 0;

//This will count the number of ifs in the program.
int ifCount = 0;

//temp var counter
int tempCount = 0;

//counters for begin and end
int beginCount = 0;
int endCount = 0;



//these will be used to handle variable storage
static bool initialVar = true;                     //intent of this global is for the first time use for STV stack.
static bool globalUsed = false;
static bool stackUsed = false;
static bool intUsed = false;
static int globalUseIndex;
static int currentVarCount = 0;                    //this will be used to hold the currentVarCount.
static ST Global;                           //this will be used to hold the global stack.
static ST Stack;                            //this will be used to hold the local stack.
static std::stack<std::string> intStack;                         //this will be used to hold the int local stack.
std::string returnedVar;                    //this will be used to hold the return variable.


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

//we will now be making a method to do the code assembly

void asmCodeGen( struct Node* root ) {
    //This section will be for Project 4
    //we'll be breaking each section into relevant sections for the given grammar.

    //the idea is to always go traversals left to right.
    //However, we will prioritize subnodes with higher depth, because it indicates precedence.

    //testing output
    std::cout << root->indents << root->nodeName << std::endl;


    if (root->nodeName == "<program>") {
        std::set<struct Node *>::iterator it = root->children.begin();
        for (; it != root->children.end(); ++it) {
            asmCodeGen(*it);
        }
        return;
    }

    if (root->nodeName == "<block>") {
        std::set<struct Node *>::iterator it = root->children.begin();
        for (; it != root->children.end(); ++it) {

            //The begin case of block
            if ((*it)->nodeName == "begin") {
                beginCount++;
            }

            asmCodeGen(*it);
            /* end of program case*/
            //the final end where we write stop
            if ( (*it)->nodeName == "end") {
                ++endCount;
                std::cout << "begin: " << beginCount << std::endl;
                std::cout << "end: " << endCount << std::endl;
                if ( beginCount == endCount && endCount > 0 ) {
                    return;
                }
            }
        }
        return;
    }

    //<vars> cases
    if (root->nodeName == "<vars>") {
        //this will handle the operation for variable productions

        //we'll be implementing stacks here
        std::string identifier;
        if( initialVar == true ) {
            std::set<struct Node *>::iterator it;
            int i = 0;
            for (it = root->children.begin(); it != root->children.end(); ++it) {
                //moving to the 3rd element
                if( i == 4 ) {
                    asmCodeGen( *it );
                    initialVar = false;
                    return;
                }

                if (i == 1) {
                    //storing identifier for now
                    identifier = (*it)->nodeName;
                }

                if (i == 3) {
                    //pushing variable and value into the global stack
                    std::cout << (*it)->nodeName << std::endl;
                    if( Global.find( (*it)->nodeName ) == -1 )
                        Global.insert( identifier, std::stoi ( (*it)->nodeName ) );
                }

                i++;
            }

        }
        if( initialVar == false ) {

            std::set<struct Node *>::iterator it;
            int i = 0;
            for (it = root->children.begin(); it != root->children.end(); ++it) {
                //moving to the 3rd element
                if (i == 3) {
                    //writing the assembly operation
                    *outFile << "LOAD " << (*it)->nodeName << std::endl;
                }
                i++;
            }
            i = 0;
            for (it = root->children.begin(); it != root->children.end(); ++it) {
                //moving to the 1st element
                if (i == 1) {
                    //writing the assembly operation for the storage
                    *outFile << "STORE " << (*it)->nodeName << std::endl;
                }
                i++;
                if (i == 6) {
                    asmCodeGen(*it);
                }
            }
            return;
        }
    }

    //<in> cases
    if (root->nodeName == "<in>") {

        std::set<struct Node *>::iterator it;
        int i = 0;
        for (it = root->children.begin(); it != root->children.end(); ++it) {
            //moving to the 3rd element
            if (i == 2) {
                //writing the assembly operation
                *outFile << "READ " << (*it)->nodeName << std::endl;
            }
            i++;
        }
        return;
    }

    //<stats> cases
    if (root->nodeName == "<stats>") {
        std::set<struct Node *>::iterator it = root->children.begin();
        for (; it != root->children.end(); ++it) {
            asmCodeGen(*it);
        }
        return;
    }

    //<mStat> cases
    if (root->nodeName == "<mStat>") {
        std::set<struct Node *>::iterator it = root->children.begin();
        for (; it != root->children.end(); ++it) {
            asmCodeGen(*it);
        }
        return;
    }

    //<stat> cases
    if (root->nodeName == "<stat>") {
        std::set<struct Node *>::iterator it = root->children.begin();
        for (; it != root->children.end(); ++it) {
            asmCodeGen(*it);
        }
    }

    //<if> cases
    if (root->nodeName == "<iffy>") {
        //<iffy> -> [ <expr> <R0> <expr> ] then <stat>

        //loopNum will keep the local loop number
        int ifNum = ifCount;
        //exprCount will keep track of the expressions
        int exprCount = 0;

        //This Node will hold the relationalOperator
        struct Node *relationalNode;

        //These Nodes will hold the expression node
        struct Node *exprNode1;
        struct Node *exprNode2;

        //index counter
//        int i = 0;

        std::set<struct Node *>::iterator it = root->children.begin();

        std::cout << "iffy children size: " << root->children.size() << std::endl;
        for (; it != root->children.end(); ++it) {
            //debugging output
//            std::cout << "i: " << i << std::endl;
            std::cout << "children node: " << (*it)->nodeName << std::endl;

            if ((*it)->nodeName == "<expr>") {

                if( outputDelayCheck(*it) ) {

                    asmCodeGen(*it);

                } else {

                    //these assume the node will have 1 child.
                    //the second expression
                    if (exprCount == 1) {
                        exprNode2 = grabNode(*it);
                        exprCount++;
                    }
                    //the first expression
                    if (exprCount == 0) {
                        exprNode1 = grabNode(*it);
                        exprCount++;
                    }

                    if (exprCount == 2) {
                        if (exprNode1->nodeName == "ident_tk") {
                            //conditionals for first expression being an id.
                            *outFile << "LOAD " << exprNode1->nodeName << std::endl;
                            *outFile << "SUB " << exprNode2->nodeName << std::endl;
                        } else {
                            //default condition ( second expr being an id ).
                            *outFile << "LOAD " << exprNode2->nodeName << std::endl;
                            *outFile << "SUB " << exprNode1->nodeName << std::endl;
                        }

                    }
                }
            }//end of if( expr )

            //we need the node at RO
            //which is what we need for grabbing the RO node.
            if ((*it)->nodeName == "<RO>") {
                //for now we will hold on to this node
                //till after we grab the second expression

                //debugging output
                std::cout << "grabbing relationalOP node now.\n";

                relationalNode = grabNode(*it);

                std::cout << "relationalNode: " << relationalNode->nodeName << std::endl;

            }

            if ( (*it)->nodeName == "]") {
//                if (relationalNode->nodeName == "<") {
//                    //less than
//                    *outFile << "BRZPOS OutIf" << ifNum << std::endl;
//                }
                if (relationalNode->nodeName == "=<") {
                    //less than or equal to
                    *outFile << "BRPOS OutIf" << ifNum << std::endl;
                }
//                if (relationalNode->nodeName == ">") {
//                    //greater than
//                    *outFile << "BRZNEG OutIf" << ifNum << std::endl;
//                }
                if (relationalNode->nodeName == "=>") {
                    //greater than or equal to
                    *outFile << "BRNEG OutIf" << ifNum << std::endl;
                }
                if (relationalNode->nodeName == "::") {
                    //inequality
                    *outFile << "BRZERO OutIf" << ifNum << std::endl;
                }
                if (relationalNode->nodeName == "==") {
                    //equivalence
                    *outFile << "BRPOS OutIf" << ifNum << std::endl;
                    *outFile << "BRNEG OutIf" << ifNum << std::endl;

                }
                ifCount++;
            }//end of RO code gen

            //debug index
//            i++;
        }//end of for loop

        //these are the conditionals to jump out for if statement.
        //that means we have to expressions and
        //are ready to lay in the conditional for the asm code.

        for (it = root->children.begin(); it != root->children.end(); ++it) {
            //debugging output
            std::cout << "node: " << (*it)->nodeName << std::endl;

            if ((*it)->nodeName == "<block>") {
                asmCodeGen(*it);
            }
        }

        //this is the jumping out mechanism
        *outFile << "OutIf" << ifNum << ": NOOP" << std::endl;

        return;
    }

    //<loop> cases
    if (root->nodeName == "<loop>") {
        //<loop> -> [ <expr> <RO> <expr> ] <stat>

        //loopNum will keep the local loop number
        int loopNum = loopCount;
        //exprCount will keep track of the expressions
        int exprCount = 0;

        //This Node will hold the relationalOperator
        struct Node* relationalNode;

        //These Nodes will hold the expression node
        struct Node* exprNode1;
        struct Node* exprNode2;

        //debugging index
        int i = 0;

        std::set<struct Node *>::iterator it = root->children.begin();
        for( ; it != root->children.end(); ++it ){
            //debugging output
            std::cout << "i: " << i << std::endl;
            std::cout << "children node: " << (*it)->nodeName << std::endl;

            //dealing with the open bracket
            if( (*it)->nodeName == "[" ){
                *outFile << "In" << loopNum << ": NOOP" << std::endl;
            }

            if( (*it)->nodeName == "<expr>" ){


                if( outputDelayCheck(*it) ) {

                    asmCodeGen(*it);

                } else {

                    //these assume the node will have 1 child.
                    //the second expression
                    if (exprCount == 1) {
                        exprNode2 = grabNode(*it);
                        exprCount++;
                    }
                    //the first expression
                    if (exprCount == 0) {
                        exprNode1 = grabNode(*it);
                        exprCount++;
                    }

                    if (exprCount == 2) {
                        if (exprNode1->nodeName == "ident_tk") {
                            //conditionals for first expression being an id.
                            *outFile << "LOAD " << exprNode1->nodeName << std::endl;
                            *outFile << "SUB " << exprNode2->nodeName << std::endl;
                        } else {
                            //default condition ( second expr being an id ).
                            *outFile << "LOAD " << exprNode2->nodeName << std::endl;
                            *outFile << "SUB " << exprNode1->nodeName << std::endl;
                        }

                    }
                }

            }//end of if( expr )

            //we are going to use findLeftMost() since it's a single traversal
            //which is what we need for grabbing the RO node.
            if( (*it)->nodeName == "<RO>" ){
                //for now we will hold on to this node
                //till after we grab the second expression
                relationalNode = grabNode( *it );

            }

            if( (*it)->nodeName == "]" ){
//                if( relationalNode->nodeName == "<"){
//                    //less than
//                    *outFile << "BRZPOS Out" << loopNum <<std::endl;
//                }
                if( relationalNode->nodeName == "=<"){
                    //less than or equal to
                    *outFile << "BRPOS Out" << loopNum << std::endl;
                }
//                if( relationalNode->nodeName == ">"){
//                    //greater than
//                    *outFile << "BRZNEG Out" << loopNum << std::endl;
//                }
                if( relationalNode->nodeName == "=>"){
                    //greater than or equal to
                    *outFile << "BRNEG Out" << loopNum << std::endl;
                }
                if( relationalNode->nodeName == "::"){
                    //inequality
                    *outFile << "BRZERO Out" << loopNum << std::endl;
                }
                if( relationalNode->nodeName == "=="){
                    //equivalence
                    *outFile << "BRNEG Out" << loopNum << std::endl;
                    *outFile << "BRPOS Out" << loopNum << std::endl;
                }
                loopCount++;
            }

            //debug index
//            i++;
        }//end of for loop

        //these are the conditional statements to jump out of loop.
        //that means we have to expressions and
        //are ready to lay in the conditional for the asm code.


        for (it = root->children.begin(); it != root->children.end(); ++it) {
            //debugging output
//            std::cout << "node: " << (*it)->nodeName << std::endl;

            if ((*it)->nodeName == "<stat>") {
                asmCodeGen(*it);
            }
        }

        //this will be the looping mechanism
        *outFile << "BR In" << loopNum << std::endl;

        //this is the jumping out mechanism
        *outFile << "Out" << loopNum << ": NOOP" << std::endl;

        return;
    }

    //<assign> case
    if (root->nodeName == "<assign>") {
        //this is on the assumption we are on the left side of the tree doing the assignment
        //we are expecting an identifier for the first child node.
        std::set<struct Node *>::reverse_iterator it = root->children.rbegin();
        for (; it != root->children.rend(); ++it) {
            //debugging output
            std::cout << (*it)->nodeName << std::endl;
            //we need a case for both a single int or id

            //this will satisfy the case of multi int/id expression.
            if (it == root->children.rbegin()) {
                //checking for multi int/id expression
                if( outputDelayCheck(*it) ){
                    //check is true so we let asmCodeGen method handle.
                    asmCodeGen(*it);
                } else {
                    //otherwise we assume that it is a single int/id.
                    *outFile << "LOAD ";
                    asmCodeGen(*it);
                }
            }
            if( (*it)->nodeName == "=" ) {
                it++;
                *outFile << "STORE " << (*it)->nodeName << std::endl;

            }
        }

        //may need unfinished need to look at the asm assign portion of code
        return;
    }

    //<out> case
    if (root->nodeName == "<out>") {
        //we need to hold the currentVarCount in the case this expression gets goes a lot down and we have to fetch
        //the right variable within the local stack.
        int stackCount = currentVarCount;
        struct Node* exprNode;
        std::set<struct Node *>::reverse_iterator it = root->children.rbegin();
        //we want to use the 2nd node
        int i = root->children.size() - 1;
        it++;
        int currentTempCount = tempCount;
        if( outputDelayCheck( *it ) == true ) {
            for (; it != root->children.rend(); ++it) {
                std::cout << (*it)->nodeName << std::endl;
                asmCodeGen(*it);
                i--;
            }
            it = root->children.rbegin();
            it++;
            *outFile << "WRITE T" << currentTempCount << std::endl;
            return;
        } else {
            for (; it != root->children.rend(); it++) {
                if( i == 3 ) {
                    std::cout << "<out>: " << (*it)->nodeName << std::endl;
                    asmCodeGen(*it);
                    exprNode = grabNode(*it);
                    //searching Global to find variable.

                    *outFile << "WRITE ";
                    *outFile << exprNode->nodeName << std::endl;
//                    if( intUsed == true ) {
//                        *outFile << intStack.top() << std::endl;
//                        intStack.pop();
//                        intUsed = false;
//                    } else {
//                        if( globalUsed == true ) {
//                            *outFile << Global.getIndexVar( globalUseIndex ) << std::endl;
//                            globalUsed = false;
//                            globalUseIndex = -1;
//                        } else if ( stackUsed == true ) {
//                            *outFile << Stack.getIndexVar( stackCount ) << std::endl;
//                            stackUsed = false;
//                        }
//                    }
                }
                i--;
            }
            return;
        }
        //finished with the out node
        return;
    }

    //<expr> case
    if (root->nodeName == "<expr>") {

        //<expr> -> <N> / <expr> | <N> * <expr> | <N>
        int stackCount = currentVarCount;
        //3 cases with expr:
        std::cout << root->children.size() << std::endl;
        std::set<struct Node *>::reverse_iterator it = root->children.rbegin();
        std::cout << "precheck: <expr>: " << (*it)->nodeName << std::endl;
        if ( root->children.size() == 3 ) {
            //1st case where we have 3 children
            //only way to account for precedence is to look at <R> due to this: ( <expr> )
            std::set<struct Node *>::iterator rightOP = root->children.begin();
            rightOP++;
            rightOP++;
            int currentTempCount = tempCount;

            //this is the case where left side has precedence
            //as well as the case where left side depth == right side depth
            std::set<struct Node *>::reverse_iterator it = root->children.rbegin();

            if (it == root->children.rbegin() && outputDelayCheck(*it) == true) {
                for (; it != root->children.rend(); ++it) {
                    if (it == root->children.rbegin()) {
                        asmCodeGen(*it);
                    } else if ((*it)->nodeName == "/") {
                        *outFile << "LOAD ";
                        it++;
                        asmCodeGen(*it);

                        if( intUsed == true ) {
                            *outFile << intStack.top() << std::endl;
                            intStack.pop();
                            intUsed = false;
                        } else {
                            if( globalUsed == true ) {
                                *outFile << Global.getIndexVar( globalUseIndex ) << std::endl;
                                globalUsed = false;
                                globalUseIndex = -1;
                            } else if ( stackUsed == true ) {
                                *outFile << Stack.getIndexVar( stackCount ) << std::endl;
                                stackUsed = false;
                            }
                        }
                        *outFile << "DIV T" << currentTempCount << std::endl;
                    } else if ((*it)->nodeName == "*") {
                        *outFile << "LOAD ";
                        it++;
                        asmCodeGen(*it);

                        if( intUsed == true ) {
                            *outFile << intStack.top() << std::endl;
                            intStack.pop();
                            intUsed = false;
                        } else {
                            if( globalUsed == true ) {
                                *outFile << Global.getIndexVar( globalUseIndex ) << std::endl;
                                globalUsed = false;
                                globalUseIndex = -1;
                            } else if ( stackUsed == true ) {
                                *outFile << Stack.getIndexVar( stackCount ) << std::endl;
                                stackUsed = false;
                            }
                        }
                        *outFile << "MULT T" << currentTempCount << std::endl;
                    }
                }
            } else {
                for (; it != root->children.rend(); ++it) {
                    if (it == root->children.rbegin()) {
                        *outFile << "LOAD ";
                        asmCodeGen(*it);

                        if( intUsed == true ) {
                            *outFile << intStack.top() << std::endl;
                            intStack.pop();
                            intUsed = false;
                        } else {
                            if( globalUsed == true ) {
                                *outFile << Global.getIndexVar( globalUseIndex ) << std::endl;
                                globalUsed = false;
                                globalUseIndex = -1;
                            } else if ( stackUsed == true ) {
                                *outFile << Stack.getIndexVar( stackCount ) << std::endl;
                                stackUsed = false;
                            }
                        }
                    } else if ((*it)->nodeName == "/") {
                        *outFile << "DIV ";
                        it++;
                        asmCodeGen(*it);

                        if( intUsed == true ) {
                            *outFile << intStack.top() << std::endl;
                            intStack.pop();
                            intUsed = false;
                        } else {
                            if( globalUsed == true ) {
                                *outFile << Global.getIndexVar( globalUseIndex ) << std::endl;
                                globalUsed = false;
                                globalUseIndex = -1;
                            } else if ( stackUsed == true ) {
                                *outFile << Stack.getIndexVar( stackCount ) << std::endl;
                                stackUsed = false;
                            }
                        }
                    } else if ((*it)->nodeName == "*") {
                        *outFile << "MULT ";
                        it++;
                        asmCodeGen(*it);

                        if( intUsed == true ) {
                            *outFile << intStack.top() << std::endl;
                            intStack.pop();
                            intUsed = false;
                        } else {
                            if( globalUsed == true ) {
                                *outFile << Global.getIndexVar( globalUseIndex ) << std::endl;
                                globalUsed = false;
                                globalUseIndex = -1;
                            } else if ( stackUsed == true ) {
                                *outFile << Stack.getIndexVar( stackCount ) << std::endl;
                                stackUsed = false;
                            }
                        }
                    }
                }
            }
            return;
        } else {
            //case of just a single non terminal <N>
            if ( outputDelayCheck(*it) == true) {
                //checking to see if there are more expressions inside this node.
                if (it == root->children.rbegin()) {
                    asmCodeGen(*it);
                }
            } else {
                //2nd case where <expr> has 1 children.
                asmCodeGen(*it);
                *outFile << "LOAD ";

                if( intUsed == true ) {
                    *outFile << intStack.top() << std::endl;
                    intStack.pop();
                    intUsed = false;
                } else {
                    if( globalUsed == true ) {
                        *outFile << Global.getIndexVar( globalUseIndex ) << std::endl;
                        globalUsed = false;
                        globalUseIndex = -1;
                    } else if ( stackUsed == true ) {
                        *outFile << Stack.getIndexVar( stackCount ) << std::endl;
                        stackUsed = false;
                    }
                }
                return;
            }
        }
    }

    //<N> case
    if (root->nodeName == "<N>") {
        //<N> -> <A> + <N> | <A> - <N> | <A>
        int stackCount = currentVarCount;

        //3 cases with <N>:
        std::cout << root->children.size() << std::endl;
        if( root->children.size() == 3 ) {
            //1st case where we have 3 children
            //we need to find where <R> contains 3 children for priority.

            //this is the case where left side has precedence
            //as well as the case where left side depth == right side depth
            std::set<struct Node *>::reverse_iterator it = root->children.rbegin();
            int currentTempCount = tempCount;

            for (; it != root->children.rend(); it++) {
                if (it == root->children.rbegin()) {
                    *outFile << "LOAD ";
                    asmCodeGen(*it);
                    if (intUsed == true) {
                        *outFile << intStack.top() << std::endl;
                        intStack.pop();
                        intUsed = false;
                    } else {
                        if (globalUsed == true) {
                            *outFile << Global.getIndexVar(globalUseIndex) << std::endl;
                            globalUsed = false;
                            globalUseIndex = -1;
                        } else {
                            *outFile << Stack.getIndexVar(stackCount) << std::endl;
                            stackUsed = false;
                        }
                    }
                } else if ((*it)->nodeName == "+") {
                    *outFile << "ADD ";
                    it++;
                    asmCodeGen(*it);
                    if (intUsed == true) {
                        *outFile << intStack.top() << std::endl;
                        intStack.pop();
                        intUsed = false;
                    } else {
                        if (globalUsed == true) {
                            *outFile << Global.getIndexVar(globalUseIndex) << std::endl;
                            globalUsed = false;
                            globalUseIndex = -1;
                        } else {
                            *outFile << Stack.getIndexVar(stackCount) << std::endl;
                            stackUsed = false;
                        }
                    }
                    *outFile << "STORE T" << currentTempCount << std::endl;
                } else if ((*it)->nodeName == "-") {
                    *outFile << "SUB ";
                    it++;
                    asmCodeGen(*it);
                    if (intUsed == true) {
                        *outFile << intStack.top() << std::endl;
                        intStack.pop();
                        intUsed = false;
                    } else {
                        if (globalUsed == true) {
                            *outFile << Global.getIndexVar(globalUseIndex) << std::endl;
                            globalUsed = false;
                            globalUseIndex = -1;
                        } else {
                            *outFile << Stack.getIndexVar(stackCount) << std::endl;
                            stackUsed = false;
                        }
                    }
                    *outFile << "STORE T" << currentTempCount << std::endl;
                }
            }
            tempCount++;
            return;
        } else {
            //2nd case where <N> has 1 children.
            std::set<struct Node *>::iterator it = root->children.begin();
            asmCodeGen(*it);
            return;
        }
    }

    //<A> case
    if (root->nodeName == "<A>") {
        //<A> -> % <A> | <R>
        //2 cases

        std::set<struct Node *>::reverse_iterator it = root->children.rbegin();
        //1st case we have 2 children
        if (root->children.size() == 2) {
            //this is the case for negation

            if(it == root->children.rbegin() && outputDelayCheck( *it ) == true ){
                asmCodeGen(*it);
                *outFile << "MULT -1" << std::endl;
                return;
            }
        } else if( root->children.size() == 1) {
            //this case we have 1 child and only wanna pass through
            asmCodeGen(*it);
            return;
        }
    }

    //<R> case
    if (root->nodeName == "<R>") {
        //since the rest of the conditionals handle precedence we only need to move thru <R>
        std::set<struct Node *>::iterator it = root->children.begin();
        std::cout << root->nodeName << ": " << (*it)->nodeName << std::endl;
        int stackCount = currentVarCount;

        if (root->children.size() == 3) {
            it++;
            asmCodeGen(*it);

            std::cout << "jumped out of recursion." << std::endl;
            std::cout << "globalUsed: " << globalUsed << std::endl;
            //we've jumped out of the recursion.
            if( globalUsed == false ) {
                //this means we found nothing in the Global stack

                //now two cases, either Stack has a variable or integer.

                if( intUsed == true ) {
                    //We've temp stored a number in here.
                    *outFile << "LOAD " << intStack.top() << std::endl;
                    intStack.pop();
                    intUsed = false;
                    return;
                }
                if( Stack.isempty() == false && stackUsed == true ) {
                    //we have a variable stored in here
                    *outFile << "LOAD " << Stack.getIndexVar( stackCount ) << std::endl;
                    stackUsed = false;
                    return;
                }
            } else {
                //this means we've found something in the Global stack and a global is used
                *outFile << "LOAD " << Global.getIndexVar( globalUseIndex ) << std::endl;
                //resetting the global flag
                globalUsed = false;
                globalUseIndex = -1;

            }
        } else if (root->children.size() == 1 ) {
            std::cout << "inserting: " << (*it)->nodeName << std::endl;
            //we'll need to insert stack if the nodeName is a variable
            if( isNumber( (*it)->nodeName ) == false ) {
                //we have a variable
                //we'll check if the variable is a global first
                if( Global.find( (*it)->nodeName ) == 0) {
                    //if global is found we'll do nothing
                    globalUsed = true;
                    //we want to grab the globalUsedIndex and returning
                    globalUseIndex = Global.findIndex( (*it)->nodeName );
                    return;
                }
                if( Stack.find( (*it)->nodeName ) == -1 ) {
                    stackUsed = true;
                    Stack.insert((*it)->nodeName, 0);
                    currentVarCount++;
                    return;
                }

            } else {
                //this is the case where we do have integers in the midst
                intStack.push( (*it)->nodeName );
                intUsed = true;
                std::cout << "number pushed into stack... returning from <R>" << std::endl;
                return;
            }
        } else {
            return;
        }
    }

    if ( !root ){
        return;
    }

    if (root->nodeName == "stop"){
        //here is where we'll implement code generation for global stack
        *outFile << "STOP" << std::endl;

        //here is where we implement global stack
        for( std::deque<std::string>::iterator it = Global.varStack.begin(); it!= Global.varStack.end(); ++it){
            //programming output
            //std::cout << *it << std::endl;

            //outputting stack to the file
            *outFile << *it << " " << Global.findValue( *it ) << std::endl;
        }
        for( int i = 0; i < tempCount; i++) {
            *outFile << "T" << i << " 0" << std::endl;
        }
    }
}

int maxDepth(struct Node* root)
{
    int depthCount = 0;
    if (root == NULL) {
        return 0;
    }

    else if( root ) {
//        std::cout << root->indents << root->nodeName << std::endl;
        std::set<struct Node*>::iterator move;
        for(move = root->children.begin() ;move != root->children.end(); ++move ){
            //std::cout << (*move)->indents << (*move)->nodeName << std::endl;
            depthCount = maxDepth( *move );
        }

        /* returning the count on depth */
        return ( depthCount + 1 );
    }
    return( depthCount + 1);
}

struct Node *grabNode( struct Node *root ){

    //debugging output
//    std::cout << "IN GRABNODE FUNC\n";

    struct Node* returnNode;

    if( root->nodeName == "<R>" ) {
        //debugging output
//        std::cout << "found node!\n";
        if (root->children.size() == 1) {
            std::set<struct Node*>::iterator it = root->children.begin();
            return (*it);
        }
    }
    if( root->nodeName == "<RO>" ){
        if (root->children.size() == 1 ) {
            //we are considering cases where we have single tokens ( =<, =>, ==, :: )
            std::set<struct Node*>::iterator it = root->children.begin();
            return (*it);
        }
    }
    if( !root ){
        return NULL;
    }

    std::set<struct Node*>::iterator move = root->children.begin();
    //debugging output
    std::cout << root->nodeName << " -> " << (*move)->nodeName << std::endl;

    for( ; move != root->children.end(); ++move ){
        returnNode = grabNode(*move);
        if( isNumber( returnNode->nodeName ) == true || isalpha( returnNode->nodeName[0] == true ) ){
            //debugging output
//            std::cout << "returning found node!\n";
            return ( returnNode );
        }

    }
    return returnNode;
}

bool outputDelayCheck( struct Node* root ){
    //This function will do a path check for the tree.
    //indicating whether the expression going forward will contain multiple operations.

    std::set<struct Node*>::iterator move = root->children.begin();
    bool found;
    if( root->children.size() > 1 ){
        std::cout << "Delay output \n";
        return true;
    }
    for( ; move != root->children.end() ; ++move ) {
        found = outputDelayCheck(*move);
        if (found == true) {
            return true;
        }
    }
    if(found == true){
        return true;
    } else {
        return false;
    }
}

void findLeftMost( struct Node* root ){
    std::set<struct Node*>::iterator move = root->children.begin();
    if (root->nodeName == "<R>") {
        if ((*move)->nodeName == "token_int") {
            *outFile << (*move)->nodeName << std::endl;
            return;
        }
        if ((*move)->nodeName == "ident_tk") {
            *outFile << (*move)->nodeName << std::endl;
            return;
        }
    }
    if(*move) {
        findLeftMost(*move);
    }
    return;
}

bool findParenth( struct Node* root ){
    std::set<struct Node*>::iterator move = root->children.begin();
    bool found;
    if( root->nodeName == "<R>" && root->children.size() == 3 ){
        std::cout << "Parenthesis found! \n";
        return true;
    }
    for( ; move != root->children.end() ; ++move ) {
        found = findParenth(*move);
        if (found == true) {
            return true;
        }
    }
    if(found == true){
        return true;
    } else {
        return false;
    }
}

//borrowed this from geekforgeeks: https://www.geeksforgeeks.org/program-check-input-integer-string/
// need a function to check for numbers in the strings.
// Returns true if s is a number else false
bool isNumber(std::string s)
{
    //making slight changes so that it won't fail the int test on a negative sign.
    std::cout << "inside isNumber(...) " << std::endl;
    for (int i = 0; i < s.length(); i++) {
//        if( i == 0 && s == "-" ){
//            //skipping the first entry if it is a negative sign.
//            i++;
//        }
        if (isdigit(s[i]) == false) {
            std::cout << "this is not a number " << std::endl;
            return false;
        }
    }
    std::cout << "this is a number " << std::endl;
    return true;
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

