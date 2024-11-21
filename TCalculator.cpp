#include "TCalculator.h"

TCalculator::TCalculator(): stNum(100), stChar(100) {}

double TCalculator::CalcPostfix() 
{
    stNum.Clear();
    for (int i = 0; i < postfix.size(); i++) { 
        if ((postfix[i] >= '0' && postfix[i] <= '9') || postfix[i] == '.') {
            size_t idx;
            double ntmp = std::stod(&postfix[i], &idx);
            stNum.Push(ntmp);
            i += idx - 1;
        }
        else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '^') {
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
                if (secondNum == 0) {
                    throw - 1;
                }
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

double TCalculator::Calc() {
    stNum.Clear();
    stChar.Clear();
    std::string tmp = '(' + infix + ')';
    for (int i = 0; i < tmp.size(); i++) {
        if (tmp[i] == '(') {
            stChar.Push('(');
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                stNum.Push(res);
                i += idx;
            }
        }
        else if (tmp[i] == '+' || tmp[i] == '-' || tmp[i] == '*' || tmp[i] == '/' || tmp[i] == '^') {
            while (Prior(stChar.Top()) >= Prior(tmp[i])) {
                char a = stChar.Pop();
                double secondNum = stNum.Pop();
                double firstNum = stNum.Pop();
                switch (a)
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
                    if (secondNum == 0) {
                        throw - 1;
                    }
                    stNum.Push(firstNum / secondNum);
                    break;
                case '^':
                    stNum.Push(pow(firstNum, secondNum));
                    break;
                }
            }
            stChar.Push(tmp[i]);
        }
        else if (tmp[i] >= '0' && tmp[i] <= '9' || tmp[i] == '.') {
            size_t idx;
            double res = std::stod(&tmp[i], &idx);
            stNum.Push(res);
            i += idx - 1;
        }
        else if (tmp[i] == ')') {
            while (stChar.Top() != '(') {
                char a = stChar.Pop();
                double secondNum = stNum.Pop();
                double firstNum = stNum.Pop();
                switch (a)
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
                    if (secondNum == 0) {
                        throw - 1;
                    }
                    stNum.Push(firstNum / secondNum);
                    break;
                case '^':
                    stNum.Push(pow(firstNum, secondNum));
                    break;
                }
            }
            stChar.Pop();
        }
    }
    double res = stNum.Pop();
    if (!stNum.isEmpty()) throw - 1;
    return res;
}

void TCalculator::setInfix(std::string str) 
{
    if (Check(str) && CheckOperators(str)) {
        infix = str;
    }
    else {
        throw -1;
    }
}

std::string TCalculator::getInfix() 
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
    std::string tmp = "(" + infix + ")";
    bool wasOperator = true;
    for (int i = 0; i < tmp.length(); i++) {
        if (tmp[i] == '(') {
            stChar.Push(tmp[i]);
            wasOperator = true;
        }
        else if ((tmp[i] >= '0' && tmp[i] <= '9')) {
            postfix += tmp[i];
            wasOperator = false;
            if (tmp[i + 1] != '.' && (i + 1 == tmp.length() || !isdigit(tmp[i + 1]))) {
                postfix += ' ';
            }
        }
        else if (tmp[i] == '.') {
            postfix += tmp[i];
        }
        else if (tmp[i] == ')') {
            char tmp_char = stChar.Pop();
            while (tmp_char != '(' && !stChar.isEmpty()) {
                postfix += tmp_char;
                postfix += ' ';
                tmp_char = stChar.Pop();
            }
            wasOperator = false;
        }
        else if (tmp[i] == '+' || tmp[i] == '-' || tmp[i] == '/' || tmp[i] == '*' || tmp[i] == '^') {
            if (wasOperator && tmp[i] == '-') {
                postfix += '0';
                postfix += ' ';
            }
            while (Prior(stChar.Top()) >= Prior(tmp[i]) && !stChar.isEmpty()) {
                postfix += stChar.Pop();
                postfix += ' ';
            }
            stChar.Push(tmp[i]);
            wasOperator = true;
        }
    }
}


std::string TCalculator::getPostfix() 
{
    return postfix;
}

bool TCalculator::Check(std::string str) 
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

bool TCalculator::CheckOperators(std::string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    for (int i = 1; i < str.size(); i++) {
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
            if (str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == '*' || str[i - 1] == '/' || str[i - 1] == '^') {
                return false;
            }
        }
    }
    return true;
}
