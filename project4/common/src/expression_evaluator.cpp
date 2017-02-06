/** @file: expression_evaluator.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visaul C++ v110

	@brief ExpressionEvaluator class implementation.
	*/
/*
Bill Jeoung
2016-12-03
*/

#include "expression_evaluator.hpp"
#include "tokenizer.hpp"
#include "parser.hpp"
#include "RPNEvaluator.hpp"
#include "function.hpp"

#if defined(SHOW_STEPS)
#include <iostream>
#endif

ExpressionEvaluator::result_type ExpressionEvaluator::evaluate( ExpressionEvaluator::expression_type const& expr ) {

	auto result = rpn_.evaluate(parser_.parse(tokenizer_.tokenize(expr)));
	Result::resultVector.push_back(result);
	return result;
	
	// todo: everything
	//return make<Integer>();
}

/*=============================================================

Revision History

Version 0.0.0: 2010-10-31
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
