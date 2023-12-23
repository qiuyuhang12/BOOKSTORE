//
// Created by qiuyuhang on 23-12-16.
//
#include "account_system.h"

void Account_system::add_log() {
    Do_table doTable;
    strcpy(doTable.UserID, log_on_now.UserID);
    strcpy(doTable.do_, blogSystem->do_str->c_str());
    blogSystem->add_log(doTable);
}

void Account_system::add_employ() {
    if (log_on_now.Privilege != 3) {
        return;
    }
    Employee_table employeeTable;
    strcpy(employeeTable.UserID, log_on_now.UserID);
    strcpy(employeeTable.do_, blogSystem->do_str->c_str());
    blogSystem->add_employee(employeeTable);
}

void Account_system::init(Blog_system &blogSystem_) {
    blogSystem = &blogSystem_;
}

bool check_num_letter_(const char *in) {
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

Account_system::Account_system() : UserID_index_file("UserID_index_file") {
    UserID_index_file.initialize("UserID_index_file");
    file.open("accounts", std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        file.open("accounts", std::ios::out | std::ios::binary);
        file.close();
        file.open("accounts", std::ios::in | std::ios::out | std::ios::binary);
        char a[31] = "root", b[31] = "sjtu";
        useradd_hard(a, b, 7, a);
    }
    if (!file) {
        std::cerr << "log file wrong";
    }
}

void Account_system::delete_(char *UserID) {
    if (log_on_now.Privilege != 7) {
        IV();
        return;
    }
    std::string s = UserID;
    if (loger_num[s] != 0) {
        IV();
        return;
    } else {
        loger_num.erase(s);
    }

    std::vector<int> all = UserID_index_file.find_no_output(UserID);
    if (all.empty()) {
        IV();
        return;
    }
    UserID_index_file.delete_(UserID, all.front());
    add_log();
}

void Account_system::passwd(char *UserID, char *NewPassword, char *CurrentPassword) {
    if (log_on_now.Privilege < 1) {
        IV();
        return;
    }
    if (check_num_letter_(NewPassword)) {
        return;
    }
    std::vector<int> all = UserID_index_file.find_no_output(UserID);
    if (all.empty()) {
        IV();
        return;
    }
    int position = all.front();
    Account tmp = get(position);
    if (CurrentPassword == nullptr) {
        if (log_on_now.Privilege != 7) {
            IV();
            return;
        }
    } else {
        if (strcmp(CurrentPassword, tmp.Password) != 0) {
            IV();
            return;
        }
    }
    for (int i = 0; i < 31; ++i) {
        tmp.Password[i] = NewPassword[i];
    }
    change(position, tmp);
    add_log();
}

Account Account_system::get(int position) {
    Account tmp;
    file.seekg(position, std::ios::beg);
    file.read(reinterpret_cast<char *>(&tmp), sizeof(Account));
    return tmp;
}

void Account_system::change(int position, Account &new_) {
    file.seekp(position, std::ios::beg);
    file.write(reinterpret_cast<char *>(&new_), sizeof(Account));
}

void Account_system::useradd(char *UserID, char *Password, int Privilege, char *Username) {
    if (log_on_now.Privilege < 3) {
        IV();
        return;
    }
    if (check_num_letter_(UserID) || check_num_letter_(Password)) {
        return;
    }
    if (Privilege != 1 && Privilege != 3) {
        IV();
        return;
    }
    if (Privilege >= log_on_now.Privilege) {
        IV();
        return;
    }
    if (!UserID_index_file.find_no_output(UserID).empty()) {
        IV();
        return;
    }
    Account new_;
    strcpy(new_.Password, Password);
    strcpy(new_.UserID, UserID);
    strcpy(new_.Username, Username);
    new_.Privilege = Privilege;
    change(last_position_of_account, new_);
    UserID_index_file.insert(UserID, last_position_of_account);
    last_position_of_account += sizeof(Account);
    add_log();
    add_employ();
}

void Account_system::useradd_hard(char *UserID, char *Password, int Privilege, char *Username) {
    Account new_;
    strcpy(new_.Password, Password);
    strcpy(new_.UserID, UserID);
    strcpy(new_.Username, Username);
    new_.Privilege = Privilege;
    change(last_position_of_account, new_);
    UserID_index_file.insert(UserID, last_position_of_account);
    last_position_of_account += sizeof(Account);
}

void Account_system::register_(char *UserID, char *Password, char *Username) {
    if (check_num_letter_(UserID) || check_num_letter_(Password)) {
        return;
    }
    if (!UserID_index_file.find_no_output(UserID).empty()) {
        IV();
        return;
    }
    Account new_;
    strcpy(new_.Password, Password);
    strcpy(new_.UserID, UserID);
    strcpy(new_.Username, Username);
    new_.Privilege = 1;
    change(last_position_of_account, new_);
    UserID_index_file.insert(UserID, last_position_of_account);
    last_position_of_account += sizeof(Account);
    add_log();
}

Account Account_system::get(char *UserID) {
    auto item = UserID_index_file.find_no_output(UserID);
    if (item.empty()) {
        throw Err();
    }
    int position = item.front();
    Account tmp;
    file.seekg(position, std::ios::beg);
    file.read(reinterpret_cast<char *>(&tmp), sizeof(Account));
    return tmp;
}