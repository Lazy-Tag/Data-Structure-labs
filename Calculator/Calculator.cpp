//
// Created by 胡博文 on 2022/10/20.
//

#include "Calculator.h"
#include <climits>

#define PI acos(-1)

std::map<std::string, Fuction> name2Fuction;
extern std::unordered_set<std::string> nameSet;

Calculator::Calculator() //运算符的优先级的初始化
{
    prior['('] = -1;
    prior['-'] = 0, prior['+'] = 0;
    prior['*'] = 1, prior['/'] = 1;
    prior['^'] = 2;
    prior['!'] = 3, prior['D'] = 3, prior['T'] = 3;
    prior['~'] = 3, prior['E'] = 3, prior['&'] = 3;
}

void Calculator::calcExpression() // 表达式计算
{
    datas.clear(), options.clear();
    std::string expr;
    matrixCount = 0, variableCount = 0;
    bool isNegetive = false;
    printf("请输入表达式!\n以'#'代替矩阵; 以'$'代替多项式\n");
    std::getline(std::cin, expr);
    std::getline(std::cin, expr);
    for(int i = 0; i < expr.size(); i ++ )
    {
        if(expr[i] == ' ') continue;
        else if(expr[i] == 'P') // pi的特判
        {
            bool flag = i < expr.size() - 1 && expr[i + 1] == 'I';
            assert(("Expression Error!", flag));
            datas.push(Data(PI));
            i ++ ;
        }
        else if(std::isdigit(expr[i])) //读取数字
        {
            double result = getNumber(expr, i);
            result *= isNegetive ? -1 : 1;
            datas.push(Data(result));
            isNegetive = false;
        }
        else if(expr[i] == '-' && i + 1 < expr.size() && (std::isdigit(expr[i + 1]) || expr[i + 1] == '(')) isNegetive ^= 1;
        else if(expr[i] == '(') options.push({expr[i], 1});
        else if(expr[i] == '#') // 读取矩阵
        {
            Matrix matrix = inputMatrix(expr, i);
            datas.push(Data(matrix));
        }
        else if(expr[i] == '$') // 读取多项式
        {
            printf("请输入表达式中第%d个变量表达式:\n", ++ variableCount);
            datas.push(Data(Quantic(true, true)));
        }
        else if(expr[i] == ')')
        {
            while(options.top().first != '(') calculate();
            options.pop();
        }
        else
        {
            char c = expr[i];
            bool flag = expr[i] == '&' || expr[i] == '~';
            int cnt = 1;
            if(flag && std::isdigit(expr[i + 1])) cnt = getNumber(expr, ++ i);
            while(options.size() && options.top().first != '(' &&
                  prior[options.top().first] >= prior[c]) calculate();
            options.push({c, std::max(cnt, 1)});
        }
    }
    while(options.size()) calculate();
    print();
}

double Calculator::fac(int t) // 阶乘计算
{
    double res = 1;
    for(int i = 1; i <= t; i ++ ) res *= t;
    return res;
}

void Calculator::calculate() // 计算
{
    auto item = options.pop();
    char option = item.first;
    int cnt = item.second;
    if(option == '+' || option == '-' || option == '*' || option == '/' || option == '^')
    {
        Data rsh = datas.pop(), lsh = datas.pop();
        int lType = lsh.getType(), rType = rsh.getType();
        assert(("Calculate Error!", lType * rType >= 0));
        bool flag = (lType != 0 || rType != 2) && (rType != 0 || lType != 2);
        assert(("Expression Error!", flag));
        if(lType == 1 && rType != 1)
        {
            std::swap(lType, rType);
            swap(lsh, rsh);
        }
        if(option == '^')
        {
            if(lType != 1 || rType != 1) assert("Expression Error!");
            double result = 1;
            for(int i = 0; i < rsh.getNumber(); i ++ )
                result *= lsh.getNumber();
            datas.push(Data(result));
        }
        else if(option == '+')
        {
            assert(("Expression Error!", lType == rType));
            if(lType == 0) datas.push(Data(lsh.getMatrix() + rsh.getMatrix()));
            else if(lType == 1) datas.push(Data(lsh.getNumber() + rsh.getNumber()));
            else datas.push(Data(lsh.getQuantic() + rsh.getQuantic()));
        }
        else if(option == '-')
        {
            assert(("Expression Error!", lType == rType));
            if(lType == 0) datas.push(Data(lsh.getMatrix() - rsh.getMatrix()));
            else if(lType == 1) datas.push(Data(lsh.getNumber() - rsh.getNumber()));
            else datas.push(Data(lsh.getQuantic() - rsh.getQuantic()));
        }
        else if(option == '*')
        {
            if(rType == 0) datas.push(Data(lsh.getMatrix() * rsh.getMatrix()));
            else if(rType == 1)
            {
                if(lType == 0) datas.push(Data(lsh.getMatrix() * rsh.getNumber()));
                else if(lType == 1) datas.push(Data(lsh.getNumber() * rsh.getNumber()));
                else datas.push(Data(lsh.getQuantic() * rsh.getNumber()));
            }
            else datas.push(Data(lsh.getQuantic() * rsh.getQuantic()));
        }
        else if(option == '/')
        {
            assert(("Expression Error!", lType * rType == 1));
            datas.push(Data(lsh.getNumber() / rsh.getNumber()));
        }
    }
    else
    {
        Data sh = datas.pop();
        int type = sh.getType();
        if(option == '!')
        {
            assert(("Expression Error!", type == 1));
            datas.push(Data(fac(sh.getNumber())));
        }
        else if(option == 'T')
        {
            assert(("Expression Error!", type == 0));
            sh.getMatrix().trans();
            datas.push(Data(sh.getMatrix()));
        }
        else if(option == 'E')
        {
            assert(("Expression Error!", type == 0));
            auto result = sh.getMatrix().eig();
            assert(("Expression Error!", datas.empty() && options.empty()));
            printEig(result);
        }
        else if(option == 'D')
        {
            assert(("Expression Error!", type == 0));
            datas.push(Data(sh.getMatrix().det()));
        }
        else if(option == '~')
        {
            assert(("Expression Error!", type == 2));
            Quantic q(sh.getQuantic());
            for(int i = 0; i < cnt; i ++ )
                q = ~q;
            datas.push(Data(q));
        }
        else if(option == '&')
        {
            assert(("Expression Error!", type == 2));
            Quantic q(sh.getQuantic());
            for(int i = 0; i < cnt; i ++ )
                q = &q;
            datas.push(Data(q));
        }
        else
            assert(("Option Error!", false));
    }
}

