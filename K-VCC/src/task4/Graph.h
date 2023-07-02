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
#include <map>
#include <queue>
#include <cmath>
#include <set>

using namespace std;

typedef pair<int, int> PII;

class Graph {
    int N, M, INF = 1e8;
    int *h, *e, *ne, *f, *bk, idx = 0;
    int *d, *q, *cur;
    int *deposit, *pru;
    int n = 0, k, S = 0, T = 0;
    unordered_set<int> ver, cutSet, left, right;
    unordered_set<int> sideVertex, notSideVertex, hasEdge;
    unordered_map<int, vector<int>> nearBy;
    set<PII> disSet;
    vector<PII> edges;

    void sweep(int u) {
        pru[u] = true;
        bool flag = isSideVertex(u);
        for (auto v: nearBy[u])
            if (!pru[v]) {
                deposit[v]++;
                if (flag || deposit[v] >= k)
                    sweep(v);
            }
    }

    int min_cut() {
        int minv = INF, u;
        for (const auto &it: nearBy)
            if (it.second.size() < minv) {
                u = it.first;
                minv = (int) it.second.size();
            }
        dijkstra(u);
        memset(pru, 0, N * sizeof(int));
        sweep(u);
        S = u + n;
        int mc, res = k, minCut;
        for (auto it: disSet) {
            T = it.second;
            if (T + n == S || pru[T]) continue;
            minCut = dinic();
            if (minCut < res) {
                res = minCut;
                mc = T;
                break;
            }
            sweep(T);
        }

        int x = S - n;
        if (res == k && !isSideVertex(x)) {
            for (auto s: nearBy[x])
                for (auto t: nearBy[x]) {
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
        dinic();
        bfs();
        cutSet.clear();
        for (auto i: ver) {
            if (d[i] != -1 && d[i + n] == -1) {
                cutSet.insert(i);
            }
        }
        for (auto i: ver)
            if (!left.count(i))
                right.insert(i);

        delete deposit;
        delete pru;
        delete h;
        delete e;
        delete ne;
        delete f;
        delete d;
        delete cur;
        delete q;
        delete bk;

        return res;
    }

    bool isSideVertex(int v) {
        if (sideVertex.count(v)) return true;
        if (notSideVertex.count(v)) return false;
        for (auto i: nearBy[v])
            for (auto j: nearBy[v]) {
                if (j <= i || hasEdge.count(i * 10000 + j))
                    continue;
                vector<int> result;
                set_intersection(nearBy[i].begin(), nearBy[i].end(), nearBy[j].begin(),
                                 nearBy[j].end(), inserter(result, result.begin()));
                if (result.size() < k) {
                    notSideVertex.insert(v);
                    return false;
                }
            }
        sideVertex.insert(v);
        return true;
    }

    void dijkstra(int u) {
        priority_queue<PII, vector<PII>, greater<>> heap;
        heap.emplace(0, u);
        d[u] = 0;

        while (!heap.empty()) {
            auto t = heap.top();
            heap.pop();

            int v = t.second, distance = t.first;
            if (pru[v]) continue;
            disSet.emplace(-distance, v);
            pru[v] = true;

            for (auto j: nearBy[v]) {
                if (d[j] > distance + 1) {
                    d[j] = distance + 1;
                    heap.emplace(d[j], j);
                }
            }
        }
    }

    void add(int a, int b, int c) { // 加边函数
        e[idx] = b, ne[idx] = h[a], bk[idx] = c, h[a] = idx++;
        e[idx] = a, ne[idx] = h[b], bk[idx] = 0, h[b] = idx++;
    }

    bool bfs() { // 遍历全图，求残留网络
        left.clear();
        memset(d, -1, N * sizeof(int));
        int hh = 0, tt = 0;
        q[0] = S, d[S] = 0, cur[S] = h[S];

        left.insert(S - n);
        while (hh <= tt) {
            int t = q[hh++];
            for (int i = h[t]; ~i; i = ne[i]) {
                int j = e[i];
                if (d[j] == -1 && f[i]) {
                    d[j] = d[t] + 1;
                    cur[j] = h[j];
                    if (j == T) return true;
                    if (j <= n)
                        left.insert(j);
                    q[++tt] = j;
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
        memcpy(f, bk, M * sizeof(int));
        while (bfs())  // 当还存在残留网络
            while ((flow = dfs(S, INF))) // 当残留网络中还存在增广路径
                r += flow;
        return r;
    }

public:
    Graph(unordered_set<int> _ver, const vector<PII> &edge, int _k,
          unordered_set<int> sideVer, unordered_set<int> notSideVer) : k(_k) {
        ver = std::move(_ver);
        sideVertex = std::move(sideVer);
        notSideVertex = std::move(notSideVer);
        edges = edge;
        for (auto v: ver)
            n = max(n, v);
        N = n * 2 + 10, M = (edge.size() + N) * 2;
        h = new int[N];
        e = new int[M], ne = new int[M], f = new int[M], bk = new int[M];
        d = new int[N], q = new int[N], cur = new int[N];
        deposit = new int[N], pru = new int[N];
        memset(h, -1, N * sizeof(int));
        memset(deposit, 0, N * sizeof(int));
        memset(pru, 0, N * sizeof(int));
        memset(d, 0x3f, N * sizeof(int));
        for (auto v: ver)
            add(v, n + v, 1);
        for (auto p: edge) {
            add(p.first + n, p.second, INF);
            if (p.first < p.second)
                hasEdge.insert(p.first * 10000 + p.second);
            nearBy[p.first].emplace_back(p.second);
        }
    }

    vector<unordered_set<int>> KVCC() {
        vector<unordered_set<int>> K_VCC_vers;
        if (min_cut() >= k || ver.size() <= k) {
            if (ver.size() > k)
                K_VCC_vers.emplace_back(ver);

            return K_VCC_vers;
        }
        right.insert(cutSet.begin(), cutSet.end());
        vector<PII> edge1, edge2;
        for (auto p: edges) {
            if (left.count(p.first) && left.count(p.second)) edge1.emplace_back(p);
            if (right.count(p.first) && right.count(p.second)) edge2.emplace_back(p);
        }
        edges.clear();
        unordered_set<int> lSideVer, lNotSideVer, rSideVer, rNotSideVer;
        for (auto i: sideVertex)
            if (!cutSet.count(i)) {
                if (left.count(i)) lSideVer.insert(i);
                else rSideVer.insert(i);
            }
        for (auto i: notSideVertex)
            if (!cutSet.count(i)) {
                if (left.count(i)) lNotSideVer.insert(i);
                else rNotSideVer.insert(i);
            }
        sideVertex.clear();
        notSideVertex.clear();
        Graph g1(left, edge1, k, lSideVer, lNotSideVer), g2(right, edge2, k, rSideVer, rNotSideVer);
        auto res1 = g1.KVCC(), res2 = g2.KVCC();
        K_VCC_vers = res1;
        K_VCC_vers.insert(K_VCC_vers.end(), res2.begin(), res2.end());
        return K_VCC_vers;
    }
};

#endif //K_VCC_GRAPH_H
