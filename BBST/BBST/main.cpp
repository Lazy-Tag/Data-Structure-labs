#include <iostream>
#include <cassert>
#include "BST.h"
#include "AVLTree.h"
#include "RBTree.h"

int main() {
    int m;
    std::cin >> m;
    BST* bbst = new RBTree();
    while (m -- )
    {
        int option, x;
        std::cin >> option >> x;
        switch (option) {
            case 1: {
                bbst->insert(x);
                break;
            }
            case 2: {
                bbst->remove(x);
                break;
            }
            case 3: {
                std::cout << bbst->getRank(x) << std::endl;
                break;
            }
            case 4: {
                std::cout << bbst->getValue(x) << std::endl;
                break;
            }
            case 5: {
                std::cout << bbst->getPrev(x) << std::endl;
                break;
            }
            case 6: {
                std::cout << bbst->getSucc(x) << std::endl;
                break;
            }
            default:{
                puts("Illegal Input!");
                break;
            }
        }
    }
    return 0;
}
