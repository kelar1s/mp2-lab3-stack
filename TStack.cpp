#include "TStack.h"

template <class T>
TStack<T>& TStack<T>::operator=(const TStack& oth) 
{
	if (this == &oth) {
		return *this;
	}
	if (MaxSize != oth.MaxSize) {
		MaxSize = oth.MaxSize;
		delete[] pMem;
		pMem = new T[MaxSize];
	}
	Num = oth.Num;
	for (int i = 0; i <= Num; i++) {
		pMem[i] = oth.pMem[i];
	}
	return *this;
}

template <class T>
void TStack<T>::Push(T value) 
{
	if (this->isFull()) {
		throw - 1;
	}
	pMem[++Num] = value;
}

template <class T>
T TStack<T>::Top() 
{
	if (this->isEmpty()) {
		throw - 1;
	}
	return pMem[Num];
}

template <class T>
void TStack<T>::Clear() 
{
	delete[] pMem;
	Num = -1;
}


////////////////////////////

//bool Check(string str) {
//	TStack<char> s;
//	bool res = true;
//	for (int i = 0; i < str.size(); i++) {
//		if (str[i] == '(') s.Push('(');
//		if (str[i] == ')') {
//			if (s.isEmpty()) {
//				return false;
//				s.Pop();
//			}
//
//		}
//		if (!s.isEmpty()) {
//			return false;
//		}
//	}
//	return true;
//}

////////////////////////////