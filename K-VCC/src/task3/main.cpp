//
// Created by 胡博文 on 2023/7/2.
//

#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <queue>
#include <set>
#include "Graph.h"

using namespace std;

typedef pair<int, int> PII;

const int N = 1000010, M = 1000010, K = 1000010, L = 100;

unordered_set<int> S;
priority_queue<PII, vector<PII>, greater<>> degree;
vector<int> edges[K];
vector<unordered_set<int>> branch;
unordered_map<int, int> M1, M2;
int n, m, k = 30;
int h[N], e[M], ne[M], idx;
int d[K], colors[N];

void add(int a, int b) { // 加边函数
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}

void dfs(int u, int fa, int c) {
    colors[u] = c;
    for (int i = h[u]; ~i; i = ne[i]) {
        int j = e[i];
        if (j != fa && !colors[j])
            dfs(j, u, c);
    }
}

int main() {
    fstream fin, fout;
    fin.open("../data/dblp.txt", ios::in);
    fout.open("../data/out.txt", ios::out);
    fin >> n >> m;
    memset(h, -1, sizeof h);

    while (m -- ) {
        int a, b;
        fin >> a >> b;
        edges[a].emplace_back(b);
        edges[b].emplace_back(a);
        d[a] ++ , d[b] ++ ;
        n = max(a, n);
    }

    for (int i = n; i >= 0; i -- ) S.insert(i);

    for (int i = 0; i <= n; i ++ )
        degree.emplace(d[i], i);

    do {
        int node = degree.top().second;
        degree.pop();
        if (!S.count(node)) continue;
        for (auto i : edges[node])
            if (S.count(i))
                degree.emplace(--d[i], i);
        S.erase(node);
    } while (degree.top().first < k);

    int cnt = 0;
    for (auto i : S) {
        M1[i] = ++cnt;
        M2[cnt] = i;
    }

    for (int i = 0; i <= n; i ++ )
        if (S.count(i)) {
            vector<int> E;
            for (int j = 0; j < edges[i].size(); j ++ ) {
                int b = edges[i][j];
                if (S.count(b)) {
                    E.emplace_back(b);
                    add(i, b);
                }
            }
            edges[i] = E;
        }

    int color = 0;
    for (int i = 0; i <= n; i ++ )
        if (!colors[i] && S.count(i))
            dfs(i, -1, ++ color);

    for (int i = 0; i < L; i ++ )
        branch.emplace_back();

    for (int i = 0; i <= n; i ++ )
        if (S.count(i))
            branch[colors[i]].insert(M1[i]);

    int size = 0;
    vector<unordered_set<int>> K_VCCs;
    for (const auto& v : branch) {
        if (v.empty()) continue;
        vector<PII> edge;
        for (auto i : v) {
            for (auto b : edges[M2[i]])
                if (S.count(b))
                    edge.emplace_back(i, M1[b]);
        }
        Graph g(v, edge, k);
        auto p = g.KVCC();
        size += p.first;
        for (const auto& i : p.second)
            K_VCCs.emplace_back(i);
    }
    printf("K = %d, KVCC num = %d\n", k, size);

    for (const auto& t : K_VCCs) {
        printf("Node num: %zu\n", t.size());
        set<int> temp;
        for (auto i : t)
            temp.insert(M2[i]);
        for (auto i : temp)
            cout << i << ' ';
        cout << endl;
    }

    return 0;
}