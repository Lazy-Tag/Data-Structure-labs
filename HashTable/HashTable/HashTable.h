//
// Created by 胡博文 on 2022/11/29.
//

#ifndef LAB5_HASHTABLE_H
#define LAB5_HASHTABLE_H

#include <string>
#include <utility>
#include <vector>
#include "../Hash/Hash.h"
#include "../Collection/Collection.h"
#include "../Collection/CollectionInClose.h"
#include "../Collection/CollectionInOpenWithStep.h"
#include "../Collection/CollectionInOpenWithDoubleSquare.h"
#include "../Hash/Hash4Ascii.h"
#include "../Hash/Hash4UTF_8.h"

using std::pair;
using std::string;

class HashTable {
public:
    explicit HashTable(Collection* _collection, Hash* _hash) : collection(_collection), hash(_hash) {}
    void insert(const pair<string, pair<int, int>>&);
    pair<int, int> get(std::string);
    HashTable* createHashTable() { return new HashTable(collection->createCollection(), hash->createHash()); }
    ~HashTable();
private:
    Hash* hash;
    Collection* collection;
};

void HashTable::insert(const pair<string, pair<int, int>>& object) {
    Index index = hash->hash(object.first);
    collection->insert(object, index);
}

pair<int, int> HashTable::get(std::string str) {
    Index index = hash->hash(std::move(str));
    auto res = collection->get(str, index);
    return res;
}

HashTable::~HashTable() {
    delete hash;
    delete collection;
}


#endif //LAB5_HASHTABLE_H
