//
// Created by 胡博文 on 2022/11/19.
//
#include "AVLTree.h"
#include <algorithm>

Node* AVLTree::insert(int x) {
    auto node = BST::insert(x);
    for (auto g = _parent; g; g = g->parent) {
        if (!g->isBalance()) {
            auto& tar = FromParentTo(g);
            tar = rotateAt(g->tallerChild()->tallerChild());
            break;
        } else {
            pushUp(g);
        }
    }
    return node;
}

bool AVLTree::remove(int x) {
    if (!BST::remove(x)) return false;
    for (auto g = _parent; g; g = g->parent) {
        if (!g->isBalance()) {
            auto& tar = FromParentTo(g);
            g = tar = rotateAt(g->tallerChild()->tallerChild());
        }
        if (g) pushUp(g);
        else break;
    }
    return true;
}

void AVLTree::pushUp(Node* node) {
    BST::pushUp(node);
    node->height = std::max(Height(node->lc), Height(node->rc)) + 1;
}

