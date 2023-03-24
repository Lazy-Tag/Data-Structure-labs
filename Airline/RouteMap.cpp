//
// Created by 胡博文 on 2022/10/29.
//

#include "RouteMap.h"
#include <cstring>
#include <unordered_map>

// 建图用的全局数组与映射
int RouteMap::head[N] = {0};
int RouteMap::elems[N] = {0};
int RouteMap::next[N] = {0};
int RouteMap::w[80][80] = {0};
bool RouteMap::isVisited[N] = {false};
std::map<std::tuple<int, Date, int>, int> airport2Index;
std::vector<Date> departureDate[M];
std::vector<Date> arriveDate[M];
int RouteMap::index = 1, RouteMap::airportID = 79;
Airline RouteMap::airlines[N] = {Airline()};
std::map<int, std::tuple<int, Date, int>> index2Airport;

//数据读入、建图
void RouteMap::input()
{
    std::fstream file;
    file.open("data.csv", std::ios::in);
    std::string source;
    memset(w, 0x3f, sizeof w);
    std::getline(file, source);
    while(std::getline(file, source)) //原航线建图
    {
        Airline airline(source);
        std::tuple<int, Date, int> departureAirport = {airline.departureAirport, airline.departureDate, 1};
        std::tuple<int, Date, int> arriveAirport = {airline.arriveAirport, airline.arriveDate, 0};
        if(!airport2Index.count(departureAirport))
            airport2Index[departureAirport] = ++ airportID;

        if(!airport2Index.count(arriveAirport))
            airport2Index[arriveAirport] = ++ airportID;

        w[airline.departureAirport][airline.arriveAirport] = 1;
        add(airport2Index[departureAirport], airport2Index[arriveAirport], airline);
        arriveDate[airline.arriveAirport].push_back(airline.arriveDate);
        departureDate[airline.departureAirport].push_back(airline.departureDate);
    }

    //floyd算法预处理连通性
    for(int k = 1; k <= 79; k ++ )
        for(int i = 1; i <= 79; i ++ )
            for(int j = 1; j <= 79; j ++ )
                w[i][j] = std::min(w[i][j], w[i][k] + w[k][j]);

    //将机场原编号的节点连向机场各出发时段的节点
    for(int i = 1; i <= airportNum; i ++ )
    {
        std::sort(departureDate[i].begin(), departureDate[i].end());
        departureDate[i].erase(std::unique
        (departureDate[i].begin(), departureDate[i].end()), departureDate[i].end());
        for(const auto& date : departureDate[i])
            add(i, airport2Index[{i, date, 1}], Airline(i, i));
    }

    // 将机场到达时各节点连向原编号点
    for(int i = 1; i <= airportNum; i ++ )
    {
        std::sort(arriveDate[i].begin(), arriveDate[i].end());
        arriveDate[i].erase(std::unique
        (arriveDate[i].begin(), arriveDate[i].end()), arriveDate[i].end());
        for(const auto& date : arriveDate[i])
            add(airport2Index[{i, date, 0}], i, Airline(i, i));
    }

    //将到达点连向出发点为候机时间
    for(int i = 1; i <= airportNum; i ++ )
    {
        for(const auto& departdate : departureDate[i])
            for(const auto& arrivedate : arriveDate[i])
                if(arrivedate < departdate)
                    add(airport2Index[{i, arrivedate, 0}], airport2Index[{i, departdate, 1}],
                        Airline(i, i, arrivedate, departdate));
    }
    file.close();
}

// 加边函数
void RouteMap::add(int a, int b, Airline airline)
{
    elems[index] = b, airlines[index] = airline;
    next[index] = head[a], head[a] = index ++ ;
}

//dfs遍历
void RouteMap::DFS(int airport, std::vector<int>& result)
{
    isVisited[airport] = true;
    if(airport <= airportNum) result.push_back(airport);
    for(int i = head[airport]; i; i = next[i])
    {
        int nextAirport = elems[i];
        if(isVisited[nextAirport]) continue;
        DFS(nextAirport, result);
    }
}

//bfs遍历
std::vector<int> RouteMap::BFS(int airport)
{
    int queue[N];
    int hh = 0, tt = 0;
    queue[0] = airport;
    isVisited[airport] = true;
    std::vector<int> result;
    while(hh <= tt)
    {
        int t = queue[hh ++ ];
        if(t <= airportNum) result.push_back(t);
        for(int i = head[t]; i; i = next[i])
        {
            int nextAirport = elems[i];
            if(isVisited[nextAirport]) continue;
            isVisited[nextAirport] = true;
            queue[ ++ tt] = nextAirport;
        }
    }
    return result;
}

//对外接口、返回有序向量
void RouteMap::travBFS(int id)
{
    if(id > 79) printf("机场不存在!\n");
    memset(isVisited, 0, sizeof isVisited);
    std::vector<int> result = BFS(id);
    std::sort(result.begin(), result.end());
    for(const auto& item : result)
        printf("%d ", item);
    puts("");
}

