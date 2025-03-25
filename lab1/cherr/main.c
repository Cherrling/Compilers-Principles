#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

extern int yyparse();
extern ast_node* root;
extern FILE* yyin;

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Failed to open input file");
        return 1;
    }

    if (yyparse() == 0) {
        printf("Abstract Syntax Tree:\n");
        print_ast(root, 0);
    }

    free_ast(root);
    fclose(yyin);
    return 0;
}