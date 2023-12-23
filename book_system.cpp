//
// Created by qiuyuhang on 23-12-16.
//
#include "book_system.h"
#include <algorithm>

void Book_system::add_log(Price &in, Price &out) {
    Do_table doTable;
    doTable.in = in;
    doTable.out = out;
    strcpy(doTable.UserID, accountSystem1->log_on_now.UserID);
    strcpy(doTable.do_, blogSystem->do_str->c_str());
    blogSystem->add_log(doTable);
}

void Book_system::add_employ() {
    if (accountSystem1->log_on_now.Privilege != 3) {
        return;
    }
    Employee_table employeeTable;
    strcpy(employeeTable.UserID, accountSystem1->log_on_now.UserID);
    strcpy(employeeTable.do_, blogSystem->do_str->c_str());
    blogSystem->add_employee(employeeTable);
}

void Book_system::add_finance(Price &in, Price &out, char *ISBN, char *UserID, int Quality) {
    Finance_table financeTable;
    financeTable.money_in = in;
    financeTable.money_out = out;
    strcpy(financeTable.do_, blogSystem->do_str->c_str());
    strcpy(financeTable.UserID, UserID);
    strcpy(financeTable.ISBN, ISBN);
    financeTable.Quality = Quality;
    blogSystem->add_finance(financeTable);
}

void Book_system::add_count(Price &in, Price &out) {
    Count count;
    count.money_in = in;
    count.money_out = out;
    blogSystem->add_count(count);
}

void Book_system::init(Blog_system &blogSystem_, Account_system &accountSystem_) {
    blogSystem = &blogSystem_;
    accountSystem1 = &accountSystem_;
}
//void IV() {
//    std::cout << "Invalid\n";
//}

bool check_no_quote(const char *in) {
    if (in == nullptr) {
        return false;
    }
    for (int i = 0; i < 60; ++i) {
        if (in[i] == '\"') {
            return true;
        }
    }
    return false;
}


Book_system::Book_system() : fAuthor("fAuthor"), fBookName("fBookName"), fISBN("fISBN"), fKeyWord("fKeyWord") {
    books.open("books", std::ios::in | std::ios::out | std::ios::binary);
    if (!books) {
        books.open("books", std::ios::out | std::ios::binary);
        books.close();
        books.open("books", std::ios::in | std::ios::out | std::ios::binary);
    }
    if (!books) {
        std::cerr << "books file wrong";
    }
    fISBN.initialize("fISBN");
    fKeyWord.initialize("fKeyWord");
    fAuthor.initialize("fAuthor");
    fBookName.initialize("fBookName");
}
bool cmpp(const Book lhs,const Book rhs){
    if (strcmp(lhs.ISBN,rhs.ISBN)<0) {
        return true;
    }
    return false;
}
bool check_split(char *in){
    int i=0;
    while (in[i]!=0){
        if (in[i]=='|'){
            return true;
        }
        i++;
    }
    return false;
}
void Book_system::show(char *index, index_type type) {
    if (accountSystem1->log_on_now.Privilege < 1) {
        IV();
        return;
    }
    if (index == nullptr) {
        show_all();
        return;
    }
    std::vector<int> all;
    switch (type) {
        case ISBN:
            all = fISBN.find_no_output(index);
            break;
        case name:
            all = fBookName.find_no_output(index);
            break;
        case author:
            all = fAuthor.find_no_output(index);
            break;
        case keyword:
            if (check_split(index)){
                IV();
                return;
            }
            all = fKeyWord.find_no_output(index);
            break;
    }
    std::set<Book,cmp> bs;
    for (int pos: all) {
        Book book = get(pos);
        bs.insert(book);
    }
    for (auto book:bs) {
        std::cout << book;
    }
    if (all.empty()) {
        std::cout << '\n';
    }
    Price price1, price2;
    add_log(price1, price2);
//    add_log(Price(0),Price(0));
}

void Book_system::buy(char *ISBN, long long Quantity) {
    if (accountSystem1->log_on_now.Privilege < 1) {
        IV();
        return;
    }
    std::vector<int> all = fISBN.find_no_output(ISBN);
    if (all.empty()) {
        IV();
        return;
    }
    Book tmp = get(all.front());
    tmp.storage -= Quantity;
    if (tmp.storage < 0) {
        IV();
        return;
    }
    change(all.front(), tmp);
    Price price_in, price_out;
    price_in = Quantity * tmp.price;
    std::cout << price_in << '\n';
    add_log(price_in, price_out);
    add_count(price_in, price_out);
    add_finance(price_in, price_out, ISBN, accountSystem1->log_on_now.UserID, Quantity);
}

