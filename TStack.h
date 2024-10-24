#pragma once

template <class T>

class TStack {
	T* pMem;
	int Num;
	int MaxSize;
public:

	int GetMaxSize() { return MaxSize; }

	TStack(int Size = 10);
	TStack(const TStack& oth);
	~TStack() { delete[] pMem; };

	TStack<T>& TStack<T>::operator=(const TStack& oth);

	bool TStack<T>::operator==(const TStack& oth);
	bool TStack<T>::operator!=(const TStack& oth);

	bool isEmpty() const return Num == -1;
	bool isFull() const return Num == MaxSize - 1;

	void Push(T value);
	T Pop();
	T Top();
};