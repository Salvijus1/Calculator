#include "parser.h"
#include <unordered_set>
#include <iostream>

int main() {
    std::string input;
    std::cout << "Enter expression: ";
    std::getline(std::cin, input);

    try {
        // Parse the input expression
        Parser parser(input);
        auto expressionTree = parser.parse();

        // Collect variable names
        std::map<std::string, double> variables;
        std::unordered_set<char> uniqueVariables;

        for (char c : input) {
            if (isalpha(c)) {
                uniqueVariables.insert(c);
            }
        }

        // Request values for variables
        for (char var : uniqueVariables) {
            std::cout << "Enter value for " << var << ": ";
            std::cin >> variables[std::string(1, var)];
        }

        // Display results
        std::cout << "Parsed Expression: ";
        expressionTree->print();
        std::cout << std::endl;

        std::cout << "Result: " << expressionTree->calc(variables) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
