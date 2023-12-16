//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_BLOG_SYSTEM_H
#define BOOKSTORE_2023_BLOG_SYSTEM_H

class Blog_system;

struct blog;

class Blog_system {
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    void show_finance(int count = -1);

    void log();

    void report_finance();

    void report_employee();
};

#endif //BOOKSTORE_2023_BLOG_SYSTEM_H
