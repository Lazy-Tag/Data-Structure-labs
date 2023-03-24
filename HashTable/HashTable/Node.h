//
// Created by 胡博文 on 2022/11/30.
//

#ifndef LAB5_NODE_H
#define LAB5_NODE_H

#include <string>

using std::string;
using std::pair;

typedef unsigned long long Index;

struct Node {
    Node() = default;
    Node(string _tag, pair<int, int> _data, Index _index) :
            data(std::move(_data)), index(_index), tag(std::move(_tag)) {}
    pair<int, int> data = {-1, -1};
    Index index = 0;
    string tag;
};



#endif //LAB5_NODE_H
