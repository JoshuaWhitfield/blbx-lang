#pragma once 

enum class LexerType {
    // punctuation
    COMMA,
    DOT,
    SEMICOLON,
    COLON,
    ASSIGN,
    NEW_LINE,
    RIGHT_CAROT,

    // symbols
    OPEN_ARRAY,
    CLOSE_ARRAY,
    OPEN_OBJECT,
    CLOSE_OBJECT,
    OPEN_PAREN,
    CLOSE_PAREN,

    // var, func, method, declarative names
    NAMESPACE,

    // tokenize literals
    STRING,
    INTEGER,
    FLOAT, // add lexing later
    BOOLEAN,

    // unexpected
    UNEXPECTED

};