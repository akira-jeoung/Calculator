/** @file: tokenizer.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 0.2.0
	@date 2012-11-16
	@note Compiles under Visaul C++ v110

	@brief Tokenizer class implementation.
	*/
/*
Bill Jeoung
2016-11-24
*/

#include "tokenizer.hpp"
#include "boolean.hpp"
#include "function.hpp"
#include "integer.hpp"
#include "operator.hpp"
#include "pseudo_operation.hpp"
#include "real.hpp"
#include "variable.hpp"

#include <exception>
#include <limits>
#include <sstream>
#include <stack>
#include <string>
using namespace std;

/** Default constructor loads the keyword dictionary. */
Tokenizer::Tokenizer() {
	keywords_["abs"]    = keywords_["Abs"]		= keywords_["ABS"]		= make<Abs>();
	keywords_["mod"]	= keywords_["MOD"]		= keywords_["Mod"]		= make<Modulus>();
	keywords_["arccos"] = keywords_["ARCCOS"]	= keywords_["Arccos"]	= make<Arccos>();
	keywords_["arcsin"] = keywords_["ARCSIN"]	= keywords_["Arcsin"]	= make<Arcsin>();
	keywords_["arctan"] = keywords_["ARCTAN"]	= keywords_["Arctan"]	= make<Arctan>();
	keywords_["ceil"]	= keywords_["CEIL"]		= keywords_["Ceil"]		= make<Ceil>();
	keywords_["cos"]	= keywords_["COS"]		= keywords_["Cos"]		= make<Cos>();
	keywords_["exp"]	= keywords_["EXP"]		= keywords_["Exp"]		= make<Exp>();
	keywords_["floor"]	= keywords_["FLOOR"]	= keywords_["Floor"]	= make<Floor>();
	keywords_["lb"]		= keywords_["LB"]		= keywords_["Lb"]		= make<Lb>();
	keywords_["ln"]		= keywords_["LN"]		= keywords_["Ln"]		= make<Ln>();
	keywords_["log"]	= keywords_["LOG"]		= keywords_["Log"]		= make<Log>();
	keywords_["sin"]	= keywords_["SIN"]		= keywords_["Sin"]		= make<Sin>();
	keywords_["sqrt"]	= keywords_["SQRT"]		= keywords_["Sqrt"]		= make<Sqrt>();
	keywords_["tan"]	= keywords_["TAN"]		= keywords_["Tan"]		= make<Tan>();
	keywords_["NOT"]	= keywords_["not"]		= keywords_["Not"]		= make<Not>();
	keywords_["TRUE"]	= keywords_["true"]		= keywords_["True"]		= make<True>();
	keywords_["false"]	= keywords_["FALSE"]	= keywords_["False"]	= make<False>();
	keywords_["AND"]	= keywords_["and"]		= keywords_["And"]		= make<And>();
	keywords_["OR"]		= keywords_["or"]		= keywords_["Or"]		= make<Or>();
	keywords_["XOR"]	= keywords_["xor"]		= keywords_["Xor"]		= make<Xor>();
	keywords_["NAND"]	= keywords_["nand"]		= keywords_["Nand"]		= make<Nand>();
	keywords_["NOR"]	= keywords_["nor"]		= keywords_["Nor"]		= make<Nor>();
	keywords_["XNOR"]	= keywords_["xnor"]		= keywords_["Xnor"]		= make<Xnor>();
	keywords_["PI"]		= keywords_["pi"]		= keywords_["Pi"]		= make<Pi>();
	keywords_["E"]		= keywords_["e"]								= make<E>();
	keywords_["arctan2"] = keywords_["Arctan2"] = keywords_["ARCTAN2"] = make<Arctan2>();
	keywords_["MIN"] = keywords_["min"] = keywords_["Min"] = make<Min>();
	keywords_["MAX"] = keywords_["max"] = keywords_["Max"] = make<Max>();
	keywords_["POW"] = keywords_["pow"] = keywords_["Pow"] = make<Pow>();
	keywords_["GREG"] = keywords_["greg"] = keywords_["Greg"] = make<Greg>();
	keywords_["JULIAN"] = keywords_["julian"] = keywords_["Julian"] = 
	keywords_["JULI"] = keywords_["juli"] = keywords_["Juli"] = make<Julian>();
	keywords_["JDN"] = keywords_["jdn"] = keywords_["Jdn"] = make<Jdn>();
	keywords_["YEAR"] = keywords_["year"] = keywords_["Year"] = make<Year>();
	keywords_["MONTH"] = keywords_["month"] = keywords_["Month"] = make<Month>();
	keywords_["DAY"] = keywords_["day"] = keywords_["Day"] = make<Day>();
	keywords_["RESULT"] = keywords_["result"] = keywords_["Result"] = make<Result>();
	keywords_["TODAY"] = keywords_["today"] = keywords_["Today"] = make<Today>();
}


/** Get an identifier from the expression.
	Assumes that the currentChar is pointing to a alphabetic.
	*/
Token::pointer_type Tokenizer::_get_identifier( Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression ) {
	// accumulate identifier
	string_type ident;
	do
		ident += *currentChar++;
	while( currentChar != end(expression) && isalnum( *currentChar ) );

	// check for predefined identifier
	dictionary_type::iterator iter = keywords_.find(ident);
	if( iter != end(keywords_) )
		return iter->second;
	else
	{
		iter = variables_.find(ident);
		if(iter != end(variables_))
			return iter->second;
		else
			return variables_[ident]= make<Variable>();
	}

	throw XBadCharacter(expression, currentChar - begin(expression));
}


