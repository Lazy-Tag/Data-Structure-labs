//
// Created by 胡博文 on 2022/11/30.
//

#ifndef LAB5_COLLECTIONINOPENWITHSTEP_H
#define LAB5_COLLECTIONINOPENWITHSTEP_H

#include "CollectionInOpen.h"

class CollectionInOpenWithStep : public CollectionInOpen {
public:
    Collection* createCollection() override { return new CollectionInOpenWithStep(); }
protected:
    Index next(Index, int) override;
};

Index CollectionInOpenWithStep::next(Index index, int cnt) {
    return (index + 1) % _capacity;
}


#endif //LAB5_COLLECTIONINOPENWITHSTEP_H
