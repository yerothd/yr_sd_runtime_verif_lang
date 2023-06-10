
%{
#include "YR_HEADING.h"

void yr_printf(string a_val_str, const char *zeichen = "");

int yyerror(char *s);

int yylex(void);





YR_SPEC_STMT_MEALY_AUTOMATON *a_spec_stmt_ROOT; 

%}


%union{
  int		int_val;
  string*	opt_val;
}

%start	input 

%token	<opt_val>	YR_SD_MEALY_AUTOMATON_SPEC_TOK
%token	<opt_val>	RIGHT_ARROW_TOK
%token	<opt_val>	ALPHA_NUM_TOK
%token	<opt_val>	LEFT_BRACKET_TOK
%token	<opt_val>	RIGHT_BRACKET_TOK
%token	<opt_val>	LEFT_PARENTHESIS_TOK
%token	<opt_val>	RIGHT_PARENTHESIS_TOK
%token	<opt_val>	LEFT_BRACE_TOK
%token	<opt_val>	RIGHT_BRACE_TOK
%token	<opt_val>	SLASH_TOK
%token	<opt_val>	DOT_TOK
%token	<opt_val>	COLON_TOK
%token	<opt_val>	COMA_TOK
%token	<opt_val>	STRING_TOK
%token	<opt_val>	IN_SQL_EVENT_LOG_TOK
%token	<opt_val>	NOT_IN_SQL_EVENT_LOG_TOK
%token	<opt_val>	IN_SET_TRACE_TOK
%token	<opt_val>	NOT_IN_SET_TRACE_TOK
%token	<opt_val>	IN_PRE_TOK
%token	<opt_val>	IN_POST_TOK
%token	<opt_val>	NOT_IN_PRE_TOK
%token	<opt_val>	NOT_IN_POST_TOK
%token	<opt_val>	START_STATE_TOK
%token	<opt_val>	ERROR_STATE_TOK
%token	<opt_val>	FINAL_STATE_TOK
%token	<opt_val>	STATE_TOK

%type	<opt_val>	mealy_automaton_spec
%type	<opt_val>	state_property_specification
%type	<opt_val>	sut_edge_state_spec
%type	<opt_val>	algebra_set_specification
%type	<opt_val>	in_spec
%type	<opt_val>	not_in_spec
%type	<opt_val>	in_sql_event_log
%type	<opt_val>	in_set_trace
%type	<opt_val>	not_in_sql_event_log
%type	<opt_val>	not_in_set_trace
%type	<opt_val>	trace_specification
%type	<opt_val>	inside_algebra_set_specification
%type	<opt_val>	not_inside_algebra_set_specification
%type	<opt_val>	db_table
%type	<opt_val>	db_column
%type	<opt_val>	function_call
%type	<opt_val>	function_id
%type	<opt_val>	prog_variable
%type <opt_val> edge_mealy_automaton_guard_cond
%type	<opt_val>	sut_edge_mealy_automaton_spec
%type	<opt_val>	event_call

%left	COLON_TOK
%left	RIGHT_ARROW_TOK

%%

input : /* empty */
			| YR_SD_MEALY_AUTOMATON_SPEC_TOK ALPHA_NUM_TOK
					LEFT_BRACE_TOK 
						mealy_automaton_spec DOT_TOK	
					RIGHT_BRACE_TOK																																{ a_spec_stmt_ROOT->PROCESS_mealy_automaton_spec($2->c_str()); }
			;
mealy_automaton_spec : sut_state_spec 																									{ }
										 | sut_state_spec RIGHT_ARROW_TOK sut_edge_state_spec 							{ }
										 ;
sut_edge_state_spec : sut_edge_mealy_automaton_spec RIGHT_ARROW_TOK mealy_automaton_spec{ }
										;
sut_edge_mealy_automaton_spec : edge_mealy_automaton_guard_cond event_call				{ }
															;
edge_mealy_automaton_guard_cond : /* empty */ SLASH_TOK 
																| LEFT_BRACKET_TOK 																			{ a_spec_stmt_ROOT->set_CURRENTLY_WITHIN_TRACE_SPECIFICATION(true); }
																		trace_specification
																	RIGHT_BRACKET_TOK SLASH_TOK 													{ a_spec_stmt_ROOT->set_CURRENTLY_WITHIN_TRACE_SPECIFICATION(false); }
																; 																					
trace_specification : in_sql_event_log																									{ a_spec_stmt_ROOT->set_current_TRACE_SPECIFICATION_ID_TOKEN($1->c_str()); }
										| not_in_sql_event_log																							{ a_spec_stmt_ROOT->set_current_TRACE_SPECIFICATION_ID_TOKEN($1->c_str()); }
										| in_set_trace																											{ a_spec_stmt_ROOT->set_current_TRACE_SPECIFICATION_ID_TOKEN($1->c_str()); }
									 	| not_in_set_trace 																									{ a_spec_stmt_ROOT->set_current_TRACE_SPECIFICATION_ID_TOKEN($1->c_str()); }
										;	
in_sql_event_log : IN_SQL_EVENT_LOG_TOK																									{ yr_printf("in_sql_event_log"); a_spec_stmt_ROOT->SET_in_set_trace(); }
						 			LEFT_PARENTHESIS_TOK 
										event_call COMA_TOK state_property_specification
									RIGHT_PARENTHESIS_TOK																								
						 ;
in_set_trace : IN_SET_TRACE_TOK																													{ yr_printf("in_set_trace"); a_spec_stmt_ROOT->SET_in_set_trace(); }
						 			LEFT_PARENTHESIS_TOK 
										event_call COMA_TOK state_property_specification
									RIGHT_PARENTHESIS_TOK																								
						 ;
