//
// Created by 胡博文 on 2022/11/29.
//

#ifndef LAB5_COLLECTION_H
#define LAB5_COLLECTION_H

#include <string>
#define DefaultCapacity 7

using std::pair;
using std::string;

typedef unsigned long long Index;

class Collection {
public:
    virtual ~Collection() = default;
    virtual pair<int, int> get(string, Index) = 0;
    virtual void insert(const pair<string, pair<int, int>>&, Index) = 0;
    virtual Collection* createCollection() = 0;
protected:
    Collection() = default;
    virtual void expand() = 0;
    int _capacity = DefaultCapacity, hasInsert = 0;
};

#endif //LAB5_COLLECTION_H
