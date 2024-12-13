template <class T>
struct TNode {
    T val;
    TNode* next = nullptr;
public:
    TNode() : val(T()) {}
    TNode(T value) : val(value) {}
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

    bool isEmpty() const { return pFirst == nullptr; }
    bool isFull() const;

    void Clear();

    T Top() const;
    T Pop();
    void Push(T value);
};

template <class T>
TStack<T>::TStack() : pFirst(nullptr) {}

template <class T>
TStack<T>::TStack(const TStack& oth) : pFirst(nullptr) {
    if (oth.pFirst == nullptr) {
        return;
    }
    pFirst = new TNode<T>(oth.pFirst->val);
    TNode<T>* tmp = oth.pFirst->next;
    TNode<T>* prev = pFirst;
    while (tmp != nullptr) {
        TNode<T>* node = new TNode<T>(tmp->val);
        prev->next = node;
        tmp = tmp->next;
        prev = prev->next;
    }
}

template <class T>
TStack<T>::~TStack() {
    Clear();
}

template <class T>
bool TStack<T>::operator==(const TStack& oth) const {
    if (this == &oth) {
        return true;
    }
    TNode<T>* tmp1 = pFirst;
    TNode<T>* tmp2 = oth.pFirst;
    while (tmp1 != nullptr && tmp2 != nullptr) {
        if (tmp1->val != tmp2->val) {
            return false;
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return tmp1 == tmp2;
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
    Clear();
    if (oth.pFirst == nullptr) {
        pFirst = nullptr;
        return *this;
    }
    pFirst = new TNode<T>(oth.pFirst->val);
    TNode<T>* tmp = oth.pFirst->next;
    TNode<T>* prev = pFirst;
    while (tmp != nullptr) {
        TNode<T>* node = new TNode<T>(tmp->val);
        prev->next = node;
        tmp = tmp->next;
        prev = prev->next;
    }
    return *this;
}

template <class T>
bool TStack<T>::isFull() const {
    try {
        TNode<T>* tmp = new TNode<T>();
        delete tmp;
        return false;
    }
    catch (...) {
        return true;
    }
}

template <class T>
void TStack<T>::Clear() {
    while (pFirst != nullptr) {
        TNode<T>* p = pFirst;
        pFirst = pFirst->next;
        delete p;
    }
}

template <class T>
T TStack<T>::Top() const {
    if (pFirst == nullptr) {
        throw -1;
    }
    return pFirst->val;
}

template <class T>
T TStack<T>::Pop() {
    if (isEmpty()) {
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
    if (isFull()) {
        throw -1;
    }
    TNode<T>* tmp = new TNode<T>(value);
    tmp->next = pFirst;
    pFirst = tmp;
}

