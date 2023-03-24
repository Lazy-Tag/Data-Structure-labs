//
// Created by 胡博文 on 2022/10/20.
//

#include <cassert>
#include <algorithm>
#include <cmath>
#include <ctime>
#include "Matrix.h"
#define eps 1e-5

Matrix::Matrix(int _row, int _col, bool isInit) : row(_row), col(_col) // 矩阵初始化
{
    if(isInit)
    {
        printf("请读入矩阵数据!\n");
        for(int i = 0; i < row; i ++ )
        {
            myVector<double> temp;
            for(int j = 0; j < col; j ++ )
            {
                double t;
                scanf("%lf", &t);
                temp.push_back(t);
            }
            data.push_back(temp);
        }
    }
}

Matrix& Matrix::operator+ (Matrix& matrix) // 矩阵相加
{
    bool flag = row == matrix.getRow() && col == matrix.getCol();
    assert(("Matrix Add Error!", flag));
    for(int i = 0; i < row; i ++ )
        for(int j = 0; j < col; j ++ )
            data[i][j] += matrix.data[i][j];
    return *this;
}

Matrix& Matrix::operator- (Matrix& matrix) // 矩阵相减
{
    bool flag = row == matrix.getRow() && col == matrix.getCol();
    assert(("Matrix Subtract Error!", flag));
    for(int i = 0; i < row; i ++ )
        for(int j = 0; j < col; j ++ )
            data[i][j] -= matrix.data[i][j];
    return *this;
}

Matrix Matrix::operator* (Matrix& matrix) // 矩阵相乘
{
    assert(("Matrix Multiply Error!", col == matrix.row));
    Matrix result(row, matrix.col, false);
    for(int i = 0; i < row; i ++ )
    {
        myVector<double> temp;
        for(int j = 0; j < matrix.col; j ++ )
        {
            double t = 0;
            for(int k = 0; k < col; k ++ )
                t += data[i][k] * matrix.data[k][j];
            temp.push_back(t);
        }
        result.data.push_back(temp);
    }
    return result;
}

Matrix& Matrix::operator/ (double t) // 矩阵数除
{
    for(int i = 0; i < row; i ++ )
        for(int j = 0; j < col; j ++ )
            data[i][j] /= t;
    return *this;
}

Matrix& Matrix::operator* (double t) // 矩阵数乘
{
    for(int i = 0; i < row; i ++ )
        for(int j = 0; j < col; j ++ )
            data[i][j] *=t;
    return *this;
}

void Matrix::trans() //转置
{
    for(int i = 0; i < row; i ++ )
        for(int j = 0; j < i; j ++ )
            std::swap(data[i][j], data[j][i]);
}

double Matrix::det() // 行列式计算
{
    assert(("Matrix Det Error!\n", row == col));
    if(row == 1) return data[0][0];
    Matrix next(row - 1, col - 1, false);
    int t = row;
    for(int i = 0; i < row; i ++ )
        if(data[i][0] != 0)
        {
            t = i;
            break;
        }
    if(t == row) return 0;
    for(int i = 0; i < col; i ++ )
        std::swap(data[0][i], data[t][i]);
    for(int i = 1; i < row; i ++ )
    {
        myVector<double> temp;
        double k = data[i][0] / data[0][0];
        for(int j = 1; j < col; j ++ )
            temp.push_back(data[i][j] - k * data[0][j]);
        next.data.push_back(temp);
    }
    for(int i = 0; i < col; i ++ )
        std::swap(data[0][i], data[t][i]);
    return data[0][0] * next.det();
}

double rand(double l, double r)
{
    return (double) rand() / RAND_MAX * (r - l) + l;
}

myVector<double> Matrix::eig()// 模拟退火求矩阵特征值
{
    assert(("Eig Error!\n", row == col));
    srand(time(NULL));
    myVector<double> result;
    for(int i = 0; i < 100; i ++ )
    {
        double cur = rand(-1e4, 1e4);
        for(double t = 1e4; t >= 1e-6; t *= 0.99)
        {
            double np = rand(-t + cur, t + cur);
            change(cur);
            double prevDet = fabs(det());
            change( -cur + np);
            double nowDet = fabs(det());
            change(-np);
            double dt = nowDet - prevDet;
            if(exp(-dt / t) > rand(0, 1)) cur = np;
        }
        change(cur);
        if(fabs(det()) < eps)
        {
            bool flag = true;
            for(int k = 0; k < result.size(); k ++ )
                if(fabs(cur - result[k]) < eps) flag = false;
            if(flag) result.push_back(cur);
        }
        change(-cur);
        if(result.size() == row) break;
    }
    result.sort();
    return result;
}

void Matrix::change(double d) // 矩阵对角线减d
{
    for(int i = 0; i < row; i ++ )
        data[i][i] -= d;
}

void Matrix::print() // 矩阵计算结果的打印
{
    for(int i = 0; i < row; i ++ )
    {
        for(int j = 0; j < col; j ++ )
            printf("%10lf  ", data[i][j]);
        puts("");
    }
}

Matrix::Matrix() {}
