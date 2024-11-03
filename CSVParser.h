
#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <unordered_map>
#include <string>
#include <map>

#include "structs.h"

class CSVParser {
public:
    std::unordered_map<std::string, Connection> getConnections();
    std::unordered_map<std::string, Customer> getCustomers();
    std::unordered_map<std::string, Refinery> getRefineries();
    std::unordered_map<std::string, Tank> getTanks();
    std::unordered_map<std::string, Demand> getDemands();
};



#endif //CSVPARSER_H
