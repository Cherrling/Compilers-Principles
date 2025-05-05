# include <stdio.h>
# include <stdlib.h>
# include "semantic.h"
# include "interim.h"

extern FILE* yyin;
extern int yylineno;
extern int Err;
extern TABLE table[16385];

extern struct Node* head;
extern int yylex();
extern int yyparse (void);
extern void yyrestart (FILE *input_file);

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
    if (Err == 0) {

        printf("\n=====================\n\n");
        printf("File: %s\n\n", argv[1]);
        Program(head);
        translate2ir(head);
    }
    return 0;
}