#pragma once

#include <FlexLexer.h>

#include "Token.hpp"

namespace utec {
namespace compilers {

class FlexScanner : public yyFlexLexer {
 public:
  FlexScanner(std::istream& arg_yyin, std::ostream& arg_yyout)
      : yyFlexLexer(arg_yyin, arg_yyout) {}
  FlexScanner(std::istream* arg_yyin = nullptr,
              std::ostream* arg_yyout = nullptr)
      : yyFlexLexer(arg_yyin, arg_yyout) {}

  Token query_token(){
    if(last_token._lexema == "END")
      last_token = get_token();
    return last_token;
  }

  Token get_token() {
    if(last_token._lexema != "END"){
      Token token_copy = last_token;
      last_token = Token();
      return token_copy;
    }
    int value;
    if ((value = yylex()) == 0) return Token();

    return Token(yytext, (Categoria)value);
  }

  private:
    Token last_token;
};

}  // namespace compilers
}  // namespace utec