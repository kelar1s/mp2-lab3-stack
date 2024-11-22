#include "TCalculator.h"
#include <math.h>

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
        if (tmp[i] == tLeftBracket) {
            stChar.Push(tLeftBracket);
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                stNum.Push(res);
                i += idx;
            }
        }

        else if (tmp[i] == 's') {
            if (tmp[i + 1] == 'i' && tmp[i + 2] == 'n' && tmp[i + 3] == '(') {
                stChar.Push(tSin);
                i += 3;
                if (tmp[i + 1] == '-') {
                    size_t idx;
                    double res = std::stod(&tmp[i + 1], &idx);
                    stNum.Push(res);
                    i += idx;
                }
            }
        }
        else if (tmp[i] == 'c') {
            if (tmp[i + 1] == 'o' && tmp[i + 2] == 's' && tmp[i + 3] == '(') {
                stChar.Push(tCos);
                i += 3;
                if (tmp[i + 1] == '-') {
                    size_t idx;
                    double res = std::stod(&tmp[i + 1], &idx);
                    stNum.Push(res);
                    i += idx;
                }
            }
        }
        else if (tmp[i] == 'e') {
            if (tmp[i + 1] == 'x' && tmp[i + 2] == 'p' && tmp[i + 3] == '(') {
                stChar.Push(tExp);
                i += 3;
                if (tmp[i + 1] == '-') {
                    size_t idx;
                    double res = std::stod(&tmp[i + 1], &idx);
                    stNum.Push(res);
                    i += idx;
                }
            }
        }
        else if (tmp[i] == tAdd || tmp[i] == tSub || tmp[i] == tMult || tmp[i] == tDiv || tmp[i] == tPow) {
            while (!stChar.isEmpty() && Prior(stChar.Top()) >= Prior(tmp[i])) {
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
        else if ((tmp[i] >= '0' && tmp[i] <= '9') || tmp[i] == '.') {
            size_t idx;
            double res = std::stod(&tmp[i], &idx);
            stNum.Push(res);
            i += idx - 1;
        }
        else if (tmp[i] == ')') {
            while (!stChar.isEmpty() && stChar.Top() != tLeftBracket) {
                char a = stChar.Pop();
                if (a == tSin || a == tCos || a == tExp) {
                    double Num = stNum.Pop();
                    switch (a) {
                    case tSin:
                        stNum.Push(sin(Num));
                        break;
                    case tCos:
                        stNum.Push(cos(Num));
                        break;
                    case tExp:
                        stNum.Push(exp(Num));
                        break;
                    }
                }
                else {
                    double secondNum = stNum.Pop();
                    double firstNum = stNum.Pop();
                    switch (a)
                    {
                    case tAdd:
                        stNum.Push(firstNum + secondNum);
                        break;
                    case tSub:
                        stNum.Push(firstNum - secondNum);
                        break;
                    case tMult:
                        stNum.Push(firstNum * secondNum);
                        break;
                    case tDiv:
                        if (secondNum == 0) {
                            throw - 1;
                        }
                        stNum.Push(firstNum / secondNum);
                        break;
                    case tPow:
                        stNum.Push(pow(firstNum, secondNum));
                        break;
                    }
                }
            }
            if (!stChar.isEmpty() && stChar.Top() == tLeftBracket) {
                stChar.Pop();
            }
        }
    }
    double res = stNum.Pop();
    if (!stNum.isEmpty()) throw - 1;
    return res;
}

void TCalculator::setInfix(std::string str) 
{
    if (Check(str)) {
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
    if (op == tAdd || op == tSub) {
        return 1;
    }
    else if (op == tMult || op == tDiv) {
        return 2;
    }
    else if (op == tPow) {
        return 3;
    }
    else if (op == tLeftBracket || op == tSin || op == tCos || op == tExp) {
        return 0;
    }
    return -1;
}

void TCalculator::setPostfix() 
{
    postfix = "";
    stChar.Clear();
    std::string tmp = "(" + infix + ")";
    for (int i = 0; i < tmp.length(); i++) 
    {
        if (tmp[i] == tLeftBracket) {
            stChar.Push(tLeftBracket);
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                std::string str = std::to_string(res);
                postfix += str.substr(0, str.find_last_not_of('0')) + ' ';
                i += idx;
            }
        }
        else if ((tmp[i] >= '0' && tmp[i] <= '9')) {
            postfix += tmp[i];
            if (tmp[i + 1] != '.' && (!isdigit(tmp[i + 1])))  postfix += ' ';
        }
        else if (tmp[i] == '.') {
            postfix += tmp[i];
        }
        else if (tmp[i] == tAdd || tmp[i] == tSub || tmp[i] == tMult || tmp[i] == tDiv || tmp[i] == tPow) {
            while (Prior(stChar.Top()) >= Prior(tmp[i])) {
                postfix += stChar.Pop();
                postfix += " ";
            }
            stChar.Push(tmp[i]);
        }
        else if (tmp[i] == 's' && tmp.substr(i, 4) == "sin(") {
            stChar.Push(tSin);
            i += 3;
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                std::string str = std::to_string(res);
                postfix += str.substr(0, str.find_last_not_of('0')) + ' ';
                i += idx;
            }
        }
        else if (tmp[i] == 'c' && tmp.substr(i, 4) == "cos(") {
            stChar.Push(tCos);
            i += 3;
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                std::string str = std::to_string(res);
                postfix += str.substr(0, str.find_last_not_of('0')) + ' ';
                i += idx;
            }
        }
        else if (tmp[i] == 'e' && tmp.substr(i, 4) == "exp(") {
            stChar.Push(tExp);
            i += 3;
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                std::string str = std::to_string(res);
                postfix += str.substr(0, str.find_last_not_of('0')) + ' ';
                i += idx;
            }
        }
        else if (tmp[i] == ')') {
            while (!(stChar.Top() == tLeftBracket || stChar.Top() == tSin || stChar.Top() == tCos || stChar.Top() == tExp)) {
                postfix += stChar.Pop();
                postfix += ' ';
            }
            char intmp = stChar.Pop();
            switch (intmp) {
            case tSin:
                postfix += "sin ";
                break;
            case tCos:
                postfix += "cos ";
                break;
            case tExp:
                postfix += "exp ";
                break;
            }     
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
