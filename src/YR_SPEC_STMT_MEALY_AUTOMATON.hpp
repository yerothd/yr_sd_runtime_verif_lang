
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
		
		inline virtual void set_CURRENTLY_WITHIN_TRACE_SPECIFICATION(bool a_boolean_value)
		{
			_CURRENTLY_WITHIN_TRACE_SPECIFICATION = a_boolean_value;
		}

		virtual void set_current_TRACE_SPECIFICATION_ID_TOKEN(const char *current_trace_SPECIFICATION_ID);
		
		inline virtual void set_current_TRACE_SPECIFICATION_EVENT_TOKEN(const char *current_trace_event)
		{
			_current_TRACE_SPECIFICATION_EVENT_TOKEN = QString(current_trace_event);
		}

		virtual void SET_not_in_set_trace();
		
		virtual void SET_in_set_trace();


		/* processing ALGEBRA SET SPECIFICATION methods */

		virtual void process_inside_algebra_set_specification(const char *IN_PRE_tok__or__IN_POST_tok,
																													const char *prog_variable,
																												  const char *db_table,
																													const char *db_column);

		virtual void process_not_inside_algebra_set_specification(const char *notIN_PRE_tok__or__notIN_POST_tok,
																														  const char *prog_variable,
																												  		const char *db_table,
																															const char *db_column);


		/* processing edges methods */

		virtual void _process_edge_creation_();
		
		virtual void process_event_call(const char *STRING_TOK);
	
		
		/* PROCESSING STATES METHODS */	
		virtual void PROCESS_STATE_spec(const char *START_STATE_TOK);
		
		virtual void PROCESS_FINAL_STATE_spec(const char *START_STATE_TOK);
		
		virtual void PROCESS_START_STATE_spec(const char *START_STATE_TOK);
		

		virtual void PROCESS_mealy_automaton_spec(const char *YR_SD_MEALY_AUTOMATON_SPEC_name);

	protected:

		inline virtual void YR_PARSER_SET_last_EVENT_METHOD_CALL_name(const char *last_EVENT_METHOD_CALL_name)
		{
			_last_EVENT_METHOD_CALL_name = QString(last_EVENT_METHOD_CALL_name);
		}

		inline virtual void YR_PARSER_SET_PREVIOUS_state_name (const char *a_PREVIOUS_state_name)
		{
			_PREVIOUS_state_name = QString(a_PREVIOUS_state_name);
		}


	

		static const QString IN_SET_TRACE_ID_TOKEN;

		static const QString IN_SQL_EVENT_LOG_ID_TOKEN;

		static const QString NOT_IN_SET_TRACE_ID_TOKEN;

		static const QString NOT_IN_SQL_EVENT_LOG_ID_TOKEN;	


		static const QString IN_BEFORE_ID_TOKEN;
		
		static const QString NOT_IN_BEFORE_ID_TOKEN;
		
		static const QString IN_AFTER_ID_TOKEN;
		
		static const QString NOT_IN_AFTER_ID_TOKEN;

	
		static const QString IN_PRE_ID_TOKEN;
		
		static const QString NOT_IN_PRE_ID_TOKEN;
		
		static const QString IN_POST_ID_TOKEN;
		
		static const QString NOT_IN_POST_ID_TOKEN;


		static const QList<QString> in_set_trace_ID_TOKEN;
		
		static const QList<QString> not_in_set_trace_ID_TOKEN;


		bool _PROCESS_notinset_set_TRACE_SPECIFICATION;
		
		bool _set_notinset_INSET_trace;

		bool _CURRENTLY_WITHIN_TRACE_SPECIFICATION;

		bool _is_LAST_YR_PARSER_EVENT_method_call;

		bool _print_dot_file_WITH_SQL_EVENT_LOG;


		QString _last_EVENT_METHOD_CALL_name;
		
		QString _current_TRACE_SPECIFICATION_ID_TOKEN;
		
		QString _current_TRACE_SPECIFICATION_EVENT_TOKEN;
		
		QString _current_TRACE_SPECIFICATION_state_name;
		
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
