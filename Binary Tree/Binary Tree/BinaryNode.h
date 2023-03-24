//
// Created by 胡博文 on 2022/10/26.
//

#ifndef BINARY_TREE_BINARYNODE_H
#define BINARY_TREE_BINARYNODE_H

#include <vector>
#include <iostream>
#include <fstream>

extern std::fstream file;

template <typename T>
struct BinaryNode {
    int height = -1, id{};
    T data;
    BinaryNode<T>* leftChild = nullptr;
    BinaryNode<T>* rightChild = nullptr;
    BinaryNode<T>* father = nullptr;

    BinaryNode() : leftChild(nullptr), rightChild(nullptr), father(nullptr), id(-1) {}
    ~BinaryNode();
    BinaryNode<T>* input(BinaryNode<T>*);
    void print();
    bool operator< (const BinaryNode &t) const {return data < t.data; }
    bool operator== (const BinaryNode &t) const {return id == t.id; }
};

/*
 * 递归方式输入整棵二叉树：
 *每一个节点依次输入其编号、数值、是否有左、右孩子，若有，则递归进入构造左、右孩子。
 * */
template<typename T>
BinaryNode<T> *BinaryNode<T>::input(BinaryNode<T> *_father)
{
    bool hasLeftChild, hasRightChild;
    auto *node = new BinaryNode<double>();
    file >> node->id >> node->data;
    node->father = _father;
    file >> hasLeftChild >> hasRightChild;
    if(hasLeftChild) node->leftChild = input(node);
    if(hasRightChild) node->rightChild = input(node);
    return node;
}

template<typename T>
BinaryNode<T>::~BinaryNode()
{
    if(leftChild) leftChild->~BinaryNode();
    if(rightChild) rightChild->~BinaryNode();
    delete data;
}

template<typename T>
void BinaryNode<T>::print()
{
    printf("ID: %02d data: %4lf\n", id, data);
}


#endif //BINARY_TREE_BINARYNODE_H
