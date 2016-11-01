cmake_minimum_required(VERSION 3.6)
project(XternCoin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CoinServer.cpp CoinServer.h CoinUser.cpp CoinUser.h)
add_executable(XternCoin ${SOURCE_FILES})