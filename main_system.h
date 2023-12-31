//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_MAIN_SYSTEM_H
#define BOOKSTORE_2023_MAIN_SYSTEM_H

#include "book_system.h"
#include "account_system.h"
#include "blog_system.h"
#include "log_system.h"
#include <iostream>
#include <string>
#include <vector>

class Piece {//将line分割，依次取出
public:
    Piece(std::string line);

    std::string get();

private:
    int time = 0;
    std::string line_;
    std::vector<int> blank = {-1};
};

class Main_system {
public:


    Main_system() {
        logSystem.Log_system_init(accountSystem, bookSystem, blogSystem);
        accountSystem.init(blogSystem);
        bookSystem.init(blogSystem, accountSystem);
        std::fstream file;
        file.open("2int", std::ios::in | std::ios::out | std::ios::binary);
        if (!file) {
            file.open("2int", std::ios::out | std::ios::binary);
            file.close();
            file.open("2int", std::ios::in | std::ios::out | std::ios::binary);
        } else {
            file.read(reinterpret_cast<char *>(&bookSystem.end_of_book), sizeof(int));
            file.read(reinterpret_cast<char *>(&accountSystem.last_position_of_account), sizeof(int));
        }
        file.close();
    };

    ~Main_system() {
        std::fstream file;
        file.open("2int", std::ios::in | std::ios::out | std::ios::binary);
        file.write(reinterpret_cast<char *>(&bookSystem.end_of_book), sizeof(int));
        file.write(reinterpret_cast<char *>(&accountSystem.last_position_of_account), sizeof(int));
        file.close();
    }

    //仅保证格式合法，不保证权限合法,char[]也许有非法字符
    //log
    void logout();

    void su(char *UserID, char *Password = nullptr);

    //account
    void register_(char *UserID, char *Password, char *Username);

    void useradd(char *UserID, char *Password, int Privilege, char *Username);

    void passwd(char *UserID, char *NewPassword, char *CurrentPassword = nullptr);

    void delete_(char *UserID);

    //book
    void show(char *index, index_type);

    void buy(char *ISBN, int Quantity);

    void select(char *ISBN);

    void modify(char *ISBN, char *name, char *author, char *keyword, char *price);

    void import(int Quantity, int TotalCost_interger, int TotalCost_float);

    //blog
    void show_finance(int count = -1);

    void log();

    void report_finance();

    void report_employee();

    Blog_system blogSystem;
    Account_system accountSystem;
    Book_system bookSystem;
    Log_system logSystem;

private:
};

#endif //BOOKSTORE_2023_MAIN_SYSTEM_H
