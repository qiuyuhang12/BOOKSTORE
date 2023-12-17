//
// Created by qiuyuhang on 23-12-16.
//
#include "account_system.h"
void IV() {
    std::cout << "Invalid\n";
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
Account_system::Account_system() : UserID_index_file("UserID_index_file"), stack_kvd("stack_kvd"){
    file.open("accounts",std::ios::in|std::ios::out|std::ios::binary);
    if (!file){
        file.open("accounts",std::ios::out|std::ios::binary);
        file.close();
        file.open("accounts",std::ios::in|std::ios::out|std::ios::binary);
    }
    if (!file){
        std::cerr<<"log file wrong";
    }
}
void Account_system::delete_(char *UserID) {
    if (log_on_now.Privilege!=7){
        IV();
        return;
    }
    if (!stack_kvd.find_no_output(UserID).empty()){
        IV();
        return;
    }
    std::vector<int> all=UserID_index_file.find_no_output(UserID);
    if (all.empty()){
        IV();
        return;
    }
//    erase(all.front());
    UserID_index_file.delete_(UserID,all.front());
}

//void Account_system::erase(int position) {
//    file.seekp(position);
//}
void Account_system::passwd(char *UserID, char *NewPassword, char *CurrentPassword) {
    if (check(NewPassword)){
        IV();
        return;
    }
    std::vector<int> all=UserID_index_file.find_no_output(UserID);
    if (all.empty()){
        IV();
        return;
    }
    int position=all.front();
    Account tmp= get(position);
    if (CurrentPassword==nullptr){
        if (log_on_now.Privilege!=7){
            IV();
            return;
        }
    } else {
        if (strcmp(CurrentPassword,tmp.Password)!=0){
            IV();
            return;
        }
    }
    for (int i = 0; i < 31; ++i) {
        tmp.Password[i]=NewPassword[i];
    }
    change(position,tmp);
}

Account Account_system::get(int position) {
    Account tmp;
    file.seekg(position);
    file.read(reinterpret_cast<char*>(&tmp), sizeof(Account));
    return tmp;
}

void Account_system::change(int position, Account &new_) {
    file.seekp(position);
    file.write(reinterpret_cast<char*>(&new_), sizeof(Account));
}
void Account_system::useradd(char *UserID, char *Password, int Privilege, char *Username) {
    if (check(UserID) || check(Password)) {
        IV();
        return;
    }
    if (Privilege != 0 && Privilege != 1 && Privilege != 3) {
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
    strcpy(new_.Password,Password);
    strcpy(new_.UserID,UserID);
    strcpy(new_.Username,Username);
    new_.Privilege=Privilege;
    change(last_position_of_account,new_);
    UserID_index_file.insert(UserID,last_position_of_account);
    last_position_of_account+= sizeof(Account);
}

void Account_system::register_(char *UserID, char *Password, char *Username) {
    if (check(UserID) || check(Password)) {
        IV();
        return;
    }
    if (!UserID_index_file.find_no_output(UserID).empty()) {
        IV();
        return;
    }
    Account new_;
    strcpy(new_.Password,Password);
    strcpy(new_.UserID,UserID);
    strcpy(new_.Username,Username);
    new_.Privilege=1;
    change(last_position_of_account,new_);
    UserID_index_file.insert(UserID,last_position_of_account);
    last_position_of_account+= sizeof(Account);
}

Account Account_system::get(char *UserID) {
    int position=UserID_index_file.find_no_output(UserID).front();
    Account tmp;
    file.seekg(position);
    file.read(reinterpret_cast<char*>(&tmp), sizeof(Account));
}