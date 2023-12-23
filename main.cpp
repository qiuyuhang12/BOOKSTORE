//
// Created by qiuyuhang on 23-12-12.
//
#include <iostream>
#include "main_system.h"
#include <string>
#include <cstring>
#include <cstdlib>
#include <assert.h>

//
void order_analyse(std::string &line, Main_system &);

bool show_form_iv(std::string &in, index_type type);

std::string get_information(std::string &in, index_type type);

//输出Invalid
//void IV();
void clear_file() {
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/accounts");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/books");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/count_file");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fAuthorcatalog");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fAuthordictionary");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fBookNamecatalog");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fBookNamedictionary");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fISBNcatalog");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fISBNdictionary");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fKeyWordcatalog");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/fKeyWorddictionary");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/log_file");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/report_employee_file");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/report_finance_file");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/UserID_index_filecatalog");
    remove("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/cmake-build-debug/UserID_index_filedictionary");
    remove("2int");
}

int main() {
//    clear_file();
//    exit(0);
//    freopen("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/tmp","w",stdout);
    Main_system mainSystem;
    std::string line;
    Catalog catalog;
    Dictionary dictionary;
//    int i=0;
    while (getline(std::cin, line)) {
//        i++;
//        std::cout<<i;
        if (line.empty()) {
            continue;
        }
        if (line == "quit" || line == "exit") {
            break;
        }
        try {
            order_analyse(line, mainSystem);
        } catch (Err) {
            IV();
        }
        {
//            std::fstream fstream;
//            fstream.open("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/code/cmake-build-debug/fAuthorcatalog",std::ios::in|std::ios::out|std::ios::binary);
//            if (fstream){
//                fstream.seekg(sizeof(Stack),std::ios::beg);
//                fstream.read(reinterpret_cast<char*>(&catalog), sizeof(Catalog));
//            }
//            fstream.close();
//            fstream.open("/run/media/qiuyuhang/data/cpp_file/Bookstore-2023/code/cmake-build-debug/fAuthordictionary",std::ios::in|std::ios::out|std::ios::binary);
//            if (fstream){
//                fstream.seekg(0,std::ios::beg);
//                fstream.read(reinterpret_cast<char*>(&dictionary), sizeof(Dictionary));
//            }
        }
    }
    return 0;
}

//void IV() {
//    std::cout << "Invalid\n";
//}

bool show_form_iv(std::string &in, index_type type) {
    bool rsl = false;
    std::string tmp;
    switch (type) {
        case ISBN:
            tmp.insert(0, in, 0, 6);
            if (tmp != "-ISBN=") {
                rsl = true;
            }
            break;
        case name:
            tmp.insert(0, in, 0, 7);
            if (tmp != "-name=\"" || in.back() != '\"') {
                rsl = true;
            }
            break;
        case author:
            tmp.insert(0, in, 0, 9);
            if (tmp != "-author=\"" || in.back() != '\"') {
                rsl = true;
            }
            break;
        case keyword:
            tmp.insert(0, in, 0, 10);
            if (tmp != "-keyword=\"" || in.back() != '\"') {
                rsl = true;
            }
            break;
        case price:
            tmp.insert(0, in, 0, 7);
            if (tmp != "-price=") {
                rsl = true;
            }
            break;
    }
    return rsl;
}

std::string get_information(std::string &in, index_type type) {//todo测试
    std::string tmp;
    switch (type) {
        case ISBN:
            if (in.size() <= 6) {
                throw Err();
            }
            if (in[0 + 5] == 0) {
                throw Err();
            }
            tmp.insert(0, in, 6, in.size() - 6);
            break;
        case name:
            if (in.size() <= 8) {
                throw Err();
            }
            if (in[0 + 6] == '\"' && in[1 + 6] == '\"' && in.size() == 8) {
                throw Err();
            }
            tmp.insert(0, in, 7, in.size() - 8);
            break;
        case author:
            if (in.size() <= 10) {
                throw Err();
            }
            if (in[0 + 8] == '\"' && in[1 + 8] == '\"' && in.size() == 10) {
                throw Err();
            }
            tmp.insert(0, in, 9, in.size() - 10);
            break;
        case keyword:
            if (in.size() <= 11) {
                throw Err();
            }
            if (in[0 + 10 - 1] == '\"' && in[1 + 10 - 1] == '\"' && in.size() == 11) {
                throw Err();
            }
            tmp.insert(0, in, 10, in.size() - 11);
            break;
        case price:
            if (in.size() <= 7) {
                throw Err();
            }
            if (in[0 + 6] == 0) {
                throw Err();
            }
            tmp.insert(0, in, 7, in.size() - 7);
            break;
    }
    return tmp;
}

