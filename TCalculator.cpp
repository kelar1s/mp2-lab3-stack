#include "TCalculator.h"
#include <math.h>

double TCalculator::CalcPostfix() {
    stNum.Clear();
    for (int i = 0; i < postfix.size(); i++) {
        if (postfix[i] >= '0' && postfix[i] <= '9' || postfix[i] == '.'
            || postfix[i] == '-' && postfix[i + 1] >= '0' && postfix[i + 1] <= '9') {
            size_t idx;
            double tmp = std::stod(&postfix[i], &idx);
            stNum.Push(tmp);
            i += idx - 1;
        }
        else if (postfix[i] == tAdd || postfix[i] == tSub || postfix[i] == tMult || postfix[i] == tDiv || postfix[i] == tPow) {
            double secondNum = stNum.Pop();
            double firstNum = stNum.Pop();
            switch (postfix[i])
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
        else if (postfix[i] == 'c' && postfix.substr(i, 3) == "cos") {
            i += 2;
            stNum.Push(cos(stNum.Pop()));
        }
        else if (postfix[i] == 's' && postfix.substr(i, 3) == "sin") {
            i += 2;
            stNum.Push(sin(stNum.Pop()));
        }
        else if (postfix[i] == 'e' && postfix.substr(i, 3) == "exp") {
            i += 2;
            stNum.Push(exp(stNum.Pop()));
        }
    }
    double result = stNum.Pop();
    if (!stNum.isEmpty()) {
        throw - 1;
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
        else if ((tmp[i] >= '0' && tmp[i] <= '9') || tmp[i] == '.') {
            size_t idx;
            double res = std::stod(&tmp[i], &idx);
            stNum.Push(res);
            i += idx - 1;
        }
        else if (tmp[i] == 's' && tmp.substr(i, 4) == "sin(") {
            stChar.Push(tSin);
            i += 3;
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                stNum.Push(res);
                i += idx;
            }
        }
        else if (tmp[i] == 'c' && tmp.substr(i, 4) == "cos(") {
            stChar.Push(tCos);
            i += 3;
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                stNum.Push(res);
                i += idx;
            }
        }
        else if (tmp[i] == 'e' && tmp.substr(i, 4) == "exp(") {
            stChar.Push(tExp);
            i += 3;
            if (tmp[i + 1] == '-') {
                size_t idx;
                double res = std::stod(&tmp[i + 1], &idx);
                stNum.Push(res);
                i += idx;
            }
        }
        else if (tmp[i] == tAdd || tmp[i] == tSub || tmp[i] == tMult || tmp[i] == tDiv || tmp[i] == tPow) {
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
        else if (tmp[i] == ')'){
            while (!(stChar.Top() == tLeftBracket || stChar.Top() == tSin || stChar.Top() == tCos || stChar.Top() == tExp)) {
                double secondNum = stNum.Pop();
                double firstNum = stNum.Pop();
                switch (stChar.Pop())
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
            switch (stChar.Pop())
            {
            case tLeftBracket:
                break;
            case tSin:
                stNum.Push(sin(stNum.Pop()));
                break;
            case tCos:
                stNum.Push(cos(stNum.Pop()));
                break;
            case tExp:
                stNum.Push(exp(stNum.Pop()));
                break;
            }
        }
    }
    double result = stNum.Pop();
    if (!stNum.isEmpty()) throw - 1;
    return result;
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
                postfix += '-';
                i++;
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
                postfix += '-';
                i++;
            }
        }
        else if (tmp[i] == 'c' && tmp.substr(i, 4) == "cos(") {
            stChar.Push(tCos);
            i += 3;
            if (tmp[i + 1] == '-') {
                postfix += '-';
                i++;
            }
        }
        else if (tmp[i] == 'e' && tmp.substr(i, 4) == "exp(") {
            stChar.Push(tExp);
            i += 3;
            if (tmp[i + 1] == '-') {
                postfix += '-';
                i++;
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
    TStack<char> s;
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
