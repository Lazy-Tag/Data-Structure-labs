//
// Created by 胡博文 on 2022/10/21.
//

#ifndef CALCULATOR_MYVECTOR_H
#define CALCULATOR_MYVECTOR_H

#define DEFAULT_CAPACITY 10
#include <algorithm>

// 向量模板类
template <typename T>
class myVector{
protected:
    int _size, _capacity;
    T* elem;
public:
    myVector();
    myVector(const myVector& t);
    void expand();
    virtual int size() const { return _size; }
    void push_back(const T&);
    T& operator[] (int r) const { return elem[r]; };
    T& remove(int r);
    void sort() { std::sort(elem, elem + _size); }
    void unique();
    void shrink();
    virtual void clear();
};

template <typename T>
myVector<T>::myVector()
{
    _size = 0, _capacity = DEFAULT_CAPACITY;
    elem = new T[DEFAULT_CAPACITY];
}

template <typename T>
void myVector<T>::expand()
{
    if(_size < _capacity) return ;
    T* oldelem = elem;
    elem = new T[_capacity <<= 1];
    for(int i = 0; i < _size; i ++ )
        elem[i] = oldelem[i];
    delete[] oldelem;
}

template <typename T>
void myVector<T>::push_back(const T& e)
{
    expand();
    elem[_size ++ ] = e;
}

template <typename T>
T& myVector<T>::remove(int r)
{
    T& e = elem[r];
    for(int i = r; i < _size - 1; i ++ ) elem[i] = elem[i + 1];
    _size -- ;
    return e;
}

template <typename T>
void myVector<T>::unique()
{
    int i = 0, j = 0;
    while( ++ j < _size)
        if(elem[i] != elem[j])
            elem[ ++ i] = elem[j];
    _size = i + 1;
}

template<typename T>
void myVector<T>::shrink()
{
    if(_capacity < DEFAULT_CAPACITY << 1) return ;
    if(_size << 2 > _capacity) return ;
    T* oldElem = elem;
    elem = new T[_capacity >> 1];
    for(int i = 0; i < _size; i ++ ) elem[i] = oldElem[i];
    delete[] oldElem;
}

template<typename T>
void myVector<T>::clear()
{
    _size = 0;
    shrink();
}

template<typename T>
myVector<T>::myVector(const myVector& t)
{
    elem = new T[t._size];
    _size = t._size, _capacity = t._capacity;
    for(int i = 0; i < _size; i ++ )
        elem[i] = t[i];
}

#endif //CALCULATOR_MYVECTOR_H
