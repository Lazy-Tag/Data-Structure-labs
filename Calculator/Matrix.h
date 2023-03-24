//
// Created by 胡博文 on 2022/10/20.
//

#ifndef CALCULATOR_MATRIX_H
#define CALCULATOR_MATRIX_H

#include "myVector.h"
#include <cstdio>

// 矩阵类
class Matrix{
public:
    int getRow() const { return row; }
    int getCol() const { return col; }
    void setRow(int t) { row = t; }
    void setCol(int t) { col = t; }
    myVector<myVector<double>>& getData() { return data; }
    Matrix(int, int, bool);

    Matrix();

    Matrix& operator+ (Matrix&);// 矩阵加法
    Matrix& operator- (Matrix&);// 矩阵减法
    Matrix& operator* (double);// 矩阵数乘
    Matrix& operator/ (double);// 矩阵数除
    Matrix operator* (Matrix&);// 矩阵乘法
    void trans();// 矩阵转置
    double det();// 求矩阵行列式
    myVector<double> eig(); // 求矩阵特征值
    void print();// 矩阵打印函数
private:
    myVector<myVector<double>> data;
    int row, col;
    void change(double d);
};


#endif //CALCULATOR_MATRIX_H
