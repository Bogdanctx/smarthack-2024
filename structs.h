#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Connection
{
    std::string from_id;
    std::string to_id;
    unsigned long long distance;
    unsigned long long  lead_time_days;
    std::string connection_type;
    unsigned long long max_capacity;
};

struct Customers
{
    std::string name;
    unsigned long long max_input;
    double over_input_penalty;
    double late_delivery_penalty;
    double early_delivery_penalty;
};

struct Demand {
    Demand(const std::string& customerId, unsigned long long amount,
            unsigned int postDay, unsigned int startDay, unsigned int endDay) : customerId(customerId), postDay(postDay),
                                                                                amount(amount), startDay(startDay), endDay(endDay) {}

    std::string customerId;
    unsigned long long amount;
    unsigned int postDay;
    unsigned int startDay;
    unsigned int endDay;
};

struct Movement
{
    Movement(const std::string& connectionId, unsigned long long amount) : connectionId(connectionId), amount(amount) {}
    std::string connectionId;
    unsigned long long amount;
};

#endif //STRUCTS_H
