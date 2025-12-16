#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// include lexer
#include "../../lexer/lexer.h"

// helper to print token types nicely
const char* lexer_type_to_string(LexerType type) {
    switch (type) {
        case LexerType::BOOLEAN:   return "BOOLEAN";
        case LexerType::INTEGER:   return "INTEGER";
        case LexerType::STRING:    return "STRING";
        case LexerType::NAMESPACE: return "NAMESPACE";
        case LexerType::NEW_LINE:  return "NEW_LINE";
        case LexerType::COLON:     return "COLON";
        case LexerType::COMMA:     return "COMMA";
        case LexerType::DOT:       return "DOT";
        case LexerType::ASSIGN:    return "ASSIGN";
        default:                   return "UNKNOWN";
    }
}

int main() {
    // path to test input
    const std::string test_file_path =
        "C:\\Users\\jos2394075\\Desktop\\dev\\blbx-lang\\tests\\first_test.bx";

    // read file into string
    std::ifstream file(test_file_path);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file: " << test_file_path << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    file.close();

    // initialize lexer
    Lexer lexer(source);

    // tokenize
    lexer.tokenize();

    // dump tokens
    const auto& tokens = lexer.get_output();

    std::cout << "==== TOKEN DUMP ====" << std::endl;

    for (const auto& token : tokens) {
        std::cout
            << "Line " << token.get_line()
            << " | " << lexer_type_to_string(token.get_type())
            << " | \"" << token.get_value() << "\""
            << std::endl;
    }

    std::cout << "==== END ====" << std::endl;

    return 0;
}
