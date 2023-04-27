/*
* @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
*/


%{
#include "YR_HEADINGS.h"
#include "YR_TOK.h"
int yyerror(char *s);
int yylineno = 1;
%}


space									[ \t\n]+
digit									[0-9]+
alpha									[a-zA-Z]+
alpha_num							[_a-zA-Z]+[_0-9a-zA-Z]*
string								"'"[ \t\n_a-zA-Z0-9]*"'"
l_par									"{"
r_par									"}"
db_column							{alpha_num}
db_table							{alpha_num}
prog_variable					{alpha_num}
in										IN
notin									NOT_IN
state									STATE
mealy_automaton_spec	mealy_automaton_spec



%%
{int_const}	{ yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }
"+"		{ yylval.op_val = new std::string(yytext); return PLUS; }
"*"		{ yylval.op_val = new std::string(yytext); return MULT; }

[ \t]*		{}
[\n]		{ yylineno++;	}

.		{ std::cerr << "SCANNER "; yyerror(""); exit(1);	}


{MEALY_AUTOMATON_SPEC}	printf("Found a MEALY AUTOMATON specification %s !", yytext);
.												printf("");
%%


int main(int argc, char* argv[])
{
  printf("Give me your input:\n");
  yylex();

  return 0;
}

