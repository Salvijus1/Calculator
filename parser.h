#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <sstream>
#include <map>
#include <memory>
#include <cctype>

// Interface for all nodes
class INode {
public:
    virtual double calc(std::map<std::string, double>& variables) = 0;
    virtual void print() = 0;
    virtual ~INode() = default;
};

// Value Node
class Value : public INode {
    double value;
public:
    explicit Value(double val);
    double calc(std::map<std::string, double>&) override;
    void print() override;
};

// Variable Node
class Variable : public INode {
    std::string name;
public:
    explicit Variable(std::string var);
    double calc(std::map<std::string, double>& variables) override;
    void print() override;
};

// Operator Nodes
class Sum : public INode {
    std::unique_ptr<INode> left, right;
public:
    Sum(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs);
    double calc(std::map<std::string, double>& variables) override;
    void print() override;
};

class Substr : public INode {
    std::unique_ptr<INode> left, right;
public:
    Substr(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs);
    double calc(std::map<std::string, double>& variables) override;
    void print() override;
};

class Multipl : public INode {
    std::unique_ptr<INode> left, right;
public:
    Multipl(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs);
    double calc(std::map<std::string, double>& variables) override;
    void print() override;
};

class Divide : public INode {
    std::unique_ptr<INode> left, right;
public:
    Divide(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs);
    double calc(std::map<std::string, double>& variables) override;
    void print() override;
};

// Parser Class
class Parser {
    std::string expression;
    size_t index = 0;
    char peek();
    char get();
    std::unique_ptr<INode> parsePrimary();
    std::unique_ptr<INode> parseNumber();
    std::unique_ptr<INode> parseVariable();
    std::unique_ptr<INode> parseTerm();
    std::unique_ptr<INode> parseExpression();
public:
    explicit Parser(std::string expr);
    std::unique_ptr<INode> parse();
};

#endif
