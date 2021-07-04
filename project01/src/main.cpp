//
// Created by Patrick Kong on 4/5/2020.
//

#include "scanner.h"
#include <iostream>
#include <fstream>

int main( int argc, char** argv ) {
    fileHandle( argc, argv );
    Tokenizer scanner;
    if( inFile == NULL ){
        perror( "ERROR: there is no file" );
        exit( 1 );
    }
	 
	 if( inFile->eof() ){
	 	std::cout << "ERROR: EOF\n";
	 }
	 else{ 
	 	scanner.scanDriver( );
	 }
	 inFile->close();

}
