/** @file: variable.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visaul C++ v110

	@brief Variable class implementation.
	*/

#include <boost\lexical_cast.hpp>
#include "variable.hpp"
#include <iostream>
using namespace std;

Variable::string_type Variable::to_string() const {
	if(get_value() == 0) return boost::lexical_cast<string_type>("Variable: null");
	return boost::lexical_cast<string_type>(*get_value());

	string sr = boost::lexical_cast<string_type>(get_value());
	string rr = "";
	auto length = sr.size();
	auto t_flag = (length + 2) % 3;
	for (unsigned i = 0; i < length; ++i)
	{
		rr.push_back(sr[i]);
		if (i % 3 == t_flag && i != length - 1)
			rr.push_back(',');
	}
	if (rr[0] == '-' && t_flag == 0)
		rr.erase(rr.begin() + 1);
	return rr;

}

/*=============================================================

Revision History

Version 0.0.1: 2012-11-13
C++ 11 cleanup

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
