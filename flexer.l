 // Skeleton Flex file for the project - Part 1
 //"/*"([^"*/"])*"*/"   /* Comment, do nothing */
%option c++
%option noyywrap
%option yylineno
%{
#include "token.h"
%}
ws [ \t\r\n]
letter [a-zA-Z]
digit [0-9]


%%
{ws}+                /* do nothing */
"/*"("/*"|[^"*/"])*"*/"  /*nothing*/

"++"            { return Tokentype::OpArtInc; }
"+"             { return Tokentype::OpArtPlus; }
"--"            { return Tokentype::OpArtDec; }
"-"             { return Tokentype::OpArtMinus; }
"*"             { return Tokentype::OpArtMult; }
"/"             { return Tokentype::OpArtDiv; }
"%"             { return Tokentype::OpArtModulus; }

"=="            { return Tokentype::OpRelEQ; }
"!="            { return Tokentype::OpRelNEQ; }
"<="            { return Tokentype::OpRelLTE; }
"<"             { return Tokentype::OpRelLT; }
">="            { return Tokentype::OpRelGTE; }
">"             { return Tokentype::OpRelGT; }

"&&"            { return Tokentype::OpLogAnd; }
"||"            { return Tokentype::OpLogOr; }
"!"             { return Tokentype::OpLogNot; }

"="             { return Tokentype::OpAssign; }

"class"         { return Tokentype::kwClass; }
"static"        { return Tokentype::kwStatic; }
"void"          { return Tokentype::kwVoid; }
"if"            { return Tokentype::kwIf; }
"else"          { return Tokentype::kwElse; }
"for"           { return Tokentype::kwFor; }
"return"        { return Tokentype::kwReturn; }
"break"         { return Tokentype::kwBreak; }
"continue"      { return Tokentype::kwContinue; }
"int"           { return Tokentype::kwInt; }
"real"          { return Tokentype::kwReal; }

"{"             { return Tokentype::ptLBrace; }
"}"             { return Tokentype::ptRBrace; }
"["             { return Tokentype::ptLBracket; }
"]"             { return Tokentype::ptRBracket; }
"("             { return Tokentype::ptLParen; }
")"             { return Tokentype::ptRParen; }
";"             { return Tokentype::ptSemicolon; }
","             { return Tokentype::ptComma; }

{digit}+("."{digit}*("E"(([+-])?{digit})?)?)?   { return Tokentype::Number; }
{letter}({letter}|{digit}|"_")*                 { return Tokentype::Identifier; }

.               { return Tokentype::ErrUnknown; }
%%
 // No need to add any code here.
