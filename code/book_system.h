//
// Created by qiuyuhang on 23-12-16.
//

#ifndef BOOKSTORE_2023_BOOK_SYSTEM_H
#define BOOKSTORE_2023_BOOK_SYSTEM_H
enum index_type {
    none, ISBN, name, author, keyword, price
};

class Book_system;

struct Book {

};

class Book_system {
    //保证格式、权限合法，不保证输入（如特定书籍）存在
    void show(char *index, index_type);

    void buy(char *ISBN, int Quantity);

    void select(char *ISBN);

    void modify(char *index, index_type);

    void import(int Quantity, int TotalCost);
};

#endif //BOOKSTORE_2023_BOOK_SYSTEM_H
