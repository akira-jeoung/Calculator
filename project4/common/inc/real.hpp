#if !defined(GUARD_real_hpp20091125_)
#define GUARD_real_hpp20091125_

/** @file: real.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 1.0.0
	@note Compiles under Visaul C++ v120

	@brief Real class declaration.
	*/
/*
Bill Jeoung
2016-11-20
*/

#include "operand.hpp"
#include "boolean.hpp"
#include "function.hpp"
#include "operator.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <boost\multiprecision\cpp_dec_float.hpp>
#include <boost\math\constants\constants.hpp>


/** Real number token. */
class Real : public Operand {
public:
	DEF_POINTER_TYPE(Real)
	using value_type = boost::multiprecision::number < boost::multiprecision::cpp_dec_float<1000, int32_t, void> >;
	static unsigned precision_;
private:
	value_type	value_;
public:
	Real( value_type value = value_type(0) ) : value_( value ) { }
	value_type				get_value() const { return value_; }
	virtual void			set_value(value_type v) { value_ = v; }
	string_type				to_string() const;
	static void setPrecision(unsigned const p);
	DEF_IS_CONVERTABLE_FROM(Real)
};


/** Pi constant token. */
class Pi : public Real {
public:
	Pi() : Real( boost::math::constants::pi<value_type>() ) { }

	DEF_IS_CONVERTABLE_FROM(Pi)
};

/** E constant token. */
class E : public Real {
public:
	E() : Real(boost::math::constants::e<value_type>()) { }

	DEF_IS_CONVERTABLE_FROM(E)
};

/** Jd Calendar token. */
class Jd : public Real {	
public:
	Jd(value_type jdn) : Real(jdn) {}
	string_type						to_string() const;
	DEF_IS_CONVERTABLE_FROM(Jd)
	DEF_POINTER_TYPE(Jd)	
	virtual void to_greg(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day);
	virtual void from_greg(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day);
	virtual void to_juli(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day);
	virtual void from_juli(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day);
	static std::array<std::array<int, 13>, 2> const daysOfMonth;
};

/** Gregorian calendar token. */
class Gregorian : public Jd {
public:
	Gregorian(value_type jdn) : Jd(jdn) {}

	DEF_IS_CONVERTABLE_FROM(Gregorian)
	DEF_POINTER_TYPE(Gregorian)
	string_type				to_string() const;	
};
inline bool is_Gregorian_leapyear(Jd::value_type &year){
	return (year.convert_to<Integer::value_type>() % 400 == 0) || ((year.convert_to<Integer::value_type>() % 4 == 0) && (year.convert_to<Integer::value_type>() % 100 != 0));}
/** JulianC calendar token. */
class JulianC : public Jd {
public:
	JulianC(value_type jdn) : Jd(jdn) {}
	DEF_IS_CONVERTABLE_FROM(JulianC)
	DEF_POINTER_TYPE(JulianC)	
	string_type				to_string() const;
};
inline bool is_juli_leapyear(Jd::value_type &year){	return year.convert_to<Integer::value_type>() % 4 == 0;}
/** YearC calendar token. */
class YearC : public Jd {
public:
	YearC(value_type jdn) : Jd(jdn) {}
	DEF_IS_CONVERTABLE_FROM(YearC)
	DEF_POINTER_TYPE(YearC)
};
/** MonthC calendar token. */
class MonthC : public Jd {
public:
	MonthC(value_type jdn) : Jd(jdn) {}
	DEF_IS_CONVERTABLE_FROM(MonthC)
	DEF_POINTER_TYPE(MonthC)
};
/** DayC calendar token. */
class DayC : public Jd {
public:
	DayC(value_type jdn) : Jd(jdn) {}
	DEF_IS_CONVERTABLE_FROM(DayC)
	DEF_POINTER_TYPE(DayC)
	string_type				to_string() const;	
};

/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Switched value_type to boost::multiprecision::cpp_dec_float_100

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
#endif // GUARD_real_hpp20091125_
