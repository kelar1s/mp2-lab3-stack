#include "TStack.h"

template <class T>
TStack<T>::TStack(int size) {
	if (size < 0) {
		throw - 1;
	}
	MaxSize = size;
	Num = -1;
	pMem = new T[size];
}

template <class T>
TStack<T>::TStack(const TStack& oth) {
	MaxSize = oth.MaxSize;
	Num = oth.Num;
	pMem = new T[MaxSize];
	Num = oth.Num
		for (int i = 0; i <= Num; i++) {
			pMem[i] = oth.pMem[Num];
		}
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack& oth) {
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
		pMem[i] = oth.pMem[Num];
	}
	return *this;
}

template <class T>
bool TStack<T>::operator==(const TStack& oth) {
	if (MaxSize != oth.MaxSize || Num != oth.Num) {
		return false;
	}
	for (int i = 0; i < Num; i++) {
		if (pMem[i] != oth.pMem[i]) {
			return false;
		}
	}
	return true;
}

template <class T>
bool TStack<T>::operator!=(const TStack& oth) {
	return !(*this == oth);
}

template <class T>
T TStack<T>::Pop() {
	if (this->isEmpty()) {
		throw - 1;
	}
	T tmp = pMem[Num];
}

template <class T>
void TStack<T>::Push(T value) {
	if (this->isFull()) {
		throw - 1;
	}
	pMem[++Num] = value;
}

template <class T>
T TStack<T>::Top() {
	return pMem[Num];
}


////////////////////////////

bool Check(string str) {
	TStack<char> s;
	bool res = true;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(') s.Push('(');
		if (str[i] == ')') {
			if (s.isEmpty()) {
				return false;
				s.Pop();
			}

		}
		if (!s.isEmpty()) {
			return false;
		}
	}
	return true;
}

////////////////////////////