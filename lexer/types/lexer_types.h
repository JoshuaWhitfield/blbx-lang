#pragma once 

enum class LexerTypes {
    // punctuation
    COMMA,
    DOT,
    SEMICOLON,
    EQUALS,
    // symbols
    OPEN_ARRAY,
    CLOSE_ARRAY,
    OPEN_OBJECT,
    CLOSE_OBJECT,
    OPEN_PAREN,
    CLOSE_PAREN,

    // keywords 

    // operators

    // control-flow

    // literals
    STRING,
    INTEGER,
};