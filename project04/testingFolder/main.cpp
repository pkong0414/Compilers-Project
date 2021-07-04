//
// Created by Patrick Kong on 11/13/2020.
//

#include "scanner.h"
#include "parser.h"
#include <iostream>
#include <fstream>

int main( int argc, char** argv ) {
    fileHandle( argc, argv );
    Parser parser;
    if( inFile == NULL ){
        perror( "main.c ERROR: there is no file" );
        exit( 1 );
    }
	 
	 if( inFile->eof() ){
	 	std::cout << "main.c ERROR: EOF\n";
	 }
	 else{
         parser.program();
	 }
    inFile->close();
	outFile->close();
}
