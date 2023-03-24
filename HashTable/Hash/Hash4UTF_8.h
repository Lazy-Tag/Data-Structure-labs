//
// Created by 胡博文 on 2022/11/30.
//

#ifndef LAB5_HASH4UTF_8_H
#define LAB5_HASH4UTF_8_H

#include "Hash.h"

class Hash4UTF_8 : public Hash {
public:
    Index hash(string) override;
    Hash* createHash() override { return new Hash4UTF_8(); }
};

Index Hash4UTF_8::hash(string str) {
    Index res = 0;
    for (int i = 0; i < str.size(); ) {
        Index character = (unsigned char) str[i ++ ];
        while (i < str.size() && str[i] < -64) {
            character *= 256;
            character += (unsigned char) str[i ++ ];
        }
        res *= P;
        res += character;
    }
    return res;
}

#endif //LAB5_HASH4UTF_8_H
