#pragma once
#include <string>
#include "../types/lexer_type.h"

class LexerToken {
    private:
        LexerType type;
        std::string value;
        int line;

    public:
        LexerToken(
            LexerType _type,
            std::string _value,
            int _line
        ) {
            type = _type;
            value = _value;
            line = _line;
        }

        LexerType get_type() {
            return this->type;
        }

        std::string get_value() {
            return this->value;
        }
};