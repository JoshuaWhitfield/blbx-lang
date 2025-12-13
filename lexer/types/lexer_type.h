#pragma once 

enum class LexerType {
    // punctuation
    COMMA,
    DOT,
    SEMICOLON,
    COLON,
    ASSIGN,

    // symbols
    OPEN_ARRAY,
    CLOSE_ARRAY,
    OPEN_OBJECT,
    CLOSE_OBJECT,
    OPEN_PAREN,
    CLOSE_PAREN,

    // keywords 

    // operators
    OPERATOR,

    // control-flow
    DECLARATIVE,

    // literals
    STRING,
    INTEGER,

    // functions
    FUNC_DECL,
    FUNC_CALL,
    ANON_DECL,
};