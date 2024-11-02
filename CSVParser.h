
#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <unordered_map>
#include <string>
#include <vector>

class CSVParser {
public:
    CSVParser();
    ~CSVParser();
    std::unordered_map<std::string, std::vector<std::string>> getConnections();
};



#endif //CSVPARSER_H
