#include "ast.h"
#include <stdarg.h>

ast_node* create_node(const char* type, int child_count, ...) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = strdup(type);
    node->value = NULL;
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

ast_node* create_leaf(const char* type, const char* value) {
    ast_node* node = (ast_node*)malloc(sizeof(ast_node));
    node->type = strdup(type);
    node->value = value ? strdup(value) : NULL;
    node->child_count = 0;
    node->children = NULL;
    return node;
}

void print_ast(ast_node* node, int level) {
    if (!node) return;
    
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s", node->type);
    if (node->value) printf(": %s", node->value);
    printf("\n");
    
    for (int i = 0; i < node->child_count; i++) {
        print_ast(node->children[i], level + 1);
    }
}

void free_ast(ast_node* node) {
    if (!node) return;
    
    free(node->type);
    if (node->value) free(node->value);
    
    for (int i = 0; i < node->child_count; i++) {
        free_ast(node->children[i]);
    }
    
    if (node->children) free(node->children);
    free(node);
}