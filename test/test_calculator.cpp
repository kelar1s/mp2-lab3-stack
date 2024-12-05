#include "../TCalculator.cpp"
#include "gtest.h"

TEST(TCalculator, can_create_calculator)
{
	ASSERT_NO_THROW(TCalculator calc);
}

TEST(TCalculator, can_set_infix)
{
	TCalculator calc;
	ASSERT_NO_THROW(calc.setInfix("2/5+3*5^7"));
	ASSERT_NO_THROW(calc.setInfix("(2/5+(3*5)^(7+1)) - cos(30)"));
};

TEST(TCalculator, can_set_postfix)
{
	TCalculator calc;
	calc.setInfix("1 + 2 * 2");
	ASSERT_NO_THROW(calc.setPostfix());
	EXPECT_EQ(calc.getPostfix(), "1 2 2 * + ");
	calc.setInfix("((cos(-30) / 20 * 5 ^ 2))");
	ASSERT_NO_THROW(calc.setPostfix());
	EXPECT_EQ(calc.getPostfix(), "-30 cos 20 / 5 2 ^ * ");
}

TEST(TCalculator, cant_calculate_incorrect_mathematical_expression)
{
	TCalculator calc;
	ASSERT_ANY_THROW(calc.setInfix("((1 + 1) + 2 +(3 + 3"));
	calc.setInfix("1 ++ 2 ** 2 ^ ++2 + cos(30)");
	ASSERT_ANY_THROW(calc.Calc());
	calc.setPostfix();
	ASSERT_ANY_THROW(calc.CalcPostfix());
}

//------------------------CALCULATE POSTFIX------------------------//

TEST(TCalculator, can_calculate_correct_postfix_with_add_operations)
{
	TCalculator calc;
	calc.setInfix("(1 + 2 + 3 + 4 + (6 + 6) + 12 + 0.5)");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), (1 + 2 + 3 + 4 + (6 + 6) + 12 + 0.5));
};

TEST(TCalculator, can_calculate_correct_postfix_with_sub_operations)
{
	TCalculator calc;
	calc.setInfix("(100 - 50) - 25 - 1 - 2 - (3 - 4) - 1 - 1.5");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), (100 - 50) - 25 - 1 - 2 - (3 - 4) - 1 - 1.5);
};

TEST(TCalculator, can_calculate_correct_postfix_with_mult_operations)
{
	TCalculator calc;
	calc.setInfix("1 * 2 * (3 * 4) * 5 * 6 * 7 * 1.1");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), 5544);
};

TEST(TCalculator, can_calculate_correct_postfix_with_div_operations)
{
	TCalculator calc;
	calc.setInfix("(((600 / 10) / 30) / 2) / 2");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), 0.5);
};

TEST(TCalculator, can_calculate_correct_postfix_with_pow_operations)
{
	TCalculator calc;
	calc.setInfix("0.5 ^ 2");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), 0.25);
	calc.setInfix("2 ^ 5");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), 32);
};

TEST(TCalculator, can_calculate_correct_postfix_with_sin_operations)
{
	TCalculator calc;
	calc.setInfix("sin(1.5708)");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), 1.0, 1e-9);
	calc.setInfix("sin(90)");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), 0.8939966636, 1e-9);
};

TEST(TCalculator, can_calculate_correct_postfix_with_cos_operations)
{
	TCalculator calc;
	calc.setInfix("cos(6.28319)");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), 1.0, 1e-9);
	calc.setInfix("cos(30)");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), 0.15425144988, 1e-9);
};

TEST(TCalculator, can_calculate_correct_postfix_with_exp_operations)
{
	TCalculator calc;
	calc.setInfix("exp(0)");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), 1.0, 1e-9);
	calc.setInfix("exp(2)");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), 7.38905609893, 1e-9);
};

TEST(TCalculator, can_calculate_correct_postfix_with_unary_minus)
{
	TCalculator calc;
	calc.setInfix("(-1) + (-2) + (-3) + 6");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), 0);
	calc.setInfix("(-1) + cos(-30) * (-1) + (-3) * 3");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), -10.1542514499, 1e-9);
};

