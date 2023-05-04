
#ifndef _YR_SPEC_STMT_MEALY_AUTOMATON_HPP_
#define _YR_SPEC_STMT_MEALY_AUTOMATON_HPP_


/**
 * @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 *
 * 		YR_SPEC_STMT_MEALY_AUTOMATON.hpp
 */


#include <QtCore/QString>



class YR_CPP_MONITOR_EDGE;
class YR_CPP_MONITOR_STATE;
class YR_CPP_MONITOR;


class YR_SPEC_STMT_MEALY_AUTOMATON
{
	public:
		
		YR_SPEC_STMT_MEALY_AUTOMATON();

		virtual ~YR_SPEC_STMT_MEALY_AUTOMATON();


		/* processing trace specification methods */

		inline virtual bool is_CURRENTLY_WORKING_TRACE_SPECIFICATION()
		{
			return _CURRENTLY_WITHIN_TRACE_SPECIFICATION;
		}
		
		inline virtual void set_TRACE_SPECIFICATION(bool a_boolean_value)
		{
			_CURRENTLY_WITHIN_TRACE_SPECIFICATION = a_boolean_value;
		}


		/* processing edges methods */

		virtual void _process_edge_creation_();
		
		virtual void process_event_method_call(const char *STRING_TOK);
	
		
		/* PROCESSING STATES METHODS */	
		virtual void PROCESS_STATE_spec(const char *START_STATE_TOK);
		
		virtual void PROCESS_FINAL_STATE_spec(const char *START_STATE_TOK);
		
		virtual void PROCESS_START_STATE_spec(const char *START_STATE_TOK);
		

		virtual void PROCESS_mealy_automaton_spec(const char *YR_SD_MEALY_AUTOMATON_SPEC_TOK);

	protected:

		inline virtual void YR_PARSER_SET_last_EVENT_METHOD_CALL_name(const char *last_EVENT_METHOD_CALL_name)
		{
			_last_EVENT_METHOD_CALL_name = QString(last_EVENT_METHOD_CALL_name).replace("'", "");
		}

		inline virtual void YR_PARSER_SET_PREVIOUS_state_name (const char *a_PREVIOUS_state_name)
		{
			_PREVIOUS_state_name = QString(a_PREVIOUS_state_name);
		}


		bool _CURRENTLY_WITHIN_TRACE_SPECIFICATION;

		bool _is_LAST_YR_PARSER_EVENT_method_call;


		QString _last_EVENT_METHOD_CALL_name;
		
		
		QString _CURRENT_state_name;
		QString _PREVIOUS_state_name;


		YR_CPP_MONITOR *_a_monitor_mealy_machine;
};


#define DELETE_POINTER_YR_NOT_NULL(P)\
{\
	if (0 != P) {	\
		delete P; 	\
	}				\
}




#endif //_YR_SPEC_STMT_MEALY_AUTOMATON_HPP_
