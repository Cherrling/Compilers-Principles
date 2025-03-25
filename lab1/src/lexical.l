%{
# include <stdio.h>
# include <stdlib.h>
# include "syntax.tab.h" // 包含另一个文件 syntax.tab.h
int yycolumn = 1; // 设置全局变量 yycolumn 初始值为 1

#define YY_USER_ACTION\
    yylloc.first_line=yylloc.last_line=yylineno;\
    yylloc.first_column=yycolumn;\
    yylloc.last_column=yycolumn+yyleng-1;\
    yycolumn+=yyleng; // 定义宏 YY_USER_ACTION，每次扫描符号时更新行列信息

struct Node* create_Node_l(char* name) { // 定义函数 create_Node_l，用于创建节点
    struct Node* newnode=(struct Node*)malloc(sizeof(struct Node)); // 分配内存给节点
    newnode->judge=0; // 初始化节点的判别值为0
    newnode->child=NULL; // 初始化节点的子节点为空
    newnode->brother=NULL; // 初始化节点的兄弟节点为空
    newnode->linenumber=0; // 初始化节点的行号为0
    strcpy(newnode->index,name); // 复制节点的名字
    return newnode; // 返回创建的节点
}
%}

%option yylineno // 开启 yylineno 选项，使得可以在词法分析器中使用 yylineno 表示当前行号
IGNORE [\r \t] // 定义忽略的空白字符
CHANGELINE [\n] // 定义换行符

// 定义正则表达式
INT 0|[1-9][0-9]* // 匹配整数
FLOAT {INT}\.[0-9]+ // 匹配浮点数
ID [_a-zA-Z][0-9_a-zA-Z]* // 匹配标识符
RELOP >|<|>=|<=|==|!= // 匹配关系运算符
TYPE int|float // 匹配类型
DIGIT [0-9] // 匹配数字

%%
// 规则与动作部分
";" {
    yylval = create_Node_l("SEMI\0"); // 创建分号节点
    return SEMI; // 返回分号标记
}

"," {
    yylval = create_Node_l("COMMA\0"); // 创建逗号节点
    return COMMA; // 返回逗号标记
}

"=" {
    yylval = create_Node_l("ASSIGNOP\0"); // 创建赋值运算符节点
    return ASSIGNOP; // 返回赋值运算符标记
}

{RELOP} {
    yylval = create_Node_l("RELOP\0"); // 创建关系运算符节点
    return RELOP; // 返回关系运算符标记
}

"+" {
    yylval = create_Node_l("PLUS\0"); // 创建一个表示加法操作符的节点
    return PLUS; // 返回加法操作符标记
}

"-" {
    yylval = create_Node_l("MINUS\0"); // 创建一个表示减法操作符的节点
    return MINUS; // 返回减法操作符标记
}

"*" {
    yylval = create_Node_l("STAR\0"); // 创建一个表示乘法操作符的节点
    return STAR; // 返回乘法操作符标记
}

"/" {
    yylval = create_Node_l("DIV\0"); // 创建一个表示除法操作符的节点
    return DIV; // 返回除法操作符标记
}

"&&" {
    yylval = create_Node_l("AND\0"); // 创建一个表示逻辑与操作符的节点
    return AND; // 返回逻辑与操作符标记
}

"||" {
    yylval = create_Node_l("OR\0"); // 创建一个表示逻辑或操作符的节点
    return OR; // 返回逻辑或操作符标记
}

"." {
    yylval = create_Node_l("DOT\0"); // 创建一个表示成员访问操作符的节点
    return DOT; // 返回成员访问操作符标记
}

"!" {
    yylval = create_Node_l("NOT\0"); // 创建一个表示逻辑非操作符的节点
    return NOT; // 返回逻辑非操作符标记
}

{TYPE} {
    yylval = create_Node_l("TYPE\0"); // 创建一个表示类型关键字的节点
    strcpy(yylval->char_name, yytext); // 将识别到的类型名称复制到节点中
    return TYPE; // 返回类型关键字标记
}

"(" {
    yylval = create_Node_l("LP\0"); // 创建一个表示左圆括号的节点
    return LP; // 返回左圆括号标记
}

")" {
    yylval = create_Node_l("RP\0"); // 创建一个表示右圆括号的节点
    return RP; // 返回右圆括号标记
}

"[" {
    yylval = create_Node_l("LB\0"); // 创建一个表示左方括号的节点
    return LB; // 返回左方括号标记
}

"]" {
    yylval = create_Node_l("RB\0"); // 创建一个表示右方括号的节点
    return RB; // 返回右方括号标记
}

"{" {
    yylval = create_Node_l("LC\0"); // 创建一个表示左大括号的节点
    return LC; // 返回左大括号标记
}

"}" {
    yylval = create_Node_l("RC\0"); // 创建一个表示右大括号的节点
    return RC; // 返回右大括号标记
}

"struct" {
    yylval = create_Node_l("STRUCT\0"); // 创建一个表示结构体关键字的节点
    return STRUCT; // 返回结构体关键字标记
}

"return" {
    yylval = create_Node_l("RETURN\0"); // 创建一个表示返回关键字的节点
    return RETURN; // 返回返回关键字标记
}

"if" {
    yylval = create_Node_l("IF\0"); // 创建一个表示if关键字的节点
    return IF; // 返回if关键字标记
}

"else" {
    yylval = create_Node_l("ELSE\0"); // 创建一个表示else关键字的节点
    return ELSE; // 返回else关键字标记
}

"while" {
    yylval = create_Node_l("WHILE\0"); // 创建一个表示while关键字的节点
    return WHILE; // 返回while关键字标记
}


{IGNORE} {} // 忽略空白字符

{CHANGELINE} {yycolumn=1;} // 换行时更新列号为1

// 匹配整数和浮点数
{INT} {
    yylval = create_Node_l("INT\0"); // 创建整数节点
    yylval -> int_number = atoi(yytext); // 将识别到的整数字符串转换成整数并赋值给节点
    return INT; // 返回整数标记
}

{FLOAT} {
    yylval = create_Node_l("FLOAT\0"); // 创建浮点数节点
    yylval -> float_number = atof(yytext); // 将识别到的浮点数字符串转换成浮点数并赋值给节点
    return FLOAT; // 返回浮点数标记
}

{ID} {
    yylval = create_Node_l("ID\0"); // 创建标识符节点
    strcpy(yylval->char_name,yytext); // 将识别到的标识符字符串复制到节点的 char_name 字段
    return ID; // 返回标识符标记
}

. {
    char msg[32]; // 定义错误信息缓冲区
    sprintf(msg, "Mysterious character \"%s\"", yytext); // 格式化错误消息
    printError('A', msg); // 打印错误消息
    Err = 1; // 设置错误标记
}

%%
