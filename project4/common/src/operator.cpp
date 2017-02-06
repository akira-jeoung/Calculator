/** @file: operator.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 0.1.1
	@note Compiles under Visaul C++ v110

	@brief Operator class implementations.
	*/
/*
Bill Jeoung
2016-12-03
*/
#include <string>
#include "operator.hpp"
// Power 
Operand::pointer_type Power::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {	
	if (flag == 1)
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
	else if (flag == 4)
		throw XPerform(typeid(*this).name() + 6);
	else
		throw XConvert(typeid(*this).name() + 6);
}
void adjust_gerg_month_day(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day) {

	if (day > Jd::daysOfMonth[is_Gregorian_leapyear(year)][static_cast<int>(month)])
	{
		day -= Jd::daysOfMonth[is_Gregorian_leapyear(year)][static_cast<int>(month)];
		++month;		
	}
}
void adjust_juli_month_day(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day) {

	if (day > Jd::daysOfMonth[is_juli_leapyear(year)][static_cast<int>(month)])
	{
		day -= Jd::daysOfMonth[is_juli_leapyear(year)][static_cast<int>(month)];
		++month;
	}
}
// Addition
Operand::pointer_type Addition::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 1)
		return make_operand<Real>(get_value<Real>(vecOper[0]) + get_value<Real>(vecOper[1]));
	else if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) || get_value<Boolean>(vecOper[1]));
	else if (flag == 0)
		return make_operand<Integer>(get_value<Integer>(vecOper[0]) + get_value<Integer>(vecOper[1]));	
	else if (flag == 200) {
		return make_operand<Jd>(get_value<Jd>(vecOper[1]) + get_value<Jd>(vecOper[0]));
	}
	else if (flag == 300)
	{
		if (is<Gregorian>(vecOper[1])) return make_operand<Gregorian>(get_value<Gregorian>(vecOper[1]) + get_value<Jd>(vecOper[0]));
		else return make_operand<Jd>(get_value<Jd>(vecOper[1]) + get_value<Gregorian>(vecOper[0]));
	}
	else if (flag == 400)
	{
		return make_operand<Gregorian>(get_value<Gregorian>(vecOper[1]) + get_value<Gregorian>(vecOper[0]));
	}
	else if (flag == 500)
	{
		if (is<JulianC>(vecOper[1])) return make_operand<JulianC>(get_value<JulianC>(vecOper[1]) + get_value<Jd>(vecOper[0]));
		else return make_operand<Jd>(get_value<Jd>(vecOper[1]) + get_value<JulianC>(vecOper[0]));
	}
	else if (flag == 600)
	{
		if (is<Gregorian>(vecOper[1])) return make_operand<Gregorian>(get_value<Gregorian>(vecOper[1]) + get_value<JulianC>(vecOper[0]));
		else return make_operand<JulianC>(get_value<JulianC>(vecOper[1]) + get_value<Gregorian>(vecOper[0]));
	}
	else if (flag == 800)
	{
		 return make_operand<JulianC>(get_value<JulianC>(vecOper[1]) + get_value<JulianC>(vecOper[0]));
	}
	else if (flag == 310) 
	{
		Jd jd = get_value<Gregorian>(vecOper[1]), jdn = 0.0;		
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_greg(year, month, day);
		year = year + get_value<YearC>(vecOper[0]);
		adjust_gerg_month_day(year, month, day);				
		jdn.from_greg(year, month, day);

		return make_operand<Gregorian>(jdn.get_value());
	}
	else if (flag == 510)
	{
		Jd jd = get_value<JulianC>(vecOper[1]), jdn = 0.0;
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_juli(year, month, day);
		year = year + get_value<YearC>(vecOper[0]);		
		adjust_juli_month_day(year, month, day);
		jdn.from_juli(year, month, day);		

		return make_operand<JulianC>(jdn.get_value());
	}
	else if (flag == 320) 
	{
		Jd jd = get_value<Gregorian>(vecOper[1]), jdn = 0.0;
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_greg(year, month, day);
		month = month + get_value<MonthC>(vecOper[0]);
		while (month > 12) { year = year + 1; month = month - 12; }
		while (month < 0)  { year = year - 1; month = month + 12; }
		adjust_gerg_month_day(year, month, day);
		jdn.from_greg(year, month, day);

		return make_operand<Gregorian>(jdn.get_value());
	}
	else if (flag == 520)
	{
		Jd jd = get_value<JulianC>(vecOper[1]), jdn = 0.0;
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_juli(year, month, day);
		month = month + get_value<MonthC>(vecOper[0]);
		while (month > 12) { year = year + 1; month = month - 12; }
		while (month < 0) { year = year - 1; month = month + 12; }
		adjust_juli_month_day(year, month, day);
		jdn.from_juli(year, month, day);

		return make_operand<JulianC>(jdn.get_value());
	}	
	else if (is<YearC>(vecOper[0]))
		throw std::exception("Year should be calculated with Gregorian or Julian!");
	else if (is<MonthC>(vecOper[0]))
		throw std::exception("Month should be calculated with Gregorian or Julian!");
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Subtraction
Operand::pointer_type Subtraction::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 1)
		return make_operand<Real>(get_value<Real>(vecOper[1]) - get_value<Real>(vecOper[0]));
	else if (flag == 0)
		return make_operand<Integer>(get_value<Integer>(vecOper[1]) - get_value<Integer>(vecOper[0]));
	else if (flag == 200) {
		return make_operand<Jd>(get_value<Jd>(vecOper[1]) - get_value<Jd>(vecOper[0]));
	}
	else if (flag == 300)
	{
		if (is<Gregorian>(vecOper[1])) return make_operand<Gregorian>(get_value<Gregorian>(vecOper[1]) - get_value<Jd>(vecOper[0]));
		else return make_operand<Jd>(get_value<Jd>(vecOper[1]) - get_value<Gregorian>(vecOper[0]));
	}
	else if (flag == 400)
	{
		return make_operand<DayC>(get_value<Gregorian>(vecOper[1]) - get_value<Gregorian>(vecOper[0]));
	}
	else if (flag == 500)
	{
		if (is<JulianC>(vecOper[1])) return make_operand<JulianC>(get_value<JulianC>(vecOper[1]) - get_value<Jd>(vecOper[0]));
		else return make_operand<DayC>(get_value<Jd>(vecOper[1]) - get_value<JulianC>(vecOper[0]));
	}
	else if (flag == 600)
	{
		if (is<Gregorian>(vecOper[1])) return make_operand<DayC>(get_value<Gregorian>(vecOper[1]) - get_value<JulianC>(vecOper[0]));
		else return make_operand<DayC>(get_value<JulianC>(vecOper[1]) - get_value<Gregorian>(vecOper[0]));
	}
	else if (flag == 800)
	{
		return make_operand<DayC>(get_value<JulianC>(vecOper[1]) - get_value<JulianC>(vecOper[0]));
	}
	else if (flag == 310)
	{
		Jd jd = get_value<Gregorian>(vecOper[1]), jdn = 0.0;
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_greg(year, month, day);
		year = year - get_value<YearC>(vecOper[0]);
		adjust_gerg_month_day(year, month, day);
		jdn.from_greg(year, month, day);

		return make_operand<Gregorian>(jdn.get_value());
	}
	else if (flag == 510)
	{
		Jd jd = get_value<JulianC>(vecOper[1]), jdn = 0.0;
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_juli(year, month, day);
		year = year - get_value<YearC>(vecOper[0]);
		adjust_juli_month_day(year, month, day);
		jdn.from_juli(year, month, day);

		return make_operand<JulianC>(jdn.get_value());
	}
	else if (flag == 320)
	{
		Jd jd = get_value<Gregorian>(vecOper[1]), jdn = 0.0;
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_greg(year, month, day);
		month = month - get_value<MonthC>(vecOper[0]);
		while (month > 12) { year = year + 1; month = month - 12; }
		while (month < 0) { year = year - 1; month = month + 12; }
		adjust_gerg_month_day(year, month, day);
		jdn.from_greg(year, month, day);

		return make_operand<Gregorian>(jdn.get_value());
	}
	else if (flag == 520)
	{
		Jd jd = get_value<JulianC>(vecOper[1]), jdn = 0.0;
		Jd::value_type day = 0, month = 0, year = 0;

		jd.to_juli(year, month, day);
		month = month - get_value<MonthC>(vecOper[0]);
		while (month > 12) { year = year + 1; month = month - 12; }
		while (month < 0) { year = year - 1; month = month + 12; }
		adjust_juli_month_day(year, month, day);
		jdn.from_juli(year, month, day);

		return make_operand<JulianC>(jdn.get_value());
	}
	else if (is<YearC>(vecOper[0]))
		throw std::exception("Year should be calculated with Gregorian or Julian!");
	else if(is<MonthC>(vecOper[0]))
		throw std::exception("Month should be calculated with Gregorian or Julian!");
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Division
Operand::pointer_type Division::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 1)
		return make_operand<Real>(get_value<Real>(vecOper[1]) / get_value<Real>(vecOper[0]));
	else if (flag == 0)
		return make_operand<Integer>(get_value<Integer>(vecOper[1]) / get_value<Integer>(vecOper[0]));
	else
		throw XConvert(typeid(*this).name() + 6);
}
// Multiplication
Operand::pointer_type Multiplication::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {	
	if (flag == 1)
		return make_operand<Real>(get_value<Real>(vecOper[0]) * get_value<Real>(vecOper[1]));
	else if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) && get_value<Boolean>(vecOper[1]));
	else if (flag == 0)
		return make_operand<Integer>(get_value<Integer>(vecOper[0]) * get_value<Integer>(vecOper[1]));
	else
		throw XConvert(typeid(*this).name() + 6);

}
// Modulus
Operand::pointer_type Modulus::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag)
		throw XPerform(typeid(*this).name() + 6);
	else
		return make_operand<Integer>(get_value<Integer>(vecOper[1]) % get_value<Integer>(vecOper[0]));
}
// Factorial
Operand::pointer_type Factorial::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag)
		throw XPerform(typeid(*this).name() + 6);
	if (get_value<Integer>(vecOper[0]) < 0)
		throw XNegativeArg(typeid(*this).name() + 6);
	Integer::value_type result = 1;
	for (Integer::value_type i = 1; i <= get_value<Integer>(vecOper[0]); ++i)
		result *= i;
	return make_operand<Integer>(result);
}
// Identity
Operand::pointer_type Identity::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 2)
		throw XPerform(typeid(*this).name() + 6);
	return vecOper[0];
}
// Negation
Operand::pointer_type Negation::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 1)
		return make_operand<Real>(- get_value<Real>(vecOper[0]));
	else if (flag == 2)
		throw XPerform(typeid(*this).name() + 6);
	else
		return make_operand<Integer>(- get_value<Integer>(vecOper[0]));
}
// Not
Operand::pointer_type Not::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag >= 2)
		return make_operand<Boolean>(!(get_value<Boolean>(vecOper[0])));
	else if (flag == 1)
		return make_operand<Real>(!(get_value<Real>(vecOper[0])));
	else 
		return make_operand<Integer>(!(get_value<Integer>(vecOper[0])));
}
// And
Operand::pointer_type And::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 4)
		throw XPerform(typeid(*this).name() + 6);
	return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) && get_value<Boolean>(vecOper[1]));
}
// Or
Operand::pointer_type Or::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 4)
		throw XPerform(typeid(*this).name() + 6);
	return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) || get_value<Boolean>(vecOper[1]));
}
// Nand
Operand::pointer_type Nand::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 4)
		throw XPerform(typeid(*this).name() + 6);
	return make_operand<Boolean>(!(get_value<Boolean>(vecOper[0]) && get_value<Boolean>(vecOper[1])));
}
// Nor
Operand::pointer_type Nor::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 4)
		throw XPerform(typeid(*this).name() + 6);
	return make_operand<Boolean>(!(get_value<Boolean>(vecOper[0]) || get_value<Boolean>(vecOper[1])));
}
// Xor
Operand::pointer_type Xor::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 4)
		throw XPerform(typeid(*this).name() + 6);
	return make_operand<Boolean>( (get_value<Boolean>(vecOper[0])) ^ (get_value<Boolean>(vecOper[1])) );
}
// Xnor
Operand::pointer_type Xnor::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag != 4)
		throw XPerform(typeid(*this).name() + 6);
	return make_operand<Boolean>( !( (get_value<Boolean>(vecOper[0])) ^ (get_value<Boolean>(vecOper[1])) ) );
}
// Equality
Operand::pointer_type Equality::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) == get_value<Boolean>(vecOper[1]));
	else if (flag==1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
		return make_operand<Boolean>(get_value<Real>(vecOper[0]) == get_value<Real>(vecOper[1]));
	else if(flag == 0) return make_operand<Boolean>(get_value<Integer>(vecOper[0]) == get_value<Integer>(vecOper[1]));	
	else throw XConvert(typeid(*this).name() + 6);
}
// Inequality
Operand::pointer_type Inequality::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) != get_value<Boolean>(vecOper[1]));
	else if (flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
		return make_operand<Boolean>(get_value<Real>(vecOper[0]) != get_value<Real>(vecOper[1]));
	else if (flag == 0) return make_operand<Boolean>(get_value<Integer>(vecOper[0]) != get_value<Integer>(vecOper[1]));
	else throw XConvert(typeid(*this).name() + 6);
}
// Greater
Operand::pointer_type Greater::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) < get_value<Boolean>(vecOper[1]));
	else if (flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
		return make_operand<Boolean>(get_value<Real>(vecOper[0]) < get_value<Real>(vecOper[1]));
	else if (flag == 0) return make_operand<Boolean>(get_value<Integer>(vecOper[0]) < get_value<Integer>(vecOper[1]));
	else throw XConvert(typeid(*this).name() + 6);
}
// GreaterEqual
Operand::pointer_type GreaterEqual::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) <= get_value<Boolean>(vecOper[1]));
	else if (flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
		return make_operand<Boolean>(get_value<Real>(vecOper[0]) <= get_value<Real>(vecOper[1]));
	else if (flag == 0) return make_operand<Boolean>(get_value<Integer>(vecOper[0]) <= get_value<Integer>(vecOper[1]));
	else throw XConvert(typeid(*this).name() + 6);
}
// Less
Operand::pointer_type Less::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) > get_value<Boolean>(vecOper[1]));
	else if (flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
		return make_operand<Boolean>(get_value<Real>(vecOper[0]) > get_value<Real>(vecOper[1]));
	else if (flag == 0) return make_operand<Boolean>(get_value<Integer>(vecOper[0]) > get_value<Integer>(vecOper[1]));
	else throw XConvert(typeid(*this).name() + 6);
}

// LessEqual
Operand::pointer_type LessEqual::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if (flag == 4)
		return make_operand<Boolean>(get_value<Boolean>(vecOper[0]) >= get_value<Boolean>(vecOper[1]));
	else if (flag == 1 || flag == 200 || flag == 300 || flag == 400 || flag == 500 || flag == 600 || flag == 800)
		return make_operand<Boolean>(get_value<Real>(vecOper[0]) >= get_value<Real>(vecOper[1]));
	else if (flag == 0) return make_operand<Boolean>(get_value<Integer>(vecOper[0]) >= get_value<Integer>(vecOper[1]));
	else throw XConvert(typeid(*this).name() + 6);
}
// Assignment
Operand::pointer_type Assignment::perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) {
	if(!is<Variable>(vecOper[1]))
		throw std::exception("Error: assignment to a non-variable.");
	convert<Variable>(vecOper[1])->set_value(vecOper[0]);
	return vecOper[1];
}
/*=============================================================

Revision History

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-08
Added exception for assignment to a non-variable.

Version 0.0.0: 2009-12-14
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
