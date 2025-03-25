%locations // 开启了词法位置追踪

%{
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

// 声明了一些外部变量和函数
extern int yylineno; // 表示当前的行号
extern char* yytext; // 表示当前识别到的文本
extern int yylex(); // 词法分析器的接口函数

void yyerror(const char* s); // 错误处理函数

int Err = 0; // 错误标志，用于指示是否出现了错误
int lastErrLineno = 0; // 记录上一个错误的行号

// 定义了一个结构体 Node，表示语法树中的节点
struct Node {
    struct Node* child; // 指向子节点的指针
    struct Node* brother; // 指向兄弟节点的指针
    int linenumber; // 节点所在的行号
    char index[15]; // 节点的类型或标识符名
    short judge; // 用于判别节点类型的标志
    union { // 联合体，用于存储节点值的不同类型
        char char_name[30]; // 字符串类型
        int int_number; // 整数类型
        float float_number; // 浮点数类型
    };
};

#define YYSTYPE struct Node* // 定义 YYSTYPE 类型，表示词法分析器的返回值类型

struct Node* head=NULL; // 定义了一个指向语法树根节点的指针 head
struct Node* create_Node(struct Node* ch,char* name,int line); // 声明创建节点的函数
void print_tree(struct Node* now,int depth); // 声明打印语法树的函数
void printError(char errorType, char* msg); // 声明打印错误信息的函数
int isNewError(int errorLineno); // 声明检查是否是新错误的函数
%}

// 定义了一系列的 token，每个 token 对应一个词法单元
%token STRUCT
%token RETURN
%token IF
%token ELSE
%token WHILE
%token SEMI
%token COMMA
%token ASSIGNOP
%token PLUS
%token MINUS
%token STAR
%token DIV
%token AND
%token OR
%token NOT
%token LP
%token RP
%token LB
%token RB
%token LC
%token RC
%token TYPE
%token INT
%token FLOAT
%token ID
%token RELOP
%token DOT

// 定义了一些操作符的结合性
%right ASSIGNOP // 右结合的赋值操作符
%left OR // 左结合的逻辑或操作符
%left AND // 左结合的逻辑与操作符
%left RELOP // 左结合的关系运算符
%left PLUS MINUS // 左结合的加减号
%left STAR DIV // 左结合的乘除号
%right LOWER_THAN_NOT NOT // 右结合的逻辑非操作符
%right DOT LP LB RP RB // 右结合的点号和括号
%nonassoc LOWER_THAN_ELSE // 不关联的比 else 小的操作符
%nonassoc ELSE // 不关联的 else 操作符
%%

Program: ExtDefList{     
    if($1->int_number==0) // 如果 ExtDefList 返回的整数值为0
        $$=create_Node($1,"Program\0",$1->linenumber); // 创建一个名为 "Program" 的节点，并指定行号为 $1 的行号
    else // 否则
        $$=create_Node($1,"Program\0",@1.first_line); // 创建一个名为 "Program" 的节点，并指定行号为 @1 的行号
};

ExtDefList: {
    $$ = create_Node(NULL,"ExtDefList\0",yylineno); // 创建一个名为 "ExtDefList" 的节点，并指定行号为当前行号
    $$ -> int_number=0; // 设置节点的整数值为0
} | ExtDef ExtDefList {
    $$ = create_Node($1,"ExtDefList\0",@1.first_line); // 创建一个名为 "ExtDefList" 的节点，并指定行号为 @1 的行号
    $$ -> int_number = 2; // 设置节点的整数值为2
    $1 -> brother = $2; // 将第一个子节点与第二个子节点链接起来
}

