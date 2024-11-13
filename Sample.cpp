#include "TCalculator.h"
#include <stdexcept>

int main() 
{
	TCalculator calculator;
	calculator.setInfix("10 ^ 2 + 10 / 10 + 10 * 2 + (1 + (1 + 1))");
	calculator.setPostfix();
	cout << "Infix form: " << calculator.getInfix() << endl;
	cout << "Postfix form: " << calculator.getPostfix() << endl;
	cout << "Answer: " << calculator.CalcPostfix() << endl;
	
	cout << endl;

	calculator.setInfix("(-1) + (-3) + (-3)^2 + 2 * 2 + ((-1) * (-1) - 1)");
	calculator.setPostfix();
	cout << "Infix form: " << calculator.getInfix() << endl;
	cout << "Postfix form: " << calculator.getPostfix() << endl;
	cout << "Answer: " << calculator.CalcPostfix() << endl;
	
	cout << endl;

	calculator.setInfix("1.1 ^ 2 + 10.5 ^ 2 + 1.1 ^ 5 + (-1.1)^2");
	calculator.setPostfix();
	cout << "Infix form: " << calculator.getInfix() << endl;
	cout << "Postfix form: " << calculator.getPostfix() << endl;
	cout << "Answer: " << calculator.CalcPostfix() << endl;
	return 0;
}