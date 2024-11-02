#ifndef API_H
#define API_H

#include <string>
#include <vector>
#include "structs.h"

class API {
public:
    API(const std::string& key, const std::string& link);

    void startSession();
    void endSession();

    std::vector<Demand> playRound(int day, std::vector<Movement> movements);
private:
    std::string key;
    std::string link;
    std::string session;
};


#endif //API_H
