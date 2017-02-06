#if !defined(GUARD_function_hpp20091126_)
#define GUARD_function_hpp20091126_

/** @file: function.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@version 1.0.0
	@date 2012-11-13
	@note Compiles under Visaul C++ v120

	@brief function token declarations.
	*/

/*
Bill Jeoung
2016-11-20
*/
#include <vector>
#include "operation.hpp"
#include "operand.hpp"
#include "integer.hpp"
#include "boolean.hpp"
#include "real.hpp"
#include "variable.hpp"

#define DEF_PERFORM(vecOper, flag) Operand::pointer_type perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) override;

/** Function token base class. */
class Function : public Operation { 
	virtual Operand::pointer_type perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) override = 0;
};

		/** One argument function token base class. */
		class OneArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 1; }
//			DECL_OPERATION_PERFORM()
		};

				/** Absolute value function token. */
				class Abs : public OneArgFunction {
				DEF_IS_CONVERTABLE_FROM(Abs)
				DEF_PERFORM(vecOper, flag)
				};

				/** Arccos value function token. */
				class Arccos : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arccos)
					DEF_PERFORM(vecOper, flag)
				};

				/** Arcsin value function token. */
				class Arcsin : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arcsin)
					DEF_PERFORM(vecOper, flag)
				};

				/** Arctan value function token. */
				class Arctan : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arctan)
					DEF_PERFORM(vecOper, flag)
				};

				/** Ceil value function token. */
				class Ceil : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Ceil)
					DEF_PERFORM(vecOper, flag)
				};

				/** Cos value function token. */
				class Cos : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Cos)
					DEF_PERFORM(vecOper, flag)
				};

				/** Exp value function token. */
				class Exp : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Exp)
					DEF_PERFORM(vecOper, flag)
				};

				/** Floor value function token. */
				class Floor : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Floor)
					DEF_PERFORM(vecOper, flag)
				};

				/** Lb value function token. */
				class Lb : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Lb)
					DEF_PERFORM(vecOper, flag)
				};

				/** Ln value function token. */
				class Ln : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Ln)
					DEF_PERFORM(vecOper, flag)
				};

				/** Log value function token. */
				class Log : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Log)
					DEF_PERFORM(vecOper, flag)
				};

				/** Sin value function token. */
				class Sin : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Sin)
					DEF_PERFORM(vecOper, flag)
				};

				/** Sqrt value function token. */
				class Sqrt : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Sqrt)
					DEF_PERFORM(vecOper, flag)
				};

				/** Tan value function token. */
				class Tan : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Tan)
					DEF_PERFORM(vecOper, flag)
				};

				/** Jdn function token. */
				class Jdn : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Jdn)
						DEF_PERFORM(vecOper, flag)
				};

				/** Year function token. */
				class Year : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Year)
					DEF_PERFORM(vecOper, flag)
				};

				/** Month function token. */
				class Month : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Month)
					DEF_PERFORM(vecOper, flag)
				};

				/** Day function token. */
				class Day : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Day)
					DEF_PERFORM(vecOper, flag)
				};
				/** Today value function token. */
				class Today : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Today)
					DEF_PERFORM(vecOper, flag)				
				};

				/** Result token. */
				class Result : public OneArgFunction {
					DEF_IS_CONVERTABLE_FROM(Result)
					DEF_PERFORM(vecOper, flag)		
					// static container for result
					static std::vector<Operand::pointer_type> resultVector;
					static void clear(); 					
				};
				


		/** Two argument function token base class. */
		class TwoArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 2; }
			//			DECL_OPERATION_PERFORM()
		};

				/** Max value function token. */
				class Max : public TwoArgFunction {
					DEF_IS_CONVERTABLE_FROM(Max)
					DEF_PERFORM(vecOper, flag)
				};

				/** Min value function token. */
				class Min : public TwoArgFunction {
					DEF_IS_CONVERTABLE_FROM(Min)
					DEF_PERFORM(vecOper, flag)
				};

				/** Pow value function token. */
				class Pow : public TwoArgFunction {
					DEF_IS_CONVERTABLE_FROM(Pow)
					DEF_PERFORM(vecOper, flag)
				};

				/** Arctan2 value function token. */
				class Arctan2 : public TwoArgFunction {
					DEF_IS_CONVERTABLE_FROM(Arctan2)
					DEF_PERFORM(vecOper, flag)					
				};

		/** Three argument function token base class. */
		class ThreeArgFunction : public Function {
		public:
			virtual unsigned number_of_args() const override { return 3; }				
			//			DECL_OPERATION_PERFORM()
		};
				/** Greg function token. */
				class Greg : public ThreeArgFunction {
					DEF_IS_CONVERTABLE_FROM(Greg)
					DEF_PERFORM(vecOper, flag)
				};
				/** Julian function token. */
				class Julian : public ThreeArgFunction {
					DEF_IS_CONVERTABLE_FROM(Julian)
					DEF_PERFORM(vecOper, flag)
				};

				


/*=============================================================

Revision History

Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.0.2: 2014-10-30
Removed binary function

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
#endif // GUARD_function_hpp20091126_
