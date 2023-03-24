#include <iostream>
#include <algorithm>
#include "SplayTree.h"

int main()
{
    int n, m;
    std::cin >> n >> m;
    SplayTree splayTree{};
    for (int i = 0; i <= n + 1; i ++ ) splayTree.insert(i);

    while (m -- )
    {
        int a, b;
        std::cin >> a >> b;
        if(a > b) std::swap(a, b);
        splayTree.reverse(a, b);
    }

    splayTree.print(splayTree.getRoot());

    return 0;
}