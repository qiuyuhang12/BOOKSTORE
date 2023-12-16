//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_MAIN_SYSTEM_H
#define BOOKSTORE_2023_MAIN_SYSTEM_H

#include "book_system.h"
#include "account_system.h"
#include "blog_system.h"
#include "log_system.h"

class Main_system {
public:
    Main_system();

    Main_system(Account_system &accountSystem_, Blog_system &blogSystem_, Book_system &bookSystem_,
                Log_system &logSystem_) : accountSystem(accountSystem_), blogSystem(blogSystem_),
                                          bookSystem(bookSystem_), logSystem(logSystem_) {}

    //仅保证格式合法，不保证权限合法
    //log
    void logout();

    void su(char *UserID, char *Password = nullptr);

    //account
    void register_(char *UserID, char *Password, char *Username);

    void useradd(char *UserID, char *Password, char *Username);

    void passwd(char *UserID, char *NewPassword, char *CurrentPassword = nullptr);

    void delete_(char *UserID);

    //book
    void show(char *index, index_type);

    void buy(char *ISBN, int Quantity);

    void select(char *ISBN);

    void modify(char *index, index_type);

    void import(int Quantity, int TotalCost);

    //blog
    void show_finance(int count = -1);

    void log();

    void report_finance();

    void report_employee();

private:
    Account_system &accountSystem;
    Book_system &bookSystem;
    Blog_system &blogSystem;
    Log_system &logSystem;
};

bool privilege_check(int lowest_privilege);

#endif //BOOKSTORE_2023_MAIN_SYSTEM_H
