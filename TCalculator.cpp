#include "TCalculator.h"

double TCalculator::CalcPostfix() {
	stNum.Clear();
	for (int i = 0; i < postfix.size(); i++) {
		if (postfix[i] >= '0' && postfix[i] <= '9') {
			stNum.Push(postfix[i] - '0');
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/') {
			double secondNum = stNum.Pop();
			double firstNum = stNum.Pop();
			switch (postfix[i])
			{
			case('+'):
				stNum.Push(firstNum + secondNum);
				break;
			case('-'):
				stNum.Push(firstNum - secondNum);
				break;
			case('*'):
				stNum.Push(firstNum * secondNum);
				break;

			case('/'):
				stNum.Push(firstNum / secondNum);
				break;
			}
		}
	}

	double result = stNum.Pop();
	if (!stNum.isEmpty()) {
		throw -1;
	}
	return result;
}

void TCalculator::setInfix() {
	getline(cin, infix);
}

string TCalculator::getInfix() {
	return infix;
}