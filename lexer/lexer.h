#pragma once 

#include <string_view>
#include <vector>
#include "./types/lexer_type.h"
#include "./tokens/lexer_token.h"

class Lexer {
    private:
        std::string_view input;
        std::vector<LexerToken> output;

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
};