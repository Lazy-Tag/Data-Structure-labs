//
// Created by 胡博文 on 2022/11/17.
//

#ifndef UNTITLED_SPLAYTREE_H
#define UNTITLED_SPLAYTREE_H

const int N = 100010;

struct Node{
    int p, v;
    int size, rev;
    int s[2];
    void init(int _p, int _v){
        p = _p, v = _v;
        size = 1;
    }
};

class SplayTree {
public:
    void insert(int);
    void reverse(int, int);
    void print(int);
    int getRoot() { return root; }
private:
    int getValue(int) const;
    void splay(int, int);
    static void pushDown(int);
    static void pushUp(int);
    static void rotate(int);
private:
    int root, index;
};


#endif //UNTITLED_SPLAYTREE_H
