//
// Created by 胡博文 on 2022/11/29.
//

#ifndef LAB5_HASH_H
#define LAB5_HASH_H

#include <string>

typedef unsigned long long Index;

using std::string;

class Hash {
public:
    virtual ~Hash() = default;
    virtual Index hash(string) = 0;
    virtual Hash* createHash() = 0;
protected:
    Hash() = default;
    const int P = 13331;
};


#endif //LAB5_HASH_H
