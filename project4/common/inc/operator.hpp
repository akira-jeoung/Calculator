#if !defined(GUARD_operator_hpp20091126_)
#define GUARD_operator_hpp20091126_

/** @file: operator.hpp
	@author Garth Santor/Trinh Han
	@author garth.santor@sympatico.ca
	@author http://www.gats.ca/
	@date 2012-11-16
	@version 0.2.0
	@note Compiles under Visaul C++ v110

	@brief Operator class declarations
	*/
/*
Bill Jeoung
2016-11-20
*/

#include "operation.hpp"
#include "operand.hpp"
#include "integer.hpp"
#include "boolean.hpp"
#include "real.hpp"
#include "variable.hpp"


/** Operator Precedence values. */
typedef enum { 
	MIN = 0, 
	ASSIGNMENT,
	LOGOR,
	LOGXOR,
	LOGAND,
	BITOR,
	BITAND,
	EQUALITY,
	RELATIONAL,
	BITSHIFT,
	ADDITIVE, 
	MULTIPLICATIVE,  
	POWER, 
	UNARY, 
	POSTFIX, 
	MAX } precedence_type;



/** Defines a precedence category method.  Used inside a class declaration. */
#define DEF_PRECEDENCE(category)	public: precedence_type get_precedence() const override { return category; }

#define DEF_PERFORM(vecOper, flag) Operand::pointer_type perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) override;


/** Operator token base class. */
class Operator : public Operation {
public:
	DEF_POINTER_TYPE(Operator)
	virtual precedence_type get_precedence() const = 0;	
	Operand::pointer_type perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) override = 0;
};

		/** Binary operator token base class. */
		class BinaryOperator : public Operator {
		public:
			virtual unsigned number_of_args() const override { return 2; }
			Operand::pointer_type perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) override = 0;
		};

				/** Right-associative operator base class. */
				class RAssocOperator : public BinaryOperator { };

						/** Power token. */
						class Power : public RAssocOperator {
						DEF_IS_CONVERTABLE_FROM(Power)
						DEF_PRECEDENCE(POWER)
						DEF_PERFORM(vecOper, flag)
						};

						/** Assignment token. */
						class Assignment : public RAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Assignment)
							DEF_PRECEDENCE(ASSIGNMENT)
							DEF_PERFORM(vecOper, flag)
						};

				/** Left-associative operator base class. */
				class LAssocOperator : public BinaryOperator { };


						/** Addition token. */
						class Addition : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Addition)
							DEF_PRECEDENCE(ADDITIVE)
							DEF_PERFORM(vecOper, flag)
						};

						/** Subtraction token. */
						class Subtraction : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Subtraction)
							DEF_PRECEDENCE(ADDITIVE)
							DEF_PERFORM(vecOper, flag)
						};


						/** Division token. */
						class Division : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Division)
							DEF_PRECEDENCE(MULTIPLICATIVE)
							DEF_PERFORM(vecOper, flag)
						};

						/** Multiplication token. */
						class Multiplication : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Multiplication)
							DEF_PRECEDENCE(MULTIPLICATIVE)
							DEF_PERFORM(vecOper, flag)
						};

						/** Modulus token. */
						class Modulus : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Modulus)
							DEF_PRECEDENCE(MULTIPLICATIVE)
							DEF_PERFORM(vecOper, flag)
						};
												

						/** And token. */
						class And : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(And)
							DEF_PRECEDENCE(LOGAND)
							DEF_PERFORM(vecOper, flag)
						};

						/** Nand token. */
						class Nand : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Nand)
							DEF_PRECEDENCE(LOGAND)
							DEF_PERFORM(vecOper, flag)
						};

						/** Nor token. */
						class Nor : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Nor)
							DEF_PRECEDENCE(LOGOR)
							DEF_PERFORM(vecOper, flag)
						};

						/** Or token. */
						class Or : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Or)
							DEF_PRECEDENCE(LOGOR)
							DEF_PERFORM(vecOper, flag)
						};

						/** Xor token. */
						class Xor : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Xor)
							DEF_PRECEDENCE(LOGXOR)
							DEF_PERFORM(vecOper, flag)
						};

						/** Xnor token. */
						class Xnor : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Xnor)
							DEF_PRECEDENCE(LOGXOR)
							DEF_PERFORM(vecOper, flag)
						};

						/** Equality token. */
						class Equality : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Equality)
							DEF_PRECEDENCE(EQUALITY)
							DEF_PERFORM(vecOper, flag)
						};

						/** Greater token. */
						class Greater : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Greater)
							DEF_PRECEDENCE(RELATIONAL)
							DEF_PERFORM(vecOper, flag)
						};

						/** GreaterEqual token. */
						class GreaterEqual : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(GreaterEqual)
							DEF_PRECEDENCE(RELATIONAL)
							DEF_PERFORM(vecOper, flag)
						};

						/** Inequality token. */
						class Inequality : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Inequality)
							DEF_PRECEDENCE(EQUALITY)
							DEF_PERFORM(vecOper, flag)
						};

						/** Less token. */
						class Less : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(Less)
							DEF_PRECEDENCE(RELATIONAL)
							DEF_PERFORM(vecOper, flag)
						};

						/** LessEqual token. */
						class LessEqual : public LAssocOperator {
							DEF_IS_CONVERTABLE_FROM(LessEqual)
							DEF_PRECEDENCE(RELATIONAL)
							DEF_PERFORM(vecOper, flag)
						};
						


		/** Unary operator token base class. */
		class UnaryOperator : public Operator {
		public:
			virtual unsigned number_of_args() const override { return 1; }
			Operand::pointer_type perform(std::vector<Operand::pointer_type>& vecOper, unsigned& flag) override = 0;
		};
				/** Factorial token */
				class Factorial : public UnaryOperator {
					DEF_IS_CONVERTABLE_FROM(Factorial)
					DEF_PRECEDENCE(POSTFIX)
					DEF_PERFORM(vecOper, flag)
				};
				/** Identity token. */
				class Identity : public UnaryOperator {
					DEF_IS_CONVERTABLE_FROM(Identity)
					DEF_PRECEDENCE(UNARY)
					DEF_PERFORM(vecOper, flag)
				};
				/** operator base class. */
				class Negation : public UnaryOperator {
					DEF_IS_CONVERTABLE_FROM(Negation)
					DEF_PRECEDENCE(UNARY)
					DEF_PERFORM(vecOper, flag)
				};

				/** Not token. */
				class Not : public UnaryOperator {
					DEF_IS_CONVERTABLE_FROM(Not)
						DEF_PRECEDENCE(UNARY)
						DEF_PERFORM(vecOper, flag)
				};



/*=============================================================

Revision History
Version 1.0.0: 2016-11-02
Added 'override' keyword where appropriate.

Version 0.3.0: 2014-10-30
Removed bitwise operators.

Version 0.2.0: 2012-11-16
Added BitAnd, BitNot, BitOr, BitShiftLeft, BitShiftRight

Version 0.1.1: 2012-11-13
C++ 11 cleanup

Version 0.1.0: 2010-11-09
Switched boost::shared_ptr<> to std::shared_ptr<>.
Added TOKEN_PTR_TYPE macro.

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
#endif // GUARD_operator_hpp20091126_
