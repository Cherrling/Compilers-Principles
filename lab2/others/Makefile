# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99

# 编译目标：src目录下的所有.c文件
CFILES = $(shell find ./ -name "*.c")
OBJS = $(CFILES:.c=.o)
LFILE = $(shell find ./ -name "*.l")
YFILE = $(shell find ./ -name "*.y")
LFC = $(shell find ./ -name "*.l" | sed s/[^/]*\\.l/lex.yy.c/)
YFC = $(shell find ./ -name "*.y" | sed s/[^/]*\\.y/syntax.tab.c/)
LFO = $(LFC:.c=.o)
YFO = $(YFC:.c=.o)





parser: syntax $(filter-out $(LFO),$(OBJS))
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) -lfl -ly

# flex -o ./lex.yy.c ./lexical.l
# bison -o ./syntax.tab.c -d -v ./syntax.y
# gcc -c ./syntax.tab.c -o ./syntax.tab.o

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

# flex -o ./lex.yy.c ./lexical.l
# bison -o ./syntax.tab.c -d -v ./syntax.y
# gcc -c ./syntax.tab.c -o ./syntax.tab.o
# gcc -std=c99   -c -o tree.o tree.c
# gcc -std=c99   -c -o main.o main.c
# gcc -o parser ./tree.o ./syntax.tab.o ./main.o -lfl -ly
# ./parser ../test/testtest1.cmm

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

# flex -o ./lex.yy.c ./lexical.l

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v -t $(YFILE)

# bison -o ./syntax.tab.c -d -v ./syntax.y

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test
test:
	./parser ../test/test1.cmm
	./parser ../test/test2.cmm
	./parser ../test/test3.cmm
	./parser ../test/test4.cmm
	./parser ../test/test5.cmm
	./parser ../test/test6.cmm
	./parser ../test/test7.cmm
	./parser ../test/test8.cmm
	./parser ../test/test9.cmm
	./parser ../test/test10.cmm
	./parser ../test/test11.cmm
	./parser ../test/test12.cmm
	./parser ../test/test13.cmm
	./parser ../test/test14.cmm
	./parser ../test/test15.cmm
	./parser ../test/test16.cmm
	./parser ../test/test17.cmm

clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
