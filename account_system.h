//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_ACCOUNT_SYSTEM_H
#define BOOKSTORE_2023_ACCOUNT_SYSTEM_H

#include <blog_system.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <key_value_database.h>
#include <unordered_map>
#include <map>
class Account_system;
class Blog_system;
struct Account {
    char UserID[31] = {0};
    char Password[31] = {0};
    char Username[31] = {0};
    int Privilege = 0;
};
//struct cmp{
//    bool operator ()(Account&lhs,Account&rhs)const{
//        if (strcpy(lhs.UserID,))
//    }
//};
class Account_system {
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    Account_system();
    ~Account_system(){
        file.close();
    }
    void init(Blog_system&blogSystem);
    void register_(char *UserID, char *Password, char *Username);

    void useradd(char *UserID, char *Password, int Privilege, char *Username);

    void passwd(char *UserID, char *NewPassword, char *CurrentPassword = nullptr);

    void delete_(char *UserID);

    Account log_on_now;

    Account get(char *UserID);
    std::map<std::string ,int> loger_num;
//    std::unordered_map<char*,int> loger_num;
    int last_position_of_account=0;//最后一个account的begin//todo内存转外存
    std::fstream file;

private:
    void useradd_hard(char *UserID, char *Password, int Privilege, char *Username);
    void add_log();
    void add_employ();
    Blog_system*blogSystem= nullptr;
    Key_value_database UserID_index_file;
//    void erase(int position);//删去accounts中此处
    Account get(int position);//得到accounts中此处
    void change(int position,Account& new_);//修改accounts中此处
};
bool check_num_letter_(const char *in);
#endif //BOOKSTORE_2023_ACCOUNT_SYSTEM_H
