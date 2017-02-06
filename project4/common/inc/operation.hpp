#if !defined(GUARD_operation_hpp20091210_)
#define GUARD_operation_hpp20091210_

/** @file: operation.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.1.1
	@date 2012-11-13
	@note Compiles under Visaul C++ v110
	@brief Operation class declaration.
	*/


#include "operand.hpp"
#include <stack>


/** Operation token base class. */
class Operation : public Token {
public:
	DEF_POINTER_TYPE(Operation)

	virtual unsigned number_of_args() const = 0;
	virtual Operand::pointer_type perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) = 0;

	class XOperation : public std::exception {
	public:
		XOperation(char const* msg): std::exception(msg) { }
	};
		/** Cannot perform exception class. */
		class XPerform : public XOperation {
		public:
			XPerform(std::string msg) : XOperation(("Error: Cannot perform: <" + msg + ">").c_str()) { }
		};
		/** Cannot convert exception class. */
		class XConvert: public XOperation {
		public:
			XConvert(std::string msg) : XOperation(("Cannot convert: <" + msg + ">").c_str()) { }
		};
		/** Insufficient parameter exception class. */
		class XParameter : public XOperation {
		public:
			XParameter(std::string msg) : XOperation(("Error: insufficient parameters to <" + msg + ">").c_str()) { }
		};
		/** variable exception class. */
		class XVariable : public XOperation {
		public:
			XVariable(std::string msg) : XOperation(("Error: variable not initialized <" + msg + ">").c_str()) { }
		};
		/** result index type exception class. */
		class XResultIndex : public XOperation {
		public:
			XResultIndex(std::string msg) : XOperation(("The type of <" + msg + "> can NOT be the index for variables. \nThe number of index for result should be a Integer. \nThis exception was found by Bill. Thank you Bill.").c_str()) { }
		};
		/** result index range exception class. */
		class XResultRange : public XOperation {
		public:
			XResultRange(std::string msg) : XOperation(("Error: Index for <" + msg + "> is out of range").c_str()) { }
		};
		/** factorial exception class. */
		class XNegativeArg : public XOperation {
		public:
			XNegativeArg(std::string msg) : XOperation(("Operater <" + msg + "> can Not have negative argument.").c_str()) { }
		};
		/** outofday exception class. */
		class XDayInMonth : public XOperation {
		public:
			XDayInMonth(std::string msg) : XOperation(("Operater <" + msg + ">: Inputed day is greater than last day in that month.").c_str()) { }
		};
};




/*=============================================================

Revision History
Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.1.1: 2012-11-13
C++ cleanup.

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

Version 0.0.0: 2009-12-10
Alpha release.

=============================================================

Copyright Garth Santor/Trinh Han

The copyright to the computer program(s) herein
is the property of Garth Santor/Trinh Han of Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor/Trinh Han
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/
#endif // GUARD_operation_hpp20091210_
