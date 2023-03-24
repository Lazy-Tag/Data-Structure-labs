//
// Created by 胡博文 on 2022/10/29.
//

#ifndef AIRLINE_ROUTEMAP_H
#define AIRLINE_ROUTEMAP_H

#include "Airline.h"
#include "Date.h"
#include "Heap.h"
#include <map>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>

const int N = 200000, M = 200;
const int airportNum = 79;

class RouteMap {
public:
    static void input();
    static void add(int, int, Airline);
    static void travBFS(int);
    static void travDFS(int);
    static void CheckConnect(int);
    static int checkNums(int, int, int);
    static Date dijkstra4Time(int, int);
    static std::vector<int> dijkstra4Tran(int a, int b, Date tmin, Date tmax, int model, int type, int k);
    static std::pair<std::vector<int>, int> dijkstra4Fare(int, int, Date, Date, int, int);
    static std::vector<int> dijkstra4Alter(int a, int b, Date n, int k);
    static std::pair<std::vector<int>, int> dijkstra4FareWithTime(int a, int b, Date time);
private:
    static int index, airportID;
    static int elems[N], next[N];
    static bool isVisited[N];
    static Airline airlines[N];
    static int head[N];
    static int w[80][80];

    static void DFS(int, std::vector<int>&);
    static std::vector<int> BFS(int);
    static int dfs4Count(int a, int b, int v, int cnt);
    static bool check(int, int, int, Date, Date, int, int);
    static bool check(int, int, int);
    static std::vector<int> getPath(std::unordered_map<int, std::pair<int, int>> &path, int cur);
};

#endif //AIRLINE_ROUTEMAP_H