//对外接口、返回有序向量
void RouteMap::travDFS(int id)
{
    if(id > 79) printf("机场不存在!\n");
    memset(isVisited, 0, sizeof isVisited);
    std::vector<int> result;
    DFS(id, result);
    std::sort(result.begin(), result.end());
    for(const auto& item : result)
        printf("%d ", item);
    puts("");
}

//检查连通性
void RouteMap::CheckConnect(int maxTran)
{
    if(maxTran >= 0) maxTran ++ ;
    if(maxTran == -1) maxTran = 1e9;
    for(int i = 1; i <= 79; i ++ )
        for(int j = 1; j <= 79; j ++ )
        {
            if(w[i][j] <= maxTran) printf("1 ");
            else printf("0 ");
        }
}

//航线数量对外接口
int RouteMap::checkNums(int a, int b, int cnt)
{
    return dfs4Count(a, b, 0, cnt + 1);
}

//递归求航线数量
int RouteMap::dfs4Count(int a, int b, int v, int cnt)
{
    if(v > cnt) return 0;
    if(a == b) return 1;
    int res = 0;
    for(int i = head[a]; i; i = next[i])
    {
        int j = elems[i];
        Airline edge = airlines[i];
        res += dfs4Count(j, b, v + (edge.departureAirport != edge.arriveAirport), cnt);
    }
    return res;
}

//通过哈希表逆序求出最短路路径
std::vector<int> RouteMap::getPath(std::unordered_map<int, std::pair<int, int>> &path, int cur)
{
    std::vector<int> result;
    while(path[cur].first != -1)
    {
        while(path[cur].first != -1)
        {
            int lineID = path[cur].second;
            if(lineID < 1e4 && lineID >= 1) result.push_back(lineID);
            cur = path[cur].first;
            if(!cur)
            {
                result.clear();
                result.push_back(-1);
                return result;
            }
        }
        std::reverse(result.begin(), result.end());
    }
    return result;
}

//是否满足条件
bool RouteMap::check(int a, int b, int id, Date begin, Date end, int type, int model)
{
    Airline line = airlines[id];
    if(type == -1) return airlines[id].model < 0 || airlines[id].model == model;
    else
    {
        if(type == 1 && (line.departureAirport == line.arriveAirport || line.arriveAirport != b)) return true;
        if(type == 0 && (line.departureAirport == line.arriveAirport || line.departureAirport != a)) return true;
        if(!type) return airlines[id].departureDate >= begin && airlines[id].departureDate <= end;
        return airlines[id].arriveDate >= begin && airlines[id].arriveDate <= end;
    }
}

//确保非起始点的边不经过原编号点
bool RouteMap::check(int a, int b, int id)
{
    int departure = airlines[id].departureAirport, arrive = airlines[id].arriveAirport;
    return departure != arrive || departure == a || arrive == b || airlines[id].model != -2;
}

//dijkstra算法求最短飞行时间
Date RouteMap::dijkstra4Time(int a, int b)
{
    static Date time[N];
    for(int i = 1; i < N; i ++ )
        time[i] = Date("0/31/0 0:0");
    time[a] = Date("0/0/0 0:0");
    Heap<std::pair<Date, int>> heap;
    memset(isVisited, 0, sizeof isVisited);
    heap.push({Date(), a});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second;
        if(isVisited[ver]) continue;
        isVisited[ver] = true;

        for(int i = head[ver]; i; i = next[i])
        {
            int j = elems[i];
            if(!check(a, b, i)) continue;
            if(time[ver] + airlines[i].arriveDate - airlines[i].departureDate < time[j])
            {
                time[j] = time[ver] + airlines[i].arriveDate - airlines[i].departureDate;
                heap.push({time[j], j});
            }
        }
    }
    return time[b];
}

//dijkstra算法求满足条件的飞行路径
std::vector<int> RouteMap::dijkstra4Tran(int a, int b, Date tmin, Date tmax, int model, int type, int k)
{
    k ++ ;
    static int cnt[N];
    memset(cnt, 0x3f, sizeof cnt);
    memset(isVisited, 0, sizeof isVisited);
    static std::unordered_map<int, std::pair<int, int>> path;

    Heap<std::pair<int, std::pair<int, std::pair<int, int>>>> heap;
    heap.push({0, {a, {-1, -1}}});
    cnt[a] = 0;
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second.first;
        if(isVisited[ver]) continue;
        isVisited[ver] = true;
        path[ver] = t.second.second;
        if(ver == b) break;

        for(int i = head[ver]; i; i = next[i])
        {
            int j = elems[i];
            if(!check(a, b, i, tmin, tmax, type, model) || !check(a, b, i)) continue;
            if(cnt[ver] + (airlines[i].departureAirport == airlines[i].arriveAirport) < cnt[j])
            {
                cnt[j] = cnt[ver] + (airlines[i].departureAirport == airlines[i].arriveAirport);
                heap.push({cnt[j], {j, {ver, airlines[i].id}}});
            }
        }
    }
    std::vector<int> result;
    if(cnt[b] > k)
    {
        result.push_back(-1);
        return result;
    }
    result = getPath(path, b);
    return result;
}