// 定义了 ExtDef 规则，包括了多种可能的情况
ExtDef:Specifier ExtDecList SEMI{
    $$ = create_Node($1,"ExtDef\0",@1.first_line); // 创建一个名为 "ExtDef" 的节点，并指定行号为 @1 的行号
    $1 -> brother = $2; // 将 Specifier 和 ExtDecList 两个子节点链接起来
    $2 -> brother = $3; // 将 ExtDecList 和分号节点链接起来
} | Specifier SEMI{
    $$ = create_Node($1,"ExtDef\0",@1.first_line); // 创建一个名为 "ExtDef" 的节点，并指定行号为 @1 的行号
    $1 -> brother = $2; // 将 Specifier 和分号节点链接起来
} | Specifier FunDec CompSt{
    $$ = create_Node($1,"ExtDef\0",@1.first_line); // 创建一个名为 "ExtDef" 的节点，并指定行号为 @1 的行号
    $1 -> brother=$2; // 将 Specifier 和 FunDec 两个子节点链接起来
    $2 -> brother=$3; // 将 FunDec 和 CompSt 两个子节点链接起来
} | Specifier error {
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "Missing \";\""); // 打印错误消息
}

// 定义了 ExtDecList 规则，包括了多种可能的情况
ExtDecList: VarDec{
    $$ = create_Node($1,"ExtDecList\0",@1.first_line); // 创建一个名为 "ExtDecList" 的节点，并指定行号为 @1 的行号
} | VarDec COMMA ExtDecList{
    $$ = create_Node($1,"ExtDecList\0",@1.first_line); // 创建一个名为 "ExtDecList" 的节点，并指定行号为 @1 的行号
    $1 -> brother = $2; // 将 VarDec 和逗号节点链接起来
    $2 -> brother = $3; // 将逗号节点和 ExtDecList 两个子节点链接起来
} | VarDec error ExtDecList{
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "text"); // 打印错误消息
}


Specifier: TYPE{
    $$ = create_Node($1,"Specifier\0",@1.first_line); // 创建一个名为 "Specifier" 的节点，行号为 @1 的行号
} | StructSpecifier{
    $$ = create_Node($1,"Specifier\0",@1.first_line); // 创建一个名为 "Specifier" 的节点，行号为 @1 的行号
}

StructSpecifier: STRUCT OptTag LC DefList RC{
    $$ = create_Node($1,"StructSpecifier\0",@1.first_line); // 创建一个名为 "StructSpecifier" 的节点，行号为 @1 的行号
    $1 -> brother=$2; // 将 STRUCT 和 OptTag 节点链接起来
    $2 -> brother=$3; // 将 OptTag 和 LC 节点链接起来
    $3 -> brother=$4; // 将 LC 和 DefList 节点链接起来
    $4 -> brother=$5; // 将 DefList 和 RC 节点链接起来
} | STRUCT Tag{
    $$ = create_Node($1,"StructSpecifier\0",@1.first_line); // 创建一个名为 "StructSpecifier" 的节点，行号为 @1 的行号
    $1 -> brother=$2; // 将 STRUCT 和 Tag 节点链接起来
}

OptTag: {
    $$ = create_Node(NULL,"OptTag\0",0); // 创建一个名为 "OptTag" 的节点，行号为0
    $$ -> int_number = 0; // 设置节点的整数值为0
} | ID{
    $$ = create_Node($1,"OptTag\0",@1.first_line); // 创建一个名为 "OptTag" 的节点，行号为 @1 的行号
}

Tag:ID{
    $$ = create_Node($1,"Tag\0",@1.first_line); // 创建一个名为 "Tag" 的节点，行号为 @1 的行号
}

VarDec:ID{
    $$ = create_Node($1,"VarDec\0",@1.first_line); // 创建一个名为 "VarDec" 的节点，行号为 @1 的行号
} | VarDec LB INT RB{
    $$ = create_Node($1,"VarDec\0",@1.first_line); // 创建一个名为 "VarDec" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 VarDec 和 LB 节点链接起来
    $2 -> brother = $3; // 将 LB 和 INT 节点链接起来
    $3 -> brother = $4; // 将 INT 和 RB 节点链接起来
} | VarDec LB error RB {
    Err = 1; // 设置错误标志为1
    char msg[32]; // 定义错误信息缓冲区
    sprintf(msg, "Syntax error, near \'%c\'", yytext[0]); // 格式化错误消息
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', msg); // 打印错误消息
}

