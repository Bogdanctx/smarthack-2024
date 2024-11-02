//
// Created by bgd on 02.11.2024.
//

#include "CSVParser.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

CSVParser::CSVParser() = default;

CSVParser::~CSVParser() = default;

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

std::unordered_map<std::string, std::vector<std::string>> CSVParser::getConnections() {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::ifstream fin("resources/data/connections.csv");
    if (!fin) {
        std::cerr << "Could not open the file!" << std::endl;
        return data;
    }

    std::string keys;
    fin >> keys;

    std::vector<std::string> keylist;
    std::string item;
    for (char letter : keys) {
        if (letter != ';') {
            item += letter;
        } else {
            keylist.push_back(item);
            item = "";
        }
    }
    if (!item.empty()) {
        keylist.push_back(item);
        item = "";
    }

    std::vector<std::string> values;
    for (const auto& key : keylist) {
        data[key] = values;
    }
    /*
    for (const auto& pair : data) {
        std::cout << pair.first;
        for (const auto& value : pair.second) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    */
    std::string line;
    while(fin>>line)
    {
        std::vector<std::string> valuesformap;
        for (char letter : line) {
            if (letter != ';') {
                item += letter;
            } else {
                valuesformap.push_back(item);
                item = "";
            }
        }
        if (!item.empty()) {
            valuesformap.push_back(item);
        }
        data["id"].push_back(valuesformap[0]);
        data["from_id"].push_back(valuesformap[1]);
        data["to_id"].push_back(valuesformap[2]);
        data["distance"].push_back(valuesformap[3]);
        data["lead_time_days"].push_back(valuesformap[4]);
        data["connection_type"].push_back(valuesformap[5]);
        data["max_capacity"].push_back(valuesformap[6]);
        valuesformap.clear();
    }
    /*
    for (const auto& pair : data) {
        std::cout << pair.first<<": "<<std::endl;
        for (const auto& value : pair.second) {
            std::cout << value << " "<<std::endl;
        }
        std::cout << std::endl;
    }
     */
    return data;
}

