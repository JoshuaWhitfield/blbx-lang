#pragma once 

#include <string_view>
#include <vector>
#include <regex>
#include "./types/lexer_type.h"
#include "./tokens/lexer_token.h"

class Lexer {
    private:
        std::string_view input;
        std::vector<LexerToken> output;
        int pos = 0;
        int line = 0;

        // operator regex
        std::regex math_operator_regex;
        std::regex logical_operator_regex;
        std::regex comparison_operator_regex;

    public: 
        Lexer(
            std::string_view _input
        ) : input(_input), 
            math_operator_regex(R"((mult|sum|sub|div|mod|exp|incr|decr)\()"),
            logical_operator_regex(R"((and|or|not)\()"),
            comparison_operator_regex(R"((eq|neq|gt|lt|gteq|lteq)\()")
         {}

        char get_current() {
            return this->input.empty() ? '\0' : this->input.front();
        }

        void add_token(LexerType _type, std::string_view _value, int _line) {
            this->output.push_back(LexerToken(_type, _value, _line));
        }

        char consume() {
            char current = this->get_current();
            this->input.remove_prefix(this->pos + 1);
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

                // operators

            }
        }
};