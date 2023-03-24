//
// Created by 胡博文 on 2022/10/29.
//

#ifndef AIRLINE_AIRLINE_H
#define AIRLINE_AIRLINE_H

#include "Date.h"
#include <string>
#include <sstream>
#include <random>

struct Airline {
    Airline() = default;
    Airline(int, int, Date, Date);
    explicit Airline(std::string&);
    Airline(int departure, int arrive);

    long long id = -1;
    Date departureDate, arriveDate;
    int departureAirport = -1, arriveAirport = -1;
    int fare = 0, model = -1;
};


#endif //AIRLINE_AIRLINE_H
