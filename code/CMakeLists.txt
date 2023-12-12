cmake_minimum_required(VERSION 3.27)
project(Bookstore_2023)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Bookstore_2023
        key_value_database.cpp
        key_value_database.h
        main.cpp
)
