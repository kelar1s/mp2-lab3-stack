#include "TCalculator.h"
#include <stdexcept>

int main() {
	TCalculator calculator;
	calculator.setInfix("(1.1 + 1.1) * 2");
	calculator.setPostfix();
	cout << calculator.getInfix() << endl;
	cout << calculator.getPostfix() << endl;
	cout << calculator.CalcPostfix() << endl;
	return 0;
}