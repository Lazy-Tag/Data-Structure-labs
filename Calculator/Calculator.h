//
// Created by 胡博文 on 2022/10/20.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <cstring>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <cmath>
#include <map>
#include "Matrix.h"
#include "myStack.h"
#include "Data.h"
#include "Quantic.h"
#include "Fuction.h"

class Calculator : public Quantic {
public:
    Calculator();
    void calcExpression();
    void operateFuction();
private:
    int matrixCount, variableCount;
    std::unordered_map<char, int> prior;
    myStack<Data> datas;
    myStack<std::pair<char, int>> options;

    static double fac(int);
    void calculate();
    static bool isMatrix(std::string&, int&);
    static bool isQuantic(std::string &expr, int &index);
    static void swap(Data&, Data&);
    Matrix inputMatrix(std::string&, int&);
    void print();
    static void printEig(const myVector<double>& vector);

    double calculateFuction(Fuction &fuction, double x);
};


#endif //CALCULATOR_CALCULATOR_H
