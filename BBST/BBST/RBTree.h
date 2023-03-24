//
// Created by 胡博文 on 2022/11/17.
//

#ifndef BST_RBTREE_H
#define BST_RBTREE_H

#include "BST.h"
#define IsBlack(x) (!x || (x)->color == Black)
#define IsRed(x) (!IsBlack(x))

class RBTree : public BST {
public:
    Node* insert(int) override;
    bool remove(int) override;
protected:
    void solveDoubleRed(Node*);
    void solveDoubleBlack(Node*);
    void pushUp(Node*) override;
};


#endif //BST_RBTREE_H
