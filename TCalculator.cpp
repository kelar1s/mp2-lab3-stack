#include "TCalculator.h"

TCalculator::TCalculator(): stNum(100), stChar(100) {}

double TCalculator::CalcPostfix() 
{
    stNum.Clear();
    int i = 0;
    for (i; i < postfix.size(); i++) {
        /*if (postfix[0] = '-') {
            size_t idx;
            double ntmp = -1 * stod(&postfix[1], &idx);
            stNum.Push(ntmp);
            i += idx - 1;
            ++i;
        }*/
        if (postfix[i] >= '0' && postfix[i] <= '9' || postfix[i] == '.') {
            size_t idx;
            double ntmp = stod(&postfix[i], &idx);
            stNum.Push(ntmp);
            i += idx - 1;
        }
        else if (i != 0 || postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
            double secondNum = stNum.Pop();
            double firstNum = stNum.Pop();
            switch (postfix[i])
            {
            case '+':
                stNum.Push(firstNum + secondNum);
                break;
            case '-':
                stNum.Push(firstNum - secondNum);
                break;
            case '*':
                stNum.Push(firstNum * secondNum);
                break;

            case '/':
                stNum.Push(firstNum / secondNum);
                break;
            case '^':
                stNum.Push(pow(firstNum, secondNum));
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

void TCalculator::setInfix(string str) 
{
 
    if (Check(str)) {
        infix = str;
    }
    else {
        throw -1;
    }
}

string TCalculator::getInfix() 
{
    return infix;
}

int TCalculator::Prior(char op) 
{
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else if (op == '^') {
        return 3;
    }
    else if (op == '(') {
        return 0;
    }
    return -1;
}

void TCalculator::setPostfix() 
{
    postfix = "";
    stChar.Clear();
    string tmp = "(" + infix + ")";
    for (int i = 0; i < tmp.length(); i++) {
        if (tmp[i] == '(') {
            stChar.Push(tmp[i]);
        }
        else if ((tmp[i] >= '0' && tmp[i] <= '9')) {
            postfix += tmp[i];
            if (tmp[i + 1] != '.') {
                postfix += ' ';
            }
        }
        else if ((tmp[i] == '.')) {
            postfix += tmp[i];
        }
        else if (tmp[i] == ')') {
            char tmp_char = stChar.Pop();
            while (tmp_char != '(' && !stChar.isEmpty()) {
                postfix += tmp_char;
                postfix += ' ';
                tmp_char = stChar.Pop();
            }
        }
        else if (tmp[i] == '+' || tmp[i] == '-' || tmp[i] == '/' || tmp[i] == '*' || tmp[i] == '^') {
            while (Prior(stChar.Top()) >= Prior(tmp[i]) && !stChar.isEmpty()) {
                postfix += stChar.Pop();
                postfix += ' ';
            }
            stChar.Push(tmp[i]);
        }
    }
}

string TCalculator::getPostfix() 
{
    return postfix;
}

bool TCalculator::Check(string str) 
{
    TStack<char> s(100);
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '(')
            s.Push('(');
        else if (str[i] == ')') {
            if (s.isEmpty()) {
                return false;
            }
            s.Pop();
        }
    }
    return s.isEmpty();
}