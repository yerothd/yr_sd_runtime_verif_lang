/**
 * @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUNDOU
 *
 * 		YR_SPEC_STMT_MEALY_AUTOMATON.cpp
 */


#include "YR_SPEC_STMT_MEALY_AUTOMATON.hpp"

#include "yr_sd_runtime_verif/YR_CPP_MONITOR_EDGE.hpp"
#include "yr_sd_runtime_verif/YR_CPP_MONITOR.hpp"


const QString YR_SPEC_STMT_MEALY_AUTOMATON::IN_SET_TRACE_ID_TOKEN("in_set_trace");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::IN_SQL_EVENT_LOG_ID_TOKEN("in_sql_event_log");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_SET_TRACE_ID_TOKEN("not_in_set_trace");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_SQL_EVENT_LOG_ID_TOKEN("not_in_sql_event_log");


const QString YR_SPEC_STMT_MEALY_AUTOMATON::IN_BEFORE_ID_TOKEN("IN_BEFORE");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_BEFORE_ID_TOKEN("NOT_IN_BEFORE");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::IN_AFTER_ID_TOKEN("IN_AFTER");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_AFTER_ID_TOKEN("NOT_IN_AFTER");


const QString YR_SPEC_STMT_MEALY_AUTOMATON::IN_PRE_ID_TOKEN("IN_PRE");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_PRE_ID_TOKEN("NOT_IN_PRE");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::IN_POST_ID_TOKEN("IN_POST");

const QString YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_POST_ID_TOKEN("NOT_IN_POST");


/*
 * ALL TOKEN DEFINED HERE ALIASES TOGETHER TO THE SAME MEANING.
 */
const QList<QString> YR_SPEC_STMT_MEALY_AUTOMATON::in_set_trace_ID_TOKEN =
{
	IN_SET_TRACE_ID_TOKEN,			// 0
	IN_SQL_EVENT_LOG_ID_TOKEN		// 1
};


/*
 * ALL TOKEN DEFINED HERE ALIASES TOGETHER TO THE SAME MEANING.
 */
const QList<QString> YR_SPEC_STMT_MEALY_AUTOMATON::not_in_set_trace_ID_TOKEN =
{
	NOT_IN_SET_TRACE_ID_TOKEN,			// 0
	NOT_IN_SQL_EVENT_LOG_ID_TOKEN		// 1
};



YR_SPEC_STMT_MEALY_AUTOMATON::YR_SPEC_STMT_MEALY_AUTOMATON()
:_PROCESS_notinset_set_TRACE_SPECIFICATION(false),
 _set_notinset_INSET_trace(false),
 _CURRENTLY_WITHIN_TRACE_SPECIFICATION(false),
 _is_LAST_YR_PARSER_EVENT_method_call(false),
 _print_dot_file_WITH_SQL_EVENT_LOG(true)
{
    _a_monitor_mealy_machine = YR_CPP_MONITOR::CREATE_MONITOR();
}


YR_SPEC_STMT_MEALY_AUTOMATON::~YR_SPEC_STMT_MEALY_AUTOMATON()
{
	DELETE_POINTER_YR_NOT_NULL(_a_monitor_mealy_machine);
}


void YR_SPEC_STMT_MEALY_AUTOMATON::set_current_TRACE_SPECIFICATION_ID_TOKEN(const char *current_trace_SPECIFICATION_ID)
{
	_current_TRACE_SPECIFICATION_ID_TOKEN = QString(current_trace_SPECIFICATION_ID);


	// ############ CONFIGURATION FOR PRINTING #############
	static bool first_time = true;

	if (first_time)
	{
		if ( YR_CPP_UTILS::isEqualsCaseInsensitive(_current_TRACE_SPECIFICATION_ID_TOKEN,
					NOT_IN_SQL_EVENT_LOG_ID_TOKEN) ||
				 YR_CPP_UTILS::isEqualsCaseInsensitive(_current_TRACE_SPECIFICATION_ID_TOKEN,
					IN_SQL_EVENT_LOG_ID_TOKEN) )
		{
			_print_dot_file_WITH_SQL_EVENT_LOG = true;
		}
		else
		{
			_print_dot_file_WITH_SQL_EVENT_LOG = false;
		}

		first_time = false;
	}
	// ######################################################
}


