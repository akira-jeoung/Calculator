/** @file: ee_main.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2016-10-29
	@version 1.0.0
	@note Compiles under Visaul C++ v14

	@brief Expression Evaluator application.
	*/
/*
Bill Jeoung
2016-11-24
*/

#include "expression_evaluator.hpp"
#include "function.hpp"
#include "real.hpp"
#include "tokenizer.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <regex>
#include <sstream>
using namespace std;

int main() {
		
	cout << "Expression Evaluator, (c) 2016 B(youongG)ill Jeoung\n";
	ExpressionEvaluator ee;
	unsigned realPrecision = 10;

	for (unsigned count = 1; ; ) {
		cout << "> ";
		string command;
		if (!getline(cin, command) || command.empty())
			break;
		try
		{
			cout << "[" << count << "] = " << ee.evaluate(command) << endl;
			++count;
		}
		catch (Tokenizer::XNumericOverflow& ex)
		{
			cout << ex.what() << endl << ex.get_expression() << endl;
			for (unsigned i = 0; i < ex.get_location(); ++i) cout << ".";
			cout << "^" << endl;
		}
		catch (Tokenizer::XBadCharacter& ex)
		{
			cout << ex.what() << endl << ex.get_expression() << endl;
			for (unsigned i = 0; i < ex.get_location(); ++i) cout << ".";
			cout << "^" << endl;
		}
		catch (Operation::XPerform& ex)
		{
			cout << ex.what() << endl;
		}
		catch (Operation::XConvert& ex)
		{
			cout << ex.what() << endl;
		}
		catch (Operation::XParameter& ex)
		{
			cout << ex.what() << endl;
		}
		catch (Operation::XVariable& ex)
		{
			cout << ex.what() << endl;
		}
		catch (Operation::XResultIndex& ex)
		{
			cout << ex.what() << endl;

		}
		catch (Operation::XResultRange& ex)
		{
			cout << ex.what() << endl;
		}
		catch (Operation::XNegativeArg& ex)
		{
			cout << ex.what() << endl;
		}
		catch (Tokenizer::XTokenizer& ex)
		{
			cout << ex.what() << endl << ex.get_expression() << endl;
			for (unsigned i = 0; i < ex.get_location(); ++i) cout << ".";
			cout << "^" << endl;
		}
		catch (Operation::XOperation& ex)
		{
			cout << ex.what() << endl;
		}
		catch (exception& ex)
		{
			cout << ex.what() << endl;
		}
		catch (...)
		{
			cout << "error by undefined reason." << endl;
		}
	}
}

/*=============================================================

Revision History
Version 1.0.0: 2016-10-29
Added help command.

Version 0.1.0: 2014-11-27
Added: setp to set the real number precision.

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2010-11-23
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
