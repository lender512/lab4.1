#pragma once

#include <vector>
#include "FlexScanner.hpp"
#include "Token.hpp"

namespace utec {
namespace compilers {

// Grammar:
// S -> AB
// A -> aA | a      ===>    a [A]
// B -> bB | b      ===>    b [B]

class Parser {
 public:
  Parser(std::istream& arg_yyin, std::ostream& arg_yyout) : scanner(arg_yyin, arg_yyout) {}
  
  void expect(Categoria cat_expected){
    auto token = scanner.query_token();
    if (token._atributo == cat_expected){
      scanner.get_token();
    } else{
      errors.push_back("caracter " + token._lexema + " unexpected");
    }
  }

  void A() {
    expect(Categoria::A);

    if( scanner.query_token()._atributo == Categoria::A ){
        A();
    }
  }

  void B() {
    expect(Categoria::B);

    if( scanner.query_token()._atributo == Categoria::B ){
        B();
    }
  }

  void S(){
    A();
    B();
  }

  std::vector<std::string> parse() {
    S();

    expect(Categoria::END);
    return errors;

    // if( scanner.query_token()._atributo == Categoria::END 
    //   && errors.empty())
    //   return true;
    // return false;
  }

 private:
  std::vector<std::string> errors;
  FlexScanner scanner;
};

}  // namespace compilers
}  // namespace utec