//already done:新旧都需改索引文件

//todo:xiu
void Book_system::select(char *ISBN) {
    if (accountSystem1->log_on_now.Privilege < 3) {
        IV();
        return;
    }
    std::vector<int> all = fISBN.find_no_output(ISBN);
    Book tmp;
    if (all.empty()) {
        strcpy(tmp.ISBN, ISBN);
        select_position = end_of_book;
        change(select_position, tmp);
        end_of_book += sizeof(Book);
        fISBN.insert(ISBN, select_position);
    } else {
        select_position = all.front();
        tmp = get(all.front());
    }
    already_select = true;
    selected = tmp;
    Price price_in, price_out;
    add_log(price_in, price_out);
    add_employ();
}

Price to_price(char *price) {
    std::string string2(price);
    Price tmp;
    int ti = 0, tf = 0;
    for (int i = 0; i < string2.size(); ++i) {
        if (string2[i] == '.') {
            if (string2.size() >= i + 4 || string2.size() == i + 1) {//不是.不是.xxx
                IV();
                int a;
                throw a;
            }
            if (string2.size() == i + 2) {//是.x
                if (string2[i + 1] > '9' || string2[i + 1] < '0') {
                    IV();
                    int a;
                    throw a;
                }
                tf = (string2[i + 1] - '0') * 10;
                break;
            }
            if (string2.size() == i + 3) {//是.xx
                if (string2[i + 1] > '9' || string2[i + 1] < '0' || string2[i + 2] > '9' || string2[i + 2] < '0' ||
                    string2[i + 3] != 0) {
                    IV();
                    int a;
                    throw a;
                }
                tf = (string2[i + 1] - '0') * 10 + string2[i + 2] - '0';
            }
            break;
        }
        if (string2[i] > '9' || string2[i] < '0') {
            IV();
            int a;
            throw a;
        }
        ti *= 10;
        ti += string2[i] - '0';
    }
    tmp.integer = ti;
    tmp.float_ = tf;
    return tmp;
}

std::vector<std::string> piece_keyword(char *keyword) {
    int position = 0;
    std::vector<std::string> all;
    std::string tmp;
    while (keyword[position] != 0) {
        char now = keyword[position];
        if (now == '|') {
            all.push_back(tmp);
            tmp="";
        } else {
            tmp += now;
        }
        position++;
    }
    all.push_back(tmp);
    return all;
}

bool check_repeat(std::vector<std::string> &in) {//有重为true
    if (in.empty()) {
        return false;
    }
    std::sort(in.begin(), in.end());
    for (int i = 0; i < in.size() - 1; ++i) {
        if (in[i] == in[i + 1]) {
            return true;
        }
    }
    return false;
}
bool check_kyw_length(char *in){
    if (in[0]==0||in[0]=='|'){
        return true;
    }
    int i=1;
    while (in[i]!=0){
        if (in[i]=='|'&&in[i-1]=='|'){
            return true;
        }
        i++;
    }
    if (in[i-1]=='|'){
        return true;
    }
    return false;
}
void Book_system::modify(char *ISBN, char *name, char *author, char *keyword, char *price) {
    if (accountSystem1->log_on_now.Privilege < 3) {
        IV();
        return;
    }
    if (!already_select) {
        IV();
        return;
    }
    if (check_no_quote(name) || check_no_quote(author) || check_no_quote(keyword)) {
        IV();
        return;
    }
    if (ISBN != nullptr) {
        if (strcmp(ISBN, selected.ISBN) == 0) {
            IV();
            return;
        }
    }

    Book old = selected;//todo测试这是否合法
    if (keyword != nullptr) {
        if (check_kyw_length(keyword)){
            IV();
            return;
        }
        std::vector<std::string> keys = piece_keyword(keyword);
        if (check_repeat(keys)) {
            IV();
            selected = old;
            return;
        }
    }
    if (ISBN != nullptr) {
        if (strlen(ISBN) > 20) {
            IV();
            selected = old;
            return;
        }
        if (!fISBN.find_no_output(ISBN).empty()) {
            IV();
            selected = old;
            return;
        }
    }
    if (name != nullptr) {
        if (strlen(name) > 60) {
            IV();
            selected = old;
            return;
        }
    }
    if (author != nullptr) {
        if (strlen(author) > 60) {
            IV();
            selected = old;
            return;
        }
    }



    if (price != nullptr) {
        if (strlen(price) > 13) {
            IV();
            selected = old;
            return;
        }
        try {
            selected.price = to_price(price);
        } catch (int) {
            selected = old;
            return;
        }
    }
    if (keyword != nullptr) {
        std::vector<std::string> keys = piece_keyword(keyword);
        strcpy(selected.Keyword, keyword);
        for (int &i: selected.cut_position) {
            i = 0;
        }
        int on_keyword = 0, on_store = 0;
        while (keyword[on_keyword] != 0) {
            if (keyword[on_keyword] == '|') {
                selected.cut_position[on_store] = on_keyword;
                on_store++;
            }
            on_keyword++;
        }
        delete_key(old.Keyword, select_position);
        add_key(keys, select_position);
    }
    if (ISBN != nullptr) {
        strcpy(selected.ISBN, ISBN);
        fISBN.delete_(old.ISBN, select_position);
        fISBN.insert(ISBN, select_position);
    }
    if (name != nullptr) {
        strcpy(selected.BookName, name);
        fBookName.delete_(old.BookName, select_position);
        fBookName.insert(name, select_position);
    }
    if (author != nullptr) {
        strcpy(selected.Author, author);
        if (strcmp(old.Author,"")!=0){
            fAuthor.delete_(old.Author, select_position);
        }
        fAuthor.insert(author, select_position);
    }
    change(select_position, selected);
    Price price_in, price_out;
    add_log(price_in, price_out);
    add_employ();
}


