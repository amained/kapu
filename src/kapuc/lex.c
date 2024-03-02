#include "lex.h"
#include "lib/stb_ds.h"
#include "lib/log.h"

// Some helper macro
#ifdef AGGRESSIVE_DEBUG
#define TOK_PUSH(c, b, t) struct TOK new_tok = {c, t}; \
log_debug("tokenized %s as type %d", c, t);          \
arrput(b, new_tok);
#else
#define TOK_PUSH(c, b, t) struct TOK new_tok = {c, t}; \
arrput(b, new_tok);
#endif

#define TOK_SYMBOL(b, c, d, t) if (strcmp(c, d) == 0) \
{                                                     \
TOK_PUSH(NULL, b, t)                                     \
continue;                                             \
}

#define TOK_MULTICHAR_SYMBOL(b2, t1, t2) if ((c = fgetc(stream)) == b2) \
{                                                                              \
TOK_PUSH(NULL, pToks, t2)                                               \
} else {                                                                       \
fseek(stream, -1L, SEEK_CUR);                                                  \
TOK_PUSH(NULL, pToks, t1)                                                        \
}                                                                       \
break;

/// lex tokens from file stream
/// NOTE: Free the tokens yourself idiot
/// NOTE: Close the stream/file yourself too
struct TOK *lex(FILE *stream) {
    struct TOK *pToks = NULL;
    int c;
    while ((c = fgetc(stream)) != EOF) {
        if (c >= 97 && c <= 122) {
            sds word = sdsnew((const char *) &c);
            while ((c = fgetc(stream)) != EOF && c >= 97 && c <= 122) {
                word = sdscatlen(word, &c, 1);
            }
            if (c == EOF) {
                break;
            }
            fseek(stream, -1L, SEEK_CUR);
            TOK_SYMBOL(pToks, word, "func", FUNC)
            TOK_SYMBOL(pToks, word, "return", RETURN)
            TOK_SYMBOL(pToks, word, "if", IF)
            TOK_SYMBOL(pToks, word, "elif", ELIF)
            TOK_SYMBOL(pToks, word, "else", ELSE)
            TOK_SYMBOL(pToks, word, "let", LET)
            TOK_SYMBOL(pToks, word, "const", CONST)
            TOK_PUSH(word, pToks, IDENT)
        } else if (c == ' ' || c == '\n' || c == '\t') continue;
        else if (c == '#') {
            while ((c = fgetc(stream)) != EOF && c != '\n');
        } else if (c >= 48 && c <= 57) {
            sds word = sdsnew((const char *) &c);
            while ((c = fgetc(stream)) != EOF && c >= 48 && c <= 57) {
                word = sdscatlen(word, &c, 1);
            }
            if (c == EOF) {
                TOK_PUSH(word, pToks, NUM)
                break;
            }
            fseek(stream, -1L, SEEK_CUR);
            TOK_PUSH(word, pToks, NUM)
        } else {
            switch (c) {
                case '(': {
                    TOK_PUSH(NULL, pToks, LPAREN)
                    break;
                }
                case ')': {
                    TOK_PUSH(NULL, pToks, RPAREN)
                    break;
                }
                case '{': {
                    TOK_PUSH(NULL, pToks, LBRACE)
                    break;
                }
                case '}': {
                    TOK_PUSH(NULL, pToks, RBRACE)
                    break;
                }
                case ';': {
                    TOK_PUSH(NULL, pToks, SEMICOLON)
                    break;
                }
                case ':': {
                    TOK_PUSH(NULL, pToks, COLON)
                    break;
                }
                case '"': {
                    sds word = sdsempty();
                    while ((c = fgetc(stream)) != EOF && c != '"') {
                        word = sdscatlen(word, &c, 1);
                    }
                    if (c == EOF) {
                        TOK_PUSH(word, pToks, STRING)
                        break;
                    }
                    TOK_PUSH(word, pToks, STRING)
                    break;
                }
                case '@': {
                    sds word = sdsempty();
                    while ((c = fgetc(stream)) != EOF && c >= 97 && c <= 122) {
                        word = sdscatlen(word, &c, 1);
                    }
                    if (c == EOF) {
                        break;
                    }
                    fseek(stream, -1L, SEEK_CUR);
                    TOK_PUSH(word, pToks, COFFEE)
                    break;
                }
                case '=': {
                    TOK_MULTICHAR_SYMBOL('=', EQ, COMP_EQ)
                }
                case '<': {
                    TOK_MULTICHAR_SYMBOL('=', COMP_LT, COMP_LEQ)
                }
                case '>': {
                    TOK_MULTICHAR_SYMBOL('=', COMP_MT, COMP_MEQ)
                }
                case '!': {
                    TOK_MULTICHAR_SYMBOL('=', EXCLAM, COMP_NEQ)
                }
                default: {
                    log_error("Expected symbol, got \"%c\" at %d", c, ftell(stream));
                    break;
                }
            }
        }
    }
    return pToks;
}