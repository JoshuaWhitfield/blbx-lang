#pragma once 

#include <string>
#include <vector>
#include <regex>
#include <cctype>
#include "./types/lexer_type.h"
#include "./tokens/lexer_token.h"

class Lexer {
    private:
        std::string input;
        std::vector<LexerToken> output;
        int pos = 0;
        int line = 1;

        // regex declarations
        std::regex boolean_regex;
        std::regex identifier_regex;

    public: 
        Lexer(
            std::string _input
        ) : input(_input), 

            // regex initialization
            boolean_regex(R"(^(true|false)(?=\s|$|[,:.=()]))"),
            identifier_regex(R"(^(?:[A-Za-z_][A-Za-z0-9_]*)(?=\s|$|[,:.=()]))")

        {}

        const std::vector<LexerToken>& get_output() const {
            return output;
        }


        char get_current() {
            return input.empty() ? '\0' : input.front();
        }

        void add_token(LexerType _type, std::string _value, int _line) {
            output.push_back(LexerToken(_type, _value, _line));
        }

        char consume() {
            char current = get_current();
            input.erase(pos, 1);
            return current;
        }

        void inc_line() {
            line++;
        }

        void tokenize() {
            while (input.size() > 0) {
                // skip empty space
  
                if (get_current() == ' ' or get_current() == ';') {
                    std::cout << "empty space" << std::endl;
                    consume();
                    continue;
                }

                // tokenize new_line
                if (get_current() == '\n') {
                    std::cout << "new line" << std::endl;
                    add_token(LexerType::NEW_LINE, "\n", line);
                    inc_line();
                    consume();
                    continue;
                }

                // tokenize punctuation
                if (get_current() == ':') {
                    std::cout << "colon" << std::endl;
                    add_token(LexerType::COLON, ":", line);
                    consume();
                    continue;
                }

                if (get_current() == ',') {
                    std::cout << "comma" << std::endl;
                    add_token(LexerType::COMMA, ",", line);
                    consume();
                    continue;
                }

                if (get_current() == '.') {
                    std::cout << "dot" << std::endl;
                    add_token(LexerType::DOT, ".", line);
                    consume();
                    continue;
                }

                if (get_current() == '=') {
                    std::cout << "assign" << std::endl;
                    add_token(LexerType::ASSIGN, "=", line);
                    consume();
                    continue;
                }

                // tokenize strings
                if (get_current() == '\'' || get_current() == '\"') {
                    std::cout << "string" << std::endl;
                    std::string captured_string;
                    consume();
                    while (input.size() > 0 && get_current() != '\'' && get_current() != '\"') {
                        captured_string += get_current();
                        consume();
                    }
                    add_token(LexerType::STRING, captured_string, line);
                    if (input.size() > 0 && (get_current() != '\'' && get_current() != '\"')) {
                        // might need to throw error here eventually.
                        // for no closing quotation found till EOF...
                        continue;
                    }
                    consume();
                    continue;
                }

                // tokenize integers
                if (isdigit(get_current())) {
                    std::cout << "integer" << std::endl;
                    std::string captured_integer;
                    while (isdigit(get_current()) && input.size() > 0) {
                        captured_integer += get_current();
                        consume();
                    }
                    // potential error handling
                    add_token(LexerType::INTEGER, captured_integer, line);
                    continue;
                };

                // tokenize booleans
                std::smatch boolean_match;
                if (std::regex_search(input, boolean_match, boolean_regex)) {
                    std::cout << "boolean" << std::endl;
                    int boolean_length = boolean_match[0].length();
                    std::string captured_boolean = boolean_match[0];
                    while (boolean_length > 0) {
                        consume();
                        boolean_length--;
                    };
                    add_token(LexerType::BOOLEAN, captured_boolean, line);
                    continue;
                }

                std::smatch identifier_match;
                if (std::regex_search(input, identifier_match, identifier_regex)) {
                    std::cout << "identifier" << std::endl;
                    std::string value = identifier_match[0];
                    add_token(LexerType::NAMESPACE, value, line);
                    int identifier_length = identifier_match[0].length();
                    while (identifier_length > 0) {
                        consume();
                        identifier_length--;
                    };
                    continue;
                }

                add_token(LexerType:: UNEXPECTED, "\0", line);
                consume();
            }
        }
};