//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_BOOK_SYSTEM_H
#define BOOKSTORE_2023_BOOK_SYSTEM_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <key_value_database.h>
#include <blog_system.h>
#include "account_system.h"
#include <set>

enum index_type {
    none, ISBN, name, author, keyword, price
};

class Book_system;

class Blog_system;

class Account_system;

struct Count;
struct Finance_table;
struct Employee_table;
struct Do_table;


struct cmp {
    bool operator()(const Book &lhs, const Book &rhs) const {
        if (strcmp(lhs.ISBN, rhs.ISBN) < 0) {
            return true;
        }
        return false;
    }
};

class Book_system {
public:
    //保证格式、权限合法，不保证输入（如特定书籍）存在
    Book_system();

    ~Book_system() {
        books.close();
    }

    void init(Blog_system &blogSystem, Account_system &accountSystem);

    void show(char *index, index_type);

    void buy(char *ISBN, long long Quantity);

    void select(char *ISBN);

    void modify(char *ISBN, char *name, char *author, char *keyword, char *price);

    void import(long long Quantity, long long TotalCost_integer, long long TotalCost_float);

    bool already_select = false;
    int end_of_book = 0;

    Book selected;
    int select_position = 0;
    std::fstream books;

    Book get(int position);

private:
    void add_log(Price &in, Price &out);

    void add_employ();

    void add_finance(Price &in, Price &out, char *ISBN, char *UserID, int Quality);

    void add_count(Price &in, Price &out);

    Blog_system *blogSystem = nullptr;
    Account_system *accountSystem1 = nullptr;

    void change(int position, Book &new_);


    Key_value_database fISBN;
    Key_value_database fBookName;
    Key_value_database fAuthor;
    Key_value_database fKeyWord;

    void delete_key(char *in, int position);

    void add_key(std::vector<std::string> &keys, int position);

    void show_all();

    std::set<Book, cmp> get_all_sorted();
};

bool check_no_quote(const char *in);

bool check_repeat(std::vector<std::string> &in);//有重为true
#endif //BOOKSTORE_2023_BOOK_SYSTEM_H
