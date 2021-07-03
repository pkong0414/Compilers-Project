/* parser.cpp
 *
 */

#include "parser.h"
#include "scanner.h"
#include "tree.h"
#include "node.h"
#include "token.h"
#include <string>
#include <iostream>

//global variables
std::string tk;

//Scanner object
Tokenizer Scanner;

void Parser::program(){
    //<program> -> <vars> <block>

    //the tree object
    struct Node *root = NULL;
    Scanner.scanDriver();

//    printf( "lexeme: %s\n", Scanner.getLexeme().c_str() );
//    printf( "tokenType: %d\n", Scanner.getTokenType());

    std::string indent = "";

    //creating node for <vars> production
    root = insertNode( root, "<program>", indent );

    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it = root->children.begin();
    if( Scanner.getTokenType() == KWSTART ) {
        insertNode( root, Scanner.getLexeme() , indent );
        it++;

        //we immediately have the program look into <vars> non terminal
        insertNode( root, "<vars>", indent );
        it++;
        vars( *it, indent );

        //now we look at KWMAIN before we get into <block> non terminal
        if( Scanner.getTokenType() == KWMAIN ) {
            insertNode( root, Scanner.getLexeme() , indent );
            it++;

//            printf( "lexeme: %s\n", Scanner.getLexeme().c_str() );
//            printf( "tokenType: %d\n", Scanner.getTokenType());

            //creating node for <block> production
            insertNode( root, "<block>", indent );
            it++;
            Scanner.scanDriver();
            block( *it, indent );
            if( Scanner.getTokenType() == KWSTOP ) {
                insertNode( root, Scanner.getLexeme() , indent );
                it++;

                //this is the end of the program
                std::cout << "END OF PROGRAM.\n";
                printPreorder( root );

                return;
            }
        }
    }
}

void Parser::block( struct Node *nodePtr, std::string indent ) {

//    std::cout << "inside <block>" << std::endl;

    std::string currentIndent = indent.append( "--" );
    //<block> -> begin <vars> <stats> end

    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it = nodePtr->children.begin();

    // debugging output only
//    printf( "lexeme: %s\n", Scanner.getLexeme().c_str() );
//    printf( "tokenType: %d\n", Scanner.getTokenType());


    if ( Scanner.getLexeme() == "{" ) {
//        std::cout << Scanner.getLexeme() << std::endl;
        insertNode( nodePtr, "{", currentIndent );
        it++;

        insertNode( nodePtr, "<vars>", currentIndent );
        it++;

        vars( *it, currentIndent );

        insertNode( nodePtr, "<stats>", currentIndent );
        it++;

        stats( *it, currentIndent );

//        std::cout << "lexeme: " << Scanner.getLexeme() << std::endl;

        if ( Scanner.getLexeme() == "}" ) {
            std::cout << Scanner.getLexeme() << std::endl;
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
            Scanner.scanDriver();
        }
    } else {
        std::cout << "parser.cpp: 43. ERROR: parser error, at line: " << Scanner.getLineNum() << std::endl;
        return;
    }
}

void Parser::vars( struct Node *nodePtr, std::string indent ){
    //<vars> -> empty | data Identifier = Integer . <vars>

    std::string currentIndent = indent.append( "--" );

//    std::cout << "inside: <vars>" << std::endl;
    Scanner.scanDriver();

//    printf( "lexeme: %s\n", Scanner.getLexeme().c_str() );
//    printf( "tokenType: %d\n", Scanner.getTokenType());

    if( Scanner.getTokenType() == KWLET && Scanner.getLexeme() == "let") {
        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, "let", currentIndent );
        Scanner.scanDriver();

        //iterator for the children set
        std::set< struct Node* >::iterator it;
        it = nodePtr->children.begin();

//        std::cout << "tk: " << tk << std::endl;
        if ( Scanner.getTokenType() == TK_ID ) {
//            std::cout << Scanner.getLexeme() << std::endl;

            //inserting the variable lexeme into <vars> node.
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            //iterating it to point at current parseNode.
            it++;
            Scanner.scanDriver();
            if (Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == ":") {
//                std::cout << "=" << std::endl;

                insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

                it++;
                Scanner.scanDriver();
                if ( Scanner.getTokenType() == TK_INT) {
//                    std::cout << Scanner.getLexeme() << std::endl;

                    insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
                    it++;
                    vars( *it, currentIndent );
                }
            }
        }
    } else {
        //this is the empty case.
        //insertNode( "empty" );
        return;
    }
}

