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

    Connection(const std::string &fromId, const std::string &toId, unsigned long long int distance,
               unsigned long long int leadTimeDays, const std::string &connectionType,
               unsigned long long int maxCapacity) : from_id(fromId), to_id(toId), distance(distance),
                                                     lead_time_days(leadTimeDays), connection_type(connectionType),
                                                     max_capacity(maxCapacity) {}
};

struct Customers
{
    std::string name;
    unsigned long long max_input;
    double over_input_penalty;
    double late_delivery_penalty;
    double early_delivery_penalty;

    Customers(const std::string &name, unsigned long long int maxInput, double overInputPenalty,
              double lateDeliveryPenalty, double earlyDeliveryPenalty) : name(name), max_input(maxInput),
                                                                         over_input_penalty(overInputPenalty),
                                                                         late_delivery_penalty(lateDeliveryPenalty),
                                                                         early_delivery_penalty(earlyDeliveryPenalty) {}
};
struct Refineries{
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
    std::string node_type;

    Refineries(const std::string &name, unsigned long long int capacity, unsigned long long int maxOutput,
               unsigned long long int production, double overflowPenalty, double underflowPenalty,
               double overOutputPenalty, double productionCost, double productionCo2,
               unsigned long long int initialStock, const std::string &nodeType) : name(name), capacity(capacity),
                                                                                   max_output(maxOutput),
                                                                                   production(production),
                                                                                   overflow_penalty(overflowPenalty),
                                                                                   underflow_penalty(underflowPenalty),
                                                                                   over_output_penalty(
                                                                                           overOutputPenalty),
                                                                                   production_cost(productionCost),
                                                                                   production_co2(productionCo2),
                                                                                   initial_stock(initialStock),
                                                                                   node_type(nodeType) {}
};
struct Tanks{
    std::string name;
    unsigned long long capacity;
    unsigned long long max_input;
    unsigned long long max_output;
    double overflow_penalty;
    double underflow_penalty;
    double over_input_penalty;
    double over_output_penalty;
    unsigned long long initial_stock;
    std::string node_type;

    Tanks(const std::string &name, unsigned long long int capacity, unsigned long long int maxInput,
          unsigned long long int maxOutput, double overflowPenalty, double underflowPenalty, double overInputPenalty,
          double overOutputPenalty, unsigned long long int initialStock, const std::string &nodeType) : name(name),
                                                                                                        capacity(
                                                                                                                capacity),
                                                                                                        max_input(
                                                                                                                maxInput),
                                                                                                        max_output(
                                                                                                                maxOutput),
                                                                                                        overflow_penalty(
                                                                                                                overflowPenalty),
                                                                                                        underflow_penalty(
                                                                                                                underflowPenalty),
                                                                                                        over_input_penalty(
                                                                                                                overInputPenalty),
                                                                                                        over_output_penalty(
                                                                                                                overOutputPenalty),
                                                                                                        initial_stock(
                                                                                                                initialStock),
                                                                                                        node_type(
                                                                                                                nodeType) {}
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
