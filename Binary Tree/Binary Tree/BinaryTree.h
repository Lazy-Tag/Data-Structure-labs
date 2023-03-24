//
// Created by 胡博文 on 2022/10/26.
//

#ifndef BINARY_TREE_BINARYTREE_H
#define BINARY_TREE_BINARYTREE_H

#include "BinaryNode.h"
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

template <typename T>
class BinaryTree;

typedef std::vector<double>& (BinaryTree<double>::* FuctionPointer)(std::vector<double>);

template <typename T>
class BinaryTree {
public:
    void travLevel(BinaryNode<T>*, std::vector<BinaryNode<T>*>&); // 层次扁颗粒
    void travPreByRec(BinaryNode<T>*, std::vector<BinaryNode<T>*>&); // 递归方式前序遍历
    void  travInByRec(BinaryNode<T>*, std::vector<BinaryNode<T>*>&); // 递归方式中序遍历
    void  travPostByRec(BinaryNode<T>*, std::vector<BinaryNode<T>*>&); // 递归方式后序遍历
    void  travPreByIter(BinaryNode<T>*, std::vector<BinaryNode<T>*>&); // 迭代方式前序遍历
    void  travInByIter(BinaryNode<T>*, std::vector<BinaryNode<T>*>&); // 迭代方式中序遍历
    void  travPostByIter(BinaryNode<T>*, std::vector<BinaryNode<T>*>&); // 迭代方式后序遍历
    void printTraverse(int);
    ~BinaryTree();
    void getAllSon(BinaryNode<T> *, std::vector<BinaryNode<T>*> &result);

    BinaryNode<T>* root() { return _root; }
    int size() { return _size; }
    bool empty() { return _size == 0; }
    void printResult(void(BinaryTree<T>::*)(BinaryNode<T>*, std::vector<BinaryNode<T>*>&));
    void setNodes();
    void PrintAllSons();
    int getNum(BinaryNode <T> *node);
private:
    BinaryNode<T>* _root = nullptr;
    int _size = 0;
    std::stack<BinaryNode<T>*> nodeStk;
    std::queue<BinaryNode<T>*> nodeQue;
    static void (BinaryTree<T>::* const Pointers[7])(BinaryNode<T>*, std::vector<BinaryNode<T>*>&);
};
template<typename T>
void (BinaryTree<T>::* const BinaryTree<T>::Pointers[7])(BinaryNode<T>*, std::vector<BinaryNode<T>*>&) = {
        &BinaryTree<T>::travLevel,
        &BinaryTree<T>::travPreByIter,&BinaryTree<T>::travInByIter,
        &BinaryTree<T>::travPostByIter,&BinaryTree<T>::travPreByRec,
        &BinaryTree<T>::travInByRec,&BinaryTree<T>::travPostByRec
};// 将二叉树前序、中序、后序遍历的迭代版与递归版的函数地址传入Pointers的函数指针数组中。

template<typename T>
void BinaryTree<T>::travLevel(BinaryNode<T>* root, std::vector<BinaryNode<T>*>& result)
{
    nodeQue.push(root);
    while(!nodeQue.empty())
    {
        auto currentNode = new BinaryNode<T>(*nodeQue.front());
        nodeQue.pop();
        result.push_back(currentNode);
        if(currentNode->leftChild)
        {
            currentNode->leftChild->height = currentNode->height + 1;
            nodeQue.push(currentNode->leftChild);
        }
        if(currentNode->rightChild)
        {
            currentNode->rightChild->height = currentNode->height + 1;
            nodeQue.push(currentNode->rightChild);
        }
    }
}

template<typename T>
void BinaryTree<T>::travPreByRec(BinaryNode<T>*current, std::vector<BinaryNode<T>*>& result)
{
    result.push_back(current);
    if(current->leftChild) travPreByRec(current->leftChild, result);
    if(current->rightChild) travPreByRec(current->rightChild, result);
}

