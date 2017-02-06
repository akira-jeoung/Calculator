/** @file: RPNEvaluator.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.0.1
	@date 2012-11-13
	@note Compiles under Visaul C++ v110

	@brief RPN Evaluator class implementation.
	*/
/*
Bill Jeoung
5. Dec. 2016
*/


#include "RPNEvaluator.hpp"
#include "integer.hpp"
#include "real.hpp"
#include "boolean.hpp"
#include "operation.hpp"
#include "operator.hpp"
#include <cassert>
#include <stack>
static Integer::value_type c_Flag = 0;

Operand::pointer_type RPNEvaluator::evaluate(TokenList const& rpnExpression) {
	
	// Set operand stack to empty
	std::stack<Operand::pointer_type> operandStack;		
	std::vector<Operand::pointer_type> performOper;
	std::vector<unsigned> vecFlag;

	// For each token in the expression
	for (auto x : rpnExpression)
	{	
		// 3. if the token is an operand push it onto the operand stack
		if (is<Operand>(x))
		{
			operandStack.push(convert<Operand>(x));
			continue;
		}
		else
		{				
			unsigned numFlag = 0;
			unsigned boolFlag = 0;
			unsigned calenderFlag = 0, calenderFlag1 = 0;

			// if the operation’s number of arguments > the size of the operand stack --> exception
			if (convert<Operation>(x)->number_of_args() > operandStack.size())
				throw Operation::XParameter(typeid(*x).name() + 6);
						
			// pop operation's number of arguments from stack
			for (unsigned i = 0; i < convert<Operation>(x)->number_of_args(); ++i)
			{	
				unsigned isRealCal = 0;
				Operand::pointer_type op = operandStack.top();

				if (is<Variable>(op) && !is<Assignment>(x))
				{
					if (get_value<Variable>(op) == 0)
						throw Operation::XVariable(typeid(*op).name() + 6);
					op = get_value<Variable>(op);
				}			
				
				if (is<Real>(op))
				{			
					if (is<Jd>(op)) {
						numFlag += 100;
						if (is<Gregorian>(op)) numFlag += 100;
						else if (is<JulianC>(op)) numFlag += 300;
						else if (is<YearC>(op)) calenderFlag1 = 10;
						else if (is<MonthC>(op)) calenderFlag1 = 20;
					}
					else {
						numFlag = 1;
						isRealCal = 1;
						if (is<YearC>(op)) isRealCal = 10;
						else if (is<MonthC>(op)) isRealCal = 20;
					}
				}	
				if (is<Boolean>(op)) boolFlag += 2;

				performOper.push_back(op);

				vecFlag.push_back(isRealCal);
				operandStack.pop();
			}
			
			// convert operand in vector to real (if at least one operand is real 					
			if (numFlag==1 && !is<Assignment>(x))
			{
				for (unsigned i = 0; i < performOper.size(); ++i) {
					calenderFlag += vecFlag[i];
					if (vecFlag[i] == 0)
						performOper[i] = make_operand<Real>(static_cast<Real::value_type>(get_value<Integer>(performOper[i])));					
				}
			}

			if (boolFlag > numFlag) numFlag = boolFlag;
			numFlag += calenderFlag1;
			// perform the operation
			operandStack.push(convert<Operation>(x)->perform(performOper, numFlag));

			performOper.clear();
			vecFlag.clear();
			// push the result to stack 
			continue;
		}			
	}

	// if the operand stack has more than one element --> exception
	if (operandStack.size() > 1)
		throw std::exception("Error: too many operands");
	// if if stack is empty --> exception
	if (operandStack.empty())
		throw std::exception("Error: insufficient operands");
		
	// return answer	
	return operandStack.top();
}

/*=============================================================

Revision History

Version 0.0.1: 2012-11-13
C++ 11 cleanup

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
