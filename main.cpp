//
// Begin CoinUser.h
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

// End CoinUser.h

// Begin CoinUser.Cpp

//
// Created by Kyle on 10/27/16.
//

//null parameter constructor
CoinUser::CoinUser(): coins(0), userID("") {
    //values initialized, no further implementation needed
}

//constructor with initializer list
CoinUser::CoinUser(const std::string &newUserID): coins(0), userID(newUserID) {
    //values initialized, no further implementation needed
}

CoinUser::CoinUser(int startingCoins, const std::string &newUserID): coins(startingCoins), userID(newUserID) {
    //values initialized, no further implementation needed
}

//setter for number of coins
void CoinUser::setNumberCoins(int newCoins){
    this->coins = newCoins;
}

//increments the coin count
void CoinUser::addCoin() {
    this->coins++;
}

//getter for number of coins
int CoinUser::getNumberCoins() {
    return coins;
}

//setter for userID
void CoinUser::setUserID(std::string newUserID) {
    this->userID = newUserID;
}

//getter for userID
std::string CoinUser::getUserID() {
    return userID;
}

//End CoinUser.cpp

//Begin CoinServer.h
//
// Created by Kyle on 10/27/16.
//

#ifndef XTERNCOIN_COINSERVER_H
#define XTERNCOIN_COINSERVER_H

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

//End CoinServer.h

//Begin CoinServer.cpp
//
// Created by Kyle on 10/27/16.
//

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

CoinServer::CoinServer() {
    this->numberOfUsers = 0;
    this->numberToGuess = rand() % 10 + 1;
    users = new CoinUser[numberOfUsers];
    try{
        loadUsersFromFile("userLedger.dat");
    }catch(...){
        std::cout << "Failed to load the user ledger, starting a fresh one..." << std::endl;
    }
}

CoinServer::~CoinServer() {
    saveUsersToFile("userLedger.dat");
    delete[] users;
}

void CoinServer::saveUsersToFile(std::string filename){
    //delete any existing database before we make the new one
    std::remove(filename.c_str());
    //create instance of ofstream
    std::ofstream outfile;
    //open our output file
    outfile.open(filename.c_str());
    //write the user data to the file
    for (int i = 0; i < this->numberOfUsers; i++){
        outfile << users[i].getUserID() << "," << users[i].getNumberCoins() << std::endl;
    }
}

void CoinServer::loadUsersFromFile(std::string filename){
    //create instance of the input file stream
    std::ifstream inputFile;
    //open the specified file name
    inputFile.open(filename.c_str());
    if (inputFile.fail()){
        //output an error if we can't open the file
        std::cout << "Failed to load the user ledger, starting a fresh one..." << std::endl;
    }else{
        //else we got the file loaded
        //variable to hold the current line we are parsing
        std::string line;
        while(getline(inputFile, line)){
            std::istringstream iss(line);
            //create variables to hold each piece of the line
            std::string username, coinsStr;
            //parse the line and store the strings representing each piece
            //username is delimited by a comma
            getline(iss, username, ',');
            getline(iss, coinsStr);
            //add the user to the database
            addUser(username, atoi(coinsStr.c_str()));
        }//end parsing the file
        //close the input file after we write to it
        inputFile.close();
    }//end else, file opened okay
}//end loading users from the file

bool CoinServer::addUser(std::string userID, int numberOfCoins) {
    if (!hasUser(userID)){
        //create a new user array with new size
        CoinUser * tmpUsers = new CoinUser[numberOfUsers + 1];
        //deep copy of all of user data
        for (int i = 0; i < numberOfUsers; i++){
            tmpUsers[i].setUserID(this->users[i].getUserID());
            tmpUsers[i].setNumberCoins(this->users[i].getNumberCoins());
        }
        //now we add the new user data at last index
        //assign the new user ID
        tmpUsers[numberOfUsers].setUserID(userID);
        tmpUsers[numberOfUsers].setNumberCoins(numberOfCoins);
        //free the old user database
        delete[] users;
        //set the users pointer to the new array
        users = tmpUsers;
        //increase the number of users
        this->numberOfUsers++;
        return true;
    }else return false;
}

