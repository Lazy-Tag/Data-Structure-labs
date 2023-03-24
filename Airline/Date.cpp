//
// Created by 胡博文 on 2022/10/29.
//

#include "Date.h"

Date::Date(const std::string& info)
{
    sscanf(info.c_str(), "%d/%d/%d %d:%d", &month, &day, &year, &hour, &minute);
}

bool Date::operator<(const Date &t) const
{
    if(day != t.day) return day < t.day;
    if(hour != t.hour) return hour < t.hour;
    return minute < t.minute;
}

Date Date::operator-(const Date &t) const
{
    Date date;
    date.minute = minute - t.minute;
    if(date.minute < 0)
    {
        date.minute += 60;
        date.hour --;
    }

    date.hour += hour - t.hour;
    if(date.hour < 0)
    {
        date.hour += 24;
        date.day --;
    }

    date.day += day - t.day;
    return date;
}

bool Date::operator==(const Date &t) const {
    return minute == t.minute && hour == t.hour && day == t.day;
}

Date Date::operator+(const Date &t) const {
    Date date;
    date.minute = minute + t.minute;
    if(date.minute >= 60)
    {
        date.minute -= 60;
        date.hour ++ ;
    }
    date.hour += hour + t.hour;
    if(date.hour >= 24)
    {
        date.hour -= 24;
        date.day ++ ;
    }
    date.day += t.day + day;
    return date;
}

void Date::print()
{
    int time = day * 24 * 60 + hour * 60 + minute;
    printf("%d minutes\n", time);
}

bool Date::operator>(const Date &t) const
{
    if(day != t.day) return day > t.day;
    if(hour != t.hour) return hour > t.hour;
    return minute > t.minute;
}

bool Date::operator<=(const Date &t) const {
    if(day != t.day) return day < t.day;
    if(hour != t.hour) return hour < t.hour;
    return minute <= t.minute;
}

bool Date::operator>=(const Date &t) const
{
    if(day != t.day) return day > t.day;
    if(hour != t.hour) return hour > t.hour;
    return minute >= t.minute;
}