void YR_SPEC_STMT_MEALY_AUTOMATON::SET_not_in_set_trace()
{
	_PROCESS_notinset_set_TRACE_SPECIFICATION = true;

	//'false' means THIS IS a 'not_in_set_trace' specification
	_set_notinset_INSET_trace = false;
}


void YR_SPEC_STMT_MEALY_AUTOMATON::SET_in_set_trace()
{
	_PROCESS_notinset_set_TRACE_SPECIFICATION = true;

	//'true' means THIS IS an 'in_set_trace' specification
	_set_notinset_INSET_trace = true;
}


void YR_SPEC_STMT_MEALY_AUTOMATON::
		process_inside_algebra_set_specification(const char *IN_PRE_tok__or__IN_POST_tok,
																						 const char *prog_variable,
																						 const char *db_table,
																						 const char *db_column)
{
	YR_CPP_MONITOR_STATE *_current_state =
			_a_monitor_mealy_machine->find_yr_monitor_state(_CURRENT_state_name);

	assert (0 != _current_state);


	QString DB_TABLE__db_column = QString(db_table);

	DB_TABLE__db_column.append(".").append(QString(db_column));


	QString in_pre__OR__in_post = QString(IN_PRE_tok__or__IN_POST_tok);

	if (YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::IN_BEFORE_ID_TOKEN,
																				  in_pre__OR__in_post)															||
			YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::IN_PRE_ID_TOKEN,
																				  in_pre__OR__in_post))
	{
		_current_state->set_PRE_CONDITION_IN(QString(prog_variable), DB_TABLE__db_column);
	}
	else if (YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::IN_AFTER_ID_TOKEN,
																				 		  in_pre__OR__in_post) 														||
					 YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::IN_POST_ID_TOKEN,
																				 		  in_pre__OR__in_post))
	{
		_current_state->set_POST_CONDITION_IN(QString(prog_variable), DB_TABLE__db_column);
	}
}


void YR_SPEC_STMT_MEALY_AUTOMATON::
	process_not_inside_algebra_set_specification(const char *notIN_PRE_tok__or__notIN_POST_tok,
																							 const char *prog_variable,
																							 const char *db_table,
																							 const char *db_column)
{
	YR_CPP_MONITOR_STATE *_current_state =
			_a_monitor_mealy_machine->find_yr_monitor_state(_CURRENT_state_name);

	assert (0 != _current_state);


	QString DB_TABLE__db_column = QString(db_table);

	DB_TABLE__db_column.append(".").append(QString(db_column));


	QString NOTin_pre__OR__NOTin_post = QString(notIN_PRE_tok__or__notIN_POST_tok);

	if (YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_BEFORE_ID_TOKEN,
																				  NOTin_pre__OR__NOTin_post)													 ||
			YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_PRE_ID_TOKEN,
																				  NOTin_pre__OR__NOTin_post))
	{
		_current_state->set_PRE_CONDITION_notIN(QString(prog_variable), DB_TABLE__db_column);
	}
	else if (YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_AFTER_ID_TOKEN,
																				 		   NOTin_pre__OR__NOTin_post)													||
					 YR_CPP_UTILS::isEqualsCaseSensitive(YR_SPEC_STMT_MEALY_AUTOMATON::NOT_IN_POST_ID_TOKEN,
																				 		   NOTin_pre__OR__NOTin_post))
	{
		_current_state->set_POST_CONDITION_notIN(QString(prog_variable), DB_TABLE__db_column);
	}
}


