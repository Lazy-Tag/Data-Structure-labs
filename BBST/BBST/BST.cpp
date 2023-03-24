//
// Created by 胡博文 on 2022/11/18.
//

#include "BST.h"
#include <algorithm>

int BST::getRank(Node *cur, int e) const {
    if(!cur) return 0;
    if (cur->val > e) return getRank(cur->lc, e);
    else if (cur->val == e) return cur->getChildSize(cur->lc) + 1;
    else return getRank(cur->rc, e) + cur->cnt + cur->getChildSize(cur->lc);
}

int BST::getValue(Node* cur, int k) const {
    if (!cur) return INF;
    if (k <= cur->getChildSize(cur->lc)) return getValue(cur->lc, k);
    else if (k <= cur->getChildSize(cur->lc) + cur->cnt) return cur->val;
    else return getValue(cur->rc, k - cur->cnt - cur->getChildSize(cur->lc));
}

int BST::getPrev(Node *cur, int e) const {
    if(!cur) return -INF;
    if (cur->val >= e) return getPrev(cur->lc, e);
    return std::max(cur->val, getPrev(cur->rc, e));
}

int BST::getSucc(Node *cur, int e) const {
    if(!cur) return INF;
    if(cur->val <= e) return getSucc(cur->rc, e);
    return std::min(cur->val, getSucc(cur->lc, e));
}

Node* BST::insert(int x) {
    _size ++ ;
    Node* cur = search(x);
    if (cur) {
        cur->cnt ++ ;
    } else {
        cur = new Node(_parent, x);
        if (!_root) _root = cur;
        if (_parent) (_parent->val < x? _parent->rc : _parent->lc) = cur;
    }
    update(cur);
    return cur;
}

bool BST::remove(int x) {
    auto cur = search(x);
    if (!cur) {
        return false;
    } else {
        _size -- ;
        cur->cnt -- ; cur->size -- ;
        _parent = cur->parent;
        if (!cur->cnt) {
            Node *nextNode = nullptr, *w = cur;
            if (!cur->lc) nextNode = cur = cur->rc;
            else if (!cur->rc) nextNode = cur = cur->lc;
            else {
                w = getNextNode(cur);
                std::swap(w->val, cur->val);
                std::swap(w->cnt, cur->cnt);
                Node *u = w->parent;
                (u == cur ? u->rc : u->lc) = nextNode = w->rc;
            }
            _parent = w->parent;
            if (!_parent) {
                if (w->lc) _root = w->lc;
                else _root = w->rc;
            }
            if (nextNode) {
                nextNode->parent = _parent;
                if (_parent) (_parent->val > nextNode->val ? _parent->lc : _parent->rc) = nextNode;
            }
            delete w;
            r = nextNode;
        }
        update(_parent);
    }
    return true;
}

Node *BST::getNextNode(Node *node) {
    if(node->rc) {
        Node* next = node->rc;
        while (next->lc) next = next->lc;
        return next;
    } else {
        Node *f = node->parent, *g = f->parent;
        while(g && node == f->rc && f == g->rc) {
            node = f;
            f = g;
            g = g->parent;
        }
        return g;
    }
}

void BST::pushUp(Node *node) {
    int lSize = node->lc? node->lc->size : 0;
    int rSize = node->rc? node->rc->size : 0;
    node->size = lSize + rSize + node->cnt;
}

void BST::update(Node *x) {
    for (auto p = x; p; p = p->parent) pushUp(p);
}

Node* BST::search(int e) {
    if(!_root || e == _root->val) {
        _parent = nullptr;
        return _root;
    }
    _parent = _root;

    while (true) {
        Node* v = e < _parent->val? _parent->lc : _parent->rc;
        if (!v || e == v->val) return v;
        _parent = v;
    }
}

Node* BST::rotateAt(Node *v) {
    Node *p = v->parent, *g = p->parent;
    if (IsLChild(p)) {
        if (IsLChild(v)) {
            p->parent = g->parent;
            return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
        } else {
            v->parent = g->parent;
            return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
        }
    } else {
        if (IsRChild(v)) {
            p->parent = g->parent;
            return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
        } else {
            v->parent = g->parent;
            return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
        }
    }
}

Node* BST::connect34(Node *a, Node *b, Node *c, Node *t0, Node *t1, Node *t2, Node *t3) {
    a->lc = t0; if (t0) t0->parent = a;
    a->rc = t1; if (t1) t1->parent = a;
    pushUp(a);
    c->lc = t2; if (t2) t2->parent = c;
    c->rc = t3; if (t3) t3->parent = c;
    pushUp(c);
    b->lc = a, a->parent = b;
    b->rc = c, c->parent = b;
    pushUp(b);
    return b;
}