void Parser::expr( struct Node *nodePtr, std::string indent ){
    //<expr> -> <N> / <expr> | <N> * <expr> | <N>

    std::string currentIndent = indent.append( "--" );

    //inserting a node for the <N> production
    insertNode( nodePtr, "<N>", currentIndent );

    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it= nodePtr->children.begin();

    N( *it, currentIndent );

    if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "/" ){
//        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
        it++;
        Scanner.scanDriver();

        insertNode( nodePtr, "<expr>", currentIndent );
        it++;
        expr( *it, currentIndent );
    } else if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "*" ) {
//        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
        it++;
        Scanner.scanDriver();

        insertNode( nodePtr, "<expr>", currentIndent );
        it++;
        expr( *it, currentIndent );
    }

    return;

}

void Parser::N( struct Node *nodePtr, std::string indent ){
    //<N> -> <A> + <N> | <A> - <N> | <A>

    std::string currentIndent = indent.append( "--" );

    insertNode( nodePtr, "<A>", currentIndent );

    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it = nodePtr->children.begin();

    A( *it, currentIndent );

    if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "+" ){
//        std::cout << Scanner.getTokenType() << std::endl;
        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
        it++;
        Scanner.scanDriver();

        insertNode( nodePtr, "<N>", currentIndent );
        it++;
        N( *it, currentIndent );
    }
    else if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "-" ){
//        std::cout << Scanner.getTokenType() << std::endl;
        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
        it++;
        Scanner.scanDriver();

        insertNode( nodePtr, "<N>", currentIndent );
        it++;
        N( *it, currentIndent );
    }
    return;
}

void Parser::A( struct Node *nodePtr, std::string indent ){
    //<A> -> % <A> | <R>
//    std::cout << "<A>\n";

    std::string currentIndent = indent.append( "--" );

    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it = nodePtr->children.begin();

    if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "%" ){
//        std::cout << Scanner.getLexeme() << std::endl;
        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
        it++;

        Scanner.scanDriver();

        insertNode( nodePtr, "<A>", currentIndent );
        it++;
        A( *it, currentIndent );
    } else {
        //we expect to get into <R> non terminal


        insertNode( nodePtr, "<R>", currentIndent );
        it++;
        R( *it, currentIndent );
    }
}

void Parser::R( struct Node *nodePtr, std::string indent ){
//    std::cout << "<R>" << std::endl;
    //<R> -> [ <expr> ] | Identifier | Integer

    std::string currentIndent = indent.append( "--" );
    //print for now
    std::cout << Scanner.getLexeme() << std::endl;

    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it= nodePtr->children.begin();


    if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "[" ) {
//        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );


        Scanner.scanDriver();

        insertNode( nodePtr, "<expr>", currentIndent );
        it++;

        expr( *it, currentIndent );
        if (Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "]") {
//            std::cout << ")" << std::endl;

            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
            return;
        } else {
            std::cout << "parser.cpp:282. ERRROR: Parser Error. At " << Scanner.getLineNum() << std::endl;
        }
    }
    else if( Scanner.getTokenType() == TK_ID ) {
        //print for now
        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

        Scanner.scanDriver();
        return;
    }
    else if( Scanner.getTokenType() == TK_INT ) {
        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
        Scanner.scanDriver();
        return;
    }
    else {
        std::cout << "parser.cpp:302. ERROR: Parser error. At " << Scanner.getLineNum() << std::endl;
    }
}

