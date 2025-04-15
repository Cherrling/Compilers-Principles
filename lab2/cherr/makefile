CC = gcc
LEX = flex
YACC = bison
CFLAGS = -g

all: cminus

cminus.tab.c cminus.tab.h: cminus.y
	$(YACC) -d cminus.y

lex.yy.c: cminus.l cminus.tab.h
	$(LEX) cminus.l

# 修改编译命令，添加 semantic.c
cminus: lex.yy.c cminus.tab.c cminus.tab.h utils.c semantic.c main.c
	$(CC) $(CFLAGS) -o $@ lex.yy.c cminus.tab.c utils.c semantic.c main.c

clean:
	rm -f cminus cminus.tab.c cminus.tab.h lex.yy.c

test: cminus
	-./cminus ../test/test1.cmm
	-./cminus ../test/test2.cmm
	-./cminus ../test/test3.cmm
	-./cminus ../test/test4.cmm
	-./cminus ../test/test5.cmm
	-./cminus ../test/test6.cmm
	-./cminus ../test/test7.cmm
	-./cminus ../test/test8.cmm
	-./cminus ../test/test9.cmm
	-./cminus ../test/test10.cmm
	-./cminus ../test/test11.cmm
	-./cminus ../test/test12.cmm
	-./cminus ../test/test13.cmm
	-./cminus ../test/test14.cmm
	-./cminus ../test/test15.cmm
	-./cminus ../test/test16.cmm
	-./cminus ../test/test17.cmm

.PHONY: all clean