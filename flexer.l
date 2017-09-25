 // Skeleton Flex file for the project - Part 1
%option c++
%option noyywrap
%option yylineno
%{
#include "token.h"
%}
ws [ \t\r\n]
%%
{ws}+             /* do nothing */

"{"             { return Tokentype::ptLBrace; }
"}"             { return Tokentype::ptRBrace; }
"["             { return Tokentype::ptLBracket; }
"]"             { return Tokentype::ptRBracket; }
"("            { return Tokentype::ptLParen; }
")"             { return Tokentype::ptRParen; }
";"             { return Tokentype::ptSemicolon; }
","             { return Tokentype::ptComma; }

.               { return Tokentype::ErrUnknown; }
%%
 // No need to add any code here.
