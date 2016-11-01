//
// Created by Kyle on 10/27/16.
//

#ifndef XTERNCOIN_COINSERVER_H
#define XTERNCOIN_COINSERVER_H

#include "CoinUser.h"
#include <string>

class CoinServer {

private:
    int numberToGuess;
    int numberOfUsers;
    CoinUser* users;
public:
    CoinServer();
    ~CoinServer();
    CoinUser* getUser(std::string userID);
    bool addUser(std::string userID);
    bool addUser(std::string userID, int numberOfCoins);
    bool hasUser(std::string userIDToFind);
    bool handleGuess(std::string userID, int guess);
    int getCoins(std::string userID);
    void loadUsersFromFile(std::string filename);
    void saveUsersToFile(std::string filename);
};


#endif //XTERNCOIN_COINSERVER_H
