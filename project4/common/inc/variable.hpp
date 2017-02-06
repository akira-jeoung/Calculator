





#if !defined(GUARD_variable_hpp20091126_)
#define GUARD_variable_hpp20091126_

/** @file: variable.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visaul C++ v110

	@brief Variable class declaration.
	*/

#include <boost\multiprecision\cpp_int.hpp>
#include <boost\multiprecision\debug_adaptor.hpp>
#include "operand.hpp"


	/** Variable token. */
class Variable : public Operand {
public:
	using value_type = Operand::pointer_type;
	DEF_POINTER_TYPE(Variable)
	DEF_IS_CONVERTABLE_FROM(Variable)
private:
	value_type	value_;
public:
	Variable(value_type  value=0)
		: value_(value) { }

	value_type				get_value() const { return value_; }
	void					set_value(value_type const value)  { value_ = value; }
	string_type				to_string() const;	
};
		



/*=============================================================

Revision History

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

Version 0.0.0: 2009-11-26
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
#endif // GUARD_variable_hpp20091126_
