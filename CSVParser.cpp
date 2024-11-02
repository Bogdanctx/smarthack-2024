//
// Created by bgd on 02.11.2024.
//

#include "CSVParser.h"
#include <fstream>
#include <iostream>
#include "csv.hpp"

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

        Connection connection{from_id, to_id, distance, lead_time_days, connection_type, max_capacity};
        connections[id] = connection;
    }
}

