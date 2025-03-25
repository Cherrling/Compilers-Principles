#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ast_node {
    char* type;
    union {
        char* str_value;
        int int_value;
        float float_value;  // 添加float值支持
    } val;
    int child_count;
    struct ast_node** children;
} ast_node;

// 添加创建float叶节点的函数声明

ast_node* create_node(const char* type, int child_count, ...);
ast_node* create_float_leaf(const char* type, float value);
ast_node* create_str_leaf(const char* type, const char* value);
ast_node* create_int_leaf(const char* type, int value);
void print_ast(ast_node* node, int level);
void free_ast(ast_node* node);

#endif