YR_CPP_MONITOR_EDGE *YR_SPEC_STMT_MEALY_AUTOMATON::_process_edge_creation_()
{
	if (is_CURRENTLY_WORKING_TRACE_SPECIFICATION())
	{
		return 0;
	}


	YR_CPP_MONITOR_EDGE *A_RESULTING_CREATED_EDGE = 0;

	if (_is_LAST_YR_PARSER_EVENT_method_call)
	{
		A_RESULTING_CREATED_EDGE =
			_a_monitor_mealy_machine->create_yr_monitor_edge(_PREVIOUS_state_name,
																											 _CURRENT_state_name,
																											 _last_EVENT_METHOD_CALL_name);

		if (0 != A_RESULTING_CREATED_EDGE)
		{
			bool an_edge_was_created = (0 != A_RESULTING_CREATED_EDGE);

			if (_PROCESS_notinset_set_TRACE_SPECIFICATION)
			{
				YR_CPP_notinset_inset_TRACE_expression *A_NOTINSET_inset__trace_expression
					= new YR_CPP_notinset_inset_TRACE_expression(_set_notinset_INSET_trace,
																						 					 _current_TRACE_SPECIFICATION_EVENT_TOKEN,
																						 					 _current_TRACE_SPECIFICATION_state_name);

				A_RESULTING_CREATED_EDGE->set_GUARDED_CONDITION(A_NOTINSET_inset__trace_expression);


				QDEBUG_STRING_OUTPUT_2(QString("[_process_edge_creation_] an edge (%1 -> [%2(%3, %4)] True/%5 -> %6) is created")
															.arg(_PREVIOUS_state_name,
																	 _current_TRACE_SPECIFICATION_ID_TOKEN,
																	 _current_TRACE_SPECIFICATION_EVENT_TOKEN,
																	 _current_TRACE_SPECIFICATION_state_name,
																	 _last_EVENT_METHOD_CALL_name,
																 	 _CURRENT_state_name),
														 			 BOOL_TO_STRING(an_edge_was_created));


				_PROCESS_notinset_set_TRACE_SPECIFICATION = false;

				_current_TRACE_SPECIFICATION_ID_TOKEN.clear();

				_current_TRACE_SPECIFICATION_EVENT_TOKEN.clear();

				_current_TRACE_SPECIFICATION_state_name.clear();

			}
			else
			{
				QDEBUG_STRING_OUTPUT_2(QString("[_process_edge_creation_] an edge (%1 -> True/%2 -> %3) is created")
																.arg(_PREVIOUS_state_name,
																		 _last_EVENT_METHOD_CALL_name,
																	 	 _CURRENT_state_name),
															 			 BOOL_TO_STRING(an_edge_was_created));
			}
		}
	}

	return A_RESULTING_CREATED_EDGE;
}


/* processing edges methods */
void YR_SPEC_STMT_MEALY_AUTOMATON::process_event_call(const char *STRING_TOK)
{
	if (is_CURRENTLY_WORKING_TRACE_SPECIFICATION())
	{
		set_current_TRACE_SPECIFICATION_EVENT_TOKEN(STRING_TOK);

		_is_LAST_YR_PARSER_EVENT_method_call = false;

		return ;
	}

	_is_LAST_YR_PARSER_EVENT_method_call = true;

	YR_PARSER_SET_last_EVENT_METHOD_CALL_name(STRING_TOK);

	QDEBUG_STRING_OUTPUT_2("[process_event_call] STRING_TOK", STRING_TOK);
}


