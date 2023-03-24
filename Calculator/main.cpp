#include <iostream>
#include <windows.h>
#include "Calculator.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    Calculator calculator;
    printf("欢迎使用计算器!\n");
    std::string option;
    while(true)
    {
        printf("请选择需要的计算的表达式类型: ");
        printf("表达式\\函数\\退出    EXP\\FUC\\END");
        std::cin >> option;
        if(option == "EXP") calculator.calcExpression();
        else if(option == "FUC") calculator.operateFuction();
        else if(option == "END")
        {
            printf("程序结束!\n");
            break;
        }
        else printf("非法输入! 请重新输入!\n");
    }

    return 0;
}
