//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_ACCOUNT_SYSTEM_H
#define BOOKSTORE_2023_ACCOUNT_SYSTEM_H

#include <iostream>
#include <cstring>
#include <fstream>
#include <key_value_database.h>
class Account_system;

struct Account {
    char UserID[31] = {0};
    char Password[31] = {0};
    char Username[31] = {0};
    int Privilege = 0;
};

class Account_system {
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    Account_system();
    void register_(char *UserID, char *Password, char *Username);

    void useradd(char *UserID, char *Password, int Privilege, char *Username);

    void passwd(char *UserID, char *NewPassword, char *CurrentPassword = nullptr);

    void delete_(char *UserID);

    Account log_on_now;

    Account get(char *UserID);
    Key_value_database stack_kvd;
private:
    std::fstream file;
    Key_value_database UserID_index_file;
    int last_position_of_account=0;//最后一个account的begin
//    void erase(int position);//删去accounts中此处
    Account get(int position);//得到accounts中此处
    void change(int position,Account& new_);//修改accounts中此处
};

#endif //BOOKSTORE_2023_ACCOUNT_SYSTEM_H
