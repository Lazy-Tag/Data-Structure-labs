//
// Created by 胡博文 on 2022/11/29.
//

#ifndef LAB5_HASH4ASCII_H
#define LAB5_HASH4ASCII_H

#include "Hash.h"

class Hash4Ascii : public Hash {
public:
    Index hash(string) override;
    Hash* createHash() override { return new Hash4Ascii(); }
};

Index Hash4Ascii::hash(string str) {
    Index res = 0;
    for (int i = 0; i < str.size(); ) {
        Index character = (unsigned char) str[i ++ ];
        res *= P;
        res += character;
    }
    return res;
}

#endif //LAB5_HASH4ASCII_H