//bool check_quote_quote_blank
void order_analyse(std::string &line, Main_system &mainSystem) {
    mainSystem.blogSystem.do_str = &line;
    Piece piece(line);
    std::string order = piece.get();
    if (order.empty()) {
        return;
    }
    std::string string1 = piece.get(), string2 = piece.get(), string3 = piece.get(), string4 = piece.get(), string5 = piece.get(), string6 = piece.get();
    if (order == "su") {
//        char userid[31]={0};
//        strcpy(userid,piece.get().c_str());
//        char psw[31]={0};
//        strcpy(psw,piece.get().c_str());
//        assert(0);
        char userid[31] = {0}, psw[31] = {0};
        if (string1.size() > 30 || string2.size() > 30 || string1.empty() || !string3.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        if (!string2.empty()) {
            strcpy(psw, string2.c_str());
            if (check_num_letter_(psw) || check_num_letter_(userid) || strlen(psw) > 30 || strlen(userid) > 30) {
                IV();
                return;
            }
            mainSystem.su(userid, psw);
        } else {
            if (check_num_letter_(userid) || strlen(userid) > 30) {
                IV();
                return;
            }
            mainSystem.su(userid);
        }
    } else if (order == "logout") {
        if (!string1.empty()) {//有多余
            IV();
            return;
        }
        mainSystem.logout();
//        assert(0);
    } else if (order == "register") {
        assert(0);
        char userid[31] = {0}, psw[31] = {0}, username[31] = {0};
        if (string1.empty() || string2.empty() || string3.empty() || string1.size() > 30 || string2.size() > 30 ||
            string3.size() > 30 || !string4.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        strcpy(psw, string2.c_str());
        strcpy(username, string3.c_str());
        if (check_num_letter_(psw) || check_num_letter_(userid) || strlen(userid) > 30 || strlen(psw) > 30 ||
            strlen(username) > 30) {
            IV();
            return;
        }
        mainSystem.register_(userid, psw, username);
    } else if (order == "passwd") {
        char userid[31] = {0}, cpsw[31] = {0}, npsw[31] = {0};
        if (string1.empty() || string2.empty() || string1.size() > 30 || string2.size() > 30 ||
            string3.size() > 30 || !string4.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        if (string3.empty()) {
            strcpy(npsw, string2.c_str());
            if (check_num_letter_(npsw) || check_num_letter_(userid) || strlen(userid) > 30 || strlen(npsw) > 30) {
                IV();
                return;
            }
            mainSystem.passwd(userid, npsw);
        } else {
            strcpy(cpsw, string2.c_str());
            strcpy(npsw, string3.c_str());
            if (check_num_letter_(npsw) || check_num_letter_(cpsw) || check_num_letter_(userid) ||
                strlen(userid) > 30 || strlen(npsw) > 30 || strlen(cpsw) > 30) {
                IV();
                return;
            }
            mainSystem.passwd(userid, npsw, cpsw);
        }
    } else if (order == "useradd") {
        char userid[31] = {0}, psw[31] = {0}, username[31] = {0};
        int pri = 0;
        if (string1.empty() || string2.empty() || string3.empty() || string4.empty() || string1.size() > 30 ||
            string2.size() > 30 ||
            string3.size() > 1 || string4.size() > 30 || !string5.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        strcpy(psw, string2.c_str());
        pri = string3[0] - '0';
        strcpy(username, string4.c_str());
        if (check_num_letter_(psw) || check_num_letter_(userid)) {
            return;
        }
        if ((pri != 0 && pri != 1 && pri != 3 && pri != 7) ||
            strlen(userid) > 30 || strlen(username) > 30 || strlen(psw) > 30) {
            IV();
            return;
        }
        mainSystem.useradd(userid, psw, pri, username);
    } else if (order == "delete") {
        char userid[31] = {0};
        if (string1.empty() || string1.size() > 30 || !string2.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        if (check_num_letter_(userid) || strlen(userid) > 30) {
            IV();
            return;
        }
        mainSystem.delete_(userid);

    } else if (order == "show") {
        if (string1 == "finance") {
            if (mainSystem.accountSystem.log_on_now.Privilege < 7) {
                IV();
                return;
            }
            if (string2.length() > 10 || !string3.empty()) {
                IV();
                return;
            }
            if (string2.empty()) {
                mainSystem.show_finance();
            } else {
                int count = 0;
                for (char i: string2) {
                    if (i < '0' || i > '9') {
                        IV();
                        return;
                    }
                    count *= 10;
                    count += i - '0';
                }
                mainSystem.show_finance(count);
            }
            return;
        }
        if (!string2.empty()) {
            IV();
            return;
        }
        if (string1.empty()) {
            mainSystem.show(nullptr, none);
        } else {
            char tmp = string1[1];
            char inf[61] = {0};
            if (tmp == 'I') {
                if (show_form_iv(string1, ISBN)) {
                    IV();
                    return;
                }
                strcpy(inf, get_information(string1, ISBN).c_str());
                if (strlen(inf) > 20) {
                    IV();
                    return;
                }
                mainSystem.show(inf, ISBN);
            } else if (tmp == 'n') {
                if (show_form_iv(string1, name)) {
                    IV();
                    return;
                }
                strcpy(inf, get_information(string1, name).c_str());
                if (check_no_quote(inf)) {
                    IV();
                    return;
                }
                if (strlen(inf) > 60) {
                    IV();
                    return;
                }
                mainSystem.show(inf, name);
            } else if (tmp == 'a') {
                if (show_form_iv(string1, author)) {
                    IV();
                    return;
                }
                strcpy(inf, get_information(string1, author).c_str());
                if (check_no_quote(inf)) {
                    IV();
                    return;
                }
                if (strlen(inf) > 60) {
                    IV();
                    return;
                }
                mainSystem.show(inf, author);
            } else if (tmp == 'k') {
                if (show_form_iv(string1, keyword)) {
                    IV();
                    return;
                }
                strcpy(inf, get_information(string1, keyword).c_str());
                if (check_no_quote(inf)) {
//                    check_repeat()
                    IV();
                    return;
                }
                if (strlen(inf) > 60) {
                    IV();
                    return;
                }
                mainSystem.show(inf, keyword);
            } else {
                IV();
                return;
            }
        }
    } else if (order == "buy") {
        char isbn[21] = {0};
        int q = 0;
        if (string1.empty() || string2.empty() || string1.size() > 20 || string2.size() > 10
            || !string3.empty()) {
            IV();
            return;
        }
        strcpy(isbn, string1.c_str());
        for (char i: string2) {
            if (i < '0' || i > '9') {
                IV();
                return;
            }
            q *= 10;
            q += i - '0';
        }
        if (strlen(isbn) > 20) {
            IV();
            return;
        }
        if (q == 0) {
            IV();
            return;
        }
        mainSystem.buy(isbn, q);
    } else if (order == "select") {
        char isbn[21] = {0};
        if (string1.empty() || string1.size() > 30 || !string2.empty()) {
            IV();
            return;
        }
        strcpy(isbn, string1.c_str());
        if (strlen(isbn) > 20) {
            IV();
            return;
        }
        mainSystem.select(isbn);
    } else if (order == "modify") {
        //todo查重，查格式
        if (!string6.empty()) {
            IV();
            return;
        }
        std::string *strs[5] = {&string1, &string2, &string3, &string4, &string5};
        std::vector<index_type> indexes;
        int unempty = 0;
        for (auto &str: strs) {
            if (str->empty()) {
                break;
            }
            unempty++;
            int checkRepeat[5] = {0};
            switch ((*str)[1]) {
                case 'I':
                    if (checkRepeat[0] != 0) {
                        IV();
                        return;
                    }
                    checkRepeat[0]++;
                    indexes.push_back(ISBN);
                    break;
                case 'n':
                    if (checkRepeat[1] != 0) {
                        IV();
                        return;
                    }
                    checkRepeat[1]++;
                    indexes.push_back(name);
                    break;
                case 'a':
                    if (checkRepeat[2] != 0) {
                        IV();
                        return;
                    }
                    checkRepeat[2]++;
                    indexes.push_back(author);
                    break;
                case 'k':
                    if (checkRepeat[3] != 0) {
                        IV();
                        return;
                    }
                    checkRepeat[3]++;
                    indexes.push_back(keyword);
                    break;
                case 'p':
                    if (checkRepeat[4] != 0) {
                        IV();
                        return;
                    }
                    checkRepeat[4]++;
                    indexes.push_back(price);
                    break;
                default:
                    IV();
                    return;
            }
        }
        char information[6][61] = {0};
        char *trans[6] = {nullptr};
        for (int i = 0; i < unempty; ++i) {
            index_type tmp = indexes[i];
            if (show_form_iv(*(strs[i]), tmp)) {
                IV();
                return;
            }
            strcpy(information[tmp], get_information(*(strs[i]), tmp).c_str());
            if (information[tmp] == nullptr) {
                IV();
                return;
            }
        }
        for (int i = 1; i < 6; ++i) {
            if (information[i][0] != 0) {
                trans[i] = information[i];
            }
        }
        //null,isbn,name,author,keyword,price;
        mainSystem.modify(trans[1], trans[2], trans[3], trans[4], trans[5]);
    } else if (order == "import") {
        int q = 0, ti = 0, tf = 0;
        if (string1.empty() || string2.empty() || string1.size() > 10 || string2.size() > 13
            || !string3.empty()) {
            IV();
            return;
        }
        if (string1.size() > 10) {
            IV();
            return;
        }
        for (char i: string1) {
            if (i > '9' || i < '0') {
                IV();
                return;
            }
            q *= 10;
            q += i - '0';
        }
        if (string2.size() > 13) {
            IV();
            return;
        }
        for (int i = 0; i < string2.size(); ++i) {
            if (string2[i] == '.') {
                if (string2.size() >= i + 4 || string2.size() == i + 1) {//不是.不是.xxx
//                    IV();
                    int a;
                    throw a;
                }
                if (string2.size() == i + 2) {//是.x
                    if (string2[i + 1] > '9' || string2[i + 1] < '0') {
//                        IV();
                        int a;
                        throw a;
                    }
                    tf = (string2[i + 1] - '0') * 10;
                    break;
                }
                if (string2.size() == i + 3) {//是.xx
                    if (string2[i + 1] > '9' || string2[i + 1] < '0' || string2[i + 2] > '9' || string2[i + 2] < '0' ||
                        string2[i + 3] != 0) {
//                        IV();
                        int a;
                        throw a;
                    }
                    tf = (string2[i + 1] - '0') * 10 + string2[i + 2] - '0';
                }
                break;//todo:会不会少报invalid
            }
            if (string2[i] > '9' || string2[i] < '0') {
                IV();
                return;
            }
            ti *= 10;
            ti += string2[i] - '0';
        }
        if (q <= 0 || (ti <= 0 && tf <= 0)) {
            IV();
            return;
        }
        mainSystem.import(q, ti, tf);
    } else if (order == "log") {
        if (mainSystem.accountSystem.log_on_now.Privilege < 7) {
            IV();
            return;
        }
        if (!string1.empty()) {
            IV();
            return;
        }
        mainSystem.log();
    } else if (order == "report") {
        if (mainSystem.accountSystem.log_on_now.Privilege < 7) {
            IV();
            return;
        }
        if (string1.empty() || !string2.empty()) {
            IV();
            return;
        }
        if (string1 == "finance") {
            mainSystem.report_finance();
        } else if (string1 == "employee") {
            mainSystem.report_employee();
        } else IV();
    } else IV();
}

//account_system.cpp blog_system.cpp book_system.cpp key_value_database.cpp log_system.cpp main.cpp main_system.cpp

//su root sjtu
//select a
//import 10 100.9
//show finance
//import 20 874.32
//show finance
//show finance 1
//show finance 2
//show finance 3
