//
// Created by 胡博文 on 2022/11/17.
//

#include "SplayTree.h"
#include <iostream>

Node tr[N];

void SplayTree::insert(int v) {
    int u = root, p = 0;
    while(u) {
        p = u;
        u = tr[u].s[v > tr[u].v];
    }
    u = ++ index;
    if (p) tr[p].s[v > tr[p].v] = u;
    tr[u].init(p, v);
    splay(u, 0);
}

void SplayTree::reverse(int a, int b) {
    a = getValue(a), b = getValue(b + 2);
    splay(a, 0), splay(b, a);
    tr[tr[b].s[0]].rev ^= 1;
}

void SplayTree::print(int u) {
    pushDown(u);
    if(tr[u].s[0]) print(tr[u].s[0]);
    if (tr[u].v >= 1 && tr[u].v < index - 1) std::cout << tr[u].v << ' ';
    if(tr[u].s[1]) print(tr[u].s[1]);
}

void SplayTree::splay(int x, int k) {
    while (tr[x].p != k) {
        int y = tr[x].p, z = tr[y].p;
        if (z != k)
            if ((tr[y].s[1] == x) ^ (tr[z].s[1] == y)) rotate(x);
            else rotate(y);
        rotate(x);
    }
    if (!k) root = x;
}

void SplayTree::pushDown(int x) {
    if (tr[x].rev) {
        std::swap(tr[x].s[0], tr[x].s[1]);
        tr[tr[x].s[0]].rev ^= 1;
        tr[tr[x].s[1]].rev ^= 1;
        tr[x].rev = 0;
    }
}

void SplayTree::pushUp(int u) {
    tr[u].size = tr[tr[u].s[0]].size + tr[tr[u].s[1]].size + 1;
}

void SplayTree::rotate(int x) {
    int y = tr[x].p, z = tr[y].p;
    int k = tr[y].s[1] == x;
    tr[z].s[tr[z].s[1] == y] = x, tr[x].p = z;
    tr[y].s[k] = tr[x].s[k ^ 1], tr[tr[x].s[k ^ 1]].p = y;
    tr[x].s[k ^ 1] = y, tr[y].p = x;
    pushUp(y), pushUp(x);
}

int SplayTree::getValue(int k) const {
    int u = root;
    while (true)
    {
        pushDown(u);
        if (tr[tr[u].s[0]].size >= k) u = tr[u].s[0];
        else if (tr[tr[u].s[0]].size + 1 == k) return u;
        else k -= tr[tr[u].s[0]].size + 1, u = tr[u].s[1];
    }
}

