/** @file: real.cpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-13
	@version 1.0.0
	@note Compiles under Visaul C++ v120

	@brief Real class implementation.
	*/

#include "real.hpp"
using namespace std;

unsigned Real::precision_ = 10;
std::array<std::string const, 7> const dayNames = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",  "Sunday" };
std::array<std::string const, 13> const monthNames = { "", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
std::array<std::array<int, 13>, 2> const Jd::daysOfMonth = {
	0,31,28,31,30,31,30,31,31,30,31,30,31,
	0,31,29,31,30,31,30,31,31,30,31,30,31
};
void Jd::to_greg(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day) {

	Jd::value_type jd = floor(get_value() - 0.5) + 0.5;

	Jd::value_type a = floor(jd + 0.5) + 32044;
	Jd::value_type b = floor((4 * a + 3) / 146097);
	Jd::value_type c = a - floor(b * 146097 / 4);
	Jd::value_type d = floor((4 * c + 3) / 1461);
	Jd::value_type e = c - floor(1461 * d / 4);
	Jd::value_type m = floor((5 * e + 2) / 153);

	day = e - floor((153 * m + 2) / 5) + 1;
	month = m + 3 - 12 * floor(m / 10);
	year = b * 100 + d - 4800 + floor(m / 10);
}
void Jd::from_greg(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day) {
	Jd::value_type y = (year - 1);
	Jd::value_type jdn = static_cast<Jd::value_type>((1721425.5 - 1) +
		(365 * y) +
		floor(y / 4) +
		-floor(y / 100) +
		floor(y / 400) +
		floor((static_cast<Jd::value_type>(367 * month) - 362) / 12) +
		((month <= 2) ? 0 : (
		(year.convert_to<Integer::value_type>() % 400 == 0) || ((year.convert_to<Integer::value_type>() % 4 == 0) && (year.convert_to<Integer::value_type>() % 100 != 0)) ? -1 : -2)) + day);
	set_value(jdn);	
}
void Jd::to_juli(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day) {

	Jd::value_type jd = floor(get_value() - 0.5) + 0.5;

	Jd::value_type a = floor(jd + 0.5);
	Jd::value_type b = a + 1524;
	Jd::value_type c = floor((b - 122.1) / 365.25);
	Jd::value_type d = floor(365.25*c);
	Jd::value_type e = floor((b - d) / 30.6001);

	month = floor(e < 14 ? e - 1 : e - 13);
	year = floor(month > 2 ? c - 4716 : c - 4715);
	day = b - d - floor(30.6001*e);
}
void Jd::from_juli(Jd::value_type &year, Jd::value_type &month, Jd::value_type &day) {

	Jd::value_type aa = floor((14 - month) / 12);
	Jd::value_type y = year + 4800 - aa;
	Jd::value_type m = month + 12 * aa - 3;
	Jd::value_type jdn = (day + floor((153 * m + 2) / 5) + 365 * y + floor(y / 4)) - 32083.5;
	set_value(jdn);
}
Real::string_type Real::to_string() const {
	
	ostringstream oss;
	oss << fixed << setprecision(precision_) << get_value();

	string sr = oss.str();
	string rr = "";	
	auto length = sr.size()- precision_;
	auto t_flag = (length + 1) % 3;
	for (unsigned i = 0; i < length; ++i)
	{
		rr.push_back(sr[0]);
		if (i % 3 == t_flag && sr[1]!='.')
			rr.push_back(',');
		sr.erase(sr.begin());
	}
	if (rr[0] == '-' && t_flag == 0)
		rr.erase(rr.begin() + 1);
	
	return rr+sr;
}
void Real::setPrecision(unsigned const p) { precision_ = p; }
Jd::string_type Jd::to_string() const {

	string jdn_srting = "Julian Day Number: " + Real::to_string();
	for (unsigned i = 0; i < (precision_ - 1); ++i)
		jdn_srting.erase(jdn_srting.end() - 1);

	return jdn_srting;
}
Gregorian::string_type Gregorian::to_string() const {

	string jdn_srting = "Julian Day Number: " + Real::to_string();
	for (unsigned i = 0; i < (precision_ -1); ++i)
		jdn_srting.erase(jdn_srting.end() - 1);

	Jd jd = get_value();
	string dayOfWeek = dayNames[static_cast<int>((jd.get_value() + 0.5).convert_to<Integer::value_type>() % 7)];
	value_type day,	month, year;

	jd.to_greg(year, month, day);

	ostringstream yy;
	yy << fixed << setprecision(1) << year;
	string y_str = yy.str();
	for (unsigned i = 0; i < 2; ++i)
		y_str.erase(y_str.end() - 1);	
	string m_str = monthNames[static_cast<int>(month)] + ", ";
	ostringstream dd;
	dd << fixed << setprecision(1) << day;
	string d_str = dd.str();
	for (unsigned i = 0; i < 2; ++i)
		d_str.erase(d_str.end() - 1);

	string reVal = m_str + d_str + ", " + y_str + ", " + dayOfWeek +"\t(Gregorian)\n" + jdn_srting;

	return reVal;
}
JulianC::string_type JulianC::to_string() const {

	string jdn_srting = "Julian Day Number: " + Real::to_string();
	for (unsigned i = 0; i < (precision_ - 1); ++i)
		jdn_srting.erase(jdn_srting.end() - 1);

	value_type jd = get_value();
	string dayOfWeek = dayNames[static_cast<int>((jd + 0.5).convert_to<Integer::value_type>() % 7)];
	jd = floor(jd - 0.5) + 0.5;

	value_type a = floor(jd + 0.5);
	value_type b = a + 1524;
	value_type c = floor((b - 122.1) / 365.25);
	value_type d = floor(365.25*c);
	value_type e = floor((b - d) / 30.6001);

	int month = static_cast<int>(floor(e < 14 ? e - 1 : e - 13));
	value_type year = floor(month > 2 ? c - 4716 : c - 4715);
	value_type day = b - d - floor(30.6001*e);

	ostringstream yy;
	yy << fixed << setprecision(1) << year;
	string y_str = yy.str();
	for (unsigned i = 0; i < 2; ++i)
		y_str.erase(y_str.end() - 1);
	string m_str = monthNames[month] + ", ";
	ostringstream dd;
	dd << fixed << setprecision(1) << day;
	string d_str = dd.str();
	for (unsigned i = 0; i < 2; ++i)
		d_str.erase(d_str.end() - 1);

	string reVal = m_str + d_str + ", " + y_str + ", " + dayOfWeek + "\t(Julian)\n" + jdn_srting;

	return reVal;
}

DayC::string_type DayC::to_string() const {

	string jdn_srting = Real::to_string();
	for (unsigned i = 0; i < (precision_ + 1); ++i)
		jdn_srting.erase(jdn_srting.end() - 1);
	
	string reVal = jdn_srting + " days";

	return reVal;
}


/*=============================================================

Revision History
Version 1.0.0: 2014-10-29
C++ 11 refactor.
Switched value_type to boost::multiprecision::cpp_dec_float_100

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
