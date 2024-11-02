
#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <unordered_map>
#include <string>
#include <vector>
#include "structs.h"

class CSVParser {
public:
    std::unordered_map<std::string, Connection> getConnections();
    std::unordered_map<std::string, Customers> getCustomers();
    std::unordered_map<std::string, std::vector<std::string>> getDemands();
    std::unordered_map<std::string, Refineries> getRefineries();
    std::unordered_map<std::string, Tanks> getTanks();
};



#endif //CSVPARSER_H
