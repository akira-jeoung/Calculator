/** @file: parser.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visaul C++ v120

	@brief Parser class implementation.
	*/

/*
Bill Jeoung
2016-11-20
*/

#include "parser.hpp"
#include "function.hpp"
#include "operand.hpp"
#include "operator.hpp"
#include "pseudo_operation.hpp"
#include <stack>
#include <queue>
using namespace std;

TokenList Parser::parse(TokenList const& infixTokens) {

	// 1. Set output queue to empty
	stack<Token::pointer_type> stackOperation;

	// 2.	Set operation stack to empty.
	queue<Token::pointer_type> quePostfix;
		
	//3.	For each token in the input queue.
	for (auto x : infixTokens)
	{
		// the token is an operand --> append the token to the output queue.
		if (is<Operand>(x))
			quePostfix.push(x);

		//Else if the token is a function --> push the token on to the operation stack.
		else if (is<Function>(x))
			stackOperation.push(x);

		// else if the token is an argument separator 
		else if (is<ArgumentSeparator>(x))
		{
			// While the top meta-operation on the operation-stack is not a left parenthesis do,
				// pop the operation from the operation - stack
				// append that operation to the output queue.

			while (!stackOperation.empty() && !is<LeftParenthesis>(stackOperation.top()))
			{
				quePostfix.push(stackOperation.top());
				stackOperation.pop();
			}
		}
		
		// else if the token is an left parenthesis --> push the token on to the operation-stack.
		else if (is<LeftParenthesis>(x))
			stackOperation.push(x);

		// else if the token is a right parenthesis
		else if (is<RightParenthesis>(x))
		{
			//While the top meta-operation on the operation-stack is not a left parenthesis do,
				// pop the operation from the operation - stack.
				// append that operation to the output queue
			while (!stackOperation.empty() && !is<LeftParenthesis>(stackOperation.top()))
			{
				quePostfix.push(stackOperation.top());
				stackOperation.pop();
			}

			// If the operation-stack is empty --> exception “Right parenthesis, has no matching left parenthesis”
			if (stackOperation.empty())
				throw std::exception("Right parenthesis, has no matching left parenthesis");

			// Pop the left parenthesis from the operation-stack
			stackOperation.pop();

			// If the top of the operation-stack is a function
				// pop the function from the operation - stack
				// append that function to the output queue.
			if (!stackOperation.empty() && is<Function>(stackOperation.top()))
			{
				quePostfix.push(stackOperation.top());
				stackOperation.pop();
			}
		}

		// else if the token is an operator
		else if (is<Operator>(x))
		{
			// while the operation-stack is not empty 
			while (!stackOperation.empty())
			{
				// If the top of the operation-stack is not an operator --> exit the while loop
				if (!is<Operator>(stackOperation.top()))
					break;

				// If the token is a non-associative operator --> exit the while loop.
				if (!is<RAssocOperator>(x) && !is<LAssocOperator>(x))
					break;

				// If the token is a left-associative operator and has greater precedence than the top of the operation - stack --> exit the while loop
				if (is<LAssocOperator>(x) && convert<Operator>(x)->get_precedence() > convert<Operator>(stackOperation.top())->get_precedence())
					break;

				// If the token is a right-associative operator and has greater or equal precedence than the top of the operation - stack --> exit the while loop.
				if (is<RAssocOperator>(x) && convert<Operator>(x)->get_precedence() >= convert<Operator>(stackOperation.top())->get_precedence())
					break;

				// pop an operator from the top of the operation-stack.
				// append that operator to the output queue.
				quePostfix.push(stackOperation.top());
				stackOperation.pop();
			}
			// push the token on to the operation-stack
			stackOperation.push(x);
		}

		// else exception “Unknown token”.
		else
			throw std::exception("Unknown token");
	}

	// WHILE the operation stack is not empty 
	while (!stackOperation.empty())
	{
		// If the top of the operation stack is a left-parenthesis --> exception “Missing right - parenthesis”.
		if (is<LeftParenthesis>(stackOperation.top()))
			throw std::exception("Missing right-parenthesis");

		// pop an operator from the top of the operation-stack.
		// append that operator to the output queue
		quePostfix.push(stackOperation.top());
		stackOperation.pop();
	}
	
	// move tokens from queue to TokenList
	TokenList result;
	while (!quePostfix.empty())
	{
		result.push_back(quePostfix.front());
		quePostfix.pop();
	}
	return result;
}


/*=============================================================

Revision History
Version 1.0.0: 2014-10-31
Visual C++ 2013

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-02
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
