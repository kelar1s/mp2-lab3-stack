template <class T>
struct TNode {
	T val;
	TNode* next = nullptr;
public:
	TNode() {
		val = 0;
	}
	TNode(int value) {
		val = value;
	}
};

template <class T>
class TStack {
	TNode<T>* pFirst;
public:
	TStack();
	TStack(const TStack& oth);
	~TStack();

	bool operator==(const TStack& oth) const;
	bool operator!=(const TStack& oth) const;
	TStack<T>& operator=(const TStack& oth);

	bool isEmpty() { return pFirst == nullptr; }
	bool isFull();

	void Clear();
	
	T Top();
	T Pop();
	void Push(T value);
};

template <class T>
TStack<T>::TStack() {
	pFirst = nullptr;
}

template <class T>
TStack<T>::TStack(const TStack& oth) {
	TNode<T>* tmp = oth.pFirst;
	pFirst = new TNode<T>;
	pFirst->val = oth.pFirst->val;
	pFirst->next = nullptr;
	TNode<T>* prev = pFirst;
	tmp = tmp->next;
	while (tmp != nullptr) {
		TNode<T>* node = new TNode<T>;
		node->val = tmp->val;
		node->next = nullptr;
		prev->next = node;
		tmp = tmp->next;
		prev = prev->next;
	}
}

template <class T>
TStack<T>::~TStack() {
	TNode<T>* p;
	while (pFirst != nullptr) {
		p = pFirst;
		pFirst = pFirst->next;
		delete p;
	}
}

template <class T>
bool TStack<T>::operator==(const TStack& oth) const {
	if (this == *oth) {
		return true;
	}
	if (this->pFirst == nullptr && oth->pFirst == nullptr) {
		return true;
	}
	TNode<T>* tmp1 = pFirst, tmp2 = oth.pFirst;
	while (tmp1 != nullptr && tmp2 != nullptr) {
		if (tmp1->val != tmp2->val) {
			return false;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
	}
	if (tmp1 == tmp2) {
		return true;
	}
	return false;
}

template <class T>
bool TStack<T>::operator!=(const TStack& oth) const {
	return !(*this == oth);
}

template <class T>
TStack<T>& TStack<T>::operator=(const TStack& oth) {
	if (this == &oth) {
		return *this;
	}
	if (pFirst != nullptr) {
		TNode<T>* p;
		while (pFirst != nullptr) {
			p = pFirst;
			pFirst = pFirst->next;
			delete p;
		}
	}
	TNode<T>* tmp = oth.pFirst;
	pFirst = new TNode<T>;
	pFirst->val = oth.pFirst->val;
	pFirst->next = nullptr;
	TNode<T>* prev = pFirst;
	tmp = tmp->next;
	while (tmp != nullptr) {
		TNode<T>* node = new TNode<T>;
		node->val = tmp->val;
		node->next = nullptr;
		prev->next = node;
		tmp = tmp->next;
		prev = prev->next;
	}
	return *this;
}

template <class T>
bool TStack<T>::isFull() {
	TNode<T>* tmp;
	try {
		tmp = new TNode<T>;
	}
	catch (...) {
		return true;
	}
	delete tmp;
	return false;
}

template <class T>
void TStack<T>::Clear() {
	TNode<T>* p;
	while (pFirst != nullptr) {
		p = pFirst;
		pFirst = pFirst->next;
		delete p;
	}
}

template <class T>
T TStack<T>::Top() {
	if (pFirst == nullptr) {
		throw - 1;
	}
	return pFirst->val;
}

template <class T>
T TStack<T>::Pop() {
	if (this->isEmpty()) {
		throw -1;
	}
	T res = pFirst->val;
	TNode<T>* p = pFirst;
	pFirst = pFirst->next;
	delete p;
	return res;
}

template <class T>
void TStack<T>::Push(T value) {
	if (this->isFull()) {
		throw -1;
	}
	TNode<T>* tmp = new TNode<T>;
	tmp->val = value;
	tmp->next = pFirst;
	pFirst = tmp;
}

