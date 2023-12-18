//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_BOOK_SYSTEM_H
#define BOOKSTORE_2023_BOOK_SYSTEM_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <key_value_database.h>
enum index_type {
    none, ISBN, name, author, keyword, price
};

class Book_system;

struct Price{
    int integer=0;
    int float_=0;
    Price& operator+=(Price&rhs);
    Price& operator-=(Price&rhs);
    friend std::ostream &operator<<(std::ostream &out,Price price1);
};
Price operator+(Price &lhs,Price &rhs);
Price operator-(Price &lhs,Price &rhs);
Price operator*(int &lhs,Price &rhs);
struct Book {
    char ISBN[21]={0};
    char BookName[61]={0};
    char Author[61]={0};
    char Keyword[61]={0};
    int cut_position[30]={0};//todo有存在必要吗？
    Price price;
    int storage=0;
    friend std::ostream& operator<<(std::ostream& out,Book &book);
};

class Book_system {
public:
    //保证格式、权限合法，不保证输入（如特定书籍）存在
    Book_system();
    void show(char *index, index_type);

    void buy(char *ISBN, int Quantity);

    void select(char *ISBN);

    void modify(char *ISBN, char *name, char *author, char *keyword, char *price);

    void import(int Quantity, int TotalCost_integer,int TotalCost_float);
    bool already_select= false;


private:
    Book selected;
    int select_position=0;
    int end_of_book=0;
    void change(int position,Book&new_);
    Book get(int position);
    std::fstream books;
    Key_value_database fISBN;
    Key_value_database fBookName;
    Key_value_database fAuthor;
    Key_value_database fKeyWord;
    void delete_key(char *in,int position);
    void add_key(std::vector<std::string>&keys,int position);
    void show_all();
};

#endif //BOOKSTORE_2023_BOOK_SYSTEM_H