void YR_SPEC_STMT_MEALY_AUTOMATON::
			PROCESS_recovery_sql_query_spec(const char *DB_TABLE_STRING_TOK,
																			const char *RECOVERY_SQL_QUERY_TOK)
{
	QString SQL_recovery_query_string = RECOVERY_SQL_QUERY_TOK;
	
	QString db_table = DB_TABLE_STRING_TOK;


	//QDEBUG_STRING_OUTPUT_2("[PROCESS_recovery_sql_query_spec] * SQL_recovery_query_string: ",
	//												SQL_recovery_query_string);
	
	//QDEBUG_STRING_OUTPUT_2("[PROCESS_recovery_sql_query_spec] db_table: ",
	//												db_table);

	
	YR_CPP_MONITOR_STATE * A_PREVIOUS_STATE_instance = 0;

	YR_CPP_MONITOR_STATE * A_CURRENT_ERROR_ACCEPTING_STATE_instance = 0;

	for (unsigned k = 0; k < _all_final_state_LEADING_edges.size(); ++k)
	{
		YR_CPP_MONITOR_EDGE *an_final_leading_edge =
			_all_final_state_LEADING_edges.at(k);

		if (0 != an_final_leading_edge)
		{
			A_CURRENT_ERROR_ACCEPTING_STATE_instance = 
					an_final_leading_edge->get_TARGET_STATE();

			if (0 != A_CURRENT_ERROR_ACCEPTING_STATE_instance)
			{
				if (YR_CPP_UTILS::isEqualsCaseInsensitive
							(A_CURRENT_ERROR_ACCEPTING_STATE_instance->get_MONITOR_STATE_NAME(),
							 _CURRENT_state_name))
				{
					A_PREVIOUS_STATE_instance = an_final_leading_edge->get_SOURCE_STATE();
				}
			}
		}	
	}


	if (0 != A_CURRENT_ERROR_ACCEPTING_STATE_instance)
	{
		A_CURRENT_ERROR_ACCEPTING_STATE_instance
			->Set_SQL_RECOVERY_QUERY_STRING(SQL_recovery_query_string);
	}


	if (0 !=  A_PREVIOUS_STATE_instance)
	{
		QDEBUG_STRING_OUTPUT_1("[PROCESS_recovery_sql_query_spec] Calling set_Recovery_action");

		_a_monitor_mealy_machine
			->set_Recovery_action(A_PREVIOUS_STATE_instance,
														A_CURRENT_ERROR_ACCEPTING_STATE_instance);
	}
}


/* PROCESSING STATES METHODS */
void YR_SPEC_STMT_MEALY_AUTOMATON::PROCESS_STATE_spec(const char *STATE_TOK)
{
	_CURRENT_state_name = STATE_TOK;

	if (is_CURRENTLY_WORKING_TRACE_SPECIFICATION())
	{
		_current_TRACE_SPECIFICATION_state_name = _CURRENT_state_name;
	}

	if (0 != _a_monitor_mealy_machine)
	{
		YR_CPP_MONITOR_STATE * A_STATE =
			_a_monitor_mealy_machine->create_yr_monitor_state(STATE_TOK);


		_ALL_STATE_NAME__to__Monitor_State_Instance
				.insert(_CURRENT_state_name,
								A_STATE);


		if (!is_CURRENTLY_WORKING_TRACE_SPECIFICATION())
		{
			QDEBUG_STRING_OUTPUT_2("[PROCESS_STATE_spec] (previous) STATE_TOK", _PREVIOUS_state_name);
			QDEBUG_STRING_OUTPUT_2("[PROCESS_STATE_spec] (current) STATE_TOK", _CURRENT_state_name);

			_process_edge_creation_();

      YR_PARSER_SET_PREVIOUS_state_name(STATE_TOK);
		}

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


		if (!is_CURRENTLY_WORKING_TRACE_SPECIFICATION())
		{
			YR_CPP_MONITOR_EDGE *a_resulting_edge = _process_edge_creation_();

			if (0 != a_resulting_edge)
			{
				_all_final_state_LEADING_edges.append(a_resulting_edge);
			}
		}

		YR_PARSER_SET_PREVIOUS_state_name(FINAL_STATE_TOK);
		
		QDEBUG_STRING_OUTPUT_2("[PROCESS_FINAL_STATE_spec] (previous) STATE_TOK", _PREVIOUS_state_name);
		QDEBUG_STRING_OUTPUT_2("[PROCESS_FINAL_STATE_spec] (current) STATE_TOK", _CURRENT_state_name);

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
			A_START_STATE->set_START_STATE(*_a_monitor_mealy_machine, true);
		}

		if (!is_CURRENTLY_WORKING_TRACE_SPECIFICATION())
		{
			_process_edge_creation_();
		}

		YR_PARSER_SET_PREVIOUS_state_name(START_STATE_TOK);
		
		QDEBUG_STRING_OUTPUT_2("[PROCESS_START_STATE_spec] (previous) STATE_TOK", _PREVIOUS_state_name);
		QDEBUG_STRING_OUTPUT_2("[PROCESS_START_STATE_spec] (current) STATE_TOK", _CURRENT_state_name);

		QDEBUG_STRING_OUTPUT_2("[PROCESS_START_STATE_spec] START_STATE_TOK", _PREVIOUS_state_name);
	}

	_is_LAST_YR_PARSER_EVENT_method_call = false;
}