void Parser::stats( struct Node *nodePtr, std::string indent ){
//    std::cout << "inside: <stats>" << std::endl;
    //<stats> -> <stat> <mStat>



    std::string currentIndent = indent.append( "--" );

    insertNode( nodePtr, "<stat>", currentIndent );
    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it = nodePtr->children.begin();

    stat( *it, currentIndent );

    insertNode( nodePtr, "<mStat>", currentIndent );
    it++;

    mStat( *it, currentIndent );

    return;
}

void Parser::mStat( struct Node *nodePtr, std::string indent ) {
//    std::cout << "<mStat>" << std::endl;

    std::string currentIndent = indent.append("--");

//    std::cout << "tokenType: " << Scanner.getTokenType() << std::endl;
//    std::cout << "lexeme: " << Scanner.getLexeme() << std::endl;

    //<mStat> -> empty | <stat> <mStat>


    insertNode(nodePtr, "<stat>", currentIndent);

    //iterator for the children set
    std::set<struct Node *>::iterator it;
    it = nodePtr->children.begin();

    if ( stat(*it, currentIndent) ) {

        insertNode(nodePtr, "<mStat>", currentIndent);
        it++;

        mStat(*it, currentIndent);
    } else {
        return;
    }

    return;
}

bool Parser::stat( struct Node *nodePtr, std::string indent ){
//    std::cout << "<stat>" << std::endl;

    std::string currentIndent = indent.append( "--" );
    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it = nodePtr->children.begin();

    std::cout << "tokenType: " << Scanner.getTokenType() << std::endl;
    std::cout << "lexeme: " << Scanner.getLexeme() << std::endl;

    //<stat> -> <in> . | <out> . | <block> | <if> . | <loop> . | <assign> .
    if ( Scanner.getTokenType() == KWSCANF && Scanner.getLexeme() == "scanf" ) {

        insertNode( nodePtr, "<in>", currentIndent );
        it++;
        in( *it, currentIndent );

        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "." ) {

            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

//            std::cout << "." << std::endl;
            Scanner.scanDriver();
            return true;
        }
        else {
            std::cout << "ERROR: No '.' after 'in' statement. At line: " << Scanner.getLineNum() << std::endl;
            return false;
        }
    } else if ( Scanner.getTokenType() == KWPRINTF && Scanner.getLexeme() == "printf" ) {

        insertNode( nodePtr, "<out>", currentIndent );
        it++;
        out( *it, currentIndent );

        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "." ) {
//            std::cout << "." << std::endl;

            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
            return true;
        }
        else {
            std::cout << "ERROR: No '.' after 'out' statement. At line: " << Scanner.getLineNum() << std::endl;
            return false;
        }
    } else if ( Scanner.getTokenType() == KWIF && Scanner.getLexeme() == "if" ) {
        //for the sake of things let's call this iffy instead of if()...
        insertNode( nodePtr, "<iffy>", currentIndent );
        it++;
        iffy( *it, currentIndent );
        Scanner.scanDriver();
        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "." ) {
//            std::cout << Scanner.getLexeme() << std::endl;
            it++;
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
            return true;
        }
        else {
            std::cout << "ERROR: No '.' after 'if' statement. At line: " << Scanner.getLineNum() << std::endl;
            return false;
        }
    } else if ( Scanner.getTokenType() == KWITER && Scanner.getLexeme() == "iter" ) {

        insertNode( nodePtr, "<loop>", currentIndent );
        it++;
        loop( *it, currentIndent );
        Scanner.scanDriver();
        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "." ) {
//            std::cout << Scanner.getLexeme() << std::endl;
            it++;
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
            return true;
        }
        else {
            std::cout << "ERROR: No '.' after 'loop' statement. At line:" << Scanner.getLineNum() << std::endl;
            return false;
        }
    } else if ( Scanner.getTokenType() == TK_ID ) {

        insertNode( nodePtr, "<assign>", currentIndent );
        it++;
        assign( *it, currentIndent );
        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "." ) {
//            std::cout << Scanner.getLexeme() << std::endl;
            it++;
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
            return true;
        }
        else {
            std::cout << "ERROR: No '.' after 'assign' statement. At line: " << Scanner.getLineNum() << std::endl;
            return false;
        }
    }else if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "{" ){

        insertNode( nodePtr, "<block>", currentIndent );

        //iterator for the children set
        std::set< struct Node* >::iterator it;
        it = nodePtr->children.begin();

        block( *it, currentIndent );
    }else{
        return false;
    }
    return false;

}

