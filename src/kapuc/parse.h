#ifndef KAPUC_PARSE_H
#define KAPUC_PARSE_H

// AST has value, left, right
// NOTE: value is string, left and right are AST
// NOTE: check for null you dum head

enum ASTType {
    // statements
    AST_FUNC, // func -> (value: ident, left: params, right: block)
    // NOTE: param is just linked list but worse because tree gaming
    AST_PARAMS, // params -> (value: ident, left: params | null)
    AST_RETURN, // return -> (value: expr)
    AST_IF_STMT, // if_stmt -> (value: expr, left: block, right: block | null)
    AST_BLOCK,
    // expression
    AST_EXPR,
    AST_NUM,
    AST_IDENT,
    // operation
    AST_UNARY, // unary -> (op: token, value: expr)
    AST_BINARY // binary -> (op: token, left: expr, right: expr)
};

struct AST {
    char *value;
    struct AST *left;
    struct AST *right;
    enum ASTType node_type;
};

#endif //KAPUC_PARSE_H
