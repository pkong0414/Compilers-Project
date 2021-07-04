//
// Created by Patrick Kong on 4/9/2020.
//

#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
using namespace std;

ifstream *inFile;

void fileHandle( int argc, char ** argv ){
    inFile = new ifstream;

    //cout << "argc: " << argc << endl;
    ofstream outputFile;

    string fileName = "";
    string fileNameExt = ".fs";
    string outFileName = "";
    string line;

    //debugging output
    printf( "argc: %d\n", argc);
    if( argc == 1 ){
        cout << "processing redirected file..." << endl;

        //checking to see if the file redirected is empty


        cin.seekg(0, ios::end);
        int length = cin.tellg();

        //if the file is at an end, then empty.
        if( length == 0 ){
            cout << "ERROR: this file is empty." << endl;
            exit(EXIT_FAILURE);
        }
        else{
            //resetting to the beginning of the file to start processing.
            cin.seekg(0 , ios::beg);
            while( !cin.eof() ){
                cin >> line;
                //This should take care of the case of " " parameters
                if( line.empty() ){
                    printf("\nERROR: line empty... exiting.\n");
                    printf("3 different ways to use this program:\n");
                    printf("invocation:\n");
                    printf("NOTE: single argument cases will be treated as file arguments\n");
                    printf("1: ./P0 <filename.fs>\n");
                    printf("2: ./P0 <filename>\n");
                    printf("3: ./P0 <keyboard arguments examples: hello world>\n");

                    printf("\nAnytime there are more than 1 arguments, the program will treat the arguments as words to"
                           " process\n");

                    exit(0);
                }
                //reading line in and building tree
                cout << "line: " << line << endl;
                if( !line.empty() ){
                    cout << "adding: \n" << line << endl;
                    //TODO implement something for the scanner
                }
            }
        }

        //outputting the relevant output files
        cout << "results written to: output.fs" << endl;
        return;
    }
    else if( argc > 2 ){
        //This section processes keyboard arguments
        int i = 1;
        cout << "processing keyboard arguments" << endl;

        //reading line in and building tree
        while( i < argc ){
            cout << "argv: " << argv[i] << endl;
            //TODO: implement something for the scanner
            i++;
        }

        return;
    }
    else if( argc == 2 ){
        cout << "processing filename arguments" << endl;
        fileName = argv[1];

        //processing file. If a filename is entered without the .fs extension. We'll add it!
        if( fileName.find( ".fs" ) != string::npos )
        {
            cout << "extension not detected." << endl;
            fileName.erase( fileName.length() - 3, fileName.length() );
            cout << "fileName: " << fileName << endl;
        }

        //make outputFileName append with various .fs file extension.
        if( fileName.find( "." ) == string::npos )
            fileName.append( fileNameExt );
        //debug output
        cout << "fileName: " << fileName << endl;
        cout << "opening file..." << endl;

        //opening input file
        inFile->open( fileName, ios::in );

        //opening output file
        //outputFile.open( fileName, ios::out );

        //looking to see if the file is empty
        if( inFile->peek() == ifstream::traits_type::eof() ){
            cout << "ERROR: File is empty." << endl;
            exit(EXIT_FAILURE);
        }
        else if( inFile->fail() ){         //if the file cannot be opened
            cout << "ERROR: Cannot open file." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return;
}