bool Calculator::isMatrix(std::string &expr, int &index) // 矩阵检查
{
    return index + 1 < expr.size() && expr[ ++ index] == '#';
}

Matrix Calculator::inputMatrix(std::string &expr, int &index) // 读入矩阵
{
    int row, col;
    printf("请输入表达式中第%d个矩阵:\n", ++ matrixCount);
    printf("请输入矩阵的行数与列数\n");
    scanf("%d%d", &row, &col);
    return Matrix(row, col, true);
}

bool Calculator::isQuantic(std::string &expr, int &index) // 多项式检查
{
    return index + 1 < expr.size() && expr[ ++ index] == '$';
}

void Calculator::print() // 计算结果打印
{
    if(datas.empty()) return;
    Data data = datas.pop();
    printf("计算结果为: ");
    int type = data.getType();
    if(type == -1) assert("Calculate Error!");
    if(type == 0)
    {
        puts("");
        data.getMatrix().print();
    }
    else if(type == 1) printf("%lf\n", data.getNumber());
    else data.getQuantic().print();
}

void Calculator::swap(Data &a, Data &b) //两个计算数的交换
{
    Data temp = a;
    a = b;
    b = temp;
}

void Calculator::operateFuction() // 对函数定义与计算的处理
{
    while(true)
    {
        printf("定义函数/调用函数/结束 DEF/RUN/END\n");
        std::string option;
        std::cin >> option;
        BEGIN:
        if(option == "DEF")
        {
            Fuction fuction = Fuction::defineFuction();
            name2Fuction.insert({fuction.name, fuction});
            printf("定义函数成功!\n");
        }
        else if(option == "RUN")
        {
            printf("请输入函数名与变量值: ");
            char *str = new char[20];
            double x; std::string name;
            scanf("%s", str);
            int i, len = strlen(str);
            for(i = 0; i < len && str[i] != '('; i ++ ) name += str[i];
            assert(("Expression Error!", i < len));
            assert(("Expression Error!", str[len - 1] == ')'));
            sscanf(str + i, "(%lf)", &x);
            Fuction fuction = name2Fuction[name];
            double result = calculateFuction(fuction, x);
            if(result != NAN) printf("运算结果为: %lf\n", result);
            delete[] str;
        }
        else if(option == "END") break;
        else
        {
            printf("非法操作!请重新输入!\n");
            goto BEGIN;
        }
    }

}

void Calculator::printEig(const myVector<double>& vector) // 打印矩阵特征值的计算结果
{
    printf("计算所得的矩阵特征值为\n");
    for(int i = 0; i < vector.size(); i ++ )
        printf("%10lf  ", vector[i]);
    puts("");
}

double Calculator::calculateFuction(Fuction& fuction, double x) // 函数值的计算
{
    double result = fuction.quantic.calculate(x);
    for(const auto& next : fuction.fuctionName)
    {
        Fuction nextFuction = name2Fuction[next.name];
        result += next.outQuantitic.calculate(x) *
                calculateFuction(nextFuction, next.inQuantic.calculate(x));
    }
    return result;
}