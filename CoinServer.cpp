//
// Created by Kyle on 10/27/16.
//

#include "CoinServer.h"
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




