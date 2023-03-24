//
// Created by 胡博文 on 2022/10/30.
//

#ifndef AIRLINE_HEAP_H
#define AIRLINE_HEAP_H

#include <vector>

template <typename T>
class Heap {
public:
    Heap() { elems.push_back(T()), _size = 0; }
    T& top() { return elems[1]; };
    void push(T);
    void pop();
    int size() { return _size; }
private:
    int _size;
    std::vector<T> elems;
};

template<typename T>
void Heap<T>::push(T t)
{
    if(_size < elems.size() - 1) elems[_size + 1] = t;
    else elems.push_back(t);
    int posi =  ++ _size;
    while(elems[posi] < elems[posi / 2] && posi > 1)
    {
        std::swap(elems[posi], elems[posi / 2]);
        posi /= 2;
    }
}

template<typename T>
void Heap<T>::pop()
{
    elems[1] = elems[_size -- ];
    int posi = 1;
    while(true)
    {
        T minv = elems[posi];
        int l = posi << 1, r = posi << 1 | 1;
        if(l <= _size) minv = std::min(elems[posi], elems[l]);
        if(r <= _size) minv = std::min(minv, std::min(elems[posi], elems[r]));
        if(minv == elems[posi]) break;
        int i = elems[l] < elems[r]? l : r;
        std::swap(elems[posi], elems[i]);
        posi = i;
    }
}


#endif //AIRLINE_HEAP_H
