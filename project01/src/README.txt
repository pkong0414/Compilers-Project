Patrick Kong
CS4280

Project 1

Option 4: FSA table + driver

The scanner will read the file given and produce a report in the format:

-----------------------------------------------------------------------
tokenType:
lexeme:
line:
-----------------------------------------------------------------------

***********************************************************************

Token Types:
ID:  1001
INT: 1002
OP:  1003
EOF: 1005

***********************************************************************

Errors will also be reported as such:
-----------------------------------------------------------------------

line:<num> ERROR: <error type>.

-----------------------------------------------------------------------

NOTE: Symbol errors will exit program, but lexical errors will
keep the scanner working

ERRORS: The scanner occasionally has weird outputs when making the lexeme reports.
I have not been able to figure out how to make it output it right.

********************************************* FATable ****************************************************

FOR THE FATable PLEASE REFER TO THE SCANNER PROGRAM, I TOOK GREAT PAINS TO MAKE IT LEGIBLE IN THE PROGRAM.

I decided to make = pay attention to the WS, since I can't have it desired outputs in test2 and test3.

= goes into a special state 24 which ends with WS, =, <, > to form the special operators.