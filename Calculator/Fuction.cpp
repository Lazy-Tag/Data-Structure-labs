//
// Created by 胡博文 on 2022/10/24.
//

#include <cassert>
#include "Fuction.h"

std::set<std::string> nameSet;

Fuction Fuction::defineFuction() // 函数输入与定义
{
    printf("请输入函数表达式!\n以'$'代替多项式\n");

    std::string fuctionName, variableName;
    std::string expr;
    std::getline(std::cin, expr);
    std::getline(std::cin, expr);
    int index, variableCount = 0;
    for(index = 0; expr[index] != '('; index ++ ) fuctionName += expr[index];
    variableName = getVariable(expr, ++ index);
    while(expr[index] != '=') index ++ ;

    assert(("Define Fuction repeatedly", !nameSet.count(fuctionName)));
    Fuction fuction(fuctionName);
    Quantic& quantic = fuction.quantic;
    quantic.setName(variableName.c_str());

    bool isPositive = true, isRead = false;
    double prevNumber = 1;
    std::string fName;
    Quantic prevQuantic;
    prevQuantic.toOne();
    prevQuantic.setName(variableName.c_str());
    Quantic qin, qout;
    qin.setName(variableName.c_str()), qout.setName(variableName.c_str());

    for(int i = index + 1; i < expr.size(); i ++ ) // 对表达式进行处理
    {
        if(expr[i] == ' ' || expr[i] == '*') continue;
        else if(checkFuctionName(fName, expr, i))// 调用已有函数
        {
            std::string variable = getVariable(expr, ++ i);
            qin.setParameter(variable);
            qout = prevQuantic * prevNumber;
            fuction.fuctionName.insert(Fuc(fName, qin, qout));
            isRead = false, prevQuantic.toOne();
            fName = "", prevNumber = 1, isPositive = true;
        }
        else if(expr[i] == 'P') // pi的定义
        {
            bool flag = i < expr.size() - 1 && expr[i + 1] == 'I';
            assert(("Expression Error!", flag));
            prevNumber = acos(-1);
            i ++ ;
        }
        else if(quantic.check(expr, i)) // 函数中多项式的定义
        {
            prevNumber *= isPositive? 1 : -1;
            if(expr[i] == ' ') i ++ ;
            if(i + 1 < expr.size() && expr[i] == '^')
            {
                if(expr[ ++ i] == ' ') i ++ ;
                double e = quantic.getNumber(expr, i);
                assert(("EXP Error!", e - (int)e <= 1e-6));
                while(e >= quantic.parameter.size()) quantic.parameter.push_back(0);
                quantic.parameter[(int)e] += prevNumber;
            }
            else
            {
                for(int j = quantic.parameter.size(); j < 2; j ++ ) quantic.parameter.push_back(0);
                quantic.parameter[1] += prevNumber;
            }
            prevNumber = 1;
            isRead = false, isPositive = true;
        }
        else if(std::isdigit(expr[i])) //读取数字
        {
            prevNumber = quantic.getNumber(expr, i);
            isRead = true;
        }
        else if(expr[i] == '$') // 对调用已有函数中的多项式处理
        {
            printf("请输入表达式中第%d个变量表达式:\n", ++ variableCount);
            prevQuantic = Quantic(true, false);
            isRead = true;
        }
        else if(expr[i] == '-' && i + 1 < expr.size() &&
        (std::isdigit(expr[i + 1]) || expr[i + 1] == '(')) isPositive ^= 1;
        else//加减号的处理与非法表达式的处理
        {
            if(isRead)
            {
                prevNumber *= isPositive? 1 : -1;
                quantic = quantic + prevQuantic * prevNumber;
                isRead = false, prevQuantic.toOne();
                prevNumber = 1, isPositive = true;
            }
            if(expr[i] == '+') isPositive = true;
            else if(expr[i] == '-') isPositive = false;
            else
                assert(("Quantic Expression Error!", false));
        }
    }
    if(isRead) // 处理尾数
    {
        prevNumber *= isPositive? 1 : -1;
        quantic = quantic + prevQuantic * prevNumber;
        isRead = false, prevQuantic.toOne();
        fName = "", prevNumber = 1, isPositive = true;
    }
    nameSet.insert(fuctionName);
    return fuction;
}

bool Fuction::checkFuctionName(std::string& source, std::string& expr, int& index) // 调用已有函数的检测
{
    if(expr[index] == ' ') index ++ ;
    std::string name;
    bool flag = false;
    int backup = index;
    for(; index < expr.size() && expr[index] != '('; index ++ ) name += expr[index];
    if(nameSet.count(name))
    {
        flag = true;
        source = name;
    }
    else index = backup;
    return flag;
}

std::string Fuction::getVariable(std::string &expr, int &index) // 获取函数表达式中的多项式
{
    std::string variable;
    for(; index < expr.size() && expr[index] != ')'; index ++ ) variable += expr[index];
    return variable;
}

Fuction::Fuction(std::string& _name) : name(_name) {}

