//
// Created by 胡博文 on 2022/10/29.
//

#include "Airline.h"

std::random_device rd;
std::default_random_engine gen = std::default_random_engine(rd());
std::uniform_int_distribution<long long> dis(1e4, 1e18);

Airline::Airline(std::string& source)
{
    std::stringstream ss(source);
    std::string information[15];
    int cnt = 0;
    while(std::getline(ss, information[cnt], ',')) cnt ++ ;
    id = atoll(information[0].c_str());
    departureAirport = atoi(information[4].c_str());
    arriveAirport = atoi(information[5].c_str());
    departureDate = Date(information[6]);
    arriveDate = Date(information[7]);
    model = atoi(information[9].c_str());
    fare = atoi(information[10].c_str());
}

Airline::Airline(int airport1, int airport2, Date date1, Date date2)
{
    departureAirport = airport1, arriveAirport = airport2;
    departureDate = date1, arriveDate = date2;
    id = dis(gen);
}

Airline::Airline(int departure, int arrive) : departureAirport(departure), arriveAirport(arrive), id(dis(gen)), model(-2) {}
