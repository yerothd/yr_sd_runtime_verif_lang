
#ifndef _YR_SPEC_STMT_MEALY_AUTOMATON_HPP_
#define _YR_SPEC_STMT_MEALY_AUTOMATON_HPP_


/**
 * @AUTEUR: DR.-ING. DIPL.-INF. XAVIER NOUMBISSI NOUNDOU
 *
 * 		YR_SPEC_STMT_MEALY_AUTOMATON.hpp
 */


class YR_CPP_MONITOR;


class YR_SPEC_STMT_MEALY_AUTOMATON
{
	public:
		
		YR_SPEC_STMT_MEALY_AUTOMATON();

		virtual ~YR_SPEC_STMT_MEALY_AUTOMATON();

		
		virtual void PROCESS_mealy_automaton_spec(const char *YR_SD_MEALY_AUTOMATON_SPEC_TOK);

	protected:

		YR_CPP_MONITOR *_a_monitor_mealy_machine;
};


#define DELETE_POINTER_YR_NOT_NULL(P)\
{\
	if (0 != P) {	\
		delete P; 	\
	}				\
}




#endif //_YR_SPEC_STMT_MEALY_AUTOMATON_HPP_