void Parser::in( struct Node *nodePtr, std::string indent ){
//    std::cout << "<in>" << std::endl;

    std::string currentIndent = indent.append( "--" );

    //<in> -> scanf [ Identifier ]

//    std::cout << Scanner.getLexeme() << std::endl;

    insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

    Scanner.scanDriver();
    if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "[" ) {
        //for now print output
        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

        Scanner.scanDriver();

//        std::cout << Scanner.getLexeme() << std::endl;
        if( Scanner.getTokenType() == TK_ID ) {
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
        }
        if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "]" ) {
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
        }
        return;
    }

}

void Parser::out( struct Node *nodePtr, std::string indent ){
//    std::cout << "inside <out>" << std::endl;
    //<out> -> printf [ <expr> ]

    std::string currentIndent = indent.append( "--" );

    std::cout << "tokenType: " << Scanner.getTokenType() << std::endl;
    std::cout << "lexeme: " << Scanner.getLexeme() << std::endl;

    //iterator for the children set
    std::set< struct Node* >::iterator it;
    it = nodePtr->children.begin();

    insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

    it++;
    Scanner.scanDriver();

    if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "[" ) {
        //for now print output
        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
        Scanner.scanDriver();
        it++;
//        std::cout << Scanner.getLexeme() << std::endl;
        insertNode( nodePtr, "<expr>", currentIndent );

        expr( *it, currentIndent );

        if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "]" ) {
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
        }
        return;
    }
}

void Parser::iffy( struct Node *nodePtr, std::string indent ){
    //<if> -> iffy [ <expr> <RO> <expr> ] then <stat>

    //    std::cout << "<iffy>" << std::endl;

    std::string currentIndent = indent.append( "--" );

    if ( Scanner.getTokenType() == KWIF && Scanner.getLexeme() == "if" ){
//        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

        //iterator for the children set
        std::set< struct Node* >::iterator it;
        it= nodePtr->children.begin();

        Scanner.scanDriver();

        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "[" ){
//            std::cout << Scanner.getLexeme() << std::endl;

            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
            it++;

            Scanner.scanDriver();

            insertNode( nodePtr, "<expr>", currentIndent );
            it++;
            expr( *it, currentIndent );

            insertNode( nodePtr, "<RO>", currentIndent );
            it++;
            RO( *it, currentIndent );

            insertNode( nodePtr, "<expr>", currentIndent );
            it++;
            expr( *it, currentIndent );

            if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "]" ){
//                std::cout << Scanner.getLexeme() << std::endl;

                insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
                it++;

                Scanner.scanDriver();

                if ( Scanner.getTokenType() == KWTHEN && Scanner.getLexeme() == "then" ) {
//                    std::cout << Scanner.getLexeme() << std::endl;

                    insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
                    it++;
                    Scanner.scanDriver();
                    block( *it, currentIndent );
                }
                else {
                    std::cout << "ERROR: Parser Error. At Line: " << Scanner.getLineNum() << std::endl;
                }
            }
            else {
                std::cout << "ERROR: Parser Error. At line: " << Scanner.getLineNum() << std::endl;
            }
        }
        else {
            std::cout << "ERROR: Parser Error. At line: " << Scanner.getLineNum() << std::endl;
        }
    }

}

