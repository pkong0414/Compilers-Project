# Compilers-Project
A Compiler's Project

This Project is aims to make a program translation from a custom grammar to UMSL's custom assembly code using c++ to facilitate the program translation.


BNF Grammar:

  This is the custom grammar we are using for this translation. 
  
  The grammar will start from the top and build down starting at <program> and ending with an integer or identifier.

"<&nbsp;program&nbsp;>  ->      start <&nbsp;vars&nbsp;> main <&nbsp;block&nbsp;> stop" <br />
"<&nbsp;block&nbsp;>    ->      { <&nbsp;vars&nbsp;> <&nbsp;stats&nbsp;> }" <br />
"<&nbsp;vars&nbsp;>     ->      empty | let Identifier :  Integer    <&nbsp;vars&nbsp;>" <br />
"<&nbsp;expr&nbsp;>     ->      <&nbsp;N&nbsp;> / <&nbsp;expr&nbsp;>  | <&nbsp;N&nbsp;> * <&nbsp;expr&nbsp;> | <&nbsp;N&nbsp;>" <br />
"<&nbsp;N&nbsp;>        ->      <&nbsp;A&nbsp;> + <&nbsp;N&nbsp;> | <&nbsp;A&nbsp;> - <&nbsp;N&nbsp;> | <&nbsp;A&nbsp;>" <br />
"<&nbsp;A&nbsp;>        ->      % <&nbsp;A&nbsp;> |  <&nbsp;R&nbsp;>" <br />
"<&nbsp;R&nbsp;>        ->      [ <&nbsp;expr&nbsp;> ] | Identifier | Integer" <br />
"<&nbsp;stats&nbsp;>    ->      <&nbsp;stat&nbsp;>  <&nbsp;mStat&nbsp;>" <br />
"<&nbsp;mStat&nbsp;>    ->      empty |  <&nbsp;stat&nbsp;>  <&nbsp;mStat&nbsp;>" <br />
"<&nbsp;stat&nbsp;>     ->      <&nbsp;in&nbsp;> .  | <&nbsp;out&nbsp;> .  | <&nbsp;block&nbsp;> | <&nbsp;if&nbsp;> .  | <&nbsp;loop&nbsp;> .  | <&nbsp;assign&nbsp;> ." <br />  
"<&nbsp;in&nbsp;>       ->      scanf [ Identifier ]" <br />
"<&nbsp;out&nbsp;>      ->      printf [ <&nbsp;expr&nbsp;> ]" <br />
"<&nbsp;if&nbsp;>       ->      if [ <&nbsp;expr&nbsp;> <&nbsp;RO&nbsp;> <&nbsp;expr&nbsp;> ] then <&nbsp;block&nbsp;>" <br />
"<&nbsp;loop&nbsp;>     ->      iter [ <&nbsp;expr&nbsp;> <&nbsp;RO&nbsp;> <&nbsp;expr&nbsp;> ]  <&nbsp;block&nbsp;>" <br />
"<&nbsp;assign&nbsp;>   ->      Identifier  = <&nbsp;expr&nbsp;>" <br />
"<&nbsp;RO&nbsp;>       ->      =<  | =>   |  ==  |   :  :  (two tokens)" <br />
  
Instructions:
  
  Each Projects will contain a makefile. 
  
  Commands:
  make: to make the objects for the project program.
  
  make clean: to clean up all the objects for the project program.
  
  To run the project executable, please check the readme under each projects. 
  There'll be an invocation section describing how to execute program as well as parameters needed to run the program.
    
  
  