TEST(TCalculator, can_calculate_correct_mixed_postfix)
{
	TCalculator calc;
	calc.setInfix("cos(30) + (10 / 5) + 2 * 2 - exp(0) + (sin(90) + 1) + (-1)");
	calc.setPostfix();
	EXPECT_NEAR(calc.CalcPostfix(), 6.04824811349, 1e-9);
	calc.setInfix("25 / 5 + (1 * 2) - (303 * 2) + (1 + (2.5/2) + 1 * (2 - 3)) + 1.5");
	calc.setPostfix();
	EXPECT_EQ(calc.CalcPostfix(), -596.25);
};

//------------------------CALCULATE INFIX------------------------

TEST(TCalculator, can_calculate_correct_infix_with_add_operations)
{
	TCalculator calc;
	calc.setInfix("(1 + 2 + 3 + 4 + (6 + 6) + 12 + 0.5)");
	EXPECT_EQ(calc.Calc(), 34.5);
};

TEST(TCalculator, can_calculate_correct_infix_with_sub_operations)
{
	TCalculator calc;
	calc.setInfix("(100 - 50) - 25 - 1 - 2 - (3 - 4) - 1 - 1.5");
	EXPECT_EQ(calc.Calc(), 20.5);
};

TEST(TCalculator, can_calculate_correct_infix_with_mult_operations)
{
	TCalculator calc;
	calc.setInfix("1 * 2 * (3 * 4) * 5 * 6 * 7 * 1.1");
	EXPECT_EQ(calc.Calc(), 5544);
};

TEST(TCalculator, can_calculate_correct_infix_with_div_operations)
{
	TCalculator calc;
	calc.setInfix("(((600 / 10) / 30) / 2) / 2");
	EXPECT_EQ(calc.Calc(), 0.5);
};

TEST(TCalculator, can_calculate_correct_infix_with_pow_operations)
{
	TCalculator calc;
	calc.setInfix("0.5 ^ 2");
	EXPECT_EQ(calc.Calc(), 0.25);
	calc.setInfix("2 ^ 5");
	EXPECT_EQ(calc.Calc(), 32);
};

TEST(TCalculator, can_calculate_correct_infix_with_sin_operations)
{
	TCalculator calc;
	calc.setInfix("sin(1.5708)");
	EXPECT_NEAR(calc.Calc(), 1.0, 1e-9);
	calc.setInfix("sin(90)");
	EXPECT_NEAR(calc.Calc(), 0.8939966636, 1e-9);
};

TEST(TCalculator, can_calculate_correct_infix_with_cos_operations)
{
	TCalculator calc;
	calc.setInfix("cos(6.28319)");
	EXPECT_NEAR(calc.Calc(), 1.0, 1e-9);
	calc.setInfix("cos(30)");
	EXPECT_NEAR(calc.Calc(), 0.15425144988, 1e-9);
};

TEST(TCalculator, can_calculate_correct_infix_with_exp_operations)
{
	TCalculator calc;
	calc.setInfix("exp(0)");
	EXPECT_NEAR(calc.Calc(), 1.0, 1e-9);
	calc.setInfix("exp(2)");
	EXPECT_NEAR(calc.Calc(), 7.38905609893, 1e-9);
};

TEST(TCalculator, can_calculate_correct_infix_with_unary_minus)
{
	TCalculator calc;
	calc.setInfix("(-1) + (-2) + (-3) + 6");
	EXPECT_EQ(calc.Calc(), 0);
	calc.setInfix("(-1) + cos(-30) * (-1) + (-3) * 3");
	EXPECT_NEAR(calc.Calc(), -10.1542514499, 1e-9);
};

TEST(TCalculator, can_calculate_correct_mixed_infix)
{
	TCalculator calc;
	calc.setInfix("cos(30) + (10 / 5) + 2 * 2 - exp(0) + (sin(90) + 1) + (-1)");
	EXPECT_NEAR(calc.Calc(), 6.04824811349, 1e-9);
	calc.setInfix("25 / 5 + (1 * 2) - (303 * 2) + (1 + (2.5/2) + 1 * (2 - 3)) + 1.5");
	EXPECT_EQ(calc.Calc(), -596.25);
};