FunDec:ID LP VarList RP{
    $$ = create_Node($1,"FunDec\0",@1.first_line); // 创建一个名为 "FunDec" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 ID 和 LP 节点链接起来
    $2 -> brother = $3; // 将 LP 和 VarList 节点链接起来
    $3 -> brother = $4; // 将 VarList 和 RP 节点链接起来
} | ID LP RP{
    $$ = create_Node($1,"FunDec\0",@1.first_line); // 创建一个名为 "FunDec" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 ID 和 LP 节点链接起来
    $2 -> brother = $3; // 将 LP 和 RP 节点链接起来
} | ID LP error RP {
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno)  // 如果上一个错误的行号不等于当前行号
        printError('B', "Syntax error between ()"); // 打印错误消息
}

VarList:ParamDec COMMA VarList{
    $$ = create_Node($1,"VarList\0",@1.first_line); // 创建一个名为 "VarList" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 ParamDec 和 COMMA 节点链接起来
    $2 -> brother = $3; // 将 COMMA 和 VarList 节点链接起来
} | ParamDec{
    $$ = create_Node($1,"VarList\0",@1.first_line); // 创建一个名为 "VarList" 的节点，行号为 @1 的行号
}

ParamDec:Specifier VarDec{
    $$ = create_Node($1,"ParamDec\0",@1.first_line); // 创建一个名为 "ParamDec" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Specifier 和 VarDec 节点链接起来
}

CompSt:LC DefList StmtList RC{
    $$ = create_Node($1,"CompSt\0",@1.first_line); // 创建一个名为 "CompSt" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 LC 和 DefList 节点链接起来
    $2 -> brother = $3; // 将 DefList 和 StmtList 节点链接起来
    $3 -> brother = $4; // 将 StmtList 和 RC 节点链接起来
}

StmtList: {
    $$ = create_Node(NULL,"StmtList\0",0); // 创建一个名为 "StmtList" 的节点，行号为0
    $$ -> int_number=0; // 设置节点的整数值为0
} | Stmt StmtList{
    $$ = create_Node($1,"StmtList\0",@1.first_line); // 创建一个名为 "StmtList" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Stmt 和 StmtList 节点链接起来
}


Stmt:Exp SEMI{
    $$ = create_Node($1,"Stmt\0",@1.first_line); // 创建一个名为 "Stmt" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Exp 和分号节点链接起来
}|CompSt{
    $$ = create_Node($1,"Stmt\0",@1.first_line); // 创建一个名为 "Stmt" 的节点，行号为 @1 的行号
}|RETURN Exp SEMI{
    $$ = create_Node($1,"Stmt\0",@1.first_line); // 创建一个名为 "Stmt" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 RETURN 和 Exp 节点链接起来
    $2 -> brother = $3; // 将 Exp 和分号节点链接起来
}|IF LP Exp RP Stmt %prec LOWER_THAN_ELSE{
    $$ = create_Node($1,"Stmt\0",@1.first_line); // 创建一个名为 "Stmt" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 IF 和 LP 节点链接起来
    $2 -> brother = $3; // 将 LP 和 Exp 节点链接起来
    $3 -> brother = $4; // 将 Exp 和 RP 节点链接起来
    $4 -> brother = $5; // 将 RP 和 Stmt 节点链接起来
}|IF LP Exp RP Stmt ELSE Stmt{
    $$ = create_Node($1,"Stmt\0",@1.first_line); // 创建一个名为 "Stmt" 的节点，行号为 @1 的行号
    $1 -> brother=$2; // 将 IF 和 LP 节点链接起来
    $2 -> brother=$3; // 将 LP 和 Exp 节点链接起来
    $3 -> brother=$4; // 将 Exp 和 RP 节点链接起来
    $4 -> brother=$5; // 将 RP 和 Stmt 节点链接起来
    $5 -> brother=$6; // 将 Stmt 和 ELSE 节点链接起来
    $6 -> brother=$7; // 将 ELSE 和 Stmt 节点链接起来
}|WHILE LP Exp RP Stmt{
    $$ = create_Node($1,"Stmt\0",@1.first_line); // 创建一个名为 "Stmt" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 WHILE 和 LP 节点链接起来
    $2 -> brother = $3; // 将 LP 和 Exp 节点链接起来
    $3 -> brother = $4; // 将 Exp 和 RP 节点链接起来
    $4 -> brother = $5; // 将 RP 和 Stmt 节点链接起来
}| Exp error {
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "Missing \";\""); // 打印错误消息
}