void Book_system::import(long long Quantity, long long TotalCost_integer, long long TotalCost_float) {
    if (accountSystem1->log_on_now.Privilege < 3) {
        IV();
        return;
    }
    if (!already_select) {
        IV();
        return;
    }
    selected.storage += Quantity;
    change(select_position, selected);
    Price price_in, price_out;
    price_out.integer = TotalCost_integer;
    price_out.float_ = TotalCost_float;
    add_log(price_in, price_out);
    add_count(price_in, price_out);
    add_finance(price_in, price_out, selected.ISBN, accountSystem1->log_on_now.UserID, Quantity);
    add_employ();
}

void Book_system::delete_key(char *in, int position) {
    std::vector<std::string> all = piece_keyword(in);
    for (const auto &i: all) {
        char key[61] = {0};
        strcpy(key, i.c_str());
        fKeyWord.delete_(key, position);
    }
}

//todo:key_value_database是64大小数组，如果传小了会不会出问题？一定会！！！嘶，基于strcmp的话可能没问题。
void Book_system::add_key(std::vector<std::string> &keys, int position) {
    for (const auto &i: keys) {
        char key[61] = {0};
        strcpy(key, i.c_str());
        fKeyWord.insert(key, position);
    }
}

void Book_system::show_all() {
    for (auto item: get_all_sorted()) {
        std::cout << item;
    }
//    std::vector<unsigned long long > pos_in_kvd=fISBN.get_th_to_posi_map();//1->1st的位置序;
//    for (unsigned long long i:pos_in_kvd) {
//        std::vector<int> pos_in_books=fISBN.get_whole_block(i);
//        for (int j:pos_in_books) {
//            Book book= get(j);
//            std::cout<<book;
//        }
//    }
}

void Book_system::change(int position, Book &new_) {
    books.seekp(position, std::ios::beg);
    books.write(reinterpret_cast<char *>(&new_), sizeof(Book));
}

Book Book_system::get(int position) {
    books.seekg(position, std::ios::beg);
    Book book;
    books.read(reinterpret_cast<char *>(&book), sizeof(Book));
    return book;
}

std::set<Book, cmp> Book_system::get_all_sorted() {
    books.flush();
//    std::cout<<books.tellg();
    std::set<Book, cmp> tmp;
    books.seekg(0, std::ios::beg);
    Book in;
    while (!books.eof()) {
        Book book = in;
        books.read(reinterpret_cast<char *>(&in), sizeof(Book));
        if (strcmp(book.ISBN, in.ISBN) == 0) {
            break;
        }
        tmp.insert(in);
    }
    books.close();
    books.open("books", std::ios::in | std::ios::out | std::ios::binary);
    return tmp;
}