//
// Created by bgd on 02.11.2024.
//

#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Demand {
    Demand(const std::string& customerId, unsigned long long amount,
            unsigned int postDay, unsigned int startDay, unsigned int endDay) : customerId(customerId), postDay(postDay),
                                                                                startDay(startDay), endDay(endDay) {}

    std::string customerId;
    unsigned long long amount;
    unsigned int postDay;
    unsigned int startDay;
    unsigned int endDay;
};

#endif //STRUCTS_H
