
%{
#include "YR_HEADING.h"
int yyerror(char *s);
int yylex(void);
%}

%union{
  int		int_val;
  string*	op_val;
}

%start	input 

%token	<int_val>	INTEGER_LITERAL
%token	<int_val>	SPACE_TOK
%token	<int_val>	DIGIT_TOK
%token	<int_val>	ALPHA_TOK
%token	<int_val>	ALPHA_NUM_TOK
%token	<int_val>	DB_COLUMN_TOK
%token	<int_val>	DB_TABLE_TOK
%token	<int_val>	PROG_VARIABLE_TOK
%token	<int_val>	IN_TOK
%token	<int_val>	NOT_IN_TOK
%token	<int_val>	STATE_TOK
%token	<int_val>	MEALY_AUTOMATON_SPEC_TOK

%type	<int_val>	exp

%left	PLUS
%left	MULT

%%

input:		/* empty */
		| exp	{ cout << "Result: " << $1 << endl; }
		;

exp:		INTEGER_LITERAL	{ $$ = $1; }
		| exp PLUS exp	{ $$ = $1 + $3; }
		| exp MULT exp	{ $$ = $1 * $3; }
		;

%%


int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}


