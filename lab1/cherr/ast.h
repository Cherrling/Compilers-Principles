#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ast_node {
    char* type;
    char* value;
    struct ast_node** children;
    int child_count;
} ast_node;

ast_node* create_node(const char* type, int child_count, ...);
ast_node* create_leaf(const char* type, const char* value);
void print_ast(ast_node* node, int level);
void free_ast(ast_node* node);

#endif