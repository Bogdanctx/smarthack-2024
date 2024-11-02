#ifndef API_H
#define API_H

#include <unordered_map>
#include <string>
#include <vector>

class API {
public:
    void startSession(std::unordered_map<std::string, std::vector<std::string>> data);
    void endSession();
    void playRound();
};



#endif //API_H
