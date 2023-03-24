//
// Created by 胡博文 on 2022/11/19.
//

#include "RBTree.h"

typedef int Color;

Node* RBTree::insert(int x) {
    auto node = BST::insert(x);
    solveDoubleRed(node);
    return node;
}

bool RBTree::remove(int x) {
    if (!BST::remove(x)) return false;
    if (!_size) return true;
    if (!_parent) {
        _root->color = Black;
        pushUp(_root);
        return true;
    }
    if (!r || (Height(_parent->lc) == Height(_parent->rc) &&
            Height(_parent) == (IsRed(_parent)? Height(_parent->lc)
            : Height(_parent->lc) + 1))) return true;
    if (IsRed(r)) {
        r->color = Black;
        r->height ++ ;
        return true;
    }
    solveDoubleBlack(r);
    r = nullptr;
    return true;
}

void RBTree::solveDoubleRed(Node *x) {
    if (!x->parent) {
        _root->color = Black;
        _root->height ++ ;
        return ;
    }
    auto p = x->parent;
    if (IsBlack(p)) return ;
    auto g = p->parent;
    auto u = IsLChild(p)? g->rc : g->lc;
    if (IsBlack(u)) {
        if (IsLChild(x) == IsLChild(p)) p->color = Black;
        else x->color = Black;
        g->color = Red;
        auto gg = g->parent;
        auto& tar = FromParentTo(g);
        tar = rotateAt(x);
        tar->parent = gg;
    } else {
        p->color = Black, p->height ++ ;
        u->color = Black, u->height ++ ;
        if (g->parent) g->color = Red;
        solveDoubleRed(g);
    }
}

void RBTree::solveDoubleBlack(Node *r) {
    auto p = r->parent;
    if (!p) return ;
    auto s = r == p->lc? p->lc : p->rc;
    if (IsBlack(s)) {
        Node* t = nullptr;
        if (IsRed(s->rc)) t = s->rc;
        if (IsRed(s->lc)) t = s->lc;
        if (t) {
            Color oldColor = p->color;
            auto& tar = FromParentTo(p);
            auto& b = tar = rotateAt(t);
            if (b->lc) {
                b->lc->color = Black;
                pushUp(b->lc);
            }
            if (b->rc) {
                b->rc->color = Black;
                pushUp(b->rc);
            }
            b->color = oldColor;
            pushUp(b);
        } else {
            s->color = Red; s->height -- ;
            if (IsRed(p)) p->color = Black;
            else {
                p->height -- ;
                solveDoubleBlack(p);
            }
        }
    } else {
        s->color = Black; p->color = Red;
        auto t = IsLChild(s)? s->lc : s->rc;
        _parent = p;
        auto& tar = FromParentTo(p);
        tar = rotateAt(t);
        solveDoubleBlack(r);
    }
}

void RBTree::pushUp(Node *node) {
    BST::pushUp(node);
    node->height = std::max(Height(node->lc), Height(node->rc)) + IsBlack(node);
}
