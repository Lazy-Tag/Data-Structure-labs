//
// Created by 胡博文 on 2022/11/30.
//

#ifndef LAB5_COLLECTIONINOPENWITHDOUBLESQUARE_H
#define LAB5_COLLECTIONINOPENWITHDOUBLESQUARE_H

#include "CollectionInOpen.h"

class CollectionInOpenWithDoubleSquare : public CollectionInOpen {
public:
    Collection* createCollection() override { return new CollectionInOpenWithDoubleSquare(); }
protected:
    Index next(Index, int) override;
};

Index CollectionInOpenWithDoubleSquare::next(Index index, int cnt) {
    if (cnt > 0) {
        return (index + cnt * cnt) % _capacity;
    } else {
        return (index - cnt * cnt + (Index)_capacity * _capacity) % _capacity;
    }
}


#endif //LAB5_COLLECTIONINOPENWITHDOUBLESQUARE_H
