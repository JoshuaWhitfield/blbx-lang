#pragma once
#include <string_view>
#include "../types/lexer_type.h"

class LexerToken {
    private:
        LexerType type;
        std::string_view value;
        int line;

    public:
        LexerToken(
            LexerType _type,
            std::string_view _value,
            int _line
        ) {
            type = _type;
            value = _value;
            line = _line;
        }

        LexerType get_type() {
            return this->type;
        }

        std::string_view get_value() {
            return this->value;
        }
};