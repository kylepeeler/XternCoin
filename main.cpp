#include <iostream>
#include <fstream>
#include "CoinServer.h"

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

