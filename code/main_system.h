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
class Piece{//将line分割，依次取出
public:
    Piece(std::string line);
    std::string get();
private:
    int time=0;
    std::string line_;
    std::vector<int> blank={-1};
};
class Main_system {
public:
    ////todo::question:select改不改变书库？
    //todo:记得初始化建7账户！
    //todo:logsys要有accountsys!
    //todo:怎么构造函数在头文件里？？？
    //todo:检索和修改的输入检查！！！！{有重复附加参数为非法指令,附加参数内容为空则操作失败；}
    Main_system(){
        logSystem.Log_system_init(accountSystem,bookSystem,blogSystem);
        accountSystem.init(blogSystem);
        bookSystem.init(blogSystem,accountSystem);
        char a[5]="root",b[5]="sjtu";
        useradd(a, b, 7, a);//todo::换个位置！也许不是第一次测评！
        //todo:栈第一个放空账户！
    };

    //仅保证格式合法，不保证权限合法,todo char[]也许有非法字符！！！
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

    void modify(char *ISBN,char *name,char *author,char *keyword,char* price);

    void import(int Quantity, int TotalCost_interger,int TotalCost_float);

    //blog
    void show_finance(int count = -1);

    void log();

    void report_finance();

    void report_employee();

    Blog_system blogSystem;
    Account_system accountSystem;

private:
    Book_system bookSystem;
    Log_system logSystem;
};
//todo:权限检查！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
bool privilege_check(int lowest_privilege);

#endif //BOOKSTORE_2023_MAIN_SYSTEM_H
