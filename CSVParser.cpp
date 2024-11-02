//
// Created by bgd on 02.11.2024.
//

#include "CSVParser.h"
#include <fstream>
#include <iostream>

std::unordered_map<std::string, Connection> CSVParser::getConnections() {
    std::unordered_map<std::string, Connection> data;
    std::ifstream fin("resources/data/connections.csv");
    if (!fin) {
        std::cerr << "Could not open the file!" << std::endl;
        return data;
    }

    std::string titluri;
    std::string line;
    //fin >> keys;
    std::getline(fin,titluri);
    std::string key;
    while(std::getline(fin,line))
    {
        key="";
        std::vector<std::string> kkturi;
        std::string item;
        bool foundkey= false;
        for(auto letter: line)
        {
            if(letter!=';')
            {
                item+=letter;
            }
            else
            {
                if(!foundkey)
                {
                    foundkey=true;
                    key=item;
                    item="";
                }
                else
                {
                    kkturi.push_back(item);
                    item = "";
                }
            }
        }
        //data[key] = Connection(kkturi[0],kkturi[1],std::stoull(kkturi[2]), std::stoull(kkturi[3]),kkturi[4],std::stoull(kkturi[5]));
        kkturi.clear();
    }
    /*
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
    */
    /*
    std::vector<Connection> values;
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

    std::string line;
    while(std::getline(fin,line))
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

std::unordered_map<std::string, Customers> CSVParser::getCustomers() {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::ifstream fin("resources/data/customers.csv");
    if (!fin) {
        std::cerr << "Could not open the file!" << std::endl;
        return data;
    }

    std::string keys;
    fin >> keys;
    std::getline(fin,keys);
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
    while(std::getline(fin,line))
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
            item.clear();
        }
        data["id"].push_back(valuesformap[0]);
        data["name"].push_back(valuesformap[1]);
        data["max_input"].push_back(valuesformap[2]);
        data["over_input_penalty"].push_back(valuesformap[3]);
        data["late_delivery_penalty"].push_back(valuesformap[4]);
        data["early_delivery_penalty"].push_back(valuesformap[5]);
        data["node_type"].push_back(valuesformap[6]);
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


std::unordered_map<std::string, std::vector<std::string>> CSVParser::getDemands() {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::ifstream fin("resources/data/demands.csv");
    if (!fin) {
        std::cerr << "Could not open the file!" << std::endl;
        return data;
    }

    std::string keys;
    fin >> keys;
    std::getline(fin,keys);
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
    while(std::getline(fin,line))
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
            item.clear();
        }
        data["id"].push_back(valuesformap[0]);
        data["customer_id"].push_back(valuesformap[1]);
        data["quantity"].push_back(valuesformap[2]);
        data["post_day"].push_back(valuesformap[3]);
        data["start_delivery_day"].push_back(valuesformap[4]);
        data["end_delivery_day"].push_back(valuesformap[5]);
        //data["node_type"].push_back(valuesformap[6]);
        valuesformap.clear();
    }

    for (const auto& pair : data) {
        std::cout << pair.first<<": "<<std::endl;
        for (const auto& value : pair.second) {
            std::cout << value << " "<<std::endl;
        }
        std::cout << std::endl;
    }

    return data;
}

std::unordered_map<std::string, std::vector<std::string>> CSVParser::getRefineries() {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::ifstream fin("resources/data/refineries.csv");
    if (!fin) {
        std::cerr << "Could not open the file!" << std::endl;
        return data;
    }

    std::string keys;
    fin >> keys;
    std::getline(fin,keys);
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
    while(std::getline(fin,line))
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
            item.clear();
        }
        data["id"].push_back(valuesformap[0]);
        data["name"].push_back(valuesformap[1]);
        data["capacity"].push_back(valuesformap[2]);
        data["max_output"].push_back(valuesformap[3]);
        data["production"].push_back(valuesformap[4]);
        data["overflow_penalty"].push_back(valuesformap[5]);
        data["underflow_penalty"].push_back(valuesformap[6]);
        data["over_output_penalty"].push_back(valuesformap[7]);
        data["production_cost"].push_back(valuesformap[8]);
        data["production_co2"].push_back(valuesformap[9]);
        data["initial_stock"].push_back(valuesformap[10]);
        data["node_type"].push_back(valuesformap[11]);
        valuesformap.clear();
    }

    for (const auto& pair : data) {
        std::cout << pair.first<<": "<<std::endl;
        for (const auto& value : pair.second) {
            std::cout << value << " "<<std::endl;
        }
        std::cout << std::endl;
    }
    return data;

}

std::unordered_map<std::string, std::vector<std::string>> CSVParser::getTanks() {
    std::unordered_map<std::string, std::vector<std::string>> data;
    std::ifstream fin("resources/data/tanks.csv");
    if (!fin) {
        std::cerr << "Could not open the file!" << std::endl;
        return data;
    }

    std::string keys;
    fin >> keys;
    std::getline(fin,keys);
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
    while(std::getline(fin,line))
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
            item.clear();
        }
        data["id"].push_back(valuesformap[0]);
        data["name"].push_back(valuesformap[1]);
        data["capacity"].push_back(valuesformap[2]);
        data["max_input"].push_back(valuesformap[3]);
        data["max_output"].push_back(valuesformap[4]);
        data["overflow_penalty"].push_back(valuesformap[5]);
        data["underflow_penalty"].push_back(valuesformap[6]);
        data["over_input_penalty"].push_back(valuesformap[7]);
        data["over_output_penalty"].push_back(valuesformap[8]);
        data["initial_stock"].push_back(valuesformap[9]);
        data["node_type"].push_back(valuesformap[10]);
        //data["node_type"].push_back(valuesformap[11]);
        valuesformap.clear();
    }
    /*
    for (const auto& pair : data) {
        std::cout << pair.first << ": " << std::endl;
        for (const auto &value: pair.second) {
            std::cout << value << " " << std::endl;
        }
        std::cout << std::endl;
    }
     */
    return data;

}

