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
"class"         { return Tokentype::kwClass; }
"static"        { return Tokentype::kwStatic; }
"void"          { return Tokentype::kwVoid; }
"if"            { return Tokentype::kwIf; }
"else"        { return Tokentype::kwElse; }
"for"           { return Tokentype::kwFor; }
"return"        { return Tokentype::kwReturn; }
"break"       { return Tokentype::kwBreak; }
"continue"    { return Tokentype::kwContinue; }
"int"           { return Tokentype::kwInt; }
"real"          { return Tokentype::kwReal; }

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
