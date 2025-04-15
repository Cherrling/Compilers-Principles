#include "utils.h"
#include <stdarg.h>
#include <stdio.h>

extern int Err;    
extern int yylineno;      // 当前行号
extern char* yytext;        // 当前文本
extern ast_node* root;


ast_node* create_node(const char* name, int childno, int line, ...) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    if (!node) {
        fprintf(stderr, "内存分配失败\n");
        exit(1);
    }
    node->name = name ? strdup(name) : NULL;
    
    node->val.str_value = NULL;
    node->val.int_value = 0;
    node->val.float_value = 0.0;
    // 让 node->yytext 指向 node->val.str_value
    
    node->lineno = line;    
    node->childno = childno;  // 设置子节点数量
    if (childno > 0) {
        node->child = (ast_node**)malloc(sizeof(ast_node*) * childno);
        if (!node->child) {
            fprintf(stderr, "内存分配失败\n");
            free(node);
            exit(1);
        }
        
        va_list args;
        va_start(args, line);  // 使用最后一个固定参数 line
        for (int i = 0; i < childno; i++) {
            node->child[i] = va_arg(args, ast_node*);
        }
        va_end(args);
    } else {
        node->child = NULL;
    }
    root = node;
    return node;
}


static int node_count = 0; // 用于节点编号

void print_ast(ast_node* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");
    if (node->name) {
        printf("%s", node->name);
        
        // 对于需要打印行号的节点类型
        if (strcmp(node->name, "FunDec") == 0 || 
            strcmp(node->name, "CompSt") == 0 ||
            strcmp(node->name, "DefList") == 0 ||
            strcmp(node->name, "Def") == 0 ||
            strcmp(node->name, "Specifier") == 0 ||
            strcmp(node->name, "DecList") == 0 ||
            strcmp(node->name, "Dec") == 0 ||
            strcmp(node->name, "VarDec") == 0 ||
            strcmp(node->name, "StmtList") == 0 ||
            strcmp(node->name, "StructSpecifier") == 0 ||
            strcmp(node->name, "Stmt") == 0 ||
            strcmp(node->name, "Program") == 0 ||
            strcmp(node->name, "ExtDefList") == 0 ||
            strcmp(node->name, "ExtDef") == 0 ||
            strcmp(node->name, "Exp") == 0) {
            printf(" (%d)", node->lineno);
        }
        
        // 打印节点的值
        if (node->val.str_value) {    
            if (strcmp(node->name, "ID") == 0) {
                printf(": %s", node->val.str_value);
            } else if (strcmp(node->name, "TYPE") == 0) {
                printf(": %s", node->val.str_value);
            }
        }
        if (strcmp(node->name, "INT") == 0) {
            printf(": %d", node->val.int_value);
        } else if (strcmp(node->name, "FLOAT") == 0) {
            printf(": %f", node->val.float_value);
        } else if (strcmp(node->name, "ASSIGN") == 0) {
            printf("OP");  // 打印ASSIGNOP
        } else if (strcmp(node->name, "PLUS") == 0) {
            printf(": +");
        } else if (strcmp(node->name, "LP") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->name, "RP") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->name, "LC") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->name, "RC") == 0) {
            printf("");  // 只打印节点名
        } else if (strcmp(node->name, "SEMI") == 0) {
            printf("");  // 只打印节点名
        }
    }
    printf("\n");

    // 递归打印子节点
    if (node->child) {
        for (int i = 0; i < node->childno; i++) {
            if (node->child[i]) {  // 检查子节点不为 NULL
                print_ast(node->child[i], level + 1);
            }
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