#include <gtest/gtest.h>

#include <strstream>

#include "Parser.hpp"

using namespace utec::compilers;

// Grammar:
// S -> AB
// A -> aA | a
// B -> bB | b

TEST(SimpleTest3, basicTest5) {
    std::istrstream str("(((((((((((((10 + 12");

    Parser parser(str, std::cout);
    EXPECT_FALSE(parser.parse());
}

TEST(SimpleTest, basicTest) {
  std::istrstream str("(43 + 91) * 2 - 19 + (12 * 9) - (9 * 1 + 1)");

  Parser parser(str, std::cout);
  EXPECT_TRUE(parser.parse());
}

TEST(SimpleTest2, basicTest2) {
  std::istrstream str("(((34 + 3) * 42))");

  Parser parser(str, std::cout);
    EXPECT_TRUE(parser.parse());
}

TEST(SimpleTest2, basicTest3) {
    std::istrstream str("(3 + 1) * (4 + 2)");

    Parser parser(str, std::cout);
    EXPECT_TRUE(parser.parse());
}

TEST(SimpleTest2, basicTest4) {
  std::istrstream str("34 - 12 - 10");

  Parser parser(str, std::cout);
    EXPECT_TRUE(parser.parse());
}

TEST(SimpleTest3, basicTest3) {
  std::istrstream str("12 + -32 * -10 - 55");

  Parser parser(str, std::cout);
  EXPECT_TRUE(parser.parse());
}

TEST(SimpleTest3, basicTest6) {
    std::istrstream str("10 / 12 -21");

    Parser parser(str, std::cout);
    EXPECT_FALSE(parser.parse());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}