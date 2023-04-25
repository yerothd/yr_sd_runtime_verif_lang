#
# @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
#



.PHONY=*.o

YR_DB_RUNTIME_LANG_COMPILER_BIN_NAME=yr_db_runtime_verif_lang_COMPILER

LEX=flex

GCC=gcc
GCC_FLAGS=-lfl -o ${YR_DB_RUNTIME_LANG_COMPILER_BIN_NAME} 


all:	yr_db_runtime_verif_lang.lex
	${LEX} yr_db_runtime_verif_lang.lex
	${GCC} ${GCC_FLAGS} lex.yy.c


clean:
	rm -f lex.yy.c
	rm -f *.o

