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