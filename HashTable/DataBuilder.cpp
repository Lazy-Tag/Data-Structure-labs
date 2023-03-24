//
// Created by 胡博文 on 2022/11/29.
//

#include "DataBuilder.h"

#include <utility>

void DataBuilder::exec(string _name) {
    all.clear();
    name = std::move(_name);
    std::fstream in("..//data//" + name + ".txt", std::ios::in);
    string information;
    while (std::getline(in, information)) { // 将数据存在内存中
        std::stringstream ss(information);
        User user(ss);
        all.push_back(user);
    }
    in.close();
    thread myThreads[3] = {
            thread(&DataBuilder::build, this, 0),
            thread(&DataBuilder::build, this, 50),
            thread(&DataBuilder::build, this, 100)
    };// n%从以插入的入的数据中查询，其余从全部数据中查询
    for (auto & myThread : myThreads)
        myThread.join();
    setFileName(0, 50, 100);
}

void DataBuilder::build(int percent) {
    std::vector<User> inserted;
    std::random_device rd;
    auto gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(1, 100);
    string targetFile = name + "_" + std::to_string(percent);
    fstream out;
    out.open("..//data//" + targetFile + "_in" + ".txt", std::ios::out);
    for (int i = 0; i < all.size(); i += 50) {
        for (int j = i; j < i + 50; j ++ ) { // 插入数据
            User user = all[j];
            inserted.push_back(user);
            string option = "0 " + user.str;
            out << option << std::endl;
        }

        for (int j = i; j < i + 50; j ++ ) { // 查询数据
            int rand = dis(gen); // 概率随机
            User query;
            if (rand > percent) {
                query = getRandUser(all);
            } else {
                query = getRandUser(inserted);
            }
            string option = "1 " + query.id;
            out << option << std::endl;
        }
    }
    out << 2 << std::endl;
    out.close();
    printf("file %s has been written!\n", targetFile.c_str());
}

User &DataBuilder::getRandUser(std::vector<User>& collection) {
    std::random_device rd;
    auto gen = std::default_random_engine(rd());
    std::uniform_int_distribution<int> dis(0, (int) collection.size() - 1);
    return collection[dis(gen)];
}

void DataBuilder::setFileName(int low, int mid, int high) {
    fileName.emplace_back("poj_" + std::to_string(low));
    fileName.emplace_back("poj_" + std::to_string(mid));
    fileName.emplace_back("poj_" + std::to_string(high));
    fileName.emplace_back("hdu_" + std::to_string(low));
    fileName.emplace_back("hdu_" + std::to_string(mid));
    fileName.emplace_back("hdu_" + std::to_string(high));
}
