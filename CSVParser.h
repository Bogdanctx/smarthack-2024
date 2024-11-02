
#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <unordered_map>
#include <string>
#include <vector>

class CSVParser {
public:
    std::unordered_map<std::string, std::vector<std::string>> getConnections();
    std::unordered_map<std::string, std::vector<std::string>> getCustomers();
    std::unordered_map<std::string, std::vector<std::string>> getDemands();
    std::unordered_map<std::string, std::vector<std::string>> getRefineries();
    std::unordered_map<std::string, std::vector<std::string>> getTanks();
};



#endif //CSVPARSER_H
