#include <string>
#include <deque>
#include <iostream>

#ifndef ST_H
#define ST_H

class ST{
public:
    //this will be used to hold both the Global and Local variable stack
    //Note: for the sake of simplicity we'll name the global stack STV.
    //for stack purpose we cannot use sets (sets auto sorts) but queue because its FIFO (first in first out).

    std::deque <std::string> varStack;             //this will be used to hold the var stack.
    std::deque <int> varValue;                     //this will be used to hold the var value.
    void insert(std::string input, int value);      //function used to insert variables into the stack
    bool isempty();
    int find(std::string input);                    //function used to find variable. Will return -1 on items not found
                                                    // will return 0 on item found.
    int findValue(std::string input);
    int findIndex(std::string input);
    std::string getIndexVar( int index );
    void deleteVarByIndex( int index );

    bool verify(std::string input);                 //will be used to verify the STV stack when find produces -1.
                                                    //we're using this to check global when local var does not exist.
                                                    //if the var does not exist in local and global, we'll produce
                                                    //error.
    void printStack();

};


#endif