/*
* @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
*/

%option noyywrap

%{
#include "YR_HEADING.h"
#include "tok.h"
int yyerror(char *s);
//int yylineno = 1;
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
{space}									{ return SPACE_TOK; }
{digit}									{ yylval.op_val = new std::string(yytext); return DIGIT_TOK; }
{alpha}									{ yylval.op_val = new std::string(yytext); return ALPHA_TOK; }
{alpha_num}							{ yylval.op_val = new std::string(yytext); return ALPHA_NUM_TOK; }
{db_column}							{ yylval.op_val = new std::string(yytext); return DB_COLUMN_TOK; }
{db_table}							{ yylval.op_val = new std::string(yytext); return DB_TABLE_TOK; }
{prog_variable}					{ yylval.op_val = new std::string(yytext); return PROG_VARIABLE_TOK; }
{in}										{ yylval.op_val = new std::string(yytext); return IN_TOK; }
{notin}									{ yylval.op_val = new std::string(yytext); return NOT_IN_TOK; }
{state}									{ yylval.op_val = new std::string(yytext); return STATE_TOK; }
{mealy_automaton_spec}	{ yylval.op_val = new std::string(yytext); return MEALY_AUTOMATON_SPEC_TOK; }
[\n]										{ yylineno++;	}

"+"											{ yylval.op_val = new std::string(yytext); return PLUS; }
"*"											{ yylval.op_val = new std::string(yytext); return MULT; }

.												{ std::cerr << "SCANNER "; yyerror(""); exit(1);	}
%%


/*int main(int argc, char* argv[])
{
  printf("Give me your input:\n");
  yylex();

  return 0;
}*/

