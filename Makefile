CFLAGS := -lfl
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CFLAGS += -L/usr/local/Cellar/flex/2.6.4/lib/
endif

run:
	flex lextest.l
	bison -d -v syntax.y
	gcc main.c syntax.tab.c buildtree.c $(CFLAGS) -o scanner
