//
// Created by 胡博文 on 2023/7/1.
//

#ifndef K_VCC_GRAPH_H
#define K_VCC_GRAPH_H

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <cmath>

using namespace std;

typedef pair<int, int> PII;

class Graph {
    static const int N = 10000, M = 500000, INF = 1e8;
    int *h, *e, *ne, *f, *bk, idx = 0;
    int *d, *q, *cur;
    int n = 0, k, S = 0, T = 0;
    unordered_set<int> ver, cutSet, left, right;
    unordered_map<int, vector<int>> nearBy;
    vector<PII> edges;

    int min_cut() {
        int minv = INF;
        for (const auto& it : nearBy)
            if (it.second.size() < minv) {
                S = n + it.first;
                minv = (int) it.second.size();
            }
        int mc, res = k;
        int minCut = INF;
        for (auto t : ver) {
            T = t;
            if (T + n == S) continue;
            minCut = dinic();
            if (minCut < res) {
                res = minCut;
                mc = T;
                break;
            }
        }

        int x = S - n;
        if (minCut >= k) {
            for (auto s : nearBy[x])
                for (auto t : nearBy[x]) {
                    if (s == t) continue;
                    S = s + n;
                    T = t;
                    minCut = dinic();
                    if (minCut < res) {
                        res = minCut;
                        mc = T;
                        goto END;
                    }
                }
        }
END:
        T = mc;
        dinic(); bfs();
        cutSet.clear();
        for (auto i : ver) {
            if (d[i] != -1 && d[i + n] == -1) {
                cutSet.insert(i);
            }
        }
        for (auto i : ver)
            if (!left.count(i))
                right.insert(i);

        delete h; delete e; delete ne; delete f;
        delete d; delete cur; delete q;
        return res;
    }

    void add(int a, int b, int c) { // 加边函数
        e[idx] = b, ne[idx] = h[a], bk[idx] = c, h[a] = idx ++ ;
        e[idx] = a, ne[idx] = h[b], bk[idx] = 0, h[b] = idx ++ ;
    }

    bool bfs() { // 遍历全图，求残留网络
        left.clear();
        memset(d, -1, N * sizeof (int));
        int hh = 0, tt = 0;
        q[0] = S, d[S] = 0, cur[S] = h[S];

        left.insert(S - n);
        while (hh <= tt) {
            int t = q[hh ++ ];
            for (int i = h[t]; ~i; i = ne[i]) {
                int j = e[i];
                if (d[j] == -1 && f[i]) {
                    d[j] = d[t] + 1;
                    cur[j] = h[j];
                    if (j == T) return true;
                    if (j <= n)
                        left.insert(j);
                    q[ ++ tt] = j;
                }
            }
        }

        return false;
    }

    int dfs(int u, int limit) { // 增广路径
        if (u == T)
            return limit;

        int flow = 0;
        for (int i = cur[u]; ~i && flow < limit; i = ne[i]) {
            int j = e[i];
            cur[u] = i;
            if (d[j] == d[u] + 1 && f[i]) {
                int t = dfs(j, min(f[i], limit - flow));
                if (!t) d[j] = -1;
                f[i] -= t, f[i ^ 1] += t, flow += t;
            }
        }

        return flow;
    }

    int dinic() {
        int r = 0, flow;
        memcpy(f, bk, M * sizeof (int));
        while (bfs())  // 当还存在残留网络
            while((flow = dfs(S, INF))) // 当残留网络中还存在增广路径
                r += flow;
        return r;
    }

public:
    Graph(unordered_set<int> _ver, const vector<PII>& edge, int _k) : k(_k) {
        ver = std::move(_ver);
        edges = edge;
        for (auto v : ver)
            n = max(n, v);
        h = new int[N];
        e = new int[M], ne = new int[M], f = new int[M], bk = new int[M];
        d = new int[N], q = new int[N], cur = new int[N];
        memset(h, -1, N * sizeof (int));
        for (auto v : ver)
            add (v, n + v, 1);
        for (auto p : edge) {
            add(p.first + n, p.second, INF);
            nearBy[p.first].emplace_back(p.second);
        }
    }

    pair<int, vector<unordered_set<int>>> KVCC() {
        int cnt = 0;
        vector<unordered_set<int>> K_VCC_vers;
        if (min_cut() >= k || ver.size() <= k) {
            if (ver.size() > k) {
                cnt = 1;
                K_VCC_vers.emplace_back(ver);
            }
            return {cnt, K_VCC_vers};
        }
        right.insert(cutSet.begin(), cutSet.end());
        vector<PII> edge1, edge2;
        for (auto p : edges) {
            if (left.count(p.first) && left.count(p.second)) edge1.emplace_back(p);
            if (right.count(p.first) && right.count(p.second)) edge2.emplace_back(p);
        }
        Graph g1(left, edge1, k), g2(right, edge2, k);
        auto res1 = g1.KVCC(), res2 = g2.KVCC();
        cnt = res1.first + res2.first;
        K_VCC_vers = res1.second;
        K_VCC_vers.insert(K_VCC_vers.end(), res2.second.begin(), res2.second.end());
        return {cnt, K_VCC_vers};
    }
};

#endif //K_VCC_GRAPH_H
