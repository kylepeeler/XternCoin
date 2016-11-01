//
// Created by Kyle on 10/27/16.
//

#ifndef XTERNCOIN_COINUSER_H
#define XTERNCOIN_COINUSER_H


#include <string>

class CoinUser {
private:
    int coins;
    std::string userID;
public:
    CoinUser();
    CoinUser(const std::string &newUserID);
    CoinUser(int startingCoins, const std::string &newUserID);
    void addCoin();
    int getNumberCoins();
    void setNumberCoins(int newCoins);
    void setUserID(std::string newUserID);
    std::string getUserID();
};


#endif //XTERNCOIN_COINUSER_H
