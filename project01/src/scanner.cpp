//
// Created by PatK0 on 4/5/2020.
//

#include "scanner.h"
#include "token.h"
#include <string>
#include <iostream>
#include <fstream>


//global variables
char nextChar;
int charClass;

enum charTypes { WS, LOWER_CASE, UPPER_CASE, DIGIT, EOF_OP, COM_OP,
    ASSIGN_OP, LESS_THAN, GRTR_THAN, COLON_OP, ADD_OP,
    SUB_OP, MULT_OP, DIV_OP, MOD_OP, DOT_OP,
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    SEMI_COLON, LEFT_BRACK, RIGHT_BRACK, COMMA, OTHER };


void Tokenizer::scanDriver(){
    //this is the main work horse for the scanner

    //clearing stream buffer
    std::cin.clear();
    int scanResult;
    std::cout << "scanning\n";
    if( inFile->is_open() )
        std::cout << "file stream ON!" << std::endl;
    else
        std::cout << "file isn't opened" << std::endl;

    while( !inFile->eof() ){
        scanResult = FADriver();

        if( scanResult == 0 ) {
            //this is the normal case of a token
            //outputting
            std::cout << "-----------------------------------------------------------------------" << std::endl;
            std::cout << "Token Type: " << tokenType << std::endl;
            std::cout << "Lexeme: " << lexeme << std::endl;
            std::cout << "line number: " << lineNum << std::endl;
            std::cout << "-----------------------------------------------------------------------" << std::endl;
        }
        if( scanResult == -1 ){
            //this is the case of EOF
            std::cout << "-----------------------------------------------------------------------" << std::endl;
            std::cout << "end of file! " << std::endl;
            std::cout << "Token Type: " << tokenType << std::endl;
            std::cout << "-----------------------------------------------------------------------" << std::endl;
            exit( 0 );
        }
        if( scanResult == -2 ){
            //this is the case of an error type token
            std::cout << "-----------------------------------------------------------------------" << std::endl;
            std::cout << "Token Type: " << tokenType << std::endl;
            std::cout << "Lexeme: " << lexeme << std::endl;
            std::cout << "line number: " << lineNum << std::endl;
            std::cout << "-----------------------------------------------------------------------" << std::endl;
            getChar();
        }
    }

    std::cout << "finished scanning!\n";
}

