cmake_minimum_required(VERSION 3.27)
project(Bookstore_2023)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(code
        key_value_database.cpp
        key_value_database.h
        main.cpp
        main_system.h
        log_system.h
        account_system.h
        book_system.h
        blog_system.h
        main_system.cpp
        log_system.cpp
        book_system.cpp
        blog_system.cpp
        account_system.cpp
)
