#include "utils.h"
#include <stdarg.h>
#include <stdio.h>

extern int Err;    
extern int yylineno;      // 当前行号
extern char* yytext;        // 当前文本
extern ast_node* root;


ast_node* create_node(const char* type, int child_count, int line, ...) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    if (!node) {
        fprintf(stderr, "内存分配失败\n");
        exit(1);
    }
    node->type = type ? strdup(type) : NULL;
    node->val.str_value = NULL;
    node->val.int_value = 0;
    node->val.float_value = 0.0;
    node->linenumber = line;
    node->child_count = child_count;

    if (child_count > 0) {
        node->children = (ast_node**)malloc(sizeof(ast_node*) * child_count);
        if (!node->children) {
            fprintf(stderr, "内存分配失败\n");
            free(node);
            exit(1);
        }
        
        va_list args;
        va_start(args, line);  // 使用最后一个固定参数 line
        for (int i = 0; i < child_count; i++) {
            node->children[i] = va_arg(args, ast_node*);
        }
        va_end(args);
    } else {
        node->children = NULL;
    }
    root = node;
    return node;
}


static int node_count = 0; // 用于节点编号

void print_ast(ast_node* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");
    if (node->type) {
        printf("%s", node->type);
        
        // 对于需要打印行号的节点类型
        if (strcmp(node->type, "FunDec") == 0 || 
            strcmp(node->type, "CompSt") == 0 ||
            strcmp(node->type, "DefList") == 0 ||
            strcmp(node->type, "Def") == 0 ||
            strcmp(node->type, "Specifier") == 0 ||
            strcmp(node->type, "DecList") == 0 ||
            strcmp(node->type, "Dec") == 0 ||
            strcmp(node->type, "VarDec") == 0 ||
            strcmp(node->type, "StmtList") == 0 ||
            strcmp(node->type, "StructSpecifier") == 0 ||
            strcmp(node->type, "Stmt") == 0 ||
            strcmp(node->type, "Program") == 0 ||
            strcmp(node->type, "ExtDefList") == 0 ||
            strcmp(node->type, "ExtDef") == 0 ||
            strcmp(node->type, "Exp") == 0) {
            printf(" (%d)", node->linenumber);
        }
        
        // 打印节点的值
        if (node->val.str_value) {    
            if (strcmp(node->type, "ID") == 0) {
                printf(": %s", node->val.str_value);
            } else if (strcmp(node->type, "TYPE") == 0) {
                printf(": %s", node->val.str_value);
            }
        }
        if (strcmp(node->type, "INT") == 0) {
            printf(": %d", node->val.int_value);
        } else if (strcmp(node->type, "FLOAT") == 0) {
            printf(": %f", node->val.float_value);
        } else if (strcmp(node->type, "ASSIGN") == 0) {
            printf("OP");  // 打印ASSIGNOP
        } else if (strcmp(node->type, "PLUS") == 0) {
            printf(": +");
        } else if (strcmp(node->type, "LP") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->type, "RP") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->type, "LC") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->type, "RC") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->type, "SEMI") == 0) {
            printf("");  // 只打印节点名
        }
    }
    printf("\n");

    // 递归打印子节点
    if (node->children) {
        for (int i = 0; i < node->child_count; i++) {
            print_ast(node->children[i], level + 1);
        }
    }
}

// 在打印AST之前需要重置节点计数
void reset_node_count() {
    node_count = 0;
}


void yyerror(const char *s) {
    // 不做任何输出，由我们自己的 printError 处理
}

// 打印错误信息
void printError(char errorType, char* msg) {
    // 打印错误类型和错误消息以及行号
    Err = 1;
    fprintf(stderr, "Error type %c at Line %d: %s.\n", errorType, yylineno, msg);
}