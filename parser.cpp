#include "parser.h"

// ------------------- Value Implementation -------------------
Value::Value(double val) : value(val) {}

double Value::calc(std::map<std::string, double>&) {
    return value;
}

void Value::print() {
    std::cout << value;
}

// ------------------- Variable Implementation -------------------
Variable::Variable(std::string var) : name(std::move(var)) {}

double Variable::calc(std::map<std::string, double>& variables) {
    return variables.at(name);
}

void Variable::print() {
    std::cout << name;
}

// ------------------- Sum Implementation -------------------
Sum::Sum(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs) 
    : left(std::move(lhs)), right(std::move(rhs)) {}

double Sum::calc(std::map<std::string, double>& variables) {
    return left->calc(variables) + right->calc(variables);
}

void Sum::print() {
    std::cout << "(";
    left->print();
    std::cout << " + ";
    right->print();
    std::cout << ")";
}

// ------------------- Substr Implementation -------------------
Substr::Substr(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs) 
    : left(std::move(lhs)), right(std::move(rhs)) {}

double Substr::calc(std::map<std::string, double>& variables) {
    return left->calc(variables) - right->calc(variables);
}

void Substr::print() {
    std::cout << "(";
    left->print();
    std::cout << " - ";
    right->print();
    std::cout << ")";
}

// ------------------- Multipl Implementation -------------------
Multipl::Multipl(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs) 
    : left(std::move(lhs)), right(std::move(rhs)) {}

double Multipl::calc(std::map<std::string, double>& variables) {
    return left->calc(variables) * right->calc(variables);
}

void Multipl::print() {
    std::cout << "(";
    left->print();
    std::cout << " * ";
    right->print();
    std::cout << ")";
}

// ------------------- Divide Implementation -------------------
Divide::Divide(std::unique_ptr<INode> lhs, std::unique_ptr<INode> rhs) 
    : left(std::move(lhs)), right(std::move(rhs)) {}

double Divide::calc(std::map<std::string, double>& variables) {
    double denominator = right->calc(variables);
    if (denominator == 0) throw std::runtime_error("Division by zero");
    return left->calc(variables) / denominator;
}

void Divide::print() {
    std::cout << "(";
    left->print();
    std::cout << " / ";
    right->print();
    std::cout << ")";
}

// ------------------- Parser Implementation -------------------
Parser::Parser(std::string expr) : expression(std::move(expr)) {}

char Parser::peek() {
    while (index < expression.length() && isspace(expression[index])) ++index;
    return (index < expression.length()) ? expression[index] : '\0';
}

char Parser::get() {
    return (index < expression.length()) ? expression[index++] : '\0';
}

std::unique_ptr<INode> Parser::parsePrimary() {
    char ch = peek();
    if (isdigit(ch) || ch == '.') return parseNumber();
    if (isalpha(ch)) return parseVariable();
    if (ch == '(') {
        get(); 
        auto node = parseExpression();
        get(); 
        return node;
    }
    throw std::runtime_error("Invalid character in expression.");
}

std::unique_ptr<INode> Parser::parseNumber() {
    std::string num;
    while (isdigit(peek()) || peek() == '.') num += get();
    return std::make_unique<Value>(std::stod(num));
}

std::unique_ptr<INode> Parser::parseVariable() {
    std::string var;
    while (isalpha(peek())) var += get();
    return std::make_unique<Variable>(var);
}

std::unique_ptr<INode> Parser::parseTerm() {
    auto left = parsePrimary();
    while (peek() == '*' || peek() == '/') {
        char op = get();
        auto right = parsePrimary();
        if (op == '*') left = std::make_unique<Multipl>(std::move(left), std::move(right));
        else left = std::make_unique<Divide>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<INode> Parser::parseExpression() {
    auto left = parseTerm();
    while (peek() == '+' || peek() == '-') {
        char op = get();
        auto right = parseTerm();
        if (op == '+') left = std::make_unique<Sum>(std::move(left), std::move(right));
        else left = std::make_unique<Substr>(std::move(left), std::move(right));
    }
    return left;
}

std::unique_ptr<INode> Parser::parse() {
    return parseExpression();
}
