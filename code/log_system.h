//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_LOG_SYSTEM_H
#define BOOKSTORE_2023_LOG_SYSTEM_H
#include "account_system.h"
#include "fstream"
#include <iostream>
class Log_system;
struct Log_stack;
class Log_system{
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    Log_system();
    void Log_system_init(Account_system&accountSystem);
    void logout();
    void su(char *UserID,char *Password= nullptr);
private:
    Account_system *accountSystem= nullptr;
    std::fstream log_file;
    int log_num=0;
    int last_position=0;
    void pop_back();
    void push_back(Account&in);
    Account back();
};
#endif //BOOKSTORE_2023_LOG_SYSTEM_H