//
// Created by qiuyuhang on 23-12-16.
//
#include "log_system.h"
#include <cstring>
#include <assert.h>

void Log_system::add_log() {
    Do_table doTable;
    strcpy(doTable.UserID, accountSystem->log_on_now.UserID);
    strcpy(doTable.do_, blogSystem->do_str->c_str());
    blogSystem->add_log(doTable);
}


void Log_system::clear_selected() {
    Book book;
    bookSystem->selected = book;
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
    std::string s1 = accountSystem->log_on_now.UserID;
    int num = accountSystem->loger_num[s1];
    assert(num >= 0);
    if (num == 0 || num == 1) {
        accountSystem->loger_num.erase(s1);
    } else {
        accountSystem->loger_num[s1]--;
    }
    accountSystem->log_on_now = back();
    clear_selected();

    if (!already_select_stack.empty()) {
        bookSystem->already_select = already_select_stack.back();
        already_select_stack.pop_back();
        bookSystem->select_position = select_position_stack.back();
        select_position_stack.pop_back();
        bookSystem->books.flush();
        Book book = bookSystem->get(bookSystem->select_position);
        if (bookSystem->books.tellg() == -1) {
            bookSystem->books.close();
            bookSystem->books.open("books", std::ios::out | std::ios::in | std::ios::binary);
        }
        bookSystem->selected = book;
    }
    add_log();
}

bool check(const char *in) {
    if (in == nullptr) {
        return false;
    }
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
        return;
    }
    Account account;
    try {
        account = accountSystem->get(UserID);
    } catch (Err) {
        IV();
        return;
    }
    if (Password == nullptr) {
        if (accountSystem->log_on_now.Privilege <= account.Privilege) {
            IV();
            return;
        }
    } else if (strcmp(Password, account.Password) != 0) {
        IV();
        return;
    }
    log_num++;
    accountSystem->log_on_now = account;
    push_back(account);
    std::string string2 = accountSystem->log_on_now.UserID;
    accountSystem->loger_num[string2]++;
    already_select_stack.push_back(bookSystem->already_select);
    select_position_stack.push_back(bookSystem->select_position);
    clear_selected();
    add_log();
}

Log_system::Log_system() {

    Account empty;
    loger_stack.push_back(empty);
}

void Log_system::Log_system_init(Account_system &accountSystem_, Book_system &bookSystem1_, Blog_system &blogSystem_) {
    accountSystem = &accountSystem_;
    bookSystem = &bookSystem1_;
    blogSystem = &blogSystem_;

}

void Log_system::pop_back() {
    loger_stack.pop_back();
}

void Log_system::push_back(Account &in) {
    loger_stack.push_back(in);
}

Account Log_system::back() {
    return loger_stack.back();
}
