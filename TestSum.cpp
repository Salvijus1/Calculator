#include <gtest/gtest.h>
#include "parser.h"

class SumTest : public ::testing::Test {
protected:
    std::map<std::string, double> vars;
};

TEST_F(SumTest, SimpleAddition) {
    Parser parser("5+3");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 8);
}

TEST_F(SumTest, MultipleAdditions) {
    Parser parser("5+3+2");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 10);
}

TEST_F(SumTest, AdditionWithVariables) {
    Parser parser("X+Y");
    auto exprTree = parser.parse();
    vars["X"] = 5;
    vars["Y"] = 3;
    EXPECT_EQ(exprTree->calc(vars), 8);
}

TEST_F(SumTest, AdditionWithMixedTerms) {
    Parser parser("5+X");
    auto exprTree = parser.parse();
    vars["X"] = 3;
    EXPECT_EQ(exprTree->calc(vars), 8);
}