//dijkstra算法求满足条件的最少航费
std::pair<std::vector<int>, int> RouteMap::dijkstra4Fare(int a, int b, Date tmin, Date tmax, int model, int type)
{
    static int fare[N];
    memset(fare, 0x3f, sizeof fare);
    memset(isVisited, 0, sizeof isVisited);
    static std::unordered_map<int, std::pair<int, int>> path;

    std::pair<std::vector<int>, int> result;
    Heap<std::pair<int, std::pair<int, std::pair<int, int>>>> heap;
    heap.push({0, {a, {-1, -1}}});
    fare[a] = 0;
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second.first;
        if(isVisited[ver]) continue;
        isVisited[ver] = true;
        path[ver] = t.second.second;
        if(ver == b)
        {
            result.second = t.first;
            break;
        }
        for(int i = head[ver]; i; i = next[i])
        {
            int j = elems[i];
            if(!check(a, b, i, tmin, tmax, type, model) || !check(a, b, i)) continue;
            if(fare[ver] + airlines[i].fare < fare[j])
            {
                fare[j] = fare[ver] + airlines[i].fare;
                heap.push({fare[j], {j, {ver, airlines[i].id}}});
            }
        }
    }
    int cur = b;
    result.first = getPath(path, b);
    return result;
}

//dijkstra算法求在一定中转时间内的最少航费
std::pair<std::vector<int>, int> RouteMap::dijkstra4FareWithTime(int a, int b, Date time)
{
    static int fare[N];
    memset(fare, 0x3f, sizeof fare);
    memset(isVisited, 0, sizeof isVisited);
    static std::unordered_map<int, std::pair<int, int>> path;

    std::pair<std::vector<int>, int> result;
    Heap<std::pair<std::pair<int, Date>, std::pair<int, std::pair<int, int>>>> heap;
    heap.push({{0, Date()}, {a, {-1, -1}}});
    fare[a] = 0;
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second.first;
        if(isVisited[ver]) continue;
        isVisited[ver] = true;
        path[ver] = t.second.second;
        if(ver == b)
        {
            result.second = t.first.first;
            break;
        }
        for(int i = head[ver]; i; i = next[i])
        {
            int j = elems[i];
            if(!check(a, b, i)) continue;
            bool isTran = airlines[i].departureAirport != airlines[i].arriveAirport;
            Date date = t.first.second;
            if(airlines[i].departureAirport == airlines[i].arriveAirport)
                date = date + airlines[i].arriveDate - airlines[i].departureDate;
            if(date > time) continue;
            if(fare[ver] + (airlines[i].departureAirport == airlines[i].arriveAirport) < fare[j])
            {
                fare[j] = fare[ver] + airlines[i].fare;
                heap.push({{fare[j], date}, {j, {ver, airlines[i].id}}});
            }
        }
    }
    int cur = b;
    result.first = getPath(path, b);
    return result;
}

//dijkstra算法求一定中转次数和时间内的备用路径
std::vector<int> RouteMap::dijkstra4Alter(int a, int b, Date n, int k)
{
    k ++ ;
    static Date time[N];
    for(int i = 1; i < N; i ++ )
        time[i] = Date("0/31/0 0:0");
    time[a] = Date("0/0/0 0:0");

    std::unordered_map<int, std::pair<int, int>> path;
    Heap<std::pair<std::pair<Date, int>, std::pair<int, std::pair<int, int>>>> heap;
    memset(isVisited, 0, sizeof isVisited);
    heap.push({{Date(), 0}, {a, {-1, -1}}});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        int ver = t.second.first;
        if(isVisited[ver]) continue;
        isVisited[ver] = true;
        path[ver] = t.second.second;
        if(ver == b) break;

        for(int i = head[ver]; i; i = next[i])
        {
            int j = elems[i];
            auto p = airlines[i];
            if(!check(a, b, i)) continue;
            bool isTran = airlines[i].departureAirport != airlines[i].arriveAirport;
            if(t.first.second + isTran > k) continue;
            if(time[ver] + airlines[i].arriveDate - airlines[i].departureDate < time[j])
            {
                time[j] = time[ver];
                if(!isTran) time[j] = time[j] + airlines[i].arriveDate - airlines[i].departureDate;
                heap.push({{time[j], t.first.second + isTran}, {j, {ver, airlines[i].id}}});
            }
        }
    }
    std::vector<int> result;
    if(time[b] > n)
    {
        result.push_back(-1);
        return result;
    }

    int cur = b;
    result = getPath(path, b);
    return result;
}