void Parser::loop( struct Node *nodePtr, std::string indent ){
//    std::cout << "<loop>" << std::endl;

    std::string currentIndent = indent.append( "--" );

    //<loop> -> loop [ <expr> <RO> <expr> ] <stat>

    if ( Scanner.getTokenType() == KWITER && Scanner.getLexeme() == "iter" ){
//        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

        //iterator for the children set
        std::set< struct Node* >::iterator it;
        it= nodePtr->children.begin();

        Scanner.scanDriver();
        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "[" ){
//            std::cout << Scanner.getLexeme() << std::endl;

            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
            it++;

            Scanner.scanDriver();

            insertNode( nodePtr, "<expr>", currentIndent);
            it++;

            expr( *it, currentIndent );

            insertNode( nodePtr, "<RO>", currentIndent );
            it++;

            RO( *it, currentIndent );

            insertNode( nodePtr, "<expr>", currentIndent );
            it++;

            expr( *it, currentIndent );
            if( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "]" ){
//                std::cout << Scanner.getLexeme() << std::endl;

                insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
                it++;

                Scanner.scanDriver();
                stat( *it, currentIndent );
            } else
                std::cout << "ERROR: Parser Error. At line: " << Scanner.getLineNum() << std::endl;
        }
        else
            std::cout << "ERROR: Parser Error. At line: " << Scanner.getLineNum() << std::endl;
    }
}

void Parser::assign( struct Node *nodePtr, std::string indent ){
    //<assign> -> Identifier = <expr>

    std::string currentIndent = indent.append( "--" );

//    std::cout << "tokenType: " << Scanner.getTokenType() << std::endl;
//    std::cout << "lexeme: " << Scanner.getLexeme() << std::endl;

    if ( Scanner.getTokenType() == TK_ID ) {
        //Identifier
        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

        //iterator for the children set
        std::set< struct Node* >::iterator it;
        it= nodePtr->children.begin();

        Scanner.scanDriver();
        if ( Scanner.getTokenType() == TK_OP && Scanner.getLexeme() == "=") {
//            std::cout << Scanner.getLexeme() << std::endl;

            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );
            it++;

            Scanner.scanDriver();
            expr( *it, currentIndent );
        } else {
            std::cout << "ERROR: Parser Error. At line: " << Scanner.getLineNum() << std::endl;

        }
    }

    return;
}

void Parser::RO( struct Node *nodePtr, std::string indent ){
    //<RO> -> =< | => | == | : : (two tokens)

    // These: =< , =>, == are one token.

    std::string currentIndent = indent.append( "--" );
//    std::cout << "tokenType: " << Scanner.getTokenType() << std::endl;

    if ( Scanner.getLexeme() == "=<" ) {
//        std::cout << Scanner.getLexeme() << std::endl;

        insertNode( nodePtr, Scanner.getLexeme() , currentIndent );

        std::cout << "<<" << std::endl;
        Scanner.scanDriver();
        return;

    }
    else if ( Scanner.getLexeme() == "=>" ) {

//        std::cout << ">" << std::endl;

        insertNode( nodePtr, Scanner.getLexeme() , currentIndent );
        Scanner.scanDriver();
        return;
    }
    else if ( Scanner.getLexeme() == "==" ){
//        std::cout << "==" << std::endl;

        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

        Scanner.scanDriver();
        return;
    }
    else if ( Scanner.getLexeme() == ":" ) {
        //getting the first colon
        insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

        Scanner.scanDriver();
        if( Scanner.getLexeme() == ":") {
            //getting the second colon
            insertNode( nodePtr, Scanner.getLexeme(), currentIndent );

            Scanner.scanDriver();
            return;
        }
    }

}

