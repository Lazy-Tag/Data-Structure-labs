//
// Created by 胡博文 on 2022/10/20.
//

#ifndef CALCULATOR_MYSTACK_H
#define CALCULATOR_MYSTACK_H

#include "myVector.h"

// stack模板类
template <typename T>
class myStack : myVector<T> {
public:
    void push(const T &e) { myVector<T>::push_back(e); };
    bool empty() { return myVector<T>::_size == 0; }
    T& pop() { return myVector<T>::remove(myVector<T> :: _size - 1); };
    T& top() { return myVector<T>::elem[size() - 1];}
    int size() { return myVector<T> :: size(); }
    void clear() {}
};


#endif //CALCULATOR_MYSTACK_H