template<typename T>
void BinaryTree<T>::travInByRec(BinaryNode<T>*current, std::vector<BinaryNode<T>*>& result)
{
    if(current->leftChild) travInByRec(current->leftChild, result);
    result.push_back(current);
    if(current->rightChild) travInByRec(current->rightChild, result);
}

template<typename T>
void BinaryTree<T>::travPostByRec(BinaryNode<T>*current, std::vector<BinaryNode<T>*>& result)
{
    if(current->leftChild) travPostByRec(current->leftChild, result);
    if(current->rightChild) travPostByRec(current->rightChild, result);
    result.push_back(current);
}

template<typename T>
void BinaryTree<T>::travPreByIter(BinaryNode<T>* root, std::vector<BinaryNode<T>*>& result)
{
    auto currentNode = root;
    while(true)
    {
        while(currentNode)
        {
            result.push_back(currentNode);
            nodeStk.push(currentNode->rightChild);
            currentNode = currentNode->leftChild;
        }
        if(nodeStk.empty()) break;
        currentNode = nodeStk.top(), nodeStk.pop();
    }
}

template<typename T>
void BinaryTree<T>::travInByIter(BinaryNode<T>* root, std::vector<BinaryNode<T>*>& result)
{
    auto currentNode = root;
    while(true)
    {
        while(currentNode)
        {
            nodeStk.push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if(nodeStk.empty()) break;
        currentNode = nodeStk.top(), nodeStk.pop();
        result.push_back(currentNode);
        currentNode = currentNode->rightChild;
    }
}

template<typename T>
void BinaryTree<T>::travPostByIter(BinaryNode<T>* root, std::vector<BinaryNode<T>*> &result)
{
    nodeStk.push(root);
    auto currentNode = root;
    while(!nodeStk.empty())
    {
        if(nodeStk.top() != currentNode->father)
        {
            while(nodeStk.top())
            {
                auto temp = nodeStk.top();
                if(temp->leftChild)
                {
                    if(temp->rightChild) nodeStk.push(temp->rightChild);
                    nodeStk.push(temp->leftChild);
                }
                else nodeStk.push(temp->rightChild);
            }
            nodeStk.pop();
        }
        currentNode = nodeStk.top(), nodeStk.pop();
        result.push_back(currentNode);
    }
}

template<typename T>
void BinaryTree<T>::printResult(void(BinaryTree<T>::*fuction)(BinaryNode<T>*, std::vector<BinaryNode<T>*>&))
{
    std::vector<BinaryNode<T>*>result;
    (this->*fuction)(_root, result);
    for(const auto& node : result) node->print();
    puts("");
}

template<typename T>
void BinaryTree<T>::printTraverse(int type)
{
    puts("----------\n");
    printResult(Pointers[type]);
    puts("----------\n");
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
    _root->~BinaryNode();
}

template<typename T>
void BinaryTree<T>::getAllSon(BinaryNode<T> *node, std::vector<BinaryNode<T>*> &result)
{
    std::vector<BinaryNode<T>*> current;
    if(node->leftChild) getAllSon(node->leftChild, current);
    current.push_back(node);
    if(node->rightChild) getAllSon(node->rightChild, current);
    printf(" All the sons of the node numbered %d:\n", node->id);
    for(const auto & Node : current)
    {
        result.push_back(Node);
        if(Node == node) continue;
        Node->print();
    }
    if(current.size() == 1) printf("None!");
    puts("");
}

template<typename T>
void BinaryTree<T>::setNodes()  // 以递归地方式输入整棵二叉树
{
    _root = _root->input(nullptr);
}

template<typename T>
void BinaryTree<T>::PrintAllSons()
{
    std::vector<BinaryNode<T>*> result;
    getAllSon(_root, result);
}

template<typename T>
int BinaryTree<T>::getNum(BinaryNode<T> *node)
{
    int result = 1;
    if(node->leftChild) result += getNum(node->leftChild);
    if(node->rightChild) result += getNum(node->rightChild);
    return result;
}

#endif //BINARY_TREE_BINARYTREE_H
