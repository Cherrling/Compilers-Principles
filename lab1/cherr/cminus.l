%{
#include <stdio.h>
#include "cminus.tab.h"
#include "ast.h"

extern int yylineno;
extern YYSTYPE yylval;

void yyerror(const char *s);

%}

%option noyywrap

delim       [ \t\n]
ws          {delim}+
letter      [A-Za-z]
digit       [0-9]
id          {letter}({letter}|{digit})*
number      {digit}+
digits      {digit}+
float       ({digits}"."{digits})|({digits}".")|("."{digits})
comment     "/*"[^*]*"*"+([^*/][^*]*"*"+)*"/"

%%

{ws}        { /* skip whitespace */ }
{comment}   { /* skip comments */ }

"else"      { return ELSE; }
"if"        { return IF; }
"int"       { return INT; }
"float"     { return FLOAT; }  // 添加float关键字
"return"    { return RETURN; }
"void"      { return VOID; }
"while"     { return WHILE; }

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

{id}        { 
                yylval.string = strdup(yytext); 
                return ID; 
            }
{number}    { 
                yylval.number = atoi(yytext); 
                return NUM; 
            }
{float}     {  
                yylval.floating = atof(yytext);
                return FLOAT_NUM;
}

.           { 
                fprintf(stderr, "Error type A at line %d: mysterious character '%s'\n", yylineno, yytext); 
                yyerror("lexical error"); 
            }

%%