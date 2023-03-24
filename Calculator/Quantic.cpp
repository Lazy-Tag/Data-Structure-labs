//
// Created by 胡博文 on 2022/10/21.
//

#include <cmath>
#include "myVector.h"
#include "Quantic.h"
#define eps 1e-8
#define INF 1e9

Quantic::Quantic(bool isInit, bool isSetName)
{
    if(isInit) // 是否需要输入表达式进行初始化
    {
        if(isSetName) //是否需要初始化变量名
        {
            printf("请输入变量名!\n");
            BEGIN:
            getline(std::cin, name);
            if (name.empty())
            {
                printf("输入变量名为空，请重新输入!\n");
                goto BEGIN;
            }
        }
        printf("请输入表达式!\n");
        name = DEFAULTNAME;
        std::string expr;
        std::getline(std::cin, expr);
        setParameter(expr);
    }
}

double Quantic::getNumber(std::string &expr, int &index)//获取表达式中的数字
{
    if(!std::isdigit(expr[index])) return 0;
    double result = 0;
    while(index < expr.size() && (std::isdigit(expr[index]) || expr[index] == 'e'))
    {
        if(expr[index] == 'e')
        {
            int exp = getNumber(expr, ++ index);
            result *= pow(10, exp);
            index ++ ;
        }
        else result = result * 10 + expr[index ++ ] - '0';
    }
    if(expr[index] == '.')
    {
        index ++ ;
        double t = 0.1;
        for(; index < expr.size() && std::isdigit(expr[index]); index ++ , t *= 0.1)
            result += (expr[index] - '0') * t;
    }
    if(!std::isdigit(expr[index])) index -- ;
    return result;
}

bool Quantic::check(std::string &expr, int &index) const // 检索表达式中变量
{
    int i;
    for(i = 0; index < expr.size() && expr[index] == name[i]; index ++ , i ++ );
    return i == name.size();
}

Quantic Quantic::operator+ (const Quantic &t) // 多项式加法
{
    Quantic result(std::max(parameter.size(), t.parameter.size()), name);
    for(int i = 0; i < std::max(parameter.size(), t.parameter.size()); i ++ )
        result.parameter[i] = parameter[i] + t.parameter[i];
    return result;
}

Quantic Quantic::operator- (const Quantic &t)// 多项式减法
{
    Quantic result(std::max(parameter.size(), t.parameter.size()), name);
    for(int i = 0; i < std::max(parameter.size(), t.parameter.size()); i ++ )
        result.parameter[i] = parameter[i] - t.parameter[i];
    return result;
}

Quantic Quantic::operator* (const Quantic &t) // 多项式乘法
{
    Quantic result(parameter.size() + t.parameter.size(), name);
    for(int i = 0; i < parameter.size(); i ++ )
        for(int j = 0; j < t.parameter.size(); j ++ )
            result.parameter[i + j] += parameter[i] * t.parameter[j];
    return result;
}

Quantic Quantic::operator&() // 多项式求导
{
    Quantic result(parameter.size() - 1, name);
    for(int i = 1; i < parameter.size(); i ++ )
        result.parameter[i - 1] = parameter[i] * i;
    return result;
}

Quantic Quantic::operator~() // 多项式积分
{
    Quantic result(parameter.size() + 1, name);
    for(int i = parameter.size() - 1; i >= 0; i -- )
        result.parameter[i + 1] = parameter[i] / (i + 1);
    result.isIntegral = true;
    return result;
}

Quantic::Quantic(const Quantic& t)
{
    name = t.name;
    parameter = myVector(t.parameter);
    isIntegral |= t.isIntegral;
}

Quantic Quantic::operator*(double t) // 多项式数乘
{
    Quantic result(parameter.size(), name);
    for(int i = 0; i < parameter.size(); i ++ )
        result.parameter.push_back(0), result.parameter[i] = parameter[i] *= t;
    return result;
}

void Quantic::print() const//多项式的输出
{
    bool flag = false;
    for(int i = parameter.size() - 1; i >= 0; i -- )
    {
        if(fabs(parameter[i]) < eps && (i || !isIntegral)) continue;
        flag = true;
        if(!i && isIntegral)
            printf("C ");
        else
        {
            if(fabs(parameter[i] - 1) > eps || !i) printf("%.2lf", fabs(parameter[i]));
            if(i) printf("%s", name.c_str());
            if(i > 1) printf("^%d ",  i);
            else printf(" ");
        }
        if(!i || !check(i - 1)) break;
        if(fabs(parameter[i - 1]) <= eps || parameter[i - 1] > 0) printf("+ ");
        else printf("- ");
    }
    if(!flag) printf("0");
    puts("");
}

Quantic::Quantic(int len, std::string &_name) // 初始化
{
    int n = std::min(len, 1);
    name = _name;
    for(int i = 0; i < len; i ++ )
        parameter.push_back(0);
}

bool Quantic::check(int index) const // 判零
{
    for(int i = index; i >= 0; i -- )
        if(parameter[i] != 0) return true;
    return false | isIntegral;
}

double Quantic::calculate(double x) const //多项式计算
{
    double result = 0;
    for(int i = 0; i < parameter.size(); i ++ )
        result += parameter[i] * pow(x, i);
    return result;
}

void Quantic::setParameter(std::string& expr) // 从字符串转化为
{
    toZero();
    bool isPositive = true, isRead = false;
    double prevNumber = 1;
    for(int i = 0; i < expr.size(); i ++ )
    {
        if(expr[i] == ' ' || expr[i] == '*') continue;
        else if(check(expr, i))
        {
            prevNumber *= isPositive? 1 : -1;
            if(expr[i] == ' ' && i + 1 < expr.size() && expr[i + 1] == '^') i ++ ;
            if(i + 1 < expr.size() && expr[i] == '^')
            {
                if(expr[ ++ i] == ' ') i ++ ;
                double e = getNumber(expr, i);
                assert(("EXP Error!", e - (int)e <= 1e-6));
                while(e >= parameter.size()) parameter.push_back(0);
                parameter[(int)e] += prevNumber;
            }
            else
            {
                for(int j = parameter.size(); j < 2; j ++ ) parameter.push_back(0);
                parameter[1] += prevNumber;
            }
            prevNumber = 1;
            isRead = false;
        }
        else if(expr[i] == '-' && i + 1 < expr.size() && (std::isdigit(expr[i + 1]) || expr[i + 1] == '(')) isPositive ^= 1;
        else if(std::isdigit(expr[i]))
        {
            prevNumber = getNumber(expr, i);
            isRead = true;
        }
        else
        {
            if(isRead)
            {
                prevNumber *= isPositive? 1 : -1;
                if(!parameter.size()) parameter.push_back(prevNumber);
                else parameter[0] += prevNumber;
                isRead = false;
            }
            if(expr[i] == '+') isPositive = true;
            else if(expr[i] == '-') isPositive = false;
            else
                assert(("Quantic Expression Error!", false));
        }
    }
    if(isRead)
    {
        prevNumber *= isPositive? 1 : -1;
        if(!parameter.size()) parameter.push_back(prevNumber);
        else parameter[0] += prevNumber;
        isRead = false;
    }
}

void Quantic::toOne() // 多项式置一
{
    if(!parameter.size()) parameter.push_back(0);
    for(int i = 0; i < parameter.size(); i ++ )
        parameter[i] = 0;
    parameter[0] = 1;
}

void Quantic::toZero()
{
    for(int i = 0; i < parameter.size(); i ++ )
        parameter[i] = 0;
}