int Tokenizer::FADriver(){

    //the FA table actual
    int FATable[ 25 ][ 25 ] = {
            /*                ws,  {a-z},  {A-Z},      D,    EOF,      #,      =,      <,      >,      :,      +,      -,      *,      /,      %,      .,      (,      ),     {,       },      ;,      [,     ],       ,,   OTHER */
            /*state 0*/ {      0,      1,   -100,      3, TK_EOF,      5,      6,      7,      8,      9,     10,     11,     12,     13,     14,     15,     16,     17,     18,     19,     20,     21,    22,      23,   -101},
            /*state 1*/ {  TK_ID,      1,      1,      1,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,   -100,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,   -100,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,   -100,   -100},
            /*state 2*/ {  TK_ID,      1,      1,      1,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,   -100,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,   -100,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,  TK_ID,   -100,   -100},
            /*state 3*/ { TK_INT,   -101,   -101,      3,   -101,   -101, TK_INT, TK_INT, TK_INT,   -101, TK_INT, TK_INT, TK_INT, TK_INT, TK_INT,   -101, TK_INT, TK_INT, TK_INT, TK_INT, TK_INT, TK_INT, TK_INT,   -101,   -101},
            /*state 4*/ { TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF, TK_EOF},
            /*state 5*/ {      5,      5,      5,      5,      5,   1006,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5,      5},
            /*state 6*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,     24,     24,     24,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
            /*state 7*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
            /*state 8*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
            /*state 9*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 10*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 11*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 12*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 13*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 14*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 15*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 16*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 17*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 18*/ {  TK_OP,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 19*/ {  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 20*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 21*/ {  TK_OP,  TK_OP,   -101,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,  TK_OP,  TK_OP,   -101,   -101,   -101},
           /*state 22*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 23*/ {  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
           /*state 24*/ {  TK_OP,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,  TK_OP,  TK_OP,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,  TK_OP,   -101,   -101,   -101,   -101,   -101,   -101,   -101,   -101},
    };

    /*
     * basic pseudocode for this:
     *
     * tokenType FADriver()
     * {
     *  state_t state = INITIAL;
     *  nextState;
     *  tokenType token;
     *  string S = NULL;
     *  while( state != FINAL )
     *  {
     *    nextState = table[ state ][ nextChar ];
	  *   
     *    if ( nextState == ERROR )
     *      ERROR(); //report error and exit
     *    if ( nextState == FINAL )
     *      if ( token( state ) == ID ) //need reserved keyword lookup
     *        if( S in Keywords )
     *          return ( KWtk, S ) // or specific keyword
     *        else
     *          return ( IDtk, S )
     *      else //not final
     *          state = nextState;
     *          append( S, nextChar );
     *          nextChar = getChar();
     */

    state = INITIAL;
    int nextState = INITIAL;
    int c;
    lexeme.clear();
    tokenType = 0;
//    std::cout << "driver initialized.\n";

    while( state < FINAL ){
//        std::cout << "part 1\n";
        nextState = FATable[ state ][ charClass ];
//        std::cout << "charClass: " << charClass << std::endl;
//        std::cout << "state: " << state << std::endl;
//        std::cout << "nextState: " << nextState << std::endl;


        //looking for ID or INT ERRORs
        if ( nextState == ERROR_ID_INT ){
            std::cout << "-----------------------------------------------------------------------\n" << std::endl;
            lexeme.push_back(nextChar);
            std::cout << "testScanner.cpp: 138 ERROR: incorrect ID/INT\n" << std::endl;
            std::cout << "Exiting scanner...\n";
            std::cout << "-----------------------------------------------------------------------\n" << std::endl;
            return -2;
        }
        else if ( nextState == ERROR_OP ){
            std::cout << "-----------------------------------------------------------------------\n" << std::endl;
//            lexeme.push_back(nextChar);
            std::cout << "testScanner.cpp: 143 ERROR: incorrect OP\n" << std::endl;
            std::cout << "Exiting scanner...\n";
            std::cout << "-----------------------------------------------------------------------\n" << std::endl;
            return -2;
        }
        if( nextState > FINAL ) {
            if (nextState == TK_ID) {
                if (scanKeywords(lexeme) == false) {
                    //this assumes we didn't hit a keyword.
                    tokenType = FATable[state][charClass];
                    return 0;
                } else {
                    //this assumes that we've hit upon a keyword.
                    tokenType = FATable[state][charClass];
                    return 0;
                }
            } else if (nextState == TK_EOF) {
                tokenType = TK_EOF;
                return -1;
            } else {
                tokenType = FATable[state][charClass];
                return 0;
            }
        } else {
//            std::cout << "part 2\n";

            //Not final condition and we scan the word to determine what it is.
            state = nextState;
            if( nextChar == '\n' )
                lineNum++;

            if( !isblank( nextChar ) && nextChar != '\n' ) {
                lexeme.push_back(nextChar);
//                std::cout << "current Lexeme: " << lexeme << std::endl;
            }
            //grabbing new character
            if( ( ( c = getChar() ) == -1 ) ){

                if( state == 0 && isupper(nextChar) ) {
                    printf( "-----------------------------------------------------------------------\n\n");
                    printf( "line 176: ERROR: incorrect ID starts with lower case first\n\n" );
                    printf( "-----------------------------------------------------------------------\n\n");
                    return -2;
                }
                if( charClass == TK_EOF ) {
                    lexeme.push_back(nextChar);
                    tokenType = FATable[state][charClass];
                    return -1;
                }
            }
        }
    }
    return 0;
}

bool Tokenizer::scanKeywords( std::string word ) {
    //this function will scan lexemes in the word list to find keywords

//    std::cout << "inside scanKeywords" << std::endl;
    //list of keywords to detect
    int i = 0;
    int numSize = 14;
    std::string result;
    //KEYWORDS: start stop iter void int exit scanf printf main if then let data func
    std::string keywordList[14] = { "start", "stop", "iter", "void", "int",
                                    "exit", "scanf", "printf", "main", "if",
                                    "then", "let", "data", "func" };

    while( i < numSize ){
//        std::cout << "comparing: " << word << " and " << keywordList[ i ] << std::endl;
        if( word.compare( keywordList[ i ] ) == 0 ){
//            std::cout << "we have a match!" << std::endl;
            //I want to change this to be a switch case assigning the appropriate value for the detected keyword.
                if( i == 0) {
                    //start case
                    tokenType = KWSTART;
                }
                else if( i == 1) {
                    //stop case
                    tokenType = KWSTOP;
                }
                else if( i == 2) {
                    //iter case
                    tokenType = KWITER;
                }
                else if( i == 3) {
                    //void case
                    tokenType = KWVOID;
                }
                else if( i == 4) {
                    //int case
                    tokenType = KWINT;
                }
                else if( i == 5) {
                    //exit case
                    tokenType = KWEXIT;
                }
                else if( i == 6) {
                    //scanf case
                    tokenType = KWSCANF;
                }
                else if( i == 7) {
                    //printf case
                    tokenType = KWPRINTF;
                }
                else if( i == 8) {
                    //main case
                    tokenType = KWMAIN;
                }
                else if( i == 9) {
                    //if case
                    tokenType = KWIF;
                }
                else if( i == 10) {
                    //then case
                    tokenType = KWTHEN;
                }
                else if( i == 11) {
                    //let case
                    tokenType = KWLET;
                }
                else if( i == 12) {
                    tokenType = KWDATA;
                }
                else if( i == 13) {
                    tokenType = KWFUNC;
                }
            return true;
        }
        else
            i++;
    }
    return false;
}

int Tokenizer::getChar( )
{
    //this function gets the next character set up for the scanner.
    if( inFile->peek() != std::ifstream::traits_type::eof()) {
        inFile->get(nextChar);
//        std::cout << "nextChar: " << nextChar << std::endl;

            if (isspace(nextChar)) {
                charClass = WS;
                return 0;
            }
            if (isalpha(nextChar)) {
                if( isupper(nextChar) ) {
                    charClass = UPPER_CASE;
                }
                else {
                    charClass = LOWER_CASE;
                }
                return 0;
            } else if (isdigit(nextChar)) {
                charClass = DIGIT;
                return 0;
            } else if (ispunct(nextChar)) {
                charClass = symbolClassify(nextChar);
                if (nextChar == '#') {
                    state = 15;
                    filter();
                    charClass = COM_OP;
                    return 0;
                }
                if (charClass == OTHER) {
                    printf( "-----------------------------------------------------------------------\n\n");
                    std::cout << "line:300 Scanner Error: unrecognized symbol.\n";
                    std::cout << "Exiting program...\n";
                    printf( "\n-----------------------------------------------------------------------\n\n");
                    exit(0);
                }
                if (charClass == EOF_OP) {
                    std::cout << "end of file detected. \n";
                    exit(0);
                }
            } else if (nextChar == '\n') {
                charClass = WS;
                return 0;
            }
    } else {
//        inFile->get(nextChar);
//        nextChar = '\0';
        charClass = EOF_OP;
//        std::cout << "end of file!\n";
        return -1;
    }
    return 0;
}

void Tokenizer::filter()
{
    //filter function is for filtering out characters that are commented out

    bool found = false;
    int getCharResult;
//    std::cout << "filtering: " << std::endl;
    getChar();
    //inFile->get( nextChar );
//    std::cout << "filtering nextChar: " << nextChar << std::endl;
    while( found == false )
    {
        //we can save and alter this if we want to just use # ... # rather than # ...\n
        //if( nextChar == '#' )
        //    found = true;
        if( nextChar == '\n' )
        {
            lineNum++;
            return;
        }
        else if( nextChar == '\0' ){
            std::cout << "done filtering: end of file.\n";
            exit( 0 );
        }

        //inFile->get( nextChar );

        if( (getCharResult = getChar() == -1) || nextChar == '\0' ){
            std::cout << "done filtering: end of file.\n";
            exit( 0 );
        }
//        std::cout << "filtering nextChar: " << nextChar << std::endl;
    }
    std::cout << "done!" << std::endl;
}

//setter methods

void Tokenizer::setTokenType( int tokenValue ){
    tokenType = tokenValue;
}

void Tokenizer::setLexeme( std::string word ){
    lexeme = word;
}

void Tokenizer::setCharClass( int charValue ){
    charClass = charValue;
}
void Tokenizer::setLineNum( int lineCount ){
    lineNum = lineCount;
}

void Tokenizer::incLineNum(){
    lineNum++;
}

//getter methods
int Tokenizer::getTokenType(){
    return tokenType;

}

std::string Tokenizer::getLexeme(){
    return lexeme;

}

int Tokenizer::getLineNum(){
    return lineNum;

}

int Tokenizer::getCharClass(){
    return charClass;
}

int Tokenizer::symbolClassify( char ch ){
    //this function scans symbols to see if the symbol is an operation symbol
    //any other symbols will be considered other. These are unrecognized symbols

    int nextToken = 0;
    switch( ch ){
        case ' ':
            nextToken = WS;
            break;
        case '=':
            nextToken = ASSIGN_OP;
            break;
        case '<':
            nextToken = LESS_THAN;
            break;
        case '>':
            nextToken = GRTR_THAN;
            break;
        case ':':
            nextToken = COLON_OP;
            break;
        case '+':
            nextToken = ADD_OP;
            break;
        case '-':
            nextToken = SUB_OP;
            break;
        case '*':
            nextToken = MULT_OP;
            break;
        case '/':
            nextToken = DIV_OP;
            break;
        case '%':
            nextToken = MOD_OP;
            break;
        case '.':
            nextToken = DOT_OP;
            break;
        case '(':
            nextToken = LEFT_PAREN;
            break;
        case ')':
            nextToken = RIGHT_PAREN;
            break;
        case '{':
            nextToken = LEFT_BRACE;
            break;
        case '}':
            nextToken = RIGHT_BRACE;
            break;
        case ';':
            nextToken = SEMI_COLON;
            break;
        case '[':
            nextToken = LEFT_BRACK;
            break;
        case ']':
            nextToken = RIGHT_BRACK;
            break;
        case ',':
            nextToken = COMMA;
            break;
        case '!':
            nextToken = OTHER;
            break;
        case '@':
            nextToken = OTHER;
            break;
        case '$':
            nextToken = OTHER;
            break;
        case '^':
            nextToken = OTHER;
            break;
        case '&':
            nextToken = OTHER;
            break;
        case '|':
            nextToken = OTHER;
            break;
        case '#':
            filter();
            break;
        default:
            nextToken = EOF_OP;
            break;
    }
//    std::cout << "nextToken: " << nextToken << std::endl;
    return nextToken;
}