not_in_sql_event_log : NOT_IN_SQL_EVENT_LOG_TOK																					{ yr_printf("not_in_sql_event_log"); 
										 																																			a_spec_stmt_ROOT->SET_not_in_set_trace(); }
						 			LEFT_PARENTHESIS_TOK 
										event_call COMA_TOK state_property_specification 		
									RIGHT_PARENTHESIS_TOK																								 
								 ;
not_in_set_trace : NOT_IN_SET_TRACE_TOK																									{ yr_printf("not_in_set_trace"); a_spec_stmt_ROOT->SET_not_in_set_trace(); }
						 			LEFT_PARENTHESIS_TOK 
										event_call COMA_TOK state_property_specification 		
									RIGHT_PARENTHESIS_TOK																								 
								 ;
event_call : STRING_TOK 																																{ a_spec_stmt_ROOT->process_event_call($1->c_str()); }
					 ;
sut_state_spec : state_property_specification	COLON_TOK algebra_set_specification				{ }
							 | final_state_property_specification	COLON_TOK algebra_set_specification	{ }
							 | start_state_property_specification	COLON_TOK algebra_set_specification	{ }
							 | start_state_property_specification							 
							 ;
algebra_set_specification : inside_algebra_set_specification 														{ }
													| not_inside_algebra_set_specification												{ }
													;
in_spec : IN_PRE_TOK																																		{ }
				| IN_POST_TOK																																		{ }
				;
not_in_spec : NOT_IN_PRE_TOK																														{ }
						| NOT_IN_POST_TOK																														{ }
						;
inside_algebra_set_specification : in_spec 
																 		LEFT_PARENTHESIS_TOK 
																 			prog_variable COMA_TOK db_table DOT_TOK db_column 
																		RIGHT_PARENTHESIS_TOK																{ a_spec_stmt_ROOT->
																																														process_inside_algebra_set_specification($1->c_str(),
																																																																	   $3->c_str(),
																																																																		 $5->c_str(),
																																																																		 $7->c_str()); }
																 |
																	 in_spec 
																 		LEFT_PARENTHESIS_TOK 
																 			function_call COMA_TOK db_table DOT_TOK db_column 
																		RIGHT_PARENTHESIS_TOK																{ }
																 ;
not_inside_algebra_set_specification : not_in_spec
																		 		LEFT_PARENTHESIS_TOK 
																		 			prog_variable COMA_TOK db_table DOT_TOK db_column 
																				RIGHT_PARENTHESIS_TOK														{a_spec_stmt_ROOT->
																																														process_not_inside_algebra_set_specification($1->c_str(),
																																																																				 $3->c_str(),
																																																																		 		 $5->c_str(),
																																																																		 		 $7->c_str()); }
																		 |
																			 not_in_spec
																		 		LEFT_PARENTHESIS_TOK 
																		 			function_call COMA_TOK db_table DOT_TOK db_column 
																				RIGHT_PARENTHESIS_TOK
																		 ;
function_call : function_id LEFT_PARENTHESIS_TOK STRING_TOK RIGHT_PARENTHESIS_TOK
						  ;
function_id : ALPHA_NUM_TOK
						;
state_property_specification : STATE_TOK 
														 		LEFT_PARENTHESIS_TOK 
																	ALPHA_NUM_TOK 
																RIGHT_PARENTHESIS_TOK										{ yr_printf($3->c_str(), "state_property_specification");
																																					a_spec_stmt_ROOT->PROCESS_STATE_spec($3->c_str()); }
														 ;
final_state_property_specification :ERROR_STATE_TOK 
														 					LEFT_PARENTHESIS_TOK 
																				ALPHA_NUM_TOK 
																			RIGHT_PARENTHESIS_TOK							{ yr_printf($3->c_str(), "final_state_property_specification"); 
																																					a_spec_stmt_ROOT->PROCESS_FINAL_STATE_spec($3->c_str()); }
																	 | FINAL_STATE_TOK 
														 					LEFT_PARENTHESIS_TOK 
																				ALPHA_NUM_TOK 
																			RIGHT_PARENTHESIS_TOK							{ yr_printf($3->c_str(), "final_state_property_specification"); 
																																					a_spec_stmt_ROOT->PROCESS_FINAL_STATE_spec($3->c_str()); }
														 			 ;
start_state_property_specification : START_STATE_TOK 
														 					LEFT_PARENTHESIS_TOK 
																				ALPHA_NUM_TOK 
																			RIGHT_PARENTHESIS_TOK							{ yr_printf($3->c_str(), "start_state_property_specification"); 
																																					a_spec_stmt_ROOT->PROCESS_START_STATE_spec($3->c_str()); }
														 			 ;
prog_variable : ALPHA_NUM_TOK		{ }
				 ;
db_table : ALPHA_NUM_TOK				{ }
				 ;
db_column : ALPHA_NUM_TOK				{ }
					;
%%


void yr_printf(string a_val_str, const char *zeichen /* = "" */)
{
	static bool init_zeichen = true;

	if (init_zeichen)
	{
		a_spec_stmt_ROOT = new YR_SPEC_STMT_MEALY_AUTOMATON;

		init_zeichen = false;
	}
	
	extern char *yytext;	// defined and maintained in lex.c
	
	if (0 != yylval.opt_val)
	{
		printf("[%s] %s: %s\n", zeichen, a_val_str.c_str(), yylval.opt_val->c_str());
	}
}


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

