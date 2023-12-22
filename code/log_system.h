//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_LOG_SYSTEM_H
#define BOOKSTORE_2023_LOG_SYSTEM_H
#include "account_system.h"
#include "book_system.h"
#include "fstream"
#include <iostream>
#include <blog_system.h>
#include <map>
#include <unordered_map>
class Log_system;
//struct Log_stack;
class Log_system{
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    Log_system();
    void Log_system_init(Account_system&accountSystem,Book_system&bookSystem,Blog_system&blogSystem);
    void logout();
    void su(char *UserID,char *Password= nullptr);
private:
    void add_log();
    Blog_system *blogSystem= nullptr;
    Account_system *accountSystem= nullptr;
    Book_system *bookSystem= nullptr;
    std::vector<Account> loger_stack;
    std::vector<Book> book_selected_stack;
    std::vector<bool> already_select_stack;
    std::vector<int> select_position_stack;
//    std::fstream log_file;
    int log_num=1;
    long long last_position=0;
    void pop_back();
    void push_back(Account&in);
    Account back();
    void clear_selected();
};
bool check(const char *in);
#endif //BOOKSTORE_2023_LOG_SYSTEM_H
