CC = gcc
LEX = flex
YACC = bison
CFLAGS = -g

all: cminus

cminus.tab.c cminus.tab.h: cminus.y
	$(YACC) -d cminus.y

lex.yy.c: cminus.l cminus.tab.h
	$(LEX) cminus.l

cminus: lex.yy.c cminus.tab.c cminus.tab.h utils.c main.c
	$(CC) $(CFLAGS) -o $@ lex.yy.c cminus.tab.c utils.c main.c

clean:
	rm -f cminus cminus.tab.c cminus.tab.h lex.yy.c

test: cminus
	-./cminus test1.cminus
	-./cminus test2.cminus
	-./cminus test3.cminus
	-./cminus test4.cminus

.PHONY: all clean
