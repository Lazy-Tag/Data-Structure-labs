#include "RouteMap.h"
#include <iostream>
#include <windows.h>

#define MAXTIME "5/31/2017 00:00"
#define MINTIME "5/1/2017 00:00"

int main()
{
    system("chcp 65001");
    RouteMap::input();
    printf("欢迎来到航班查询系统!\n");
    while(true)
    {
        printf("请选择查询类型: \n");
        printf("遍历/可连通性/航线数目/最短飞行时间/满足条件的航线/备选航线/结束程序:  ");
        printf("trav/conn/num/time/requ/alter/end \n");

        std::string option;
        std::cin >> option;
        if(option == "trav")
        {
            int airport;
            printf("请选择开始机场: ");
            std::cin >> airport;
            printf("请选择遍历类型: BFS/DFS B/D\n");
            std::string type;
            std::cin >> type;
            if(type == "D") RouteMap::travDFS(airport);
            else if(type == "B") RouteMap::travBFS(airport);
            else printf("非法输入! 请重新输入!\n");
        }
        else if(option == "conn")
        {
            int num;
            printf("请输入限制中转次数: ");
            std::cin >> num;
            RouteMap::CheckConnect(num);
        }
        else if(option == "num")
        {
            int departure, arrive, num;
            printf("请输入出发机场、目的机场与转机次数: ");
            std::cin >> departure >> arrive >> num;
            printf("航线数目: %d\n", RouteMap::checkNums(departure, arrive, num));
        }
        else if(option == "time")
        {
            int departure, arrive;
            printf("请输入出发机场与目的机场: ");
            std::cin >> departure >> arrive;
            RouteMap::dijkstra4Time(departure, arrive).print();
        }
        else if(option == "requ")
        {
            std::string request, type;
            printf("请输入最优化数据: 中转次数/航行费用 tran/fare \n");
            std::cin >> request;
            if(request == "tran")
            {
                printf("请输入需求类型: 起飞时间/降落时间/飞机类型/中转次数 depa/arri/model \n");
                std::cin >> type;
                std::vector<int> result;
                if(type == "depa" || type == "arri")
                {
                    std::string info1, info2;
                    int departure, arrive, cnt;
                    printf("请输入出发机场、目的机场与中转次数: \n");
                    std::cin >> departure >> arrive >> cnt;
                    getchar();
                    printf("请输入时间上限: \n");
                    std::getline(std::cin, info1);
                    printf("请输入时间下限: \n");
                    std::getline(std::cin, info2);
                    Date begin(info1), end(info2);
                    if(type == "depa") result = RouteMap::dijkstra4Tran(departure, arrive, begin, end, -1, 0, cnt);
                    else result = RouteMap::RouteMap::dijkstra4Tran(departure, arrive, begin, end, -1, 0, cnt);
                }
                else if(type == "model")
                {
                    int departure, arrive, model, cnt;
                    printf("请输入出发机、目的机场、中转次数、机型: ");
                    std::cin >> departure >> arrive >> cnt >> model;
                    result = RouteMap::dijkstra4Tran(departure, arrive, Date(MINTIME), Date(MAXTIME), model, -1, cnt);
                }
                else printf("非法输入! 请重新输入!\n");
                for(int line : result) printf("%d ", line);
                puts("");
            }
            else if(request == "fare")
            {
                printf("请输入需求类型: 起飞时间/降落时间/飞机类型/中转时间 depa/arri/model/time \n");
                std::cin >> type;
                std::pair<std::vector<int>, int> result;
                if(type == "depa" || type == "arri")
                {
                    std::string info1, info2;
                    int departure, arrive;
                    printf("请输入出发机场与目的机场: ");
                    std::cin >> departure >> arrive;
                    getchar();
                    printf("请输入时间上限: \n");
                    std::getline(std::cin, info1);
                    printf("请输入时间下限: \n");
                    std::getline(std::cin, info2);
                    Date begin(info1), end(info2);
                    if(type == "depa") result = RouteMap::dijkstra4Fare(departure, arrive, begin, end, -1, 0);
                    else result = RouteMap::RouteMap::dijkstra4Fare(departure, arrive, begin, end, -1, 1);
                }
                else if(type == "model")
                {
                    int departure, arrive, model;
                    printf("请输入出发机、目的机场、机型: ");
                    std::cin >> departure >> arrive >> model;
                    result = RouteMap::dijkstra4Fare(departure, arrive, Date(MINTIME), Date(MAXTIME), model, -1);
                }
                else if(type == "time")
                {
                    int departure, arrive;
                    std::string time;
                    printf("请输入出发机场、目的机场、最低中转时间: ");
                    std::cin >> departure >> arrive >> time;
                    result = RouteMap::dijkstra4FareWithTime(departure, arrive, Date(time));
                }
                else printf("非法输入! 请重新输入!\n");
                for(int line : result.first) printf("%d ", line);
                printf("\n%d\n", result.second);
            }
            else printf("非法输入! 请重新输入!\n");
        }
        else if(option == "alter")
        {
            int departure, arrive, cnt;
            std::string time;
            printf("请输入出发机场、目的机场、中转次数上限、中转时间上限:\n");
            std::cin >> departure >> arrive >> cnt;
            getchar();
            std::getline(std::cin, time);
            auto result = RouteMap::dijkstra4Alter(departure, arrive, Date(time), cnt);
            for(int line : result) printf("%d ", line);
            puts("");
        }
        else if(option == "end")
        {
            printf("程序结束!\n");
            break;
        }
        else printf("非法输入! 请重新输入!\n");
    }
    return 0;
}
