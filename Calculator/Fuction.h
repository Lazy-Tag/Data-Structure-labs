//
// Created by 胡博文 on 2022/10/24.
//

#ifndef CALCULATOR_FUCTION_H
#define CALCULATOR_FUCTION_H

#include "Quantic.h"
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <unordered_set>

struct Fuc{
    std::string name;
    Quantic inQuantic, outQuantitic;
    Fuc(std::string& _name, const Quantic& q1, const Quantic& q2) : name(_name), inQuantic(q1), outQuantitic(q2) {}
    bool operator < (const Fuc &t) const { return name < t.name; }
};

class Fuction{
public:
    explicit Fuction(std::string&);
    static Fuction defineFuction();
    Fuction() = default;
    friend class Calculator;
private:
    std::set<Fuc> fuctionName;
    std::string name;
    Quantic quantic;
    static std::string getVariable(std::string &expr, int &index);
    static bool checkFuctionName(std::string&, std::string&, int&);
};


#endif //CALCULATOR_FUCTION_H
