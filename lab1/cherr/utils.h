#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;      // 当前行号
extern char* yytext;        // 当前文本


typedef struct ast_node {
    char* type;
    union {
        char* str_value;
        int int_value;
        float float_value;  // 添加float值支持
    } val;
    int linenumber;
    struct ast_node* child; // 指向子节点的指针
    struct ast_node* brother; // 指向兄弟节点的指针
} ast_node;

// 添加创建float叶节点的函数声明

void yyerror(const char *s);

// 打印错误信息
void printError(char errorType, char* msg);


ast_node* create_node(const char* type, int child_count, ...);
ast_node* create_float_leaf(const char* type, float value);
ast_node* create_str_leaf(const char* type, const char* value);
ast_node* create_int_leaf(const char* type, int value);
void print_ast(ast_node* node, int level);
void free_ast(ast_node* node);

#endif
