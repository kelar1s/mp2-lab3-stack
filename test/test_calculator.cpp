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
	ASSERT_NO_THROW(calc.setInfix("(2/5+(3*5)^(7+1))"));
}

TEST(TCalculator, cant_set_incorrect_infix_with_brackets)
{
	TCalculator calc;
	ASSERT_ANY_THROW(calc.setInfix("((2/5)+3*5^7"));
	ASSERT_ANY_THROW(calc.setInfix("(2/5)+3*5^7)"));
	ASSERT_ANY_THROW(calc.setInfix("(((((2/5)+(3*5^7)))"));
}

TEST(TCalculator, cant_set_incorrect_infix_with_operations)
{
	TCalculator calc;
	ASSERT_ANY_THROW(calc.setInfix("(2/5)+3* *5^7"));
	ASSERT_ANY_THROW(calc.setInfix("(2/5+-)+3*5-^7"));
}

TEST(TCalculator, can_set_postfix)
{
	TCalculator calc;
	calc.setInfix("2.1+2+(-3)+5^(-2)+3/3*9");
	ASSERT_NO_THROW(calc.setPostfix());
}

TEST(TCalculator, can_calculate_postfix)
{
	TCalculator calc;
	calc.setInfix("2.1+2+(-3)+5^(-2)+3/3*9");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), 10.14);
}

