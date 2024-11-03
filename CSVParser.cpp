//
// Created by bgd on 02.11.2024.
//

#include "CSVParser.h"
#include <fstream>
#include <iostream>
#include "csv.hpp"


#include "CSVParser.h"
#include <fstream>
#include <sstream>

std::unordered_map<std::string, Demand> CSVParser::getDemands() {
    std::unordered_map<std::string, Demand> demands;
    csv::CSVReader reader("resources/data/demands.csv");

    for (csv::CSVRow& row : reader) {
        std::string customerId = row["customer_id"].get<std::string>();
        unsigned long long amount = row["quantity"].get<unsigned long long>();
        unsigned long long postDay = row["post_day"].get<unsigned long long>();
        unsigned long long startDay = row["start_delivery_day"].get<unsigned long long>();
        unsigned long long endDay = row["end_delivery_day"].get<unsigned long long>();

        Demand demand{customerId, amount, startDay, endDay};
        demands[customerId] = demand;
    }

    return demands;
}

std::unordered_map<std::string, Connection> CSVParser::getConnections() {

    std::unordered_map<std::string, Connection> connections;
    csv::CSVReader reader("resources/data/connections.csv");

    for(csv::CSVRow& row: reader)
    {
        std::string id = row["id"].get<std::string>();
        std::string from_id = row["from_id"].get<std::string>();
        std::string to_id = row["to_id"].get<std::string>();
        unsigned long long distance = row["distance"].get<unsigned long long>();
        unsigned long long lead_time_days = row["lead_time_days"].get<unsigned long long>();
        std::string connection_type = row["connection_type"].get<std::string>();
        unsigned long long max_capacity = row["max_capacity"].get<unsigned long long>();
        /*
        Connection connection{from_id, to_id, distance, lead_time_days, connection_type, max_capacity};
        connections[id] = connection;
         */
    }

    return connections;
}

std::unordered_map<std::string, Customer> CSVParser::getCustomers() {

    std::unordered_map<std::string, Customer> customers;
    csv::CSVReader reader("resources/data/customers.csv");

    for(csv::CSVRow& row: reader)
    {
        std::string id = row["id"].get<std::string>();
        std::string name = row["name"].get<std::string>();
        unsigned long long max_input = row["max_input"].get<unsigned long long>();
        double over_input_penalty = row["over_input_penalty"].get<double>();
        double late_delivery_penalty = row["late_delivery_penalty"].get<double>();
        double early_delivery_penalty = row["early_delivery_penalty"].get<double>();
        std::string node_type = row["node_type"].get<std::string>();

        Customer customer{name, max_input, over_input_penalty, late_delivery_penalty, early_delivery_penalty};
        customers[id] = customer;
    }

    return customers;
}


std::unordered_map<std::string, Refinery> CSVParser::getRefineries()
{
    std::unordered_map<std::string, Refinery> refineries;
    csv::CSVReader reader("resources/data/refineries.csv");

    for(csv::CSVRow& row: reader)
    {
        std::string id = row["id"].get<std::string>();
        std::string name = row["name"].get<std::string>();
        unsigned long long capacity = row["capacity"].get<unsigned long long>();
        unsigned long long max_output = row["max_output"].get<unsigned long long>();
        unsigned long long production = row["production"].get<unsigned long long>();
        double overflow_penalty = row["overflow_penalty"].get<double>();
        double underflow_penalty = row["underflow_penalty"].get<double>();
        double over_output_penalty = row["over_output_penalty"].get<double>();
        double production_cost = row["production_cost"].get<double>();
        double production_co2 = row["production_co2"].get<double>();
        unsigned long long initial_stock = row["initial_stock"].get<unsigned long long>();
        std::string node_type = row["node_type"].get<std::string>();

        Refinery refinery{name, capacity, max_output, production, overflow_penalty, underflow_penalty,
                        over_output_penalty, production_cost, production_co2, initial_stock, node_type};
        refineries[id] = refinery;
    }

    return refineries;
}


std::unordered_map<std::string, Tank> CSVParser::getTanks()
{
    std::unordered_map<std::string, Tank> tanks;
    csv::CSVReader reader("resources/data/tanks.csv");

    for(csv::CSVRow& row: reader)
    {
        std::string id = row["id"].get<std::string>();
        std::string name = row["name"].get<std::string>();
        unsigned long long capacity = row["capacity"].get<unsigned long long>();
        unsigned long long max_input = row["max_input"].get<unsigned long long>();
        unsigned long long max_output = row["max_output"].get<unsigned long long>();
        double overflow_penalty = row["overflow_penalty"].get<double>();
        double underflow_penalty = row["underflow_penalty"].get<double>();
        double over_input_penalty = row["over_input_penalty"].get<double>();
        double over_output_penalty = row["over_output_penalty"].get<double>();
        unsigned long long initial_stock = row["initial_stock"].get<unsigned long long>();
        std::string node_type = row["node_type"].get<std::string>();

        Tank tank{name, capacity, max_input, max_output, overflow_penalty, underflow_penalty, over_output_penalty, initial_stock, node_type};

        tanks[id] = tank;
    }

    return tanks;
}

