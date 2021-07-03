//
// Created by Patrick Kong on 4/5/2020.
//

#include "testScanner.h"
#include <iostream>
#include <fstream>

int main( int argc, char** argv ) {
    fileHandle( argc, argv );
    Tokenizer scanner;
    if( inFile == NULL ){
        perror( "main.c ERROR: there is no file" );
        exit( 1 );
    }
	 
	 if( inFile->eof() ){
	 	std::cout << "main.c ERROR: EOF\n";
	 }
	 else{ 
	 	scanner.scanDriver();
	 }

}
