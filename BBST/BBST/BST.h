//
// Created by 胡博文 on 2022/11/18.
//

#ifndef BST_BBST_H
#define BST_BBST_H

#include <algorithm>
#include <iostream>

static const int ERROR = -1, INF = 1e9;

#define IsRoot(x) (!((x)->parent))
#define Height(x) ((x)? x->height : -1)
#define IsLChild(x) ((x)->parent && (x == x->parent->lc))
#define IsRChild(x) ((x)->parent && (x == x->parent->rc))
#define FromParentTo(x) (IsRoot(x)? _root : (IsLChild(x)? (x)->parent->lc : (x)->parent->rc))
#define Black 0
#define Red 1

struct Node {
    Node *parent, *lc, *rc;
    int val, size, cnt, height, color;
    Node (Node* _p, int _v) {
        parent = _p;
        val = _v, size = 1;
        cnt = 1, height = 0, color = Red;
        lc = rc = nullptr;
    }
    ~Node() {
        if (parent) {
            if (parent->lc == this) parent->lc = nullptr;
            else if (parent->rc == this) parent->rc = nullptr;
        }
    }
    static int getChildSize(Node* child) {
        return child? child->size : 0;
    }
    [[nodiscard]] bool isBalance() const {
        return abs(Height(lc) - Height(rc)) <= 1;
    }
    Node* tallerChild() {
        return Height(lc) > Height(rc)? lc : rc;
    }
};

class BST {
public:
    BST() = default;
    virtual Node* insert(int);
    virtual bool remove(int);
    virtual int getValue(int e) { return getValue(_root, e); }
    virtual int getRank(int e) { return getRank(_root, e); }
    virtual int getPrev(int e) { return getPrev(_root, e); };
    virtual int getSucc(int e) { return getSucc(_root, e); };
protected:
    virtual int getValue(Node*, int) const;
    virtual int getRank(Node*, int) const;
    virtual int getPrev(Node*, int) const;
    virtual int getSucc(Node*, int) const;
    virtual Node* search(int);
    virtual Node* getNextNode(Node*);
    virtual Node* rotateAt(Node *);
    virtual Node* connect34(Node *a, Node *b, Node *c, Node *t0, Node *t1, Node *t2, Node *t3);
    virtual void pushUp(Node*);
    virtual void update(Node *x);
protected:
    Node *_root = nullptr, *_parent = nullptr, *r = nullptr;
    int _size = 0;
};

#endif //BST_BBST_H
