#include "utils.h"
#include <stdarg.h>
#include <stdio.h>

extern int Err;    
extern int yylineno;      // 当前行号
extern char* yytext;        // 当前文本


ast_node* create_node(const char* type, struct ast_node* child, int line, ...) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = strdup(type);
    node->val.str_value = NULL;
    node->val.int_value = 0;
    node->val.float_value = 0;
    node->linenumber = line;
    node->child = child;
    node->brother = NULL;
    
    return node;
}



void print_ast(ast_node* node, int level) {
    if (!node) return;
    
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s", node->type);
    
    if (strcmp(node->type, "ID") == 0) {
        printf(": %d", node->val.str_value);
    } else if (strcmp(node->type, "INT") == 0) {
        printf(": %d", node->val.int_value);
    } else if (strcmp(node->type, "FLOAT") == 0) {
        printf(": %.6f", node->val.float_value);  // 使用6位小数精度
    }


    printf("\n");
    for (int i = 0; i < node->child_count; i++) {
        if (node->children[i] == NULL) {
            printf("NULL\n");
        } else {
        print_ast(node->children[i], level + 1);
        }
    }
}

void free_ast(ast_node* node) {
    if (!node) return;
    
    free(node->type);
    if (node->val.str_value) {
        free(node->val.str_value);
    }
    
    for (int i = 0; i < node->child_count; i++) {
        free_ast(node->children[i]);
    }
    
    if (node->children) {
        free(node->children);
    }
    free(node);
}


void yyerror(const char *s) {
    fprintf(stderr, "Error type B at line %d: %s near '%s'\n", yylineno, s, yytext);
}

// 打印错误信息
void printError(char errorType, char* msg) {
    // 打印错误类型和错误消息以及行号
    Err = 1;
    fprintf(stderr, "Error type %c at Line %d: %s.\n", errorType, yylineno, msg);
}