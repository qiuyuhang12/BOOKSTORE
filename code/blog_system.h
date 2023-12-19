//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_BLOG_SYSTEM_H
#define BOOKSTORE_2023_BLOG_SYSTEM_H

#include <key_value_database.h>
#include "book_system.h"

class Blog_system;


//财务
struct Count{
    Price money_in;
    Price money_out;
};
struct Finance_table{
    Price money_in;
    Price money_out;
    char UserID[31]={0};
    char do_[6]={0};//buy or import
    char ISBN[20]={0};
    int Quality=0;
};
struct Employee_table{
    char UserID[31]={0};
    char do_[300]={0};
};
struct Do_table{
    Price in;
    Price out;
    char UserID[31]={0};
    char do_[300]={0};
};

class Blog_system {
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    Blog_system();//todo初始化文件流
    void show_finance(int count = -1);

    void log();

    void report_finance();

    void report_employee();

    void add_count(Count &count);
    void add_finance(Finance_table&financeTable);
    void add_employee(Employee_table&employeeTable);
    void add_log(Do_table&doTable);
    std::string *do_str= nullptr;
private:
    std::fstream count_file;
    std::fstream report_finance_file;
    std::fstream report_employee_file;
    std::fstream log_file;
};

#endif //BOOKSTORE_2023_BLOG_SYSTEM_H
