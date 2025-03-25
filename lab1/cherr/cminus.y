%locations
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


%type <node> program ExtDefList ExtDef VarDec FunDec 

%type <node> StructSpecifier ExtDecList VarList ParamDec CompSt StmtList Stmt arg_list
%type <node> Specifier Exp DefList Def DecList Dec OptTag Tag


%left LBRACKET RBRACKET
%left LBRACE RBRACE
%left LPAREN RPAREN
%left OR 
%left AND 
%left COMMA
%right ASSIGN
%left EQ NEQ RELOP
%left LT LTE GT GTE
%left PLUS MINUS
%left TIMES DIVIDE
%nonassoc ELSE
%nonassoc THEN

%%

program
    : ExtDefList { 
        if ($1 == NULL) {
            $$ = create_node("Program", 0, @1.first_line);
        } else if ($1->child_count == 1) {
            $$ = create_node("Program", 1, $1->linenumber, $1);
        } else {
            $$ = create_node("Program", 1, @1.first_line, $1);
        }
        root = $$;
    }
    ;

ExtDefList
    : /* empty */ { 
        $$ = NULL;  // 空规则直接返回 NULL，不创建节点
    }
    | ExtDef ExtDefList { 
        if ($2 == NULL) {
            $$ = create_node("ExtDefList", 1, @1.first_line, $1);
        } else {
            $$ = create_node("ExtDefList", 2, @1.first_line, $1, $2); 
            $$ -> val.int_value = 2;
        }
    }
    ;

ExtDef
    : Specifier ExtDecList SEMI{
        ast_node* semi_node = create_node("SEMI", 0, @3.first_line);
        $$=create_node("ExtDef", 3, @1.first_line, $1, $2, semi_node);
    
    } 
    | Specifier SEMI{
        ast_node* semi_node = create_node("SEMI", 0, @2.first_line);
        $$=create_node("ExtDef", 2, @1.first_line, $1, semi_node);
    
    } 
    | Specifier FunDec CompSt{
        $$=create_node("ExtDef", 3, @1.first_line, $1, $2, $3);
    } 
    | Specifier error {
        printError('B', "Missing \";\""); // 打印错误消息
    }

ExtDecList
    : VarDec{
        $$=create_node("ExtDecList", 1, @1.first_line, $1);
    } 
    | VarDec COMMA ExtDecList{
        $$=create_node("ExtDecList", 2, @1.first_line, $1,  $3);

    } 
    | VarDec error ExtDecList{
        printError('B', "text"); // 打印错误消息
    }

Specifier
    : TYPE { 
        ast_node* type_node = create_node("TYPE", 0, @1.first_line);
        type_node->val.str_value = strdup($1);  // 保存类型字符串
        // 创建Specifier节点
        $$ = create_node("Specifier", 1, @1.first_line, type_node);
    }
    | StructSpecifier { 
        $$ = create_node("Specifier", 1, @1.first_line, $1); 
    }
    ;



VarDec
    : ID { 
        ast_node* id_node = create_node("ID", 0, @1.first_line);
        id_node->val.str_value = strdup($1);  // 保存变量名
        $$ = create_node("VarDec", 1, @1.first_line, id_node); 
    }
    | VarDec LBRACKET INT RBRACKET {
        ast_node* lb_node = create_node("LB", 0, @2.first_line);
        ast_node* int_node = create_node("INT", 0, @3.first_line);
        int_node->val.int_value = $3;
        ast_node* rb_node = create_node("RB", 0, @4.first_line);
        $$ = create_node("VarDec", 4, @1.first_line, $1, lb_node, int_node, rb_node); 
    }
    | VarDec LBRACKET error RBRACKET {
        char msg[32]; // 定义错误信息缓冲区
        sprintf(msg, "Syntax error, near \'%c\'", yytext[0]); // 格式化错误消息
        printError('B', msg); // 打印错误消息
    }
    ;
