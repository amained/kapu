#include "lib/sds.h"
#include <stdio.h>

#ifndef KAPUC_LEX_H
#define KAPUC_LEX_H

enum TOK_TYPE {
    FUNC,
    IF,
    ELSE,
    ELIF,
    LET,
    CONST,
    IDENT,
    COFFEE,
    STRING,
    NUM,
    RETURN,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    COLON,
    SEMICOLON,
    EXCLAM,
    EQ,
    COMP_EQ,
    COMP_NEQ,
    COMP_LEQ,
    COMP_MEQ,
    COMP_MT,
    COMP_LT
};

struct TOK {
    sds s;
    enum TOK_TYPE t;
};

struct TOK *lex(FILE *stream);

#endif //KAPUC_LEX_H
