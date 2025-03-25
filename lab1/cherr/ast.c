#include "ast.h"
#include <stdarg.h>
#include <stdio.h>

ast_node* create_node(const char* type, int child_count, ...) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = strdup(type);
    node->val.str_value = NULL;
    node->val.int_value = 0;
    node->val.float_value = 0;
    node->child_count = child_count;
    node->children = (ast_node**)malloc(sizeof(ast_node*) * child_count);
    
    va_list args;
    va_start(args, child_count);
    for (int i = 0; i < child_count; i++) {
        node->children[i] = va_arg(args, ast_node*);
    }
    va_end(args);
    
    return node;
}

ast_node* create_str_leaf(const char* type, const char* value) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = strdup(type);
    node->val.str_value = value ? strdup(value) : NULL;
    node->val.int_value = 0;
    node->val.float_value = 0;
    node->child_count = 0;
    node->children = NULL;
    return node;
}

ast_node* create_int_leaf(const char* type, int value) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = strdup(type);
    node->val.str_value = NULL;
    node->val.int_value = value;
    node->val.float_value = 0;
    node->child_count = 0;
    node->children = NULL;
    return node;
}
ast_node* create_float_leaf(const char* type, float value) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = strdup(type);
    node->val.str_value = NULL;
    node->val.int_value = 0;
    node->val.float_value = value;
    node->child_count = 0;
    node->children = NULL;
    return node;
}


void print_ast(ast_node* node, int level) {
    if (!node) return;
    
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s", node->type);
    
    if (strcmp(node->type, "ID") == 0) {
        printf(": %d", node->val.str_value);
    } else if (strcmp(node->type, "NUM") == 0) {
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