DefList: {
    $$ = create_Node(NULL,"DefList\0",0); // 创建一个名为 "DefList" 的节点，行号为0
    $$ -> int_number = 0; // 设置节点的整数值为0
}|Def DefList{
    $$ = create_Node($1,"DefList\0",@1.first_line); // 创建一个名为 "DefList" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Def 和 DefList 节点链接起来
}

Def:Specifier DecList SEMI{
    $$ = create_Node($1,"Def\0",@1.first_line); // 创建一个名为 "Def" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Specifier 和 DecList 节点链接起来
    $2 -> brother = $3; // 将 DecList 和 SEMI 节点链接起来
}|Specifier error SEMI{
    Err = 1; // 设置错误标志为1
    char msg[32]; // 定义错误信息缓冲区
    sprintf(msg, "Syntax error, near \'%c\'", yytext[0]); // 格式化错误消息
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', msg); // 打印错误消息
}| Specifier DecList error {
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B',"Missing \";\""); // 打印错误消息
}

DecList:Dec{
    $$ = create_Node($1,"DecList\0",@1.first_line); // 创建一个名为 "DecList" 的节点，行号为 @1 的行号
}|Dec COMMA DecList{
    $$ = create_Node($1,"DecList\0",@1.first_line); // 创建一个名为 "DecList" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Dec 和 COMMA 节点链接起来
    $2 -> brother = $3; // 将 COMMA 和 DecList 节点链接起来
}

Dec:VarDec{
    $$ = create_Node($1,"Dec\0",@1.first_line); // 创建一个名为 "Dec" 的节点，行号为 @1 的行号
}|VarDec ASSIGNOP Exp{
    $$ = create_Node($1,"Dec\0",@1.first_line); // 创建一个名为 "Dec" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 VarDec 和 ASSIGNOP 节点链接起来
    $2 -> brother = $3; // 将 ASSIGNOP 和 Exp 节点链接起来
}

Exp:Exp ASSIGNOP Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将第一个 Exp 和 ASSIGNOP 节点链接起来
    $2 -> brother = $3; // 将 ASSIGNOP 和第二个 Exp 节点链接起来
} | Exp AND Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将第一个 Exp 和 AND 节点链接起来
    $2 -> brother = $3; // 将 AND 和第二个 Exp 节点链接起来
} | Exp OR Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将第一个 Exp 和 OR 节点链接起来
    $2 -> brother = $3; // 将 OR 和第二个 Exp 节点链接起来
} | Exp RELOP Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将第一个 Exp 和 RELOP 节点链接起来
    $2 -> brother = $3; // 将 RELOP 和第二个 Exp 节点链接起来
} | Exp PLUS Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将第一个 Exp 和 PLUS 节点链接起来
    $2 -> brother = $3; // 将 PLUS 和第二个 Exp 节点链接起来
} | Exp MINUS Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother=$2; // 将第一个 Exp 和 MINUS 节点链接起来
    $2 -> brother=$3; // 将 MINUS 和第二个 Exp 节点链接起来
} | Exp STAR Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother=$2; // 将第一个 Exp 和 STAR 节点链接起来
    $2 -> brother=$3; // 将 STAR 和第二个 Exp 节点链接起来
} | Exp DIV Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother=$2; // 将第一个 Exp 和 DIV 节点链接起来
    $2 -> brother=$3; // 将 DIV 和第二个 Exp 节点链接起来
} | LP Exp RP{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother=$2; // 将 LP 和 Exp 节点链接起来
    $2 -> brother=$3; // 将 Exp 和 RP 节点链接起来
} | MINUS Exp %prec LOWER_THAN_NOT{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 MINUS 和 Exp 节点链接起来
} | NOT Exp{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 NOT 和 Exp 节点链接起来
} | ID LP Args RP{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 ID 和 LP 节点链接起来
    $2 -> brother = $3; // 将 LP 和 Args 节点链接起来
    $3 -> brother = $4; // 将 Args 和 RP 节点链接起来
} | ID LP RP{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 ID 和 LP 节点链接起来
    $2 -> brother = $3; // 将 LP 和 RP 节点链接起来
} | Exp LB Exp RB{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将第一个 Exp 和 LB 节点链接起来
    $2 -> brother = $3; // 将 LB 和第二个 Exp 节点链接起来
    $3 -> brother = $4; // 将第二个 Exp 和 RB 节点链接起来
} | Exp DOT ID{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Exp 和 DOT 节点链接起来
    $2 -> brother = $3; // 将 DOT 和 ID 节点链接起来
} | ID{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
} | INT{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
} | FLOAT{
    $$ = create_Node($1,"Exp\0",@1.first_line); // 创建一个名为 "Exp" 的节点，行号为 @1 的行号
} | Exp LB error RB {
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "Syntax error between \"[]\""); // 打印错误消息
} | Exp ASSIGNOP error {
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "Syntax error in Exp"); // 打印错误消息
} | LP error RP {
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "Syntax error in Exp"); // 打印错误消息
} | ID LP error RP{
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "Syntax error in Exp"); // 打印错误消息
} | Exp LB Exp error RB{
    Err = 1; // 设置错误标志为1
    if (lastErrLineno != yylineno) // 如果上一个错误的行号不等于当前行号
        printError('B', "Missing \"]\""); // 打印错误消息
};

