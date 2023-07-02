//
// Created by 胡博文 on 2023/7/2.
//

#include <iostream>
#include <cstring>
#include <unordered_map>

using namespace std;

const int N = 2010, M = 201010, INF = 1e9;

int n, m, S, T;
int h[N], e[M], ne[M], w[M], f[M], bk[M], idx;
int d[N], q[N], cur[N];
unordered_map<int, vector<int>> nearBy;

void add(int a, int b, int c) { // 加边函数
    e[idx] = b, ne[idx] = h[a], f[idx] = c, h[a] = idx ++ ;
    e[idx] = a, ne[idx] = h[b], f[idx] = 0, h[b] = idx ++ ;
}

bool bfs() { // 遍历全图，求残留网络
    memset(d, -1, sizeof d);
    int hh = 0, tt = 0;
    q[0] = S, d[S] = 0, cur[S] = h[S];

    while (hh <= tt) {
        int t = q[hh ++ ];
        for (int i = h[t]; ~i; i = ne[i]) {
            int j = e[i];
            if (d[j] == -1 && f[i]) {
                d[j] = d[t] + 1;
                cur[j] = h[j];
                if (j == T) return true;
                q[ ++ tt] = j;
            }
        }
    }

    return false;
}

int dfs(int u, int limit) { // 增广路径
    if (u == T) return limit;

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
    memcpy(f, bk, sizeof f);
    int r = 0, flow;
    while (bfs())  // 当还存在残留网络
        while(flow = dfs(S, INF)) // 当残留网络中还存在增广路径
            r += flow;
    return r;
}

int main() {
    cin >> n >> m >> S >> T;
    memset(h, -1, sizeof h);
    S += n;
    for (int i = 1; i <= n; i ++ )
        add(i, n + i, 1);
    while (m -- ) {
        int a, b;
        scanf("%d%d", &a, &b);
        add(a + n, b, INF);
        add(b + n, a, INF);
        nearBy[a].emplace_back(b);
        nearBy[b].emplace_back(a);
    }

    int minv = INF;
    for (const auto& it : nearBy)
        if (it.second.size() < minv) {
            S = n + it.first;
            minv = (int) it.second.size();
        }

    int res = INF << 1, des;
    for (T = 2; T <= n; T ++ ) {
        int min_cut = dinic();
        if (min_cut < res) {
            res = min_cut;
            des = T;
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
                }
            }
    }

    T = des;
    printf("num: %d\n", dinic()); // dinic算法求最小割
    bfs();
    printf("cut: "); // 遍历全图，求连通性
    for (int i = 1; i <= n; i ++ ) {
        if (d[i] != -1 && d[i + n] == -1) // 若入点可以被到达且出点不可到达，则该点为割点
            cout << i << ' ';
    }

    return 0;
}
