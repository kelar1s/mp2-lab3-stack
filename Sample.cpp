#include "TCalculator.h"
#include <stdexcept>

int main() 
{
	TCalculator calculator;
	calculator.setInfix("10 ^ 2 + 10 / 10 + 10 * 2 + (1 + (1 + 1))");
	calculator.setPostfix();
	std::cout << "Infix form: " << calculator.getInfix() << std::endl;
	std::cout << "Postfix form: " << calculator.getPostfix() << std::endl;
	std::cout << "Answer: " << calculator.CalcPostfix() << std::endl;
	
	std::cout << std::endl;

	calculator.setInfix("(-1) + (-3) + (-3)^2 + 2 * 2 + ((-1) * (-1) - 1)");
	calculator.setPostfix();
	std::cout << "Infix form: " << calculator.getInfix() << std::endl;
	std::cout << "Postfix form: " << calculator.getPostfix() << std::endl;
	std::cout << "Answer: " << calculator.CalcPostfix() << std::endl;
	
	std::cout << std::endl;

	calculator.setInfix("1.1 ^ 2 + 10.5 ^ 2 + 1.1 ^ 5 + (-1.1)^2");
	calculator.setPostfix();
	std::cout << "Infix form: " << calculator.getInfix() << std::endl;
	std::cout << "Postfix form: " << calculator.getPostfix() << std::endl;
	std::cout << "Answer: " << calculator.CalcPostfix() << std::endl;

	calculator.setInfix("sin(90) + cos(90) + exp(2)^2");
	std::cout << "Infix form: " << calculator.getInfix() << std::endl;
	std::cout << "Answer: " << calculator.Calc() << std::endl;
	
	std::cout << std::endl;

	calculator.setInfix("1 + cos(30)^2 + exp(2) - sin(-60) + (10 - 11 / 2) + cos(-12) / 2");
	calculator.setPostfix();
	std::cout << "Infix form: " << calculator.getInfix() << std::endl;
	std::cout << "Postfix form: " << calculator.getPostfix() << std::endl;
	std::cout << "Answer: " << calculator.CalcPostfix() << std::endl;

	return 0;
}
