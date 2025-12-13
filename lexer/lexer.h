#pragma once 

#include <string_view>
#include <vector>
#include "./types/lexer_type.h"
#include "./tokens/lexer_token.h"

class Lexer {
    private:
        std::string_view input;
        std::vector<LexerToken> output;
        int pos = 0;

    public: 
        Lexer(
            std::string_view _input
        ) {
            input = _input;
        }

        char get_current() {
            return this->input.empty() ? '\0' : this->input.front();
        }

        void add_token(LexerType _type, std::string_view _value) {
            this->output.push_back(LexerToken(_type, _value));
        }

        void consume() {
            char current = this->get_current();
            this->input.remove_prefix(this->pos + 1);
        }

        void tokenize() {
            while (this->input.size() > 0 ) {
                
            }
        }
};