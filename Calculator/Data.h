//
// Created by 胡博文 on 2022/10/21.
//

#ifndef CALCULATOR_DATA_H
#define CALCULATOR_DATA_H

#include "Matrix.h"
#include "Quantic.h"
#include <cstring>

class Data{
private:
    Matrix matrix;
    double number;
    Quantic quantic;
    int type = -1;
public:
    Data() = default;
    int getType() { return type; }
    Matrix& getMatrix() { return matrix; }
    double getNumber() { return number; }
    Quantic& getQuantic() { return quantic; }
    Data(Matrix e) : matrix(e) { type = 0; }
    Data(const double e) : number(e) { type = 1; }
    Data(const Quantic& e) : quantic(e) { type = 2; };
};


#endif //CALCULATOR_DATA_H
