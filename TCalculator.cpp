#include "TCalculator.h"

TCalculator::TCalculator(): stNum(100), stChar(100) {}

double TCalculator::CalcPostfix() 
{
    stNum.Clear();
    for (int i = 0; i < postfix.size(); i++) { 
        if ((postfix[i] >= '0' && postfix[i] <= '9') || postfix[i] == '.') {
            size_t idx;
            double ntmp = stod(&postfix[i], &idx);
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
 
    if (Check(str) && CheckOperators(str)) {
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

bool TCalculator::CheckOperators(string str) {
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

//1 - число в стек
//2 - ( в стек
//3 - Такое же правило как и в прошлый раз - положить в стек операцию если приоритет >= оператора с вершины стека
//4 - ) вычислить до открывающей скобки

double TCalculator::Calc() {
    stNum.Clear();
    stChar.Clear();
    string str = '(' + infix + ')';
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    for (int i = 0; i < str.size(); i++) {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.') {
            if (str[i - 1] == '-' && str[i - 2] == '(') {
                stChar.Pop();
                size_t idx;
                double ntmp = stod(&postfix[i], &idx);
                stNum.Push(-1 * ntmp);
                i += idx - 1;
            }
            size_t idx;
            double ntmp = stod(&postfix[i], &idx);
            stNum.Push(ntmp);
            i += idx - 1;
        }
        else if (str[i] == '(') {
            stChar.Push(str[i]);
        }
        else if (str[i] == ')') {
            char a = stChar.Pop();
            while (a != '(') {
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
                    stNum.Push(firstNum / secondNum);
                    break;
                case '^':
                    stNum.Push(pow(firstNum, secondNum));
                    break;
                }
                stChar.Pop();
            }
        }
        else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^') {
            while (Prior(stChar.Top()) >= Prior(str[i]) && !stChar.isEmpty()) {
                double secondNum = stNum.Pop();
                double firstNum = stNum.Pop();
                char a = stChar.Pop();
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
                    stNum.Push(firstNum / secondNum);
                    break;
                case '^':
                    stNum.Push(pow(firstNum, secondNum));
                    break;
                }
            }
            stChar.Push(str[i]);
        }
        stChar.Push(str[i]);
    }
}