/** Get a number token from the expression.
	@return One of BinaryInteger, Integer, or Real.
	@param currentChar [in,out] an iterator to the current character.  Assumes that the currentChar is pointing to a digit.
	@param expression [in] the expression being scanned.
*/
Token::pointer_type Tokenizer::_get_number( Tokenizer::string_type::const_iterator& currentChar, Tokenizer::string_type const& expression ) 
{
	assert( isdigit( *currentChar ) && "currentChar must pointer to a digit" );
	string number="";
	bool isReal = false;
		
	while (currentChar!=end(expression)&& isdigit(*currentChar))
	{
		number += *currentChar;

		++currentChar;
		if (currentChar != end(expression) && *currentChar == '.') {
			number += *currentChar;
			isReal = true;
			++currentChar;
		}
	}	
	if(isReal) return make<Real>(Real::value_type(number));
	else return make<Integer>(Integer::value_type(number));
}



/** Tokenize the expression.
	@return a TokenList containing the tokens from 'expression'. 
	@param expression [in] The expression to tokenize.
	@note Tokenizer dictionary may be updated if expression contains variables.
	@note Will throws 'BadCharacter' if the expression contains an un-tokenizable character.
	*/
TokenList Tokenizer::tokenize(string_type const& expression) {
	TokenList tokenizedExpression;
	auto currentChar = expression.cbegin();

	for(;;) 
	{
		// strip whitespace
		while( currentChar != end(expression) && isspace(*currentChar) )
			++currentChar;

		// check of end of expression
		if( currentChar == end(expression) ) break;

		// check for a number
		else if( isdigit( *currentChar ) ) {
			tokenizedExpression.push_back( _get_number( currentChar, expression ) );
			continue;
		}

		// check Addition + (plus-sign)
		if (*currentChar == '+' ) {
			++currentChar;
			if (!tokenizedExpression.empty() && ( is<RightParenthesis>(tokenizedExpression.back()) || is<Operand>(tokenizedExpression.back()) || is<Factorial>(tokenizedExpression.back()))) {
				tokenizedExpression.push_back(make<Addition>());
				continue;
			}				
			else {
				tokenizedExpression.push_back(make<Identity>());
				continue;
			}
		}

		// check Subtraction - (dash)
		if (*currentChar == '-') {
			++currentChar;
			if (!tokenizedExpression.empty() && (is<RightParenthesis>(tokenizedExpression.back()) || is<Operand>(tokenizedExpression.back()) || is<Factorial>(tokenizedExpression.back()))) {
				tokenizedExpression.push_back(make<Subtraction>());
				continue;
			}
			else {
				tokenizedExpression.push_back(make<Negation>());
				continue;
			}
		}

		// check Factorial !
		if (*currentChar == '!') {
			++currentChar;
			if (currentChar != end(expression) && *currentChar == '=') {
				++currentChar;
				tokenizedExpression.push_back(make<Inequality>());
				continue;
			}
			else {
				tokenizedExpression.push_back(make<Factorial>());
				continue;
			}
		}

		// check Multiplication *
		if (*currentChar == '*') {
			++currentChar;
			tokenizedExpression.push_back(make<Multiplication>());
			continue;
		}

		// check Division /
		if (*currentChar == '/') {
			++currentChar;
			tokenizedExpression.push_back(make<Division>());
			continue;
		}

		// check Modulus %
		if (*currentChar == '%') {
			++currentChar;
			tokenizedExpression.push_back(make<Modulus>());
			continue;
		}
		
		// check Power #
		if (*currentChar == '#') {
			++currentChar;
			tokenizedExpression.push_back(make<Power>());
			continue;
		}

		// alphabetic
		if (isalpha(*currentChar)) {
			tokenizedExpression.push_back(_get_identifier(currentChar, expression));
			continue;
		}

		// LeftParenthesis
		if (*currentChar == '(') {
			++currentChar;
			tokenizedExpression.push_back(make<LeftParenthesis>());
			continue;
		}

		// RightParenthesis
		if (*currentChar == ')') {
			++currentChar;
			tokenizedExpression.push_back(make<RightParenthesis>());
			continue;
		}

		// ArgumentSeparator
		if (*currentChar == ',') {
			++currentChar;
			tokenizedExpression.push_back(make<ArgumentSeparator>());
			continue;
		}

		// Equality
		if (*currentChar == '=') {
			++currentChar;
			if (currentChar != end(expression) && *currentChar == '=') {
				++currentChar;
				tokenizedExpression.push_back(make<Equality>());
				continue;
			}
			else {
				tokenizedExpression.push_back(make<Assignment>());
				continue;
			}
		}

		// Greater
		if (*currentChar == '>') {
			++currentChar;
			if (currentChar != end(expression) && *currentChar == '=') {
				++currentChar;
				tokenizedExpression.push_back(make<GreaterEqual>());
				continue;
			}
			else {
				tokenizedExpression.push_back(make<Greater>());
				continue;
			}
		}

		// Less
		if (*currentChar == '<') {
			++currentChar;
			if (currentChar != end(expression) && *currentChar == '=') {
				++currentChar;
				tokenizedExpression.push_back(make<LessEqual>());
				continue;
			}
			else {
				tokenizedExpression.push_back(make<Less>());
				continue;
			}
		}

		
		// not a recognized token
		throw XBadCharacter( expression, currentChar - begin(expression) );
	}

	return tokenizedExpression;
}

/*=============================================================

Revision History

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitXOr, BitShiftLeft, BitShiftRight
Simplified CHECK_OP macros

Version 0.1.0: 2012-11-15
Replaced BadCharacter with XTokenizer, XBadCharacter, and XNumericOverflow
Added BinaryInteger, Binary <function>

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-11-25
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
