//
// Created by PatK0 on 4/5/2020.
//

#include <string>
#include <fstream>
#include <stdio.h>

#ifndef SCANNER_H
#define SCANNER_H

extern std::ifstream *inFile;


//functions
void fileHandle( int argc, char** argv );

class Tokenizer{
private:    
	 //fields for the scanner
	
   int tokenType;
   std::string lexeme;
   int lineNum = 1;
	 

   int charClass;
   int state;

public:
    //methods
    void scanDriver();
    int FADriver();
    bool scanKeywords( std::string );
    int getChar();
    void filter();
    int symbolClassify( char );

    //setters
    void setTokenType( int );
    void setLexeme( std::string );
    void setLineNum( int );
	void setCharClass( int );
	void incLineNum();

    //getters
    int getTokenType();
    std::string getLexeme();
    int getLineNum();
	int getCharClass();
};

#endif //SCANNER_H
