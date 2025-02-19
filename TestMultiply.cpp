#include <gtest/gtest.h>
#include "parser.h"

class MultiplyTest : public ::testing::Test {
protected:
    std::map<std::string, double> vars;
};

TEST_F(MultiplyTest, SimpleMultiplication) {
    Parser parser("6*7");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 42);
}

TEST_F(MultiplyTest, MultipleMultiplications) {
    Parser parser("2*3*4");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 24);
}

TEST_F(MultiplyTest, MultiplicationWithVariables) {
    Parser parser("X*Y");
    auto exprTree = parser.parse();
    vars["X"] = 6;
    vars["Y"] = 7;
    EXPECT_EQ(exprTree->calc(vars), 42);
}

TEST_F(MultiplyTest, MultiplicationWithMixedTerms) {
    Parser parser("6*X");
    auto exprTree = parser.parse();
    vars["X"] = 7;
    EXPECT_EQ(exprTree->calc(vars), 42);
}