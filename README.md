# Compilers-Project
A Compiler's Project

This Project is aims to make a program translation from a custom grammar to UMSL's custom assembly code using c++ to facilitate the program translation.


BNF Grammar:

  This is the custom grammar we are using for this translation. 
  
  The grammar will start from the top and build down starting at <program> and ending with an integer or identifier.

<program>  ->      start <vars> main <block> stop
<block>    ->      { <vars> <stats> }
<vars>     ->      empty | let Identifier :  Integer    <vars>
<expr>     ->      <N> / <expr>  | <N> * <expr> | <N>
<N>        ->      <A> + <N> | <A> - <N> | <A>
<A>        ->      % <A> |  <R>
<R>        ->      [ <expr> ] | Identifier | Integer
<stats>    ->      <stat>  <mStat>
<mStat>    ->      empty |  <stat>  <mStat>
<stat>     ->      <in> .  | <out> .  | <block> | <if> .  | <loop> .  | <assign> .  
<in>       ->      scanf [ Identifier ]
<out>      ->      printf [ <expr> ]
<if>       ->      if [ <expr> <RO> <expr> ] then <block>
<loop>     ->      iter [ <expr> <RO> <expr> ]  <block>
<assign>   ->      Identifier  = <expr> 
<RO>       ->      =<  | =>   |  ==  |   :  :  (two tokens)
  
Instructions:
  
  Each Projects will contain a makefile. 
  
  Commands:
  make: to make the objects for the project program.
  
  make clean: to clean up all the objects for the project program.
  
  To run the project executable, please check the readme under each projects. 
  There'll be an invocation section describing how to execute program as well as parameters needed to run the program.
    
  
  
