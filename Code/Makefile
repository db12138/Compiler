# GNU make手册：http://www.gnu.org/software/make/manual/make.html
# ************ 遇到不明白的地方请google以及阅读手册 *************

# 编译器设定和编译选项
CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -std=c99 -g -rdynamic -lfl 
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CFLAGS += -L/usr/local/Cellar/flex/2.6.4/lib/
endif
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
	$(CC) -o parser $(filter-out $(LFO),$(OBJS)) $(CFLAGS) -ly 
	cp parser ../

syntax: lexical syntax-c
	$(CC) -c $(YFC) -o $(YFO)

lexical: $(LFILE)
	$(FLEX) -o $(LFC) $(LFILE)

syntax-c: $(YFILE)
	$(BISON) -o $(YFC) -d -v $(YFILE)

-include $(patsubst %.o, %.d, $(OBJS))

# 定义的一些伪目标
.PHONY: clean test
test:
	./parser ../Test/test1
	./parser ../Test/test2
	./parser ../Test/test3
	./parser ../Test/test4
	./parser ../Test/test5
	./parser ../Test/test6
	./parser ../Test/test7
	./parser ../Test/test8
	./parser ../Test/test9
	./parser ../Test/test10
	./parser ../Test/test11
	./parser ../Test/test12
	./parser ../Test/test13
	./parser ../Test/test14
	./parser ../Test/test15
	./parser ../Test/test16
	./parser ../Test/test17
	./parser ../Test/test18
	./parser ../Test/test19
	./parser ../Test/test20
	./parser ../Test/test21
	./parser ../Test/test22
	./parser ../Test/test23
	./parser ../Test/test24
	./parser ../Test/test25
	./parser ../Test/test26
	./parser ../Test/test27
clean:
	rm -f parser lex.yy.c syntax.tab.c syntax.tab.h syntax.output
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f $(LFC) $(YFC) $(YFC:.c=.h)
	rm -f *~
