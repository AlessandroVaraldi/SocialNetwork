cmake_minimum_required(VERSION 3.10)
project(PROGETTO)

set(CMAKE_CXX_STANDARD 11)

add_executable(PROGETTO main.cpp User.cpp User.h Logger.cpp Logger.h Simple_User.cpp Simple_User.h Company_User.cpp Company_User.h Group_User.cpp Group_User.h News.cpp News.h Date.cpp Date.h Address.cpp Address.h Graph.hpp)