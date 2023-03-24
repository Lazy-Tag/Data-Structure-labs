//
// Created by 胡博文 on 2022/11/30.
//

#ifndef LAB5_COLLECTIONINOPEN_H
#define LAB5_COLLECTIONINOPEN_H

#include "Collection.h"
#include "../HashTable/Node.h"

#define N 1000000

extern int primes[N];

class CollectionInOpen : public Collection {
public:
    void insert(const pair<string, pair<int, int>>&, Index) override;
    pair<int, int> get(string, Index) override;
    ~CollectionInOpen() override { delete[] bucket; }
    Collection* createCollection() override = 0;
protected:
    int cnt = 3;
    Node* bucket;
protected:
    CollectionInOpen() { bucket = new Node[_capacity]; }
    virtual Index next(Index, int) = 0;
    void expand() override;
    int next();
};

void CollectionInOpen::insert(const pair<string, pair<int, int>> &object, Index index) {
    Index cur = index % _capacity;
    for (int i = 1; !bucket[cur].tag.empty(); i = i > 0? -i : -i + 1) cur = next(cur, i);
    bucket[cur] = Node(object.first, object.second, index);
    hasInsert ++ ;
    expand();
}

pair<int, int> CollectionInOpen::get(string tag, Index index) {
    Index cur = index % _capacity;
    for (int i = 1; bucket[cur].tag != tag && !bucket[cur].tag.empty(); i ++ ) cur = next(cur, i);
    return bucket[cur].data;
}

void CollectionInOpen::expand() {
    if ((double) hasInsert / _capacity > 0.5) {
        Node* oldBucket = bucket;
        int oldCapacity = _capacity;
        _capacity = next();
        bucket = new Node[_capacity];
        for (int i = 0; i < oldCapacity; i ++ ) {
            Node cur = oldBucket[i];
            if (!cur.tag.empty()) {
                Index curIndex = cur.index % _capacity;
                for (int j = 1; !bucket[curIndex].tag.empty(); j = j > 0? -j : -j + 1) curIndex = next(curIndex, j);
                bucket[curIndex] = Node(cur.tag, cur.data, cur.index);
            }
        }
        delete[] oldBucket;
    }
}

int CollectionInOpen::next() {
    while(primes[cnt] < _capacity << 1) cnt ++ ;
    return primes[cnt];
}


#endif //LAB5_COLLECTIONINOPEN_H
