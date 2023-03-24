//
// Created by 胡博文 on 2022/12/1.
//

#ifndef LAB5_TEST_H
#define LAB5_TEST_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>
#include "HashTable/HashTable.h"

using std::string;
using std::pair;
using std::vector;
using std::fstream;
using std::thread;

class Test {
public:
    explicit Test(string);
//    void test(double[]);
    void exec(double[], int, HashTable*);
private:
    string fileName;
    vector<string> options;
};

//void Test::test(double result[]) {
//
//    HashTable* hashTable[6] = {
//            new HashTable(new CollectionInClose(), new Hash4Ascii()),
//            new HashTable(new CollectionInClose(), new Hash4UTF_8()),
//            new HashTable(new CollectionInOpenWithStep(), new Hash4Ascii()),
//            new HashTable(new CollectionInOpenWithStep(), new Hash4UTF_8()),
//            new HashTable(new CollectionInOpenWithDoubleSquare(), new Hash4Ascii()),
//            new HashTable(new CollectionInOpenWithDoubleSquare(), new Hash4UTF_8()),
//    };
//    for (int i = 0; i < 6; i ++ )
//        exec(result, i, hashTable[i]);
//    thread* myThreads[6] = {
//        new thread(&Test::setFileName, this, result, 0, new HashTable(new CollectionInClose(), new Hash4Ascii())),
//        new thread(&Test::setFileName, this, result, 1, new HashTable(new CollectionInClose(), new Hash4UTF_8())),
//        new thread(&Test::setFileName, this, result, 2, new HashTable(new CollectionInOpenWithStep(), new Hash4Ascii())),
//        new thread(&Test::setFileName, this, result, 3, new HashTable(new CollectionInOpenWithStep(), new Hash4UTF_8())),
//        new thread(&Test::setFileName, this, result, 4, new HashTable(new CollectionInOpenWithDoubleSquare(), new Hash4Ascii())),
//        new thread(&Test::setFileName, this, result, 5, new HashTable(new CollectionInOpenWithDoubleSquare(), new Hash4UTF_8()))
//    };
//    for (auto &thread : myThreads) thread->join();
//}

void Test::exec(double result[], int id, HashTable* hashTable) {
    int op;
    string name;
    std::stringstream sstream("");
    auto begin = std::chrono::system_clock::now();
    for (auto &option : options) {
        sstream.clear();
        sstream << option;
        sstream >> op;
        if (op == 0) {
            pair<int, int> data;
            sstream >> name >> data.first >> data.second;
            hashTable->insert({name, data});
        } else if (op == 1) {
            sstream >> name;
            hashTable->get(name);
        } else break;
    }
    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    result[id] += double(duration.count()) * std::chrono::microseconds::period::num
            / std::chrono::microseconds::period::den;
    delete hashTable;
//    printf("ID: %s %d complete!\n", fileName.c_str(), id);
}

Test::Test(string _fileName) : fileName(std::move(_fileName)) {
    fstream in("..//data//" + fileName + "_in.txt", std::ios::in);
    string information;
    while(std::getline(in, information))
        options.push_back(information);
}


#endif //LAB5_TEST_H
