/* 
 * Description: Recognize the 32-bit hexadecimal integer from stdin
 * Pattern: 0[xX]([0-9a-fA-F]{1,8})
 */


space									[ \t\n]+
alpha									[a-zA-Z]+
in										IN
notin									NOT_IN
par_l									"{"
par_r									"}"
state_spec						STATE"("{alpha}")"
MEALY_AUTOMATON_SPEC	mealy_automaton_spec


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

