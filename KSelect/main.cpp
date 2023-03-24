#include <random>
#include <fstream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>


#define MAX 10000000
#define LEN 15000

using namespace std;

const int N = 10000010;

default_random_engine e;

int Partition(vector<int>& w, int l, int r, int it) {
    int i = l, j = r;
    swap(w[i], w[it]);
    int p = w[i];
    while(i < j) {
        while (w[j] >= p && i < j) j -- ;
        w[i] = w[j];
        while (w[i] <= p && i < j) i ++ ;
        w[j] = w[i];
    }
    w[i] = p;
    return i;
}

int RSelect(vector<int>& w, int l, int r, int k) {
    while (l < r) {
        uniform_int_distribution<int> u(l, r);
        int len = Partition(w, l, r, u(e));
        if (len == k) return w[len];
        else if (len > k) r = len - 1;
        else l = len + 1;
    }
    return w[r];
}

void mergeSort(vector<int>& w, int l, int r) {
    if (l == r) return ;
    int mid = l + r >> 1;
    mergeSort(w, l, mid), mergeSort(w, mid + 1, r);
    static int tmp[N];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
        if (w[i] < w[j]) tmp[k ++ ] = w[i ++ ];
        else tmp[k ++ ] = w[j ++ ];
    while (i <= mid) tmp[k ++ ] = w[i ++ ];
    while (j <= r) tmp[k ++ ] = w[j ++ ];

    for (i = l, k = 0; i <= r; i ++ , k ++ ) w[i] = tmp[k];
}

inline int midSelect(vector<int> &w, int it) {
    int tmp[5] = {w[it], w[it + 1], w[it + 2], w[it + 3], w[it + 4]};
    sort(tmp, tmp + 5);
    return tmp[2];
}

int DSelect(vector<int>& w, int l, int r, int k) {
    if (r - l + 1 <= LEN) {
        sort(w.begin() + l, w.begin() + r + 1);
        return k;
    }
    vector<int> mid;
    mid.push_back(0);
    for (auto i = l; i < r; i += 5 ) mid.push_back(midSelect(w, i));
    int size = mid.size();
    int it = DSelect(mid, 1, size - 1, size >> 1), p = 0;
    for (int i = l; i <= r; i ++ )
        if (w[i] == mid[it])
            p = i;
    int len = Partition(w, l, r, p);
    if (len == k) return k;
    else if (len < k) return DSelect(w, len + 1, r, k);
    return DSelect(w, l, len - 1, k);
}

int main() {
    fstream file("data.csv", ios::out);
    for (int i = 100000; i <= MAX; i += 10000) {
        printf("N: %d\n", i);
        file << i << ',';
        uniform_int_distribution<int> u1(1, i), u2(0, (1 << 31) - 1);
        int n = i, k = u1(e);
        clock_t begin, end;
        vector<int> w, bk;
        w.push_back(0);
        for (int j = 1; j <= n; j ++ )
            w.push_back(u2(e));
        bk = w;

        begin = clock();
        RSelect(w, 1, n, k);
        end = clock();
        file << end - begin << ',';
        printf("DSelect uses %ld ms\n", end - begin);

        w = bk;
        begin = clock();
        mergeSort(w, 1, n);
        end = clock();
        file << end - begin << ',';
        printf("mergeSort uses %ld ms\n", end - begin);

        w = bk;
        begin = clock();
        DSelect(w, 1, n, k);
        end = clock();
        file << end - begin << endl;
        printf("FSelect uses %ld ms\n\n", end - begin);
    }
    return 0;
}
