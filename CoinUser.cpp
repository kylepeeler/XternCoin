//
// Created by Kyle on 10/27/16.
//

#include "CoinUser.h"

CoinUser::CoinUser() {
    coins = 0;
    userID = "";
}

CoinUser::CoinUser(const std::string &newUserID): coins(0), userID(newUserID) {
    //values initialized, no further implementation needed
}

CoinUser::CoinUser(int startingCoins, const std::string &newUserID): coins(startingCoins), userID(newUserID) {
    //values initialized, no further implementation needed
}

void CoinUser::setNumberCoins(int newCoins){
    this->coins = newCoins;
}

void CoinUser::addCoin() {
    this->coins++;
}

int CoinUser::getNumberCoins() {
    return coins;
}

void CoinUser::setUserID(std::string newUserID) {
    this->userID = newUserID;
}

std::string CoinUser::getUserID() {
    return userID;
}




