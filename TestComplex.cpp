#include <gtest/gtest.h>
#include "parser.h"
#include <sstream>

class ComplexTest : public ::testing::Test {
protected:
    std::map<std::string, double> vars;
};

// ------------------- TEST CASES -------------------

TEST_F(ComplexTest, OrderOfOperations) {
    Parser parser("2+3*4");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 14);
}

TEST_F(ComplexTest, MixedOperations) {
    Parser parser("10-8/2+3");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 9);
}

TEST_F(ComplexTest, ComplexWithVariables) {
    Parser parser("X*Y+Z/W");
    auto exprTree = parser.parse();
    vars["X"] = 2;
    vars["Y"] = 3;
    vars["Z"] = 10;
    vars["W"] = 2;
    EXPECT_EQ(exprTree->calc(vars), 11);
}

TEST_F(ComplexTest, StringRepresentation) {
    Parser parser("2*3+4/2");
    auto exprTree = parser.parse();

    std::ostringstream output;
    exprTree->print(); 
    testing::internal::CaptureStdout();
    exprTree->print();
    std::string printedExpr = testing::internal::GetCapturedStdout();

    EXPECT_EQ(printedExpr, "((2 * 3) + (4 / 2))");
}
