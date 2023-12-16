//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_ACCOUNT_SYSTEM_H
#define BOOKSTORE_2023_ACCOUNT_SYSTEM_H
class Account_system;
struct account{

};
class Account_system{
public:
    //保证格式、权限合法，不保证输入（如特定user）存在
    void register_(char *UserID,char *Password,char *Username);
    void useradd(char *UserID,char *Password,char *Username);
    void passwd(char *UserID,char *NewPassword,char *CurrentPassword= nullptr);
    void delete_(char *UserID);
};
#endif //BOOKSTORE_2023_ACCOUNT_SYSTEM_H