void YR_SPEC_STMT_MEALY_AUTOMATON::
	PROCESS_mealy_automaton_spec(const char *YR_SD_MEALY_AUTOMATON_SPEC_name)
{
	if (0 != _a_monitor_mealy_machine)
	{
     QString YR_SD_MEALY_AUTOMATON_SPEC_name__string =
			 	QString(YR_SD_MEALY_AUTOMATON_SPEC_name);

		_a_monitor_mealy_machine
            ->set_RUNTIME_MONITOR_NAME(YR_SD_MEALY_AUTOMATON_SPEC_name__string);


		YR_CPP_MONITOR_STATE *A_SOURCE_state = 0;
		YR_CPP_MONITOR_STATE *A_TARGET_state = 0;		
		YR_CPP_MONITOR_EDGE *A_FINAL_STATE_leading_edge = 0;
		for (uint i = 0; i < _all_final_state_LEADING_edges.size(); ++i)
		{
			A_FINAL_STATE_leading_edge = _all_final_state_LEADING_edges.at(i);

			if (0 != A_FINAL_STATE_leading_edge)
			{
				A_SOURCE_state = A_FINAL_STATE_leading_edge->get_SOURCE_STATE();
				A_TARGET_state = A_FINAL_STATE_leading_edge->get_TARGET_STATE();
			
				if (0 != A_SOURCE_state &&
						0 != A_TARGET_state)
				{
					_a_monitor_mealy_machine->set_Recovery_action(A_SOURCE_state,
																												A_TARGET_state);
				}				
			}
		}


    bool yr_view_pdf_file = false;

		_a_monitor_mealy_machine
            ->print_TO_dot_FILE(_print_dot_file_WITH_SQL_EVENT_LOG,
                                yr_view_pdf_file);


		_a_monitor_mealy_machine
            ->YR_generate_cplusplus_headers_files__AND__SAVE__TO__DISK
                (QString("%1-GENERATED.hpp")
                    .arg(YR_SD_MEALY_AUTOMATON_SPEC_name__string),
                 YR_SD_MEALY_AUTOMATON_SPEC_name__string);


        //YR_SD_MEALY_AUTOMATON_SPEC_name__string represents a class name
		_a_monitor_mealy_machine
            ->YR_generate_cplusplus_sources_files__AND__SAVE__TO__DISK
                (QString("%1-GENERATED.cpp")
                    .arg(YR_SD_MEALY_AUTOMATON_SPEC_name__string),
                 YR_SD_MEALY_AUTOMATON_SPEC_name__string);


		QDEBUG_STRING_OUTPUT_2("[PROCESS_mealy_automaton_spec] YR_SD_MEALY_AUTOMATON_SPEC_name",
				_a_monitor_mealy_machine->get_RUNTIME_MONITOR_NAME());


        _a_monitor_mealy_machine
            ->save_yr_SOURCE_FILES("outputted_SD_MEALY_MACHINE_NAME.txt",
                                   YR_SD_MEALY_AUTOMATON_SPEC_name__string);
	}

	_is_LAST_YR_PARSER_EVENT_method_call = false;
}




