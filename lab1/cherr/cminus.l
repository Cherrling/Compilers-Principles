%{
#include <stdio.h>
#include "cminus.tab.h"
#include "utils.h"

extern int yylineno;
extern YYSTYPE yylval;

void yyerror(const char *s);


%}

%option noyywrap

delim       [ \t\n]
ws          {delim}+
id          [_a-zA-Z][0-9_a-zA-Z]*
int         0|[1-9][0-9]*
float       {int}\.[0-9]+ 
comment     "/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"

IGNORE [\r \t] 
CHANGELINE [\n] 


%%

{ws}        { /* skip whitespace */ }
{comment}   { /* skip comments */ }

"else"      { return ELSE; }
"if"        { return IF; }
"int"       { return INT; }
"float"     { return FLOAT; }
"return"    { return RETURN; }
"void"      { return VOID; }
"while"     { return WHILE; }
"struct"    { return STRUCT; }

"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return TIMES; }
"/"         { return DIVIDE; }
"<"         { return LT; }
"<="        { return LTE; }
">"         { return GT; }
">="        { return GTE; }
"=="        { return EQ; }
"!="        { return NEQ; }
"="         { return ASSIGN; }
";"         { return SEMI; }
","         { return COMMA; }
"("         { return LPAREN; }
")"         { return RPAREN; }
"["         { return LBRACKET; }
"]"         { return RBRACKET; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
"||"        { return OR; } 
"&&"        { return AND; } 
"."         { return DOT; } 
"!"         { return NOT; } 


{IGNORE} {} 

{CHANGELINE} {} 

{id}        { 
                yylval.string = strdup(yytext); 
                return ID; 
            }

{int}       { 
                yylval.int_number = atoi(yytext); 
                return INT; 
            }

{float}     {  
                yylval.float_number = atof(yytext);
                return FLOAT;
}

.           { 
                char msg[32]; // 定义错误信息缓冲区
                sprintf(msg, "Mysterious character \"%s\"", yytext); // 格式化错误消息
                printError('A', msg); // 打印错误消息
            }

%%