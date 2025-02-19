#include <gtest/gtest.h>
#include "parser.h"

class SubtractTest : public ::testing::Test {
protected:
    std::map<std::string, double> vars;
};

TEST_F(SubtractTest, SimpleSubtraction) {
    Parser parser("10-4");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 6);
}

TEST_F(SubtractTest, MultipleSubtractions) {
    Parser parser("10-4-2");
    auto exprTree = parser.parse();
    EXPECT_EQ(exprTree->calc(vars), 4);
}

TEST_F(SubtractTest, SubtractionWithVariables) {
    Parser parser("X-Y");
    auto exprTree = parser.parse();
    vars["X"] = 10;
    vars["Y"] = 4;
    EXPECT_EQ(exprTree->calc(vars), 6);
}

TEST_F(SubtractTest, SubtractionWithMixedTerms) {
    Parser parser("10-X");
    auto exprTree = parser.parse();
    vars["X"] = 4;
    EXPECT_EQ(exprTree->calc(vars), 6);
}