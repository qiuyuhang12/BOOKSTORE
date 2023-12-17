//
// Created by qiuyuhang on 23-12-16.
//

#include "main_system.h"

Piece::Piece(std::string line) {
    line_ = line;
    for (int i = 0; i < line.size(); ++i) {
        if (line[i] == ' ') {
            blank.push_back(i);
        }
    }
    blank.push_back(line.size());
}

std::string Piece::get() {
    std::string cmp;
    if (blank[time]==line_.size()) {
        return "";
    }
    for (int i = blank[time] + 1; i < blank[time + 1]; ++i) {
        cmp.push_back(line_[i]);
    }
    time++;
    if (cmp.empty()) {
        return get();
    }
    return cmp;
}
void Main_system::logout(){
    logSystem.logout();
}

void Main_system::su(char *UserID, char *Password){
    logSystem.su(UserID,Password);
}

//account
void Main_system::register_(char *UserID, char *Password, char *Username){
    accountSystem.register_(UserID,Password,Username);
}

void Main_system::useradd(char *UserID, char *Password, int Privilege, char *Username){
    accountSystem.useradd(UserID,Password,Privilege,Username);
}

void Main_system::passwd(char *UserID, char *NewPassword, char *CurrentPassword){
    accountSystem.passwd(UserID,NewPassword,CurrentPassword);
}

void Main_system::delete_(char *UserID){
    accountSystem.delete_(UserID);
}

//book
void Main_system::show(char *index, index_type a){
    bookSystem.show(index,a);
}

void Main_system::buy(char *ISBN, int Quantity){
    bookSystem.buy(ISBN,Quantity);
}

void Main_system::select(char *ISBN){
    bookSystem.select(ISBN);
}

void Main_system::modify(char *ISBN,char *name,char *author,char *keyword,char* price){
    bookSystem.modify(ISBN,name,author,keyword,price);
}

void Main_system::import(int Quantity, int TotalCost_integer,int TotalCost_float){
    bookSystem.import(Quantity,TotalCost_integer,TotalCost_float);
}

//blog
void Main_system::show_finance(int count){
    blogSystem.show_finance(count);
}

void Main_system::log(){
    blogSystem.log();
}

void Main_system::report_finance(){
    blogSystem.report_finance();
}

void Main_system::report_employee(){
    blogSystem.report_employee();
}