Args:Exp COMMA Args{
    $$ = create_Node($1,"Arg\0",@1.first_line); // 创建一个名为 "Arg" 的节点，行号为 @1 的行号
    $1 -> brother = $2; // 将 Exp 和 COMMA 节点链接起来
    $2 -> brother = $3; // 将 COMMA 和 Args 节点链接起来
} | Exp{
    $$ = create_Node($1,"Args\0",@1.first_line); // 创建一个名为 "Args" 的节点，行号为 @1 的行号
}

%%

#include "lex.yy.c"

// 创建一个节点
struct Node* create_Node(struct Node* ch, char* name, int line) {
    // 分配内存空间
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    // 设置节点属性
    newnode->judge = 1; // judge为1表示非终结符
    newnode->child = ch; // 子节点
    newnode->brother = NULL; // 兄弟节点
    newnode->linenumber = line; // 行号
    newnode->int_number = 1; // 整型值
    strcpy(newnode->index, name); // 名称
    head = newnode; // 将当前节点设置为头节点
    return newnode; // 返回新节点
}

// 打印节点信息
void print_node(struct Node* now) {
    // 如果是终结符或者整型值非0
    if (now->judge == 0 || now->int_number) {
        // 根据节点类型输出信息
        if (!strcmp(now->index, "ID\0")) {
            printf("ID: %s\n", now->char_name); // 输出标识符
        } else if (!strcmp(now->index, "TYPE\0")) {
            printf("TYPE: %s\n", now->char_name); // 输出类型
        } else if (!strcmp(now->index, "INT\0")) {
            printf("INT: %u\n", now->int_number); // 输出整型值
        } else if (!strcmp(now->index, "FLOAT\0")) {
            printf("FLOAT: %f\n", now->float_number); // 输出浮点数值
        } else {
            printf("%s\n", now->index); // 输出其他类型的节点信息
        }
    } else {
        printf("%s (%d)\n", now->index, now->linenumber); // 输出非终结符节点信息
    }
}

// 打印语法树
void print_tree(struct Node* now, int depth) {
    // 如果是终结符或者整型值非0
    if (now->judge == 0 || now->int_number) {
        // 根据深度缩进
        for (int i = 0; i < depth; ++i) printf("  ");
        // 打印节点信息
        print_node(now);
    }
    // 递归打印子节点
    if (now->child != NULL) print_tree(now->child, depth + 1);
    // 打印兄弟节点
    if (now->brother != NULL) print_tree(now->brother, depth);
    return;
}

// 打印错误信息
void printError(char errorType, char* msg) {
    // 打印错误类型和错误消息以及行号
    fprintf(stderr, "Error type %c at Line %d: %s.\n", errorType, yylineno, msg);
    lastErrLineno = yylineno; // 记录错误行号
}

// 空函数，用于避免编译器报错
void yyerror(const char* s) {}
