#pragma once
#include <iostream>


using namespace std;

const int MAX_STACK_SIZE = 1000;


template <class T>
class TStack {
	T* pMem;
	int Num;
	int MaxSize;
public:

	int GetMaxSize() { return MaxSize; }
	TStack(int size = 10);
	TStack(const TStack& oth);
	~TStack() { delete[] pMem; };

	TStack<T>& operator=(const TStack& oth);

	bool operator==(const TStack& oth) const;
	bool operator!=(const TStack& oth) const;

	bool isEmpty() { return Num == -1; };
	bool isFull() { return Num == MaxSize - 1; };

	void Push(T value);
	void Clear();
	T Pop();
	T Top();
};

template <class T>
TStack<T>::TStack(int size) {
	if (size < 0 || size > MAX_STACK_SIZE) {
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
	for (int i = 0; i <= Num; i++) {
		pMem[i] = oth.pMem[i];
	}
}

template <class T>
bool TStack<T>::operator==(const TStack& oth) const
{
	if (MaxSize != oth.MaxSize || Num != oth.Num) {
		return false;
	}
	for (int i = 0; i <= Num; i++) {
		if (pMem[i] != oth.pMem[i]) {
			return false;
		}
	}
	return true;
}

template <class T>
bool TStack<T>::operator!=(const TStack& oth) const
{
	return !(*this == oth);
}

template <class T>
T TStack<T>::Pop() {
	if (this->isEmpty()) {
		throw - 1;
	}
	return pMem[Num--];
}
