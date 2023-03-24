//
// Created by 胡博文 on 2022/10/29.
//

#ifndef AIRLINE_DATE_H
#define AIRLINE_DATE_H

#include <string>

struct Date {
    explicit Date(const std::string&);
    Date(int _year, int _month, int _day, int _hour, int _minute) :
    year(_year), month(_month), day(_day), hour(_hour), minute(_minute) {}
    Date() = default;
    bool operator== (const Date&) const;
    bool operator< (const Date&) const;
    bool operator> (const Date&) const;
    bool operator<= (const Date&) const;
    bool operator>= (const Date&) const;
    Date operator- (const Date&) const;
    Date operator+ (const Date&) const;
    void print();
    int year = 0, month = 0, day = 0;
    int hour = 0, minute = 0;
};


#endif //AIRLINE_DATE_H
