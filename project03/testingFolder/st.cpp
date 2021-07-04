/* st.cpp
 *
 *
 */

#include "st.h"
#include <iterator>

void ST::insert(std::string input, int value){
    // insert the string if not already there or error if already there
    // (you may return fail indication or issue detailed error here and exit)

    //we'll use insert as a way to initialize a variable but leave it to the parser to do the assignment itself.

    //we need to check all the existing variables
    bool check = false;

    check = verify( input );

    if( check == false ) {
        //inserting the new variable
        varStack.push_front( input );
        varValue.push_front( value );

    }
    else {
        std::cout << "ERROR: Cannot declare a variable that already exist!\n";
        exit( 0 );
    }
}

int ST::find(std::string input){
    //testing output
//    std::cout << "checking for: " << input << std::endl;

    for( std::deque<std::string>::iterator it = varStack.begin(); it != varStack.end(); ++it){
        if ( input.compare(*it) ) {
            //if something is found we'll return true

            //testing output
//            std::cout << "variable already exist.\n";
            return 0;
        }
    }
    //if we find nothing inside varStack, we'll return -1
    return -1;
}

int ST::findValue(std::string input){
    //This will be a variation of the find function. Goal of this is to find the var and return value from it.
    //We won't produce an error since we'll only use this if find doesn't produce -1.

    //testing output
//    std::cout << "checking for: " << input << std::endl;
    std::deque<int>::iterator numIt = varValue.begin();
    for( std::deque<std::string>::iterator it = varStack.begin(); it != varStack.end(); ++it){
        if ( input.compare(*it) == 0 ) {
            //if something is found we'll return the value found in numIt.
            return *numIt;
        }
        ++numIt;
    }
    return -1;
}

bool ST::verify(std::string input){
    // return true if the string is already in the container variable and false otherwise
    // (I suggest you return false indicator rather than issue detailed error here with exit but either way
    // could possibly work if you assume that no one checks verify() unless to process variable use)

    //testing output
//    std::cout << "checking for: " << input << std::endl;

    for( std::deque<std::string>::iterator it = varStack.begin(); it != varStack.end(); ++it){
        if ( input.compare( *it ) == 0 ) {
            //if something is found we'll return true

            //testing output
//            std::cout << "variable already exist.\n";
            return true;
        }
    }
    //testing output
//    std::cout << "variable is not in the stack.\n";

    return false;
}

void ST::printStack(){

    for( std::deque<std::string>::iterator it = varStack.begin(); it!= varStack.end(); ++it){
        std::cout << *it << std::endl;

    }
}