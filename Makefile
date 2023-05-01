# Makefile

SRC = src

OBJ_DIR = obj

OBJS	= bison.o lex.o yr_main.o \
		  ${OBJ_DIR}/YR_SPEC_STMT_MEALY_AUTOMATON.o

CC	= g++  

CFLAGS	= -g -Wall -pedantic \
					-fPIC -Wextra -pipe \
					-D_REENTRANT -DQT_NO_VERSION_TAGGING -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_SQL_LIB -DQT_CORE_LIB \
					-Isrc \
					-I/usr/lib/x86_64-linux-gnu \
					-I/usr/lib/x86_64-linux-gnu \
					-I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ \
					-I/usr/include/x86_64-linux-gnu/qt5 
					

LINKFLAGS	= -Llib -lyr_sd_runtime_verif \
			  -L/usr/lib/x86_64-linux-gnu -lQt5Sql -lQt5Core
					


yr_sd_runtime_verif_lang:		$(OBJS)
		$(CC) -o yr_sd_runtime_verif_lang_comp $(OBJS) $(LINKFLAGS) 


${OBJ_DIR}/YR_SPEC_STMT_MEALY_AUTOMATON.o:		${SRC}/YR_SPEC_STMT_MEALY_AUTOMATON.cpp
		mkdir -p ${OBJ_DIR}
		$(CC) $(CFLAGS) -c ${SRC}/YR_SPEC_STMT_MEALY_AUTOMATON.cpp -o ${OBJ_DIR}/YR_SPEC_STMT_MEALY_AUTOMATON.o


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
	rm -f ${OBJ_DIR}/* \
		*.o \
		*~ \
		lex.c \
		lex.yy.c \
		bison.c \
		tok.h \
		yr_sd_runtime_verif_lang.tab.c \
		yr_sd_runtime_verif_lang.tab.h \
		yr_sd_runtime_verif_lang.output

