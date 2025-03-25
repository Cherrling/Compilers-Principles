#include <stdio.h>
#include <stdlib.h>

// 外部变量声明
extern FILE *yyin;        // 输入文件流指针
extern int yylineno;      // 当前行号
extern int Err;           // 错误标记，0表示没有错误，非0表示有错误
extern struct Node *head; // 语法树的头节点指针

// 函数声明
extern int yylex();                                    // 词法分析函数
extern int yyparse(void);                              // 语法分析函数
extern void yyrestart(FILE *input_file);               // 重置词法分析器的输入文件
extern void print_tree(struct Node *heads, int depth); // 打印语法树

// 主函数
int main(int argc, char **argv)
{
    // 检查命令行参数是否足够
    if (argc <= 1)
        return 1;

    // 打开文件流
    FILE *f = fopen(argv[1], "r");
    // 检查文件是否成功打开
    if (!f)
    {
        perror(argv[1]); // 输出错误信息
        return 1;
    }

    // 初始化行号并重置词法分析器的输入文件
    yylineno = 1;
    yyrestart(f);

    // 开始语法分析
    yyparse();

    // 如果没有错误，则打印语法树
    if (Err == 0)
        print_tree(head, 0);

    return 0;
}
