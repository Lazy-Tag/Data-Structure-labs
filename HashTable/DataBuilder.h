//
// Created by 胡博文 on 2022/11/29.
//

#ifndef LAB5_DATABUILDER_H
#define LAB5_DATABUILDER_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <thread>
using std::fstream;
using std::string;
using std::thread;
using std::vector;

struct User {
    User() = default;
    explicit User(std::stringstream& ss) {
        int num;
        ss >> num >> id >> rank >> nums;
        str = id + ' ' + rank + ' ' + nums;
    }
    string id, rank, nums;
    string str;
};

class DataBuilder {
public:
    void exec(string);
    void setFileName(int, int, int);
    [[nodiscard]] string getFileName(int id) const { return fileName[id]; };
private:
    static User& getRandUser(std::vector<User>&);
    void build(int);
private:
    vector<User> all;
    vector<string> fileName;
    string name;
};


#endif //LAB5_DATABUILDER_H
