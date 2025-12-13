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
        if (this->input.empty()) {
            return '\0';
        }
        return this->input.front();
    }
};