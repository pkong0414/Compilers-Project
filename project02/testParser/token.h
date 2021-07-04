/*  token.h
 *
 * this file will contain all the tokens necessary to perform the fsa operations.
 *
 */


#ifndef TOKEN_H
#define TOKEN_H

//Errors: incorrect ID/int, incorrect OP
#define ERROR_ID_INT -100
#define ERROR_OP     -101

//Token types
#define TK_ID    1001
#define TK_INT   1002
#define TK_OP    1003
#define TK_EOF   1005
#define INITIAL     0
#define FINAL    1000

//Keyword types
//KEYWORDS: start stop iter void int exit scanf printf main if then let data func
#define KWSTART     1010
#define KWSTOP      1011
#define KWITER      1012
#define KWVOID      1013
#define KWINT       1014
#define KWEXIT      1015
#define KWSCANF     1016
#define KWPRINTF    1017
#define KWMAIN      1018
#define KWIF        1019
#define KWTHEN      1020
#define KWLET       1021
#define KWDATA      1022
#define KWFUNC      1023

#endif