FunDec
    :ID LPAREN VarList RPAREN{
        ast_node* id_node = create_node("ID", 0, @1.first_line);
        id_node->val.str_value = strdup($1);  // 保存函数名
        ast_node* lp_node = create_node("LP", 0, @2.first_line);
        ast_node* rp_node = create_node("RP", 0, @4.first_line);
        $$ = create_node("FunDec", 4, @1.first_line, id_node, lp_node, $3, rp_node); 
    } 
    | ID LPAREN RPAREN{
        ast_node* id_node = create_node("ID", 0, @1.first_line);
        id_node->val.str_value = strdup($1);  // 保存函数名
        ast_node* lp_node = create_node("LP", 0, @2.first_line);
        ast_node* rp_node = create_node("RP", 0, @3.first_line);
        $$ = create_node("FunDec", 3, @1.first_line, id_node, lp_node, rp_node); 
    
    } 
    | ID LPAREN error RPAREN {
        printError('B', "Syntax error between ()"); // 打印错误消息
    }
    ;

VarList
    : ParamDec COMMA VarList {
        $$ = create_node("VarList", 2, @1.first_line, $1,  $3); 
    } 
    | ParamDec {
        $$ = create_node("VarList", 1, @1.first_line, $1); 
    }

ParamDec
    : Specifier VarDec {
        $$ = create_node("ParamDec", 2, @1.first_line, $1, $2); 
    }

CompSt
    :LBRACE DefList StmtList RBRACE{
        ast_node* lc_node = create_node("LC", 0, @1.first_line);
        ast_node* rc_node = create_node("RC", 0, @4.first_line);
        $$ = create_node("CompSt", 4, @1.first_line, lc_node, $2, $3, rc_node); 
    }
    ;

StmtList
    : {
        $$ = NULL;
    } 
    | Stmt StmtList{
        $$ = create_node("StmtList", 2, @1.first_line, $1, $2); 
    }
    ;


Stmt
    : Exp SEMI {
        ast_node* semi_node = create_node("SEMI", 0, @2.first_line);
        $$ = create_node("Stmt", 2, @1.first_line, $1, semi_node); 
    
    }
    | CompSt {
        $$ = create_node("Stmt", 1, @1.first_line, $1); 
    }
    | RETURN Exp SEMI {
        $$ = create_node("Stmt", 1, @1.first_line, $2); 
    }
    | IF LPAREN Exp RPAREN Stmt ELSE Stmt {
        $$ = create_node("Stmt", 3, @1.first_line,  $3, $5, $7); 
    }
    | WHILE LPAREN Exp RPAREN Stmt {
        $$ = create_node("Stmt", 2, @1.first_line, $3, $5); 
    }
    | Exp error {
        printError('B', "Missing \";\""); // 打印错误消息
    }

StructSpecifier
    : STRUCT OptTag LBRACE DefList RBRACE {
        $$ = create_node("StructSpecifier", 2, @1.first_line, $2, $4); 
    } 
    | STRUCT Tag {
        $$ = create_node("StructSpecifier", 1, @1.first_line, $2); 
    }
    ;


OptTag
    : /* empty */ {
        $$ = create_node("OptTag", 0, 0);
        $$ -> val.int_value = 0; 

    }
    | ID {
        $$ = create_node("OptTag", 0, @1.first_line); 

    }
    ;

Tag
    : ID {
        $$ = create_node("Tag", 0, @1.first_line); 

    }
    ;

DefList
    : /* empty */ { 
        $$ = NULL;

    }
    | Def DefList {
        $$ = create_node("DefList", 2, @1.first_line, $1, $2);
    }
    ;

Def
    : Specifier DecList SEMI {
        $$ = create_node("Def", 2, @1.first_line, $1, $2); 

    }
    | Specifier error SEMI {
        char msg[32]; // 定义错误信息缓冲区
        sprintf(msg, "Syntax error, near \'%c\'", yytext[0]); // 格式化错误消息
        printError('B', msg); // 打印错误消息
    }
    | Specifier DecList error {
        printError('B',"Missing \";\""); // 打印错误消息
    }
    ;


DecList
    : Dec {
        $$ = create_node("DecList", 1, @1.first_line, $1); 
    }
    | Dec COMMA DecList {
        $$ = create_node("DecList", 2, @1.first_line, $1, $3); 
    }
    ;
Dec
    : VarDec {
        $$ = create_node("Dec", 1, @1.first_line, $1); // 将 VarDec 作为 Dec 的子节点
    }
    | VarDec ASSIGN Exp {
        ast_node* assign_node = create_node("ASSIGN", 0, @2.first_line);
        assign_node->val.str_value = "=";
        $$ = create_node("Dec", 3, @1.first_line, $1, assign_node, $3); 
    }
    ;



