#include "DataBuilder.h"
#include <iostream>
#include "HashTable/HashTable.h"
#include "Test.h"

#define N 1000000

int primes[N];

void getPrimes() {
    static bool st[N] = {false};
    int cnt = 0;
    for (int i = 2; i < N; i ++ ) {
        if (!st[i]) primes[cnt ++ ] = i;
        for (int j = 0; primes[j] <= N / i; j ++ ) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

using namespace std;

int main() {
    getPrimes();
    auto *dataBuilder = new DataBuilder();
//    dataBuilder->exec("poj"), dataBuilder->exec("hdu"); // 生成数据
    dataBuilder->setFileName(0, 50, 100);
    double result[6][6] = {0};
    Test* tests[6] = {
            new Test(dataBuilder->getFileName(0)), new Test(dataBuilder->getFileName(1)),
            new Test(dataBuilder->getFileName(2)), new Test(dataBuilder->getFileName(3)),
            new Test(dataBuilder->getFileName(4)), new Test(dataBuilder->getFileName(5)),
    };
    HashTable* hashTables[6] = {
            new HashTable(new CollectionInClose(), new Hash4Ascii()),
            new HashTable(new CollectionInClose(), new Hash4UTF_8()),
            new HashTable(new CollectionInOpenWithStep(), new Hash4Ascii()),
            new HashTable(new CollectionInOpenWithStep(), new Hash4UTF_8()),
            new HashTable(new CollectionInOpenWithDoubleSquare(), new Hash4Ascii()),
            new HashTable(new CollectionInOpenWithDoubleSquare(), new Hash4UTF_8()),
    };
    for (int cnt = 1; cnt <= 200; cnt ++ ) {
        for (int i = 0; i < 6; i ++ ) {
            for (int j = 0; j < 6; j ++ )
                tests[j]->exec(result[j], i, hashTables[i]->createHashTable());
        }
        cout << cnt << endl;
    }
    for (auto & i : result) {
        for (double j : i)
            printf("%10.6lf", j / 200);
        puts("");
    }
    return 0;
}
