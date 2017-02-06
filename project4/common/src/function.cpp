/** @file: function.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.0.1
	@note Compiles under Visaul C++ v110

	@brief Function class implementations.
	*/
/*
Bill Jeoung
2016-12-03
*/
#include "function.hpp"
#include <iostream>

// Max perform
Operand::pointer_type Max::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
	{
		Boolean::value_type a = get_value<Boolean>(vecOper[0]);
		Boolean::value_type b = get_value<Boolean>(vecOper[1]);
		if (a >= b) return vecOper[0];
		else return vecOper[1];
	}		
	else if(flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
	{
		Real::value_type a = get_value<Real>(vecOper[0]);
		Real::value_type b = get_value<Real>(vecOper[1]);
		if (a >= b) return vecOper[0];
		else return vecOper[1];
	}
	else if(flag == 0)
	{
		Integer::value_type a = get_value<Integer>(vecOper[0]);
		Integer::value_type b = get_value<Integer>(vecOper[1]);
		if (a >= b) return vecOper[0];
		else return vecOper[1];
	}	
	else 
		throw XConvert(typeid(*this).name() + 6);
		
}
// Min perform
Operand::pointer_type Min::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
	{
		Boolean::value_type a = get_value<Boolean>(vecOper[0]);
		Boolean::value_type b = get_value<Boolean>(vecOper[1]);
		if (a <= b) return vecOper[0];
		else return vecOper[1];
	}
	else if (flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
	{
		Real::value_type a = get_value<Real>(vecOper[0]);
		Real::value_type b = get_value<Real>(vecOper[1]);
		if (a <= b) return vecOper[0];
		else return vecOper[1];
	}
	else if (flag == 0)
	{
		Integer::value_type a = get_value<Integer>(vecOper[0]);
		Integer::value_type b = get_value<Integer>(vecOper[1]);
		if (a <= b) return vecOper[0];
		else return vecOper[1];
	}
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Pow perform 
Operand::pointer_type Pow::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
		throw XPerform(typeid(*this).name() + 6);
	else if (flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
		return make_operand<Real>(pow(get_value<Real>(vecOper[1]), get_value<Real>(vecOper[0])));
	else if (flag == 0)
	{
		Integer::value_type b1 = get_value<Integer>(vecOper[1]);
		Integer::value_type e1 = get_value<Integer>(vecOper[0]);
		if (e1 < 0)
		{
			Real::value_type b2 = static_cast<Real::value_type>(b1);
			Real::value_type e2 = static_cast<Real::value_type>(e1);
			return make_operand<Real>(pow(b2, e2));
		}
		else
		{
			Integer::value_type result = 1;
			for (Integer::value_type i = 0; i < e1; ++i)
				result *= b1;
			return make_operand<Integer>(result);
		}
	}
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Arctan2 perform 
Operand::pointer_type Arctan2::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type second;
	Real::value_type first;
	if (flag==1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
	{
		second = get_value<Real>(vecOper[0]);
		first = get_value<Real>(vecOper[1]);
	}
	else if (flag ==0)
	{
		second = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
		 first = static_cast<Real::value_type>(get_value<Integer>(vecOper[1]));
	}
	else if (flag == 4)
		throw XPerform(typeid(*this).name() + 6);
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(atan2(first, second));
}
// abs perform
Operand::pointer_type Abs::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {

	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		Real::value_type result = get_value<Real>(vecOper[0]);
		
		 return make_operand<Real>(abs(result));
	}
	else if(flag == 0)
	{
		Integer::value_type result = get_value<Integer>(vecOper[0]);
		if (result < 0)
			return make_operand<Integer>(-result);
		else return make_operand<Integer>(result);
	}
	else if (flag == 2)
	{
		if (get_value<Boolean>(vecOper[0]))
			return make_operand<Integer>(1);
		return make_operand<Integer>(0);
	}
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Arccos perform 
Operand::pointer_type Arccos::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag==1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag==0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(acos(element));
}
// Arcsin perform 
Operand::pointer_type Arcsin::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(asin(element));
}
// Arctan perform 
Operand::pointer_type Arctan::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(atan(element));
}
// Ceil perform 
Operand::pointer_type Ceil::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(Real::value_type(ceil(element)));
}
// Cos perform 
Operand::pointer_type Cos::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(cos(element));
}
// Exp perform 
Operand::pointer_type Exp::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag ==0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(exp(element));
}
// Floor perform 
Operand::pointer_type Floor::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(floor(element));
}
// Ln perform 
Operand::pointer_type Ln::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(log(element));
}
// Lb perform 
Operand::pointer_type Lb::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(log(element)/log(Real::value_type(2)));
}
// Log perform 
Operand::pointer_type Log::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(log10(element));
}
// Sin perform 
Operand::pointer_type Sin::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(sin(element));
}
// Sqrt perform 
Operand::pointer_type Sqrt::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}	
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(sqrt(element));
}
// Tan perform 
Operand::pointer_type Tan::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Real::value_type element;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100)
	{
		element = get_value<Real>(vecOper[0]);
	}
	else if (flag == 0)
	{
		element = static_cast<Real::value_type>(get_value<Integer>(vecOper[0]));
	}
	else if (flag == 2)
	{
		element = static_cast<Real::value_type>(get_value<Boolean>(vecOper[0]));
	}
	else
		throw XConvert(typeid(*this).name() + 6);
	return make_operand<Real>(tan(element));
}
// resultVector instanciation
std::vector<Operand::pointer_type> Result::resultVector;
// Result perform 
Operand::pointer_type Result::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 0)
		throw XResultIndex(typeid(*vecOper[0]).name() + 6);
	else if (get_value<Integer>(vecOper[0]) > resultVector.size() || get_value<Integer>(vecOper[0])-1 < 0)
		throw XResultRange(typeid(*this).name() + 6);

	return resultVector.at(static_cast<int>(get_value<Integer>(vecOper[0]))-1);
}
// Result clear
void Result::clear() { resultVector.clear(); }
// Jdn perform
Operand::pointer_type Jdn::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	Jd::value_type jdn;
	if (flag == 1 || flag == 200 || flag == 400 || flag == 100) {
		jdn = get_value<Real>(vecOper[0]);
	}		
	else if (flag == 0) {
		jdn = static_cast<Jd::value_type>(get_value<Integer>(vecOper[0])) ;		
	}		
	else throw XConvert(typeid(*this).name() + 6);	
	return make_operand<Jd>(jdn);
}
// Greg perform
Operand::pointer_type Greg::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 0)
		throw XConvert(typeid(*this).name() + 6);

	Jd::value_type year = static_cast<Jd::value_type>(get_value<Integer>(vecOper[2]));
	Jd::value_type month = static_cast<Jd::value_type>(get_value<Integer>(vecOper[1]));
	Jd::value_type day = static_cast<Jd::value_type>(get_value<Integer>(vecOper[0]));

	if (get_value<Integer>(vecOper[0]) > Jd::daysOfMonth[is_Gregorian_leapyear(year)][static_cast<int>(month.convert_to<Integer::value_type>())])
		throw XDayInMonth(typeid(*this).name() + 6);
	Jd jdn = 0.0;
	jdn.from_greg(year, month, day);

	return make_operand<Gregorian>(jdn.get_value());
}
// Julian perform
Operand::pointer_type Julian::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 0)
		throw XConvert(typeid(*this).name() + 6);

	Jd::value_type year = static_cast<Jd::value_type>(get_value<Integer>(vecOper[2]));
	Jd::value_type month = static_cast<Jd::value_type>(get_value<Integer>(vecOper[1]));
	Jd::value_type day = static_cast<Jd::value_type>(get_value<Integer>(vecOper[0]));
	
	if (get_value<Integer>(vecOper[0]) > Jd::daysOfMonth[is_juli_leapyear(year)][static_cast<int>(month.convert_to<Integer::value_type>())])
		throw XDayInMonth(typeid(*this).name() + 6);
	Jd jdn = 0.0;
	jdn.from_juli(year, month, day);

	return make_operand<JulianC>(jdn.get_value());
}
// Year perform
Operand::pointer_type Year::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 0)
		return make_operand<YearC>(static_cast<Jd::value_type>(get_value<Integer>(vecOper[0])));		
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Month perform
Operand::pointer_type Month::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 0)
		return make_operand<MonthC>(static_cast<Jd::value_type>(get_value<Integer>(vecOper[0])));
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Day perform
Operand::pointer_type Day::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 0)
		return make_operand<DayC>(static_cast<Jd::value_type>(get_value<Integer>(vecOper[0])));
	else if (flag == 1)
		return make_operand<DayC>(static_cast<Jd::value_type>(get_value<Real>(vecOper[0])));
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Today perform
Operand::pointer_type Today::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {

	if (flag != 0) throw XConvert(typeid(*this).name() + 6);

	Integer::value_type kind = get_value<Integer>(vecOper[0]);

	time_t nowTime = time(NULL);
	struct tm tmNow;
	localtime_s(&tmNow, &nowTime);
	Jd::value_type year = static_cast<Jd::value_type>(tmNow.tm_year + 1900);
	Jd::value_type month = static_cast<Jd::value_type>(tmNow.tm_mon + 1);
	Jd::value_type day = static_cast<Jd::value_type>(tmNow.tm_mday);
	Jd jdn = 0.0;
	jdn.from_greg(year, month, day);

	if (kind == 0) return make_operand<Gregorian>(jdn.get_value());
	else if (kind > 0) return make_operand<JulianC>(jdn.get_value());
	else return make_operand<Jd>(jdn.get_value());
}


/*=============================================================

Revision History

Version 0.0.1: 2012-11-13
C++ 11 cleanup

Version 0.0.0: 2009-12-31
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
