#include "BinaryTree.h"
#include <string>
#include <cassert>
#include <windows.h>

/*
 * printTraverse函数按照前序、中序、后序的方式以迭代方式与递归方式依次输出结果。
 * printOtherInformation函数则输出二叉树总结点数与每一个节点的所有子孙。
 * */

std::fstream file;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    file.open("input.txt", std::ios::in);
    auto *tree = new BinaryTree<double>();

    tree->setNodes();
    std::string option;
    while(true)
    {
        printf("请输入查询的信息: 遍历/节点总数/所有子孙/结束程序 trav/number/son/end \n");
        std::cin >> option;
        if(option == "trav")
        {
            int type, mode = 0;
            printf("请输入遍历类型: 0/1/2/3 层次/前序/中序/后序");
            std::cin >> type;
            assert(("Type Error!", type <= 3));
            if(type)
            {
                printf("请输入遍历方式: 0/1 迭代/递归");
                std::cin >> mode;
                assert(("Mode Error!", mode <= 1));
            }
            tree->printTraverse(type + 3 * mode);
        }
        else if(option == "number")
            printf("二叉树节点总数为: %d\n", tree->getNum(tree->root()));
        else if(option == "son")
            tree->PrintAllSons();
        else if(option == "end")
        {
            printf("程序结束!\n");
            break;
        }
        else
            printf("非法输入!请重新输入!\n");
    }

    file.close();
    return 0;
}
