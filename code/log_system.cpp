//
// Created by qiuyuhang on 23-12-16.
//
#include "log_system.h"
#include <cstring>
void IV() {
    std::cout << "Invalid\n";
}
void Log_system::logout(){
    if (log_num==0){
        IV();
        return;
    }
    log_num--;
    pop_back();
    last_position-= sizeof(Account);
    accountSystem->stack_kvd.delete_(accountSystem->log_on_now.UserID,0);
    accountSystem->log_on_now=back();
}
bool check(const char *in){
    int i=0;
    while (in[i]!=0){
        char o=in[i];
        bool is_num=(o>='0'&&o<='9');
        bool is_letter=((o>='a'&&o<='z')||(o>='A'&&o<='Z'));
        if (!is_num&&!is_letter&&o!='_'){
            IV();
            return true;
        }
        i++;
    }
    return false;
}
void Log_system::su(char *UserID,char *Password){
    if (check(UserID)|| check(Password)){
        IV();
        return;
    }
    log_num++;
    Account account=accountSystem->get(UserID);
    if (Password== nullptr){
        if (accountSystem->log_on_now.Privilege<=account.Privilege){
            return;
        }
    } else if (strcmp(Password,account.Password)!=0){
        IV();
        return;
    }
    accountSystem->log_on_now=account;
    push_back(account);
    accountSystem->stack_kvd.insert(account.UserID,0);
}
Log_system::Log_system() {
    log_file.open("log_stack",std::ios::in|std::ios::out|std::ios::binary);
    if (!log_file){
        log_file.open("log_stack",std::ios::out|std::ios::binary);
        log_file.close();
        log_file.open("log_stack",std::ios::in|std::ios::out|std::ios::binary);
    }
    if (!log_file){
        std::cerr<<"log file wrong";
    }
}

void Log_system::Log_system_init(Account_system &accountSystem_) {
    accountSystem=&accountSystem_;
}
void Log_system::pop_back(){
    Account account;
    log_file.seekp(last_position);
    log_file.write(reinterpret_cast<char*>(&account), sizeof(Account));
}
void Log_system::push_back(Account&in){
    log_file.seekp(last_position);
    log_file.write(reinterpret_cast<char*>(&in), sizeof(Account));
}
Account Log_system::back(){
    if (last_position==0){
        Account empty;
        return empty;
    }
    log_file.seekg(last_position);
    Account account;
    log_file.read(reinterpret_cast<char*>(&account), sizeof(Account));
    return account;
}
