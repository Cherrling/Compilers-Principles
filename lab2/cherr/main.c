#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "semantic.h"

extern int yyparse();
extern ast_node* root;
extern FILE* yyin;
extern int Err;    
extern int yylineno;      // 当前行号
extern void yyrestart(FILE *input_file);               // 重置词法分析器的输入文件




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

    yylineno = 1;
    yyrestart(yyin);

    yyparse();

    if (Err) {
        return 1;
    }


    if (root != NULL) {
        // printf("\nAbstract Syntax Tree:\n");
        print_ast(root, 0);
        initHashtable();
        Program(root);
        check_declar();
    }

    fclose(yyin);
    return 0;
}