%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

void yyerror(const char *s);

%}

%union {
    int number;
    char* string;
    struct ast_node* node;
}

%token <number> NUM
%token <string> ID
%token ELSE IF INT RETURN VOID WHILE
%token PLUS MINUS TIMES DIVIDE
%token LT LTE GT GTE EQ NEQ
%token ASSIGN SEMI COMMA
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE

%type <node> program declaration_list declaration var_declaration fun_declaration 
%type <node> params param_list param compound_stmt local_declarations statement_list 
%type <node> statement expression_stmt selection_stmt iteration_stmt return_stmt 
%type <node> expression var simple_expression additive_expression term factor call 
%type <node> args arg_list

%%

program
    : declaration_list { 
        $$ = $1; 
        printf("Parsing completed successfully.\n");
    }
    ;

declaration_list
    : declaration_list declaration { 
        $$ = create_node("declaration_list", 2, $1, $2); 
    }
    | declaration { 
        $$ = create_node("declaration_list", 1, $1); 
    }
    ;

declaration
    : var_declaration { $$ = $1; }
    | fun_declaration { $$ = $1; }
    ;

var_declaration
    : type_specifier ID SEMI {
        $$ = create_node("var_declaration", 2, 
            create_leaf("type_specifier", $1),
            create_leaf("ID", $2));
    }
    | type_specifier ID LBRACKET NUM RBRACKET SEMI {
        $$ = create_node("var_declaration_array", 3, 
            create_leaf("type_specifier", $1),
            create_leaf("ID", $2),
            create_leaf("NUM", $4));
    }
    ;

type_specifier
    : INT { $$ = "int"; }
    | VOID { $$ = "void"; }
    ;

fun_declaration
    : type_specifier ID LPAREN params RPAREN compound_stmt {
        $$ = create_node("fun_declaration", 4, 
            create_leaf("type_specifier", $1),
            create_leaf("ID", $2),
            $4, $6);
    }
    ;

params
    : param_list { $$ = $1; }
    | VOID { $$ = create_leaf("void_params", "void"); }
    ;

param_list
    : param_list COMMA param {
        $$ = create_node("param_list", 2, $1, $3);
    }
    | param { $$ = create_node("param_list", 1, $1); }
    ;

param
    : type_specifier ID {
        $$ = create_node("param", 2, 
            create_leaf("type_specifier", $1),
            create_leaf("ID", $2));
    }
    | type_specifier ID LBRACKET RBRACKET {
        $$ = create_node("param_array", 2, 
            create_leaf("type_specifier", $1),
            create_leaf("ID", $2));
    }
    ;

compound_stmt
    : LBRACE local_declarations statement_list RBRACE {
        $$ = create_node("compound_stmt", 2, $2, $3);
    }
    ;

local_declarations
    : local_declarations var_declaration {
        $$ = create_node("local_declarations", 2, $1, $2);
    }
    | /* empty */ { $$ = NULL; }
    ;

statement_list
    : statement_list statement {
        $$ = create_node("statement_list", 2, $1, $2);
    }
    | /* empty */ { $$ = NULL; }
    ;

statement
    : expression_stmt { $$ = $1; }
    | compound_stmt { $$ = $1; }
    | selection_stmt { $$ = $1; }
    | iteration_stmt { $$ = $1; }
    | return_stmt { $$ = $1; }
    ;

expression_stmt
    : expression SEMI { $$ = $1; }
    | SEMI { $$ = NULL; }
    ;

selection_stmt
    : IF LPAREN expression RPAREN statement {
        $$ = create_node("if_stmt", 2, $3, $5);
    }
    | IF LPAREN expression RPAREN statement ELSE statement {
        $$ = create_node("if_else_stmt", 3, $3, $5, $7);
    }
    ;

iteration_stmt
    : WHILE LPAREN expression RPAREN statement {
        $$ = create_node("while_stmt", 2, $3, $5);
    }
    ;

return_stmt
    : RETURN SEMI { $$ = create_leaf("return", "return"); }
    | RETURN expression SEMI { $$ = create_node("return_expr", 1, $2); }
    ;

expression
    : var ASSIGN expression {
        $$ = create_node("assign", 2, $1, $3);
    }
    | simple_expression { $$ = $1; }
    ;

var
    : ID { $$ = create_leaf("var", $1); }
    | ID LBRACKET expression RBRACKET {
        $$ = create_node("array_access", 2, 
            create_leaf("ID", $1), $3);
    }
    ;

simple_expression
    : additive_expression relop additive_expression {
        $$ = create_node("rel_expr", 3, $1, $2, $3);
    }
    | additive_expression { $$ = $1; }
    ;

relop
    : LTE { $$ = create_leaf("relop", "<="); }
    | LT { $$ = create_leaf("relop", "<"); }
    | GT { $$ = create_leaf("relop", ">"); }
    | GTE { $$ = create_leaf("relop", ">="); }
    | EQ { $$ = create_leaf("relop", "=="); }
    | NEQ { $$ = create_leaf("relop", "!="); }
    ;

additive_expression
    : additive_expression addop term {
        $$ = create_node("add_expr", 3, $1, $2, $3);
    }
    | term { $$ = $1; }
    ;

addop
    : PLUS { $$ = create_leaf("addop", "+"); }
    | MINUS { $$ = create_leaf("addop", "-"); }
    ;

term
    : term mulop factor {
        $$ = create_node("mul_expr", 3, $1, $2, $3);
    }
    | factor { $$ = $1; }
    ;

mulop
    : TIMES { $$ = create_leaf("mulop", "*"); }
    | DIVIDE { $$ = create_leaf("mulop", "/"); }
    ;

factor
    : LPAREN expression RPAREN { $$ = $2; }
    | var { $$ = $1; }
    | call { $$ = $1; }
    | NUM { $$ = create_leaf("NUM", $1); }
    ;

call
    : ID LPAREN args RPAREN {
        $$ = create_node("call", 2, 
            create_leaf("ID", $1), $3);
    }
    ;

args
    : arg_list { $$ = $1; }
    | /* empty */ { $$ = NULL; }
    ;

arg_list
    : arg_list COMMA expression {
        $$ = create_node("arg_list", 2, $1, $3);
    }
    | expression { $$ = create_node("arg_list", 1, $1); }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error type B at line %d: %s near '%s'\n", yylineno, s, yytext);
}