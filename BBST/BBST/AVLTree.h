//
// Created by 胡博文 on 2022/11/17.
//

#ifndef BST_AVLTREE_H
#define BST_AVLTREE_H

#include "BST.h"
#include <algorithm>

class AVLTree : public BST {
public:
    AVLTree() = default;
    Node* insert(int) override;
    bool remove(int) override;
private:
    void pushUp(Node*) override;
};


#endif //BST_AVLTREE_H
