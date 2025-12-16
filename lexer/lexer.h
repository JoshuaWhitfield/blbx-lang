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
        int line = 0;

        // regex declarations
        std::regex boolean_regex;

    public: 
        Lexer(
            std::string _input
        ) : input(_input), 

            // regex initialization
            boolean_regex(R"((true|false)(?=\s))")

        {}

        char get_current() {
            return this->input.empty() ? '\0' : this->input.front();
        }

        void add_token(LexerType _type, std::string _value, int _line) {
            this->output.push_back(LexerToken(_type, _value, _line));
        }

        char consume() {
            char current = this->get_current();
            this->input.erase(this->pos);
            return current;
        }

        void inc_line() {
            this->line++;
        }

        void tokenize() {
            while (this->input.size() > 0) {
                // skip empty space
                if (this->get_current() == ' ') {
                    this->consume();
                    continue;
                }

                // tokenize new_line
                if (this->get_current() == '\n' or this->get_current() == ';') {
                    this->add_token(LexerType::NEW_LINE, "\n", this->line);
                    this->inc_line();
                    this->consume();
                    continue;
                }

                // tokenize punctuation
                if (this->get_current() == ':') {
                    this->add_token(LexerType::COLON, ":", this->line);
                    this->consume();
                    continue;
                }

                if (this->get_current() == ',') {
                    this->add_token(LexerType::COMMA, ",", this->line);
                    this->consume();
                    continue;
                }

                if (this->get_current() == '.') {
                    this->add_token(LexerType::DOT, ".", this->line);
                    this->consume();
                    continue;
                }

                if (this->get_current() == '=') {
                    this->add_token(LexerType::ASSIGN, "=", this->line);
                    this->consume();
                    continue;
                }

                // tokenize strings
                if (this->get_current() == '\'' || this->get_current() == '\"') {
                    std::string captured_string;
                    this->consume();
                    while ((this->get_current() != '\'' && this->get_current() != '\'') && this->input.size() > 0) {
                        captured_string += this->get_current();
                        this->consume();
                    }
                    this->add_token(LexerType::STRING, captured_string, line);
                    if (this->input.size() > 0 && (this->get_current() != '\'' && this->get_current() != '\"')) {
                        // might need to throw error here eventually.
                        // for no closing quotation found till EOF...
                        continue;
                    }
                    this->consume();
                }

                // tokenize integers
                if (isdigit(this->get_current())) {
                    std::string captured_integer;
                    while (isdigit(this->get_current()) && this->input.size() > 0) {
                        captured_integer += this->get_current();
                        this->consume();
                    }
                    // potential error handling
                    this->add_token(LexerType::INTEGER, captured_integer, this->line);
                    this->consume();
                };

                std::smatch boolean_match;
                if (std::regex_search(this->input, boolean_match, boolean_regex)) {
                    
                }


            }
        }
};