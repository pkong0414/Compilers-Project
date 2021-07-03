/*
 * main.cpp
 *
 *  Created on: Feb 16, 2020
 *      Author: Patrick
 *
 * This program will build a BST based on the string length of the characters.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>
#include "tree.h"
using namespace std;

int main(int argc, char ** argv) {
	
	fstream textFile;
	ofstream outputFile;

	string outputInOrder = "output.inorder";
	string outputPreOrder = "output.preorder";
	string outputPostOrder = "output.postorder";
	string inOrderExt = ".inorder";
	string preOrderExt = ".preorder";
	string postOrderExt = ".postorder";

	string fileName = "";
	string fileNameExt = ".fs";
	string line;
	Tree node;

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
			return 0;
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
				    printf("3: ./P0 <keyboard arguments: hello world>\n");

				    printf("\nAnytime there are more than 1 arguments, the program will treat the arguments as words to"
                            " process\n");

				    exit(1);
				}
				//reading line in and building tree
				cout << "line: " << line << endl;
				if( !line.empty() ){
					cout << "adding: \n" << line << endl;
					node.buildTree( line );
				}
			}
		}
        //outputting results

		cout << "result: \n";
		cout << "\nIn order: \n";
		outputFile.open( outputInOrder, ios::out );
		node.printInOrder( outputFile, outputInOrder );
		outputFile.close();
		
		cout << "\nPre order: \n";
		outputFile.open( outputPreOrder, ios::out );
		node.printPreOrder( outputFile, outputPreOrder );
		outputFile.close();

		cout << "\nPost order: \n";
		outputFile.open( outputPostOrder, ios::out );
		node.printPostOrder( outputFile, outputPostOrder );
		outputFile.close();
		
		//outputting the relevant output files
		cout << "results written to: output.inorder, output.preorder, output.postorder" << endl;
		return 0;
	}
	else if( argc > 2 ){
	    //This section processes keyboard arguments
	 	int i = 1;
	 	cout << "processing keyboard arguments" << endl;

	 	//reading line in and building tree
	 	while( i < argc ){
	 		cout << "argv: " << argv[i] << endl;
			node.buildTree( argv[i] );
			i++;
	 	}

        //outputting results
		cout << "result: \n";
		cout << "\nIn order: \n";
		outputFile.open( outputInOrder, ios::out );	
		node.printInOrder( outputFile, outputInOrder );
		outputFile.close();

		cout << "\nPre order: \n";
		outputFile.open( outputPreOrder, ios::out );
		node.printPreOrder( outputFile, outputPreOrder );
		outputFile.close();

		cout << "\nPost order: \n";
		outputFile.open( outputPostOrder, ios::out );
		node.printPostOrder( outputFile, outputPostOrder );
		outputFile.close();
		
		//outputting the relevant output files.
		cout << "results written to: output.inorder, output.preorder, output.postorder" << endl;
		return 0;
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

		//appending all filenames with the correct extension.
		string oFileInOrder = fileName + inOrderExt;
		string oFilePreOrder = fileName + preOrderExt;
		string oFilePostOrder = fileName + postOrderExt;
		//make outputFileName append with various .fs file extension.
		if( fileName.find( "." ) == string::npos )
			fileName.append( fileNameExt );
		//debug output
		cout << "fileName: " << fileName << endl;
		cout << "opening file..." << endl;

		textFile.open( fileName, ios::in );

        //looking to see if the file is empty
		if( textFile.peek() == ifstream::traits_type::eof() ){
			cout << "ERROR: File is empty." << endl;
			return 0;
		}
		else if( textFile.fail() ){         //if the file cannot be opened
			cout << "ERROR: Cannot open file." << endl;
			return 0;
		}
		else
		{
		    //continuous parsing while file has content.
			while( textFile ){
                //reading line in and building tree
                textFile >> line;
				printf("line: %s\n", line.c_str() );
				if(line.find("\n") != string::npos)
					line.erase( line.find("\n") );
				while (line.length()==0 )
					getline(textFile, line);
				if( !line.empty() ){
					cout << "line: " << line << endl;
					node.buildTree( line );
				}
			}
			cout << "result: \n";

			//outputting results
			cout << "\nIn order: \n";
			outputFile.open( oFileInOrder, ios::out );
			node.printInOrder( outputFile, oFileInOrder );
			outputFile.close();
			
			cout << "\nPre order: \n";
			outputFile.open( oFilePreOrder, ios::out );
			node.printPreOrder( outputFile, oFilePreOrder );
			outputFile.close();

			cout << "\nPost order: \n";
			outputFile.open( oFilePostOrder, ios::out );
			node.printPostOrder( outputFile, oFilePostOrder );
			outputFile.close();
			textFile.close();
			
			//listing file information at the end
			cout << "results are written to: " << oFileInOrder << " " 
			                                << oFilePreOrder << " "
			                                << oFilePostOrder << endl;
			return 0;
		}
	}
	return 0;
}
