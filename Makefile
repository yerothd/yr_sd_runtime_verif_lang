# Makefile


OBJS	= bison.o lex.o yr_main.o

CC	= g++  

CFLAGS	= -std=c++11 -g -Wall -pedantic \
					-fPIC -Wextra -pipe \
					-D_REENTRANT -DQT_NO_VERSION_TAGGING -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_SQL_LIB -DQT_CORE_LIB \
					-Iyr_sd_runtime_verif \
					-I/usr/lib/x86_64-linux-gnu/ \
					-I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ \
					-I/usr/include/x86_64-linux-gnu/qt5 
					

LINKFLAGS	= -std=c++11 -g -Wall -pedantic \
					-fPIC -Wextra -pipe \
					-Llib \
					-L/usr/lib/x86_64-linux-gnu \
					-lQt5Sql \
					-lQt5Gui \
					-lQt5Core \
					-lyr_sd_runtime_verif


yr_sd_runtime_verif_lang:		$(OBJS)
		$(CC) $(LINKFLAGS) $(OBJS) -o yr_sd_runtime_verif_lang_comp 

lex.o:		lex.c
		$(CC) $(CFLAGS) -c lex.c -o lex.o

lex.c:		yr_sd_runtime_verif_lang.lex
		flex yr_sd_runtime_verif_lang.lex
		cp lex.yy.c lex.c

bison.o:	bison.c
		$(CC) $(CFLAGS) -c bison.c -o bison.o

bison.c:	yr_sd_runtime_verif_lang.y
		bison -d -v yr_sd_runtime_verif_lang.y
		cp yr_sd_runtime_verif_lang.tab.c bison.c
		cmp -s yr_sd_runtime_verif_lang.tab.h tok.h || cp yr_sd_runtime_verif_lang.tab.h tok.h

yr_main.o:		yr_main.cc
		$(CC) $(CFLAGS) -c yr_main.cc -o yr_main.o

lex.o yac.o yr_main.o	: YR_HEADING.h
lex.o yr_main.o		: tok.h



clean:
	rm -f *.o \
		*~ \
		lex.c \
		lex.yy.c \
		bison.c \
		tok.h \
		yr_sd_runtime_verif_lang.tab.c \
		yr_sd_runtime_verif_lang.tab.h \
		yr_sd_runtime_verif_lang.output

