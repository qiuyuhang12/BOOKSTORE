//
// Created by qiuyuhang on 23-12-16.
//
#include "log_system.h"
#include <cstring>

void Log_system::add_log() {
    Do_table doTable;
    strcpy(doTable.UserID, accountSystem->log_on_now.UserID);
    strcpy(doTable.do_, blogSystem->do_str->c_str());
    blogSystem->add_log(doTable);
}
//void IV() {
//    std::cout << "Invalid\n";
//}

void Log_system::clear_selected() {
//    Book book;
//    bookSystem->selected=book;
    bookSystem->already_select = false;
}

void Log_system::logout() {
    if (log_num == 1) {
        IV();
        return;
    }
    if (accountSystem->log_on_now.Privilege < 1) {
        IV();
        return;
    }
    log_num--;
    pop_back();
    last_position -= sizeof(Account);
//    accountSystem->stack_kvd.delete_(accountSystem->log_on_now.UserID, 0);
    accountSystem->loger_num[accountSystem->log_on_now.UserID]--;
    if (accountSystem->loger_num[accountSystem->log_on_now.UserID] == 0) {
        accountSystem->loger_num.erase(accountSystem->log_on_now.UserID);
    }
    accountSystem->log_on_now = back();
    clear_selected();
    add_log();
}

bool check(const char *in) {
    int i = 0;
    while (in[i] != 0) {
        char o = in[i];
        bool is_num = (o >= '0' && o <= '9');
        bool is_letter = ((o >= 'a' && o <= 'z') || (o >= 'A' && o <= 'Z'));
        if (!is_num && !is_letter && o != '_') {
            IV();
            return true;
        }
        i++;
    }
    return false;
}

void Log_system::su(char *UserID, char *Password) {
    if (check(UserID) || check(Password)) {
        IV();
        return;
    }
    log_num++;
    Account account = accountSystem->get(UserID);
    if (Password == nullptr) {
        if (accountSystem->log_on_now.Privilege <= account.Privilege) {
            return;
        }
    } else if (strcmp(Password, account.Password) != 0) {
        IV();
        return;
    }
    accountSystem->log_on_now = account;
    push_back(account);
//    accountSystem->stack_kvd.insert(account.UserID, 0);
    accountSystem->loger_num[accountSystem->log_on_now.UserID]++;
    clear_selected();
    add_log();
}

Log_system::Log_system() {

    Account empty;
    loger_stack.push_back(empty);
//    log_file.open("log_stack", std::ios::in | std::ios::out | std::ios::binary);
//    if (!log_file) {
//        log_file.open("log_stack", std::ios::out | std::ios::binary);
//        log_file.close();
//        log_file.open("log_stack", std::ios::in | std::ios::out | std::ios::binary);
//    }
//    if (!log_file) {
//        std::cerr << "log file wrong";
//    }
}

void Log_system::Log_system_init(Account_system &accountSystem_, Book_system &bookSystem1_, Blog_system &blogSystem_) {
    accountSystem = &accountSystem_;
    bookSystem = &bookSystem1_;
    blogSystem = &blogSystem_;
    char UserID[31] = {0};
    accountSystem->loger_num[UserID] = 1;
}

void Log_system::pop_back() {
    char *id = loger_stack.back().UserID;
    loger_stack.pop_back();
//    log_num[]--;

//    Account account;
//    log_file.seekp(last_position);
//    log_file.write(reinterpret_cast<char *>(&account), sizeof(Account));
}

void Log_system::push_back(Account &in) {
    loger_stack.push_back(in);
//    log_file.seekp(last_position);
//    log_file.write(reinterpret_cast<char *>(&in), sizeof(Account));
}

Account Log_system::back() {
    return loger_stack.back();
//    if (last_position == 0) {
//        Account empty;
//        return empty;
//    }
//    log_file.seekg(last_position);
//    Account account;
//    log_file.read(reinterpret_cast<char *>(&account), sizeof(Account));
//    return account;
}
