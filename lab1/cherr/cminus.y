%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

ast_node* root = NULL;


void yyerror(const char *s);

%}

%union {
    int number;
    float floating;  // 添加float类型
    char* string;
    struct ast_node* node;
}

%token <number> NUM
%token <floating> FLOAT_NUM  // 添加float数字token
%token <string> ID
%token ELSE IF INT FLOAT RETURN VOID WHILE
%token PLUS MINUS TIMES DIVIDE
%token LT LTE GT GTE EQ NEQ
%token ASSIGN SEMI COMMA
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE

%type <node> program declaration_list declaration var_declaration fun_declaration 
%type <node> params param_list param compound_stmt local_declarations statement_list 
%type <node> statement expression_stmt selection_stmt iteration_stmt return_stmt 
%type <node> expression var simple_expression additive_expression term factor call 
%type <node> args arg_list
%type <string> type_specifier relop addop mulop

/* 在声明部分添加以下内容 */
// 在声明部分添加或修改以下内容
%left COMMA
%right ASSIGN
%left EQ NEQ
%left LT LTE GT GTE
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc ELSE
%nonassoc THEN

/* 在文件顶部的声明中添加 */

%%

program
    : declaration_list { 
        $$ = $1; 
        root = $$;  // 将解析完成的AST赋值给root
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
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2));
    }
    | type_specifier ID ASSIGN expression SEMI {
        $$ = create_node("init_declaration", 3,
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2),
            $4);
    }
    | type_specifier ID LBRACKET NUM RBRACKET SEMI {
        $$ = create_node("array_declaration", 3,
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2),
            create_int_leaf("SIZE", $4));
    }
    ;

type_specifier
    : INT { $$ = "int"; }
    | FLOAT { $$ = "float"; }  // 添加float类型支持
    | VOID { $$ = "void"; }
    ;

fun_declaration
    : type_specifier ID LPAREN RPAREN compound_stmt {
        $$ = create_node("fun_declaration", 4, 
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2),
            create_str_leaf("params", "void"),
            $5);
    }
    | type_specifier ID LPAREN params RPAREN compound_stmt {
        $$ = create_node("fun_declaration", 4, 
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2),
            $4, $6);
    }
    ;

params
    : param_list { $$ = $1; }
    | VOID { $$ = create_str_leaf("void_params", "void"); }
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
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2));
    }
    | type_specifier ID LBRACKET RBRACKET {
        $$ = create_node("param_array", 2, 
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2));
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
    : IF LPAREN expression RPAREN statement SEMI ELSE statement SEMI {
        $$ = create_node("if_else_stmt", 3, $3, $5, $8);
    }
    | IF LPAREN expression RPAREN statement SEMI {
        $$ = create_node("if_stmt", 2, $3, $5);
    }
    ;


iteration_stmt
    : WHILE LPAREN expression RPAREN statement {
        $$ = create_node("while_stmt", 2, $3, $5);
    }
    ;

return_stmt
    : RETURN SEMI { $$ = create_str_leaf("return", "return"); }
    | RETURN expression SEMI { $$ = create_node("return_expr", 1, $2); }
    ;

expression
    : var ASSIGN expression {
        $$ = create_node("assign", 2, $1, $3);
    }
    | simple_expression { $$ = $1; }
    ;

/* 数组访问 */
var
    : ID { 
        $$ = create_str_leaf("var", $1); 
    }
    | ID LBRACKET expression RBRACKET { 
        $$ = create_node("array_access", 2, create_str_leaf("ID", $1), $3); 
    }
    | ID LBRACKET expression COMMA expression RBRACKET {
        fprintf(stderr, "Error type B at Line %d: Missing \"]\".\n", yylineno);
        YYERROR;
    }
    ;

simple_expression
    : additive_expression relop additive_expression {
        $$ = create_node("rel_expr", 3, $1, create_str_leaf("relop", $2), $3);
    }
    | additive_expression { $$ = $1; }
    ;

relop
    : LTE { $$ = "<="; }
    | LT { $$ = "<"; }
    | GT { $$ = ">"; }
    | GTE { $$ = ">="; }
    | EQ { $$ = "=="; }
    | NEQ { $$ = "!="; }
    ;

additive_expression
    : additive_expression addop term {
        $$ = create_node("add_expr", 3, $1, create_str_leaf("addop", $2), $3);
    }
    | term { $$ = $1; }
    ;

addop
    : PLUS { $$ = "+"; }
    | MINUS { $$ = "-"; }
    ;

term
    : term mulop factor {
        $$ = create_node("mul_expr", 3, $1, create_str_leaf("mulop", $2), $3);
    }
    | factor { $$ = $1; }
    ;

mulop
    : TIMES { $$ = "*"; }
    | DIVIDE { $$ = "/"; }
    ;

factor
    : LPAREN expression RPAREN { $$ = $2; }
    | var { $$ = $1; }
    | call { $$ = $1; }
    | NUM { $$ = create_int_leaf("NUM", $1); }
    ;

call
    : ID LPAREN args RPAREN {
        $$ = create_node("call", 2, 
            create_str_leaf("ID", $1), $3);
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



/* 在适当的位置添加错误恢复规则 */
statement
    : expression_stmt
    | compound_stmt
    | selection_stmt
    | iteration_stmt
    | return_stmt
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error type B at line %d: %s near '%s'\n", yylineno, s, yytext);
}
