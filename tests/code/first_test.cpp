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
        // punctuation
        case LexerType::COMMA:        return "COMMA";
        case LexerType::DOT:          return "DOT";
        case LexerType::SEMICOLON:    return "SEMICOLON";
        case LexerType::COLON:        return "COLON";
        case LexerType::ASSIGN:       return "ASSIGN";
        case LexerType::NEW_LINE:     return "NEW_LINE";
        case LexerType::RIGHT_CAROT:  return "RIGHT_CAROT";

        // symbols
        case LexerType::OPEN_ARRAY:   return "OPEN_ARRAY";
        case LexerType::CLOSE_ARRAY:  return "CLOSE_ARRAY";
        case LexerType::OPEN_OBJECT:  return "OPEN_OBJECT";
        case LexerType::CLOSE_OBJECT: return "CLOSE_OBJECT";
        case LexerType::OPEN_PAREN:   return "OPEN_PAREN";
        case LexerType::CLOSE_PAREN:  return "CLOSE_PAREN";

        // names
        case LexerType::NAMESPACE:    return "NAMESPACE";

        // literals
        case LexerType::STRING:       return "STRING";
        case LexerType::INTEGER:      return "INTEGER";
        case LexerType::FLOAT:        return "FLOAT";
        case LexerType::BOOLEAN:      return "BOOLEAN";

        // unexpected
        case LexerType::UNEXPECTED:   return "UNEXPECTED";

        default:                      return "UNKNOWN";
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