Exp
    : ID { 
        $$ = create_node("ID",0 , @1.first_line);
        $$->val.str_value = strdup($1);  // 保存ID的值
    }
    | Exp DOT ID {
        $$ = create_node("struct_access",1 , @1.first_line, $1);
    }
    | INT { 
        ast_node* int_node = create_node("INT", 0, @1.first_line);
        int_node->val.int_value = $1;  // 保存整数值
        $$ = create_node("Exp", 1, @1.first_line, int_node);
    }
    | FLOAT {
        ast_node* float_node = create_node("FLOAT", 0, @1.first_line);
        float_node->val.float_value = $1;  // 保存整数值
        $$ = create_node("Exp", 1, @1.first_line, float_node);
    }
    | Exp ASSIGN Exp {
        ast_node* assign_node = create_node("ASSIGN", 0, @2.first_line);
        assign_node->val.str_value = "=";
        ast_node* left_exp = create_node("Exp", 1, @1.first_line, $1);
        $$ = create_node("Exp", 3, @1.first_line, left_exp, assign_node, $3);
    } 
    | Exp PLUS Exp {
        ast_node* plus_node = create_node("PLUS", 0, @2.first_line);
        ast_node* left_exp = create_node("Exp", 1, @1.first_line, $1);
        ast_node* right_exp = create_node("Exp", 1, @3.first_line, $3);
        $$ = create_node("Exp", 3, @1.first_line, left_exp, plus_node, right_exp);
    }
    | Exp MINUS Exp {
        $$ = create_node("minus",2 , @1.first_line, $1, $3);
    }
    | Exp TIMES Exp {
        $$ = create_node("mul",2 , @1.first_line, $1, $3);
    }
    | Exp DIVIDE Exp {
        $$ = create_node("div",2 , @1.first_line, $1, $3);
    }
    | Exp RELOP Exp {
        $$ = create_node("RELOP",2 , @1.first_line, $1, $3);
    }     
    | Exp AND Exp {
        $$ = create_node("AND",2 , @1.first_line, $1, $3);
    } 
    | Exp OR Exp {
        $$ = create_node("OR",2 , @1.first_line, $1, $3);
    }     
    | NOT Exp{
        $$ = create_node("NOT",1 , @1.first_line, $2);
    }
    | ID LPAREN RPAREN {
        ast_node* id_node = create_node("ID", 0, @1.first_line);
        id_node->val.str_value = strdup($1);
        ast_node* lp_node = create_node("LP", 0, @2.first_line);
        ast_node* rp_node = create_node("RP", 0, @3.first_line);
        $$ = create_node("CALL", 3, @1.first_line, id_node, lp_node, rp_node);
    } 
    | ID LPAREN arg_list RPAREN{
        ast_node* id_node = create_node("ID", 0, @1.first_line);
        id_node->val.str_value = strdup($1);
        ast_node* lp_node = create_node("LP", 0, @2.first_line);
        ast_node* rp_node = create_node("RP", 0, @4.first_line);
        $$ = create_node("CALL", 4, @1.first_line, id_node, lp_node, $3, rp_node);
    } 
    | Exp LBRACKET Exp RBRACKET {
        ast_node* lb_node = create_node("LB", 0, @2.first_line);
        ast_node* rb_node = create_node("RB", 0, @4.first_line);
        $$ = create_node("array_access", 4, @1.first_line, $1, lb_node, $3, rb_node);
    }
    | LPAREN Exp RPAREN {
        ast_node* lp_node = create_node("LP", 0, @1.first_line);
        ast_node* rp_node = create_node("RP", 0, @3.first_line);
        $$ = create_node("Exp", 3, @1.first_line, lp_node, $2, rp_node);
    }
    | Exp LBRACKET Exp error RBRACKET {
        printError('B', "Missing \"]\"");
    }
    | Exp LBRACE error RBRACE {
        printError('B', "Syntax error between \"[]\""); // 打印错误消息
    }
    | ID LPAREN error RPAREN {
        printError('B', "Syntax error in Exp"); // 打印错误消息
    } 


    ;


arg_list
    : Exp COMMA arg_list {
        $$ = create_node("arg_list", 2, @1.first_line, $1, $3);
    }
    | Exp { 
        $$ = create_node("arg_list", 1, @1.first_line, $1); 
    }
    ;


%%
