#include "../TCalculator.cpp"
#include "gtest.h"

TEST(TCalculator, can_create_calculator)
{
	ASSERT_NO_THROW(TCalculator calc);
}

TEST(TCalculator, can_set_correct_infix)
{
	TCalculator calc;
	ASSERT_NO_THROW(calc.setInfix("2/5+3*5^7"));
}

TEST(TCalculator, cant_set_incorrect_infix_with_brackets)
{
	TCalculator calc;
	ASSERT_ANY_THROW(calc.setInfix("((2/5)+3*5^7"));
	ASSERT_ANY_THROW(calc.setInfix("(2/5)+3*5^7)"));
}

TEST(TCalculator, cant_set_incorrect_infix_with_operations)
{
	TCalculator calc;
	ASSERT_ANY_THROW(calc.setInfix("((2/5)+3*5^7"));
	ASSERT_ANY_THROW(calc.setInfix("(2/5)+3*5^7)"));
}
