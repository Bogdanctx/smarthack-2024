#ifndef STRUCTS_H
#define STRUCTS_H

#include <string>

struct Connection
{
    Connection() = default;
    Connection(const std::string &fromId, const std::string &toId, unsigned long long int distance,
               unsigned long long int leadTimeDays, const std::string &connectionType,
               unsigned long long int maxCapacity) : from_id(fromId), to_id(toId), distance(distance),
                                                     lead_time_days(leadTimeDays), connection_type(connectionType),
                                                     max_capacity(maxCapacity) {}

    std::string from_id;
    std::string to_id;
    unsigned long long distance;
    unsigned long long lead_time_days;
    std::string connection_type;
    unsigned long long max_capacity;
};

struct Customer
{
    Customer() = default;
    Customer(const std::string &name, unsigned long long max_input, double over_input_penalty,
             double late_delivery_penalty, double early_delivery_penalty) : name(name), max_input(max_input),
                                                                            over_input_penalty(over_input_penalty),
                                                                            late_delivery_penalty(late_delivery_penalty),
                                                                            early_delivery_penalty(early_delivery_penalty) {}

    std::string name;
    unsigned long long max_input;
    double over_input_penalty;
    double late_delivery_penalty;
    double early_delivery_penalty;
};

struct Refinery
{
    Refinery() = default;
    Refinery(const std::string &name, unsigned long long capacity, unsigned long long max_output, unsigned long long production,
             double overflow_penalty, double underflow_penalty, double over_output_penalty, double production_cost,
             double production_co2, unsigned long long initial_stock, const std::string &node_type) : name(name),
                                                                                                     capacity(capacity), max_output(max_output), production(production), overflow_penalty(overflow_penalty),
                                                                                                     underflow_penalty(underflow_penalty), over_output_penalty(over_output_penalty), production_cost(production_cost),
                                                                                                     production_co2(production_co2), initial_stock(initial_stock), node_type(node_type) {}

    std::string name;
    unsigned long long capacity;
    unsigned long long max_output;
    unsigned long long production;
    double overflow_penalty;
    double underflow_penalty;
    double over_output_penalty;
    double production_cost;
    double production_co2;
    unsigned long long initial_stock;
    unsigned long long cat_e_ocupat = 0;
    std::string node_type;
};

struct Tank
{
    Tank() = default;
    Tank(const std::string &name, unsigned long long capacity, unsigned long long max_input, unsigned long long max_output,
         double overflow_penalty, double underflow_penalty, double over_output_penalty, unsigned long long initial_stock,
         const std::string &node_type) : name(name), capacity(capacity), max_input(max_input), max_output(max_output),
                                         overflow_penalty(overflow_penalty), underflow_penalty(underflow_penalty), over_output_penalty(over_output_penalty),
                                         initial_stock(initial_stock), node_type(node_type) {}

    std::string name;
    unsigned long long capacity;
    unsigned long long max_input;
    unsigned long long max_output;
    double overflow_penalty;
    double underflow_penalty;
    double over_output_penalty;
    unsigned long long initial_stock;
    std::string node_type;
    mutable unsigned long long cat_e_ocupat = initial_stock;
    double stress = 0.0; // Stress variable
};

struct Demand
{
    Demand(const std::string &customerId, unsigned long long amount,
           unsigned int postDay, unsigned int startDay, unsigned int endDay) : customerId(customerId), postDay(postDay),
                                                                               amount(amount), startDay(startDay), endDay(endDay) {}

    std::string customerId;
    mutable unsigned long long amount;
    unsigned int postDay;
    unsigned int startDay;
    unsigned int endDay;
    Demand() : amount(0), startDay(0), endDay(0) {}
    Demand(const std::string &customerId, unsigned long long amount, unsigned long long startDay, unsigned long long endDay)
        : customerId(customerId), amount(amount), startDay(startDay), endDay(endDay) {}
};

struct Movement
{
    Movement(const std::string &connectionId, unsigned long long amount) : connectionId(connectionId), amount(amount) {}
    std::string connectionId;
    unsigned long long amount;
};

#endif // STRUCTS_H