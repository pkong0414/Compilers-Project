Patrick Kong
CS4280

Project 3

Option: local

invocation:
./statSem <filename.fs>

This program incorporates static semantics into the parser. This will allow the program to have global and local scoped
variables. We'll only do STV (global stack) on <var> before the main. Once we pass main, every block will contain its
own local stack. Local stack will stay with scope and will pop in number of variables counted to keep the local stack
consistent with scope.

NOTE:
Initially I've tried using queues instead of set since set auto sorts, but since queues has minimal interface and I need
the option for traversal, I've used deque instead.

Please forgive the late submission, just have not been feeling good past few days.

For now I'm printing local stack and global stack (no more trees).