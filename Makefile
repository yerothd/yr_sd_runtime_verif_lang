# Makefile

OBJS	= bison.o lex.o main.o

CC	= g++
CFLAGS	= -g -Wall -ansi -pedantic

yr_db_runtime_verif_lang:		$(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o yr_db_runtime_verif_lang -lfl

lex.o:		lex.c
		$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c:		yr_db_runtime_verif_lang.lex
		flex yr_db_runtime_verif_lang.lex
		cp lex.yy.c lex.c

bison.o:	bison.c
		$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c:	yr_db_runtime_verif_lang.y
		bison -d -v yr_db_runtime_verif_lang.y
		cp yr_db_runtime_verif_lang.tab.c bison.c
		cmp -s yr_db_runtime_verif_lang.tab.h tok.h || cp yr_db_runtime_verif_lang.tab.h tok.h

main.o:		main.cc
		$(CC) $(CFLAGS) -c main.cc -o main.o

lex.o yac.o main.o	: YR_HEADING.h
lex.o main.o		: YR_TOK.h

clean:
	rm -f *.o \
		*~ \
		lex.c \
		lex.yy.c \
		bison.c \
		YR_TOK.h \
		yr_db_runtime_verif_lang.tab.c \
		yr_db_runtime_verif_lang.tab.h \
		yr_db_runtime_verif_lang.output

