#include <gtest/gtest.h>

#include <strstream>

#include "Parser.hpp"

using namespace utec::compilers;

class ParamTest : public testing::TestWithParam<std::pair<std::string, std::vector<std::string>>> {
};

// Grammar:
// S -> AB
// A -> aA | a
// B -> bB | b

TEST_P(ParamTest, basicTest) {
  std::istrstream str(GetParam().first.c_str());

  Parser parser(str, std::cout);
  EXPECT_EQ(parser.parse(), GetParam().second);
}

INSTANTIATE_TEST_SUITE_P(SimpleTest,
                         ParamTest,
                         testing::Values(
                          std::make_pair("aaaaaab", std::vector<std::string>()),
                          std::make_pair("abbbbbb", std::vector<std::string>()),
                          std::make_pair("b", std::vector<std::string>{"caracter b unexpected"}),
                          std::make_pair("a", std::vector<std::string>{"caracter END unexpected"}),
                          std::make_pair("aaaaaabbbbbb", std::vector<std::string>()),
                          std::make_pair("ab", std::vector<std::string>()),
                          std::make_pair("ba", std::vector<std::string>{"caracter b unexpected", "caracter a unexpected"}),
                          std::make_pair("", std::vector<std::string>{"caracter END unexpected", "caracter END unexpected"}),
                          std::make_pair("d", std::vector<std::string>{"caracter d unexpected", "caracter d unexpected", "caracter d unexpected"}),
                          std::make_pair("ac", std::vector<std::string>{"caracter c unexpected", "caracter c unexpected"}),
                          std::make_pair("aba", std::vector<std::string>{"caracter a unexpected"})
                         ));

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}