//
// Created by 胡博文 on 2022/11/30.
//

#ifndef LAB5_COLLECTIONINCLOSE_H
#define LAB5_COLLECTIONINCLOSE_H

#include "Collection.h"
#include <list>
#include "../HashTable/Node.h"
#include <utility>

using std::list;

class CollectionInClose : public Collection {
public:
    Collection* createCollection() override { return new CollectionInClose(); }
    CollectionInClose() { bucket = new list<Node>[_capacity]; }
    void insert(const pair<string, pair<int, int>>&, Index) override;
    pair<int, int> get(string, Index) override;
    ~CollectionInClose() override { delete[] bucket; }
private:
    void expand() override;
    list<Node>* bucket;
};

void CollectionInClose::insert(const pair<string, pair<int, int>>& object, Index index) {
    Index cur = index % _capacity;
    bucket[cur].emplace_back(object.first, object.second, index);
    hasInsert ++ ;
    expand();
}

pair<int, int> CollectionInClose::get(string tag, Index index) {
    Index cur = index % _capacity;
    for (auto & object : bucket[cur])
        if (object.index == index) return object.data;
    return {-1, -1};
}

void CollectionInClose::expand() {
    if ((double)hasInsert / _capacity > 0.5) {
        list<Node>* oldBucket = bucket;
        bucket = new list<Node>[_capacity << 1];
        for (int i = 0; i < _capacity; i ++ )
            for (auto & it : oldBucket[i]){
                Index cur = it.index % _capacity;
                bucket[cur].push_back(it);
            }
        _capacity <<= 1;
        delete[] oldBucket;
    }
}


#endif //LAB5_COLLECTIONINCLOSE_H
