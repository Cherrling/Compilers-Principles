%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
extern FILE* yyin;

ast_node* root = NULL;
int Err = 0;


void yyerror(const char *s);




%}

%union {
    int int_number;
    float float_number;  // 添加float类型
    char* string;
    struct ast_node* node;
}

%token <int_number> INT 
%token <float_number> FLOAT  // 添加float数字token
%token <string> ID
%token <string> TYPE
%token ELSE IF RETURN VOID WHILE STRUCT
%token PLUS MINUS TIMES DIVIDE
%token LT LTE GT GTE EQ NEQ
%token ASSIGN SEMI COMMA
%token LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
%token OR AND DOT NOT 


%type <node> program declaration_list declaration var_declaration fun_declaration 
%type <node> params param_list param compound_stmt local_declarations statement_list 
%type <node> statement expression_stmt selection_stmt iteration_stmt return_stmt 
%type <node> expression var simple_expression additive_expression term factor call 
%type <node> args arg_list
%type <string> type_specifier relop addop mulop

%type <node> struct_member struct_member_list  StructSpecifier
%type <node> Specifier VarDec Exp DefList Def DecList Dec OptTag Tag
%type <node> array_access


%left LBRACKET RBRACKET
%left LBRACE RBRACE
%left LPAREN RPAREN
%left OR 
%left AND 
%left COMMA
%right ASSIGN
%left EQ NEQ
%left LT LTE GT GTE
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc ELSE
%nonassoc THEN

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
    | STRUCT ID ID SEMI {
        $$ = create_node("struct_var_declaration", 3,
            create_str_leaf("STRUCT", "struct"),
            create_str_leaf("TYPE_ID", $2),
            create_str_leaf("ID", $3));
    }
    | type_specifier ID ASSIGN expression SEMI {
        $$ = create_node("init_declaration", 3,
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2),
            $4);
    }
    | type_specifier ID LBRACKET INT RBRACKET SEMI {
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
    | STRUCT ID {
        char* type_name = (char*)malloc(strlen($2) + 8);
        sprintf(type_name, "struct %s", $2);
        $$ = type_name;
    }
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

struct_member
    : type_specifier ID SEMI {
        $$ = create_node("struct_member", 2,
            create_str_leaf("type_specifier", $1),
            create_str_leaf("ID", $2));
    }
    ;
struct_member_list
    : struct_member {
        $$ = create_node("struct_member_list", 1, $1);
    }
    | struct_member_list struct_member {
        $$ = create_node("struct_member_list", 2, $1, $2);
    }
    ;
StructSpecifier
    : STRUCT ID LBRACE struct_member_list RBRACE {
        $$ = create_node("struct_definition", 3,
            create_str_leaf("STRUCT", "struct"),
            create_str_leaf("ID", $2),
            $4);
    }
    | STRUCT ID LBRACE error RBRACE {
        Err = 1;
        if (lastErrLineno != yylineno)
            printError('B', "Invalid struct definition");
    }
    ;


OptTag
    : /* empty */ {
        $$ = NULL;
    }
    | ID {
        $$ = create_str_leaf("ID", $1);
    }
    ;

Tag
    : ID {
        $$ = create_str_leaf("ID", $1);
    }
    ;

Specifier
    : TYPE { 
        $$ = create_str_leaf("TYPE", $1);
    }
    | StructSpecifier { 
        $$ = $1;
    }
    ;

// 修改数组访问相关的规则
VarDec
    : ID { 
        $$ = create_str_leaf("ID", $1);
    }
    | VarDec LBRACKET INT RBRACKET {
        $$ = create_node("array_decl", 2, 
            $1, 
            create_int_leaf("size", $3));
    }
    | VarDec LBRACKET error RBRACKET {
        Err = 1;
        if (lastErrLineno != yylineno)
            printError('B', "Invalid array size");
    }
    ;




Def
    : Specifier DecList SEMI {
        $$ = create_node("def", 3, $1, $2, create_str_leaf("SEMI", ";"));
    }
    | Specifier error SEMI {
        Err = 1;
        if (lastErrLineno != yylineno)
            printError('B', "Invalid variable definition");
    }
    ;
Dec
    : VarDec {
        $$ = $1;
    }
    | VarDec ASSIGN Exp {
        $$ = create_node("init_dec", 3, $1, 
            create_str_leaf("ASSIGN", "="), $3);
    }
    ;
DefList
    : /* empty */ { 
        $$ = NULL;
    }
    | Def DefList {
        if ($2 == NULL) {
            $$ = create_node("DefList", 1, $1);
        } else {
            $$ = create_node("DefList", 2, $1, $2);
        }
    }
    ;
DecList
    : Dec {
        $$ = create_node("declist", 1, $1);
    }
    | Dec COMMA DecList {
        $$ = create_node("declist", 3, $1, 
            create_str_leaf("COMMA", ","), $3);
    }
    ;


Exp
    : ID { 
        $$ = create_str_leaf("ID", $1);
    }
    | Exp DOT ID {
        $$ = create_node("struct_access", 3,
            $1,
            create_str_leaf("DOT", "."),
            create_str_leaf("ID", $3));
    }
    | INT { 
        $$ = create_int_leaf("INT", $1);
    }
    | FLOAT {
        $$ = create_float_leaf("FLOAT", $1);
    }
    | Exp PLUS Exp {
        $$ = create_node("add", 2, $1, $3);
    }
    | Exp MINUS Exp {
        $$ = create_node("sub", 2, $1, $3);
    }
    | Exp TIMES Exp {
        $$ = create_node("mul", 2, $1, $3);
    }
    | Exp DIVIDE Exp {
        $$ = create_node("div", 2, $1, $3);
    }
    | LPAREN Exp RPAREN {
        $$ = $2;
    }
    | Exp LBRACKET Exp error RBRACKET {
        printError('B', "Missing \"]\"");
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
    | INT { $$ = create_int_leaf("INT", $1); }
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

