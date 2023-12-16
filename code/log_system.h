//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_LOG_SYSTEM_H
#define BOOKSTORE_2023_LOG_SYSTEM_H
class Log_system;
struct Log_stack;
class Log_system{
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    void logout();
    void su(char *UserID,char *Password= nullptr);
};
#endif //BOOKSTORE_2023_LOG_SYSTEM_H
