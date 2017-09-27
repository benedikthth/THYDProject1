//
// Compiler project -- main driver for part 1
//
#include "hlexer.h"

using namespace std;

HLexer::HLexer( std::istream& is, SymbolTable& symbol_table )
    : Lexer( is, symbol_table ), line_no_(1)
{
    is_.get( c_ );
}


void HLexer::get_next( Token& token )
{
    token.lexeme.clear();
    token.entry = nullptr;

    while ( is_.good() && isspace(c_) ) {
        if ( c_ == '\n' ) { ++line_no_; }
        is_.get(c_);
    }



    token.line = line_no_;

    if ( !is_.good() ) {
        token.type = Tokentype::EOI;
        return;
    }

    switch ( c_ ) {
        // Arithmetic operators
        case '+':
            token.type = Tokentype::OpArtPlus;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '+') {
                token.type = Tokentype::OpArtInc;
                token.lexeme.push_back(c_);
                is_.get(c_);
            }
            break;
        case '-':
            token.type = Tokentype::OpArtMinus;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '&') {
                token.type = Tokentype::OpArtDec;
                token.lexeme.push_back(c_);
                is_.get(c_);
            }
            break;

        case '*':
            token.type = Tokentype::OpArtMult;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case '/':
            token.type = Tokentype::OpArtDiv;
            token.lexeme.push_back(c_);
            is_.get(c_);

            if(c_ == '*'){

              //we're in a comment!!*
              while( is_.good() ){
                is_.get(c_);
                if( c_ == '*' && is_.good() ){
                    // exiting comment?
                    is_.get(c_);
                    if(c_ == '/'){
                      is_.get(c_);
                      break;
                    }
                }else if(c_ == '\n'){
                  ++ line_no_;
                }

              }
            //  is_.get(c_);
              get_next(token);
            }



            break;
        case '%':
            token.type = Tokentype::OpArtModulus;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;

        // Logical Operators and assignment
        case '!':
            token.type = Tokentype::OpLogNot;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '=') {
                token.type = Tokentype::OpRelNEQ;
                token.lexeme.push_back(c_);
                is_.get(c_);
            }
            break;
        case '|':
            token.type = Tokentype::ErrUnknown;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '|') {
                token.type = Tokentype::OpLogOr;
                token.lexeme.push_back(c_);
                is_.get(c_);
            }
            break;
        case '&':
            token.type = Tokentype::ErrUnknown;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '&') {
                token.type = Tokentype::OpLogAnd;
                token.lexeme.push_back(c_);
            }
            break;
        case '<':
            token.type = Tokentype::OpRelLT;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '=') {
                token.type = Tokentype::OpRelLTE;
                token.lexeme.push_back(c_);
            }
            break;
        case '>':
            token.type = Tokentype::OpRelGT;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '=') {
                token.type = Tokentype::OpRelGTE;
                token.lexeme.push_back(c_);
            }
            break;
        case '=':
            token.type = Tokentype::OpAssign;
            token.lexeme.push_back(c_);
            is_.get(c_);
            /*
            if(is_.good() && c_ == '=') {
                token.type = Tokentype::OpRelEQ;
                token.lexeme.push_back(c_);
                is_.get(c_);
            }
            */
            break;

        // Punctuation marks
        case '{':
            token.type = Tokentype::ptLBrace;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case '}':
            token.type = Tokentype::ptRBrace;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case '[':
            token.type = Tokentype::ptLBracket;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case ']':
            token.type = Tokentype::ptRBracket;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case '(':
            token.type = Tokentype::ptLParen;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case ')':
            token.type = Tokentype::ptRParen;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case ';':
            token.type = Tokentype::ptSemicolon;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
        case ',':
            token.type = Tokentype::ptComma;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;


        default:
            // Keyword or identifier
            if(isalpha(c_)) {
                while(is_.good() && (isalpha(c_) || c_ == '_' || isdigit(c_))) {
                    token.lexeme.push_back(c_);
                    is_.get(c_);
                }
                if(token.lexeme == "class") {
                    token.type = Tokentype::kwClass;
                }
                else if(token.lexeme == "static") {
                    token.type = Tokentype::kwStatic;
                }
                else if(token.lexeme == "void") {
                    token.type = Tokentype::kwVoid;
                }
                else if(token.lexeme == "if") {
                    token.type = Tokentype::kwIf;
                }
                else if(token.lexeme == "else") {
                    token.type = Tokentype::kwElse;
                }
                else if(token.lexeme == "for") {
                    token.type = Tokentype::kwFor;
                }
                else if(token.lexeme == "return") {
                    token.type = Tokentype::kwReturn;
                }
                else if(token.lexeme == "break") {
                    token.type = Tokentype::kwBreak;
                }
                else if(token.lexeme == "continue") {
                    token.type = Tokentype::kwContinue;
                }
                else if(token.lexeme == "int") {
                    token.type = Tokentype::kwInt;
                }
                else if(token.lexeme == "real") {
                    token.type = Tokentype::kwReal;
                }
                else {
                    token.type = Tokentype::Identifier;
                    //TODO: add symbol table entry.

                    token.entry = symbol_table_.lookup(token.lexeme);
                    if(token.entry == nullptr){
                      SymbolTable::Entry entry;
                      entry.name = token.lexeme;
                      token.entry = symbol_table_.add(entry);
                    }

                }
                //is_.get(c_);
            }
            // Number
            else if(isdigit(c_)) {
               token.type = Tokentype::Number;
               //is_.get(c_);
               //check if token is . or E
               while(isdigit(c_) && is_.good() ){

                 token.lexeme.push_back(c_);
                 is_.get(c_);

                 if(!isdigit(c_)){

                   //check if c_ is . or E.
                   // 1.2E-1E
                   if( c_ == 'E' && is_.good() ){
                     token.lexeme.push_back(c_);
                     is_.get(c_);
                     //check for sign
                     if(c_ == '+' || c_ == '-'){
                       token.lexeme.push_back(c_);
                       is_.get(c_);
                     }
                   } else if(c_ == '.'){
                     token.lexeme.push_back(c_);
                     is_.get(c_);
                   }

                 }


               }

               /**/
               token.entry = symbol_table_.lookup(token.lexeme);
               if(token.entry == nullptr){
                 SymbolTable::Entry entry;
                 entry.name = token.lexeme;
                 token.entry = symbol_table_.add(entry);
               }

            }

            else {
                token.type = Tokentype::ErrUnknown;
                token.lexeme.push_back(c_);
                is_.get(c_);
            }
            break;
    }
}

std::string HLexer::get_name() const {
    return "handmade";
}

HLexer::~HLexer()
{
}
