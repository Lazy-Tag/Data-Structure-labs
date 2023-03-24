//
// Created by 胡博文 on 2022/10/21.
//

#ifndef CALCULATOR_QUANTIC_H
#define CALCULATOR_QUANTIC_H

#include <string>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include "myVector.h"
#define DEFAULTNAME "x"

class Quantic {
public:
    Quantic(bool, bool);
    Quantic(int, std::string&);
    Quantic() = default;
    Quantic(const Quantic&);
    static const int maxLen = 100;
    bool isIntegral = false;
    Quantic operator+ (const Quantic& t);// 多项式相加
    Quantic operator- (const Quantic& t);// 多项式相减
    Quantic operator* (double t); // 多项式数乘
    Quantic operator* (const Quantic& t);// 多项式相乘
    Quantic operator& ();// 多项式求导
    Quantic operator~ ();// 多项式积分
    double calculate(double) const;
    void print() const;
    friend class Fuction;
protected:
    std::string name;
    myVector<double> parameter;

    void setName(const char *_name) { name = _name; }
    bool check(std::string&, int&) const;
    double getNumber(std::string&, int&);
    void setParameter(std::string&);
    bool check(int i) const;
    void toOne();

    void toZero();
};


#endif //CALCULATOR_QUANTIC_H
