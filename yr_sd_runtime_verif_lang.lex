/*
* @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
*/

%option noinput nounput nodefault yylineno
%option noyywrap

%{
#include "YR_HEADING.h"
#include "tok.h"
int yyerror(char *s);
//int yylineno = 1;
%}


space									[ \t\n]+
right_arrow						"->"
mealy_automaton_spec	"yr_sd_mealy_automaton_spec"
in_set_trace					"IN_SET_TRACE"
not_in_set_trace			"NOT_IN_SET_TRACE"
in_pre								"IN_PRE"
in_post								"IN_POST"
notin_pre							"NOT_IN_PRE"
notin_post						"NOT_IN_POST"
final_state						"FINAL_STATE"
start_state						"START_STATE"
state									"STATE"
string								"'"[ \t\n\._a-zA-Z0-9]*"'"
alpha_num							[_a-zA-Z]+[_0-9a-zA-Z]*
digit									[0-9]+
slash									"/"
dot										"."
coma									","
colon									":"
semicolon							";"
l_bracket							"["
r_bracket							"]"
l_parenthesis					"("
r_parenthesis					")"
l_brace								"{"
r_brace								"}"


%%
{space}            			; /* Do nothing */
{mealy_automaton_spec}	{ yylval.opt_val = new std::string(yytext); return YR_SD_MEALY_AUTOMATON_SPEC_TOK; }
{right_arrow}						{ yylval.opt_val = new std::string(yytext); return RIGHT_ARROW_TOK; }
{in_set_trace}					{ yylval.opt_val = new std::string(yytext); return IN_SET_TRACE_TOK; }
{not_in_set_trace}			{ yylval.opt_val = new std::string(yytext); return NOT_IN_SET_TRACE_TOK; }
{in_pre}								{ yylval.opt_val = new std::string(yytext); return IN_PRE_TOK; }
{in_post}								{ yylval.opt_val = new std::string(yytext); return IN_POST_TOK; }
{notin_pre}							{ yylval.opt_val = new std::string(yytext); return NOT_IN_PRE_TOK; }
{notin_post}						{ yylval.opt_val = new std::string(yytext); return NOT_IN_POST_TOK; }
{final_state}						{ yylval.opt_val = new std::string(yytext); return FINAL_STATE_TOK; }
{start_state}						{ yylval.opt_val = new std::string(yytext); return START_STATE_TOK; }
{state}									{ yylval.opt_val = new std::string(yytext); return STATE_TOK; }
{string}								{ yylval.opt_val = new std::string(yytext); return STRING_TOK; }
{alpha_num}							{ yylval.opt_val = new std::string(yytext); return ALPHA_NUM_TOK; }
{digit}									{ yylval.int_val = atoi(yytext); return DIGIT_TOK; }
{slash}									{ yylval.opt_val = new std::string(yytext); return SLASH_TOK; }
{dot}										{ yylval.opt_val = new std::string(yytext); return DOT_TOK; }
{coma}									{ yylval.opt_val = new std::string(yytext); return COMA_TOK; }
{colon}									{ yylval.opt_val = new std::string(yytext); return COLON_TOK; }
{semicolon}							{ yylval.opt_val = new std::string(yytext); return SEMI_COLON_TOK; }
{l_bracket}							{ yylval.opt_val = new std::string(yytext); return LEFT_BRACKET_TOK; }
{r_bracket}							{ yylval.opt_val = new std::string(yytext); return RIGHT_BRACKET_TOK; }
{l_parenthesis}					{ yylval.opt_val = new std::string(yytext); return LEFT_PARENTHESIS_TOK; }
{r_parenthesis}					{ yylval.opt_val = new std::string(yytext); return RIGHT_PARENTHESIS_TOK; }
{l_brace}								{ yylval.opt_val = new std::string(yytext); return LEFT_BRACE_TOK; }
{r_brace}								{ yylval.opt_val = new std::string(yytext); return RIGHT_BRACE_TOK; }
.												{ std::cerr << "SCANNER "; yyerror(""); exit(1);	}
%%

