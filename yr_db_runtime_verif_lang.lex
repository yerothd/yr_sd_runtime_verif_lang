/*
* @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
*/



space									[ \t\n]+
digit									[0-9]+
alpha									[a-zA-Z]+
alpha_num							[_a-zA-Z]+[_0-9a-zA-Z]*
in										IN
notin									NOT_IN
l_par									"{"
r_par									"}"
db_column							{alpha_num}
db_table							{alpha_num}
prog_variable					{alpha_num}
state									STATE
MEALY_AUTOMATON_SPEC	mealy_automaton_spec{l_par}{alpha_num}{r_par} 


%%
{MEALY_AUTOMATON_SPEC}	printf("Found a MEALY AUTOMATON specification %s !", yytext);
.												printf("");
%%


int main(int argc, char* argv[])
{
  printf("Give me your input:\n");
  yylex();

  return 0;
}

