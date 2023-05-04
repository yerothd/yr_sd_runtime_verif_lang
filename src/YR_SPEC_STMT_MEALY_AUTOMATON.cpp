/**
 * @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 *
 * 		YR_SPEC_STMT_MEALY_AUTOMATON.cpp
 */


#include "YR_SPEC_STMT_MEALY_AUTOMATON.hpp"


#include "yr_sd_runtime_verif/YR_CPP_MONITOR_EDGE.hpp"
#include "yr_sd_runtime_verif/YR_CPP_MONITOR_STATE.hpp"
#include "yr_sd_runtime_verif/YR_CPP_MONITOR.hpp"



YR_SPEC_STMT_MEALY_AUTOMATON::YR_SPEC_STMT_MEALY_AUTOMATON()
:_CURRENTLY_WITHIN_TRACE_SPECIFICATION(false),
 _is_LAST_YR_PARSER_EVENT_method_call(false)
{
    _a_monitor_mealy_machine = YR_CPP_MONITOR::CREATE_MONITOR();	
}


YR_SPEC_STMT_MEALY_AUTOMATON::~YR_SPEC_STMT_MEALY_AUTOMATON()
{
	DELETE_POINTER_YR_NOT_NULL(_a_monitor_mealy_machine);
}


void YR_SPEC_STMT_MEALY_AUTOMATON::_process_edge_creation_()
{
	if (is_CURRENTLY_WORKING_TRACE_SPECIFICATION())
	{
		return ;
	}

	if (_is_LAST_YR_PARSER_EVENT_method_call)
	{
		YR_CPP_MONITOR_EDGE *A_RESULTING_CREATED_EDGE = 
			_a_monitor_mealy_machine->create_yr_monitor_edge(_PREVIOUS_state_name,
																											 _CURRENT_state_name,
																											 _last_EVENT_METHOD_CALL_name);
		
		if (0 != A_RESULTING_CREATED_EDGE)
		{
			bool an_edge_was_created = (0 != A_RESULTING_CREATED_EDGE);

			QDEBUG_STRING_OUTPUT_2(QString("[_process_edge_creation_] an edge (%1 -> True/'%2' -> %3) is created")
															.arg(_PREVIOUS_state_name,
																	 _last_EVENT_METHOD_CALL_name,
																 	 _CURRENT_state_name), 
														 BOOL_TO_STRING(an_edge_was_created));
			}
		}
}


/* processing edges methods */
void YR_SPEC_STMT_MEALY_AUTOMATON::process_event_method_call(const char *STRING_TOK)
{
	_is_LAST_YR_PARSER_EVENT_method_call = true;	
	
	YR_PARSER_SET_last_EVENT_METHOD_CALL_name(STRING_TOK);
		
	QDEBUG_STRING_OUTPUT_2("[process_event_method_call] STRING_TOK", STRING_TOK);
}


/* PROCESSING STATES METHODS */
void YR_SPEC_STMT_MEALY_AUTOMATON::PROCESS_STATE_spec(const char *STATE_TOK)
{
	_CURRENT_state_name = STATE_TOK;
	
	if (0 != _a_monitor_mealy_machine)
	{
		YR_CPP_MONITOR_STATE * A_STATE = 
			_a_monitor_mealy_machine->create_yr_monitor_state(STATE_TOK);

		_process_edge_creation_();

		YR_PARSER_SET_PREVIOUS_state_name(STATE_TOK);


		QDEBUG_STRING_OUTPUT_2("[PROCESS_STATE_spec] STATE_TOK", _PREVIOUS_state_name);
	}
	
	_is_LAST_YR_PARSER_EVENT_method_call = false;
}


void YR_SPEC_STMT_MEALY_AUTOMATON::PROCESS_FINAL_STATE_spec(const char *FINAL_STATE_TOK)
{
	_CURRENT_state_name = FINAL_STATE_TOK;
	
	if (0 != _a_monitor_mealy_machine)
	{
		YR_CPP_MONITOR_STATE * A_FINAL_STATE = 
			_a_monitor_mealy_machine->create_yr_monitor_state(FINAL_STATE_TOK);

		if (0 != A_FINAL_STATE)
		{
			A_FINAL_STATE->set_FINAL_STATE(true);
		}

		_process_edge_creation_();
		
		YR_PARSER_SET_PREVIOUS_state_name(FINAL_STATE_TOK);
		
		
		QDEBUG_STRING_OUTPUT_2_N("[PROCESS_FINAL_STATE_spec] state count", 
														 _a_monitor_mealy_machine->YR_CPP_monitor_state_count());	
		
		QDEBUG_STRING_OUTPUT_2("[PROCESS_FINAL_STATE_spec] FINAL_STATE_TOK", _PREVIOUS_state_name);
	}
		
	_is_LAST_YR_PARSER_EVENT_method_call = false;	
}


void YR_SPEC_STMT_MEALY_AUTOMATON::PROCESS_START_STATE_spec(const char *START_STATE_TOK)
{
	_CURRENT_state_name = START_STATE_TOK;

	if (0 != _a_monitor_mealy_machine)
	{
		YR_CPP_MONITOR_STATE * A_START_STATE = 
			_a_monitor_mealy_machine->create_yr_monitor_state(START_STATE_TOK);

		if (0 != A_START_STATE)
		{
			A_START_STATE->set_START_STATE(true);
		}

		_process_edge_creation_();	
		
		YR_PARSER_SET_PREVIOUS_state_name(START_STATE_TOK);
		

		QDEBUG_STRING_OUTPUT_2("[PROCESS_START_STATE_spec] START_STATE_TOK", _PREVIOUS_state_name);
	}
		
	_is_LAST_YR_PARSER_EVENT_method_call = false;
}


void YR_SPEC_STMT_MEALY_AUTOMATON::
	PROCESS_mealy_automaton_spec(const char *YR_SD_MEALY_AUTOMATON_SPEC_TOK)
{
	if (0 != _a_monitor_mealy_machine)
	{
		_a_monitor_mealy_machine->set_RUNTIME_MONITOR_NAME(QString(YR_SD_MEALY_AUTOMATON_SPEC_TOK));
	

		_a_monitor_mealy_machine->
			YR_generate_cplusplus_headers_files(QString("%1.hpp")
																						.arg(_a_monitor_mealy_machine->get_RUNTIME_MONITOR_NAME()));	
		_a_monitor_mealy_machine->
			YR_generate_cplusplus_sources_files(QString("%1.cpp")
																						.arg(_a_monitor_mealy_machine->get_RUNTIME_MONITOR_NAME()));
		

		QDEBUG_STRING_OUTPUT_2("[PROCESS_mealy_automaton_spec] YR_SD_MEALY_AUTOMATON_SPEC_TOK", 
				_a_monitor_mealy_machine->get_RUNTIME_MONITOR_NAME());
	}
	
	_is_LAST_YR_PARSER_EVENT_method_call = false;
}
