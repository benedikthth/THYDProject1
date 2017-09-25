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
            }
            break;
        case '-':
            token.type = Tokentype::OpArtMinus;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '&') {
                token.type = Tokentype::OpArtDec;
                token.lexeme.push_back(c_);
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
            }
            break;
        case '|':
            token.type = Tokentype::ErrUnknown;
            token.lexeme.push_back(c_);
            is_.get(c_);
            if(is_.good() && c_ == '|') {
                token.type = Tokentype::OpLogOr;
                token.lexeme.push_back(c_);
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
            if(is_.good() && c_ == '=') {
                token.type = Tokentype::OpRelEQ;
                token.lexeme.push_back(c_);
            }
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
            token.type = Tokentype::ErrUnknown;
            token.lexeme.push_back(c_);
            is_.get(c_);
            break;
    }
}

std::string HLexer::get_name() const {
    return "handmade";
}

HLexer::~HLexer()
{
}
