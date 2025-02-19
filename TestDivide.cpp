#include <gtest/gtest.h>
#include "parser.h"

class DivideTest : public ::testing::Test {
protected:
    std::map<std::string, double> vars;
};

// ------------------- TEST CASES -------------------

TEST_F(DivideTest, SimpleDivision) {
    Parser parser("15/3");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 5);
}

TEST_F(DivideTest, MultipleDivisions) {
    Parser parser("24/3/2");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 4);
}

TEST_F(DivideTest, DivisionWithVariables) {
    Parser parser("X/Y");
    auto exprTree = parser.parse();
    vars["X"] = 15;
    vars["Y"] = 3;
    EXPECT_EQ(exprTree->calc(vars), 5);
}

TEST_F(DivideTest, DivisionWithMixedTerms) {
    Parser parser("15/X");
    auto exprTree = parser.parse();
    vars["X"] = 3;
    EXPECT_EQ(exprTree->calc(vars), 5);
}

TEST_F(DivideTest, DivisionByZero) {
    Parser parser("15/0");
    auto exprTree = parser.parse();
    EXPECT_THROW(exprTree->calc(vars), std::runtime_error);
}
