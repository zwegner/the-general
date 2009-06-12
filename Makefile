# Makefile for the General

# This is for generating y.tab.h files
YFLAGS= -d -b Y

parser:	main.c parse.c Y.tab.c Y.tab.h Lex.yy.c
	cc -Wall -g main.c parse.c Y.tab.c Lex.yy.c

Y.tab.c Y.tab.h: yparse.y
	yacc ${YFLAGS} $<

Lex.yy.c: lparse.l Y.tab.h
	lex -oLex.yy.c lparse.l

clean:
	rm -f Y.tab.c Y.tab.h Lex.yy.c
