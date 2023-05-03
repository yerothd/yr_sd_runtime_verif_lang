/**
 * @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 *
 * 		YR_SPEC_STMT_MEALY_AUTOMATON.cpp
 */


#include "YR_SPEC_STMT_MEALY_AUTOMATON.hpp"

#include "yr_sd_runtime_verif/YR_CPP_MONITOR.hpp"



YR_SPEC_STMT_MEALY_AUTOMATON::YR_SPEC_STMT_MEALY_AUTOMATON()
{
    _a_monitor_mealy_machine = YR_CPP_MONITOR::CREATE_MONITOR();	
}


YR_SPEC_STMT_MEALY_AUTOMATON::~YR_SPEC_STMT_MEALY_AUTOMATON()
{
	DELETE_POINTER_YR_NOT_NULL(_a_monitor_mealy_machine);
}


void YR_SPEC_STMT_MEALY_AUTOMATON::
	PROCESS_mealy_automaton_spec(const char *YR_SD_MEALY_AUTOMATON_SPEC_TOK)
{
	if (0 != _a_monitor_mealy_machine)
	{
		_a_monitor_mealy_machine->set_RUNTIME_MONITOR_NAME(QString(YR_SD_MEALY_AUTOMATON_SPEC_TOK));
	
		_a_monitor_mealy_machine->YR_generate_cplusplus_headers_files();
		
		_a_monitor_mealy_machine->YR_generate_cplusplus_sources_files();
		
		QDEBUG_STRING_OUTPUT_2("[PROCESS_mealy_automaton_spec] YR_SD_MEALY_AUTOMATON_SPEC_TOK", 
				_a_monitor_mealy_machine->get_RUNTIME_MONITOR_NAME());
	}
}