bool CoinServer::addUser(std::string userID) {
    if (!hasUser(userID)){
        //create a new user array with new size
        CoinUser * tmpUsers = new CoinUser[numberOfUsers + 1];
        //deep copy of all of user data
        for (int i = 0; i < numberOfUsers; i++){
            tmpUsers[i].setUserID(this->users[i].getUserID());
            tmpUsers[i].setNumberCoins(this->users[i].getNumberCoins());
        }
        //now we add the new user data at last index
        //assign the new user ID
        tmpUsers[numberOfUsers].setUserID(userID);
        //free the old user database
        delete[] users;
        //set the users pointer to the new array
        users = tmpUsers;
        //increase the number of users
        this->numberOfUsers++;
        return true;
    }else return false;
}

bool CoinServer::hasUser(std::string userIDToFind) {
    for (int i = 0; i < numberOfUsers; i++){
        if (users[i].getUserID() == userIDToFind){
            return true;
        }
    }
    return false;
}

bool CoinServer::handleGuess(std::string userID, int guess) {
    //if the user was correct assign the coin
    if (numberToGuess == guess){
        //get the user from the userID and award the coin
        getUser(userID)->addCoin();
        //generate a new random number
        this->numberToGuess = rand() % 10 + 1;
        return true;
    }else{
        return false;
    }
}

CoinUser *CoinServer::getUser(std::string userID) {
    for (int i = 0; i < numberOfUsers; i++){
        if (users[i].getUserID() == userID){
            return &users[i];
        }
    }
    //returns null if we did not find the user
    return NULL;
}

int CoinServer::getCoins(std::string userID) {
    if (hasUser(userID)){
        return getUser(userID)->getNumberCoins();
    }else return 0;
}

//End CoinServer.cpp

//Begin driver.cpp

#include <iostream>
#include <fstream>

CoinServer* coinServer;

void startGuessing(){
    std::string username = "XternCoinTester";
    coinServer->addUser(username);
    //we can't use an indefinite loop because the deconstructor saves, so we must be sure the program ends to persist
    //state. We instead will ask the user how many guesses the tester should attempt
    std::cout << "Please enter the number of guesses to run against the server: ";
    int numberOfGuesses;
    std::cin >> numberOfGuesses;
    for (int i = 0; i < numberOfGuesses; i++){
        int randomNumberToGuess = rand() % 10 + 1;
        std::cout << "#" << i+1 << ": Guessing " << randomNumberToGuess << "...";
        std::cout << "Coin Awarded? " << coinServer->handleGuess(username, randomNumberToGuess) << std::endl;
        std::cout << "Current number of coins: " << coinServer->getCoins(username) << std::endl;
    }
}

int main() {
    if (std::ifstream("userLedger.dat")){
        std::cout << "User ledger detected! Should we delete the user ledger and start fresh, or continue from the last run of the program?" << std::endl;
        bool validInput = false;
        std::string input;
        while (!validInput){
            std::cout << "Type 'd' to delete the ledger, or 'c' to continue using existing ledger" << std::endl;
            std::cin >> input;
            if (input == "d"){
                std::cout << "Attempting to remove userLedger.dat..." << std::endl;
                try{
                    std::remove("userLedger.dat");
                }catch(...){
                    std::cout << "Unable to remove userLedger.dat for some strange reason... :(" << std::endl;
                }
                validInput = true;
            }else if(input == "c"){
                std::cout << "Loading the user ledger into the server..." << std::endl;
                validInput = true;
            }else{
                std::cout << "Please enter only a 'd' or a 'c'!";
            }
        }
    }
    coinServer = new CoinServer();
    startGuessing();
    delete coinServer;
    return 0;
}



//End driver.cpp






