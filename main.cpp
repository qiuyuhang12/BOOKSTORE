//
// Created by qiuyuhang on 23-12-12.
//
#include <iostream>
#include "main_system.h"
#include <string>
#include <cstring>
#include <assert.h>
#include <istream>
#include <regex>
//
void order_analyse(std::string &line, Main_system &);

bool show_form_iv(std::string &in, index_type type);

std::string get_information(std::string &in, index_type type);

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
    Main_system mainSystem;
    std::string line;
    while (getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::string tmp=line;
        Piece piece0(tmp);
        std::string line_=piece0.get(),line_empty=piece0.get();
        if (line_ == "quit" || line_ == "exit") {
            if (line_empty.empty()){
                break;
            } else{
                IV();
                continue;
            }
        }
        try {
            order_analyse(line, mainSystem);
        } catch (Err) {
            IV();
        }
    }
    return 0;
}
void check_orthornormal(std::string& string){
//    assert(0);
//    throw Err();
    std::istringstream str(string);
    std::string word;
    str>>word;
    int sz =0;
    while (str>>word){
        if (++sz>5)throw Err();
        std::regex rg(
        R"(-ISBN=[^\x00-\x1F\s]{1,20}|-name="[^"\x00-\x1F\s]{1,60}"|-author="[^"\x00-\x1F\s]{1,60}"|-keyword="[^"\x00-\x1F\s]{1,60}"|-price=\d+(\.\d+)?)");
        if (std::regex_match(word,rg)){
            return;
        } else{
            throw Err();
        }
    }

}
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

void check_invisible(std::string string) {
    for (auto i: string) {
        if ((int) i <= 32 || (int) i >= 127) {
            throw Err();
        }
    }
}

void check_invisible_(char *string) {
    if (string == nullptr) {
        return;
    }
    int i0 = 0;
    while (string[i0] != 0) {
        char i = string[i0];
        if ((int) i <= 32 || (int) i >= 127) {
            throw Err();
        }
        i0++;
    }
}

std::string get_information(std::string &in, index_type type) {
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
            if (in[0 + 7] == '.') {
                throw Err();
            }
            tmp.insert(0, in, 7, in.size() - 7);
            break;
    }
    check_invisible(tmp);
    return tmp;
}

void order_analyse(std::string &line, Main_system &mainSystem) {
    mainSystem.blogSystem.do_str = &line;
    Piece piece(line);
    std::string order = piece.get();
    if (order.empty()) {
        return;
    }
    std::string string1 = piece.get(), string2 = piece.get(), string3 = piece.get(), string4 = piece.get(), string5 = piece.get(), string6 = piece.get();
    if (order == "su") {
        char userid[31] = {0}, psw[31] = {0};
        if (string1.size() > 30 || string2.size() > 30 || string1.empty() || !string3.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        if (!string2.empty()) {
            strcpy(psw, string2.c_str());
            if (check_num_letter_(psw) || check_num_letter_(userid)) {
                return;
            }
            if (strlen(psw) > 30 || strlen(userid) > 30) {
                IV();
                return;
            }
            check_invisible_(userid);
            check_invisible_(psw);
            mainSystem.su(userid, psw);
        } else {
            if (check_num_letter_(userid)) {
                return;
            }
            if (strlen(userid) > 30) {
                IV();
                return;
            }
            check_invisible_(userid);
            mainSystem.su(userid);
        }
    } else if (order == "logout") {
        if (!string1.empty()) {//有多余
            IV();
            return;
        }
        mainSystem.logout();
    } else if (order == "register") {
        char userid[31] = {0}, psw[31] = {0}, username[31] = {0};
        if (string1.empty() || string2.empty() || string3.empty() || string1.size() > 30 || string2.size() > 30 ||
            string3.size() > 30 || !string4.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        strcpy(psw, string2.c_str());
        strcpy(username, string3.c_str());
        if (check_num_letter_(psw) || check_num_letter_(userid)) {
            return;
        }
        if (strlen(userid) > 30 || strlen(psw) > 30 ||
            strlen(username) > 30) {
            IV();
            return;
        }
        check_invisible_(userid);
        check_invisible_(psw);
        check_invisible_(username);
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
            if (check_num_letter_(npsw) || check_num_letter_(userid)) {
                return;
            }
            if (strlen(userid) > 30 || strlen(npsw) > 30) {
                IV();
                return;
            }
            check_invisible_(userid);
            check_invisible_(npsw);
            mainSystem.passwd(userid, npsw);
        } else {
            strcpy(cpsw, string2.c_str());
            strcpy(npsw, string3.c_str());
            if (check_num_letter_(npsw) || check_num_letter_(cpsw) || check_num_letter_(userid)) {
                return;
            }
            if (strlen(userid) > 30 || strlen(npsw) > 30 || strlen(cpsw) > 30) {
                IV();
                return;
            }
            check_invisible_(userid);
            check_invisible_(npsw);
            check_invisible_(cpsw);
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
        if ((pri != 1 && pri != 3 && pri != 7) ||
            strlen(userid) > 30 || strlen(username) > 30 || strlen(psw) > 30) {
            IV();
            return;
        }
        check_invisible_(userid);
        check_invisible_(psw);
        check_invisible_(username);
        mainSystem.useradd(userid, psw, pri, username);
    } else if (order == "delete") {
        char userid[31] = {0};
        if (string1.empty() || string1.size() > 30 || !string2.empty()) {
            IV();
            return;
        }
        strcpy(userid, string1.c_str());
        if (check_num_letter_(userid)) {
            return;
        }
        if (strlen(userid) > 30) {
            IV();
            return;
        }
        check_invisible_(userid);
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
        check_orthornormal(line);
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
        check_invisible_(isbn);
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
        check_orthornormal(line);
        //查重，查格式
        if (string1.empty()){
            IV();
            return;
        }
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
        for (int i = 1; i < 6; ++i) {
            check_invisible_(trans[i]);
        }
        mainSystem.modify(trans[1], trans[2], trans[3], trans[4], trans[5]);
    } else if (order == "import") {
        int q = 0;
        long long ti = 0, tf = 0;
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
        if (string2[0]=='.'){
            IV();
            return;
        }
        for (int i = 0; i < string2.size(); ++i) {
            if (string2[i] == '.') {
                if (string2.size() >= i + 4){//是.xxx
                    int num=0;
                    for (auto item:string2) {
                        if ((item<'0'||item>'9')&&item!='.'){
                            throw Err();
                        }
                        if (item=='.'){
                            num++;
                        }
                    }
                    if (num>=2){
                        throw Err();
                    }
                    tf=(string2[i+1]-'0')*10+string2[i+2]-'0';
                    if (string2[i+3]>='5'){
                        tf++;
                    }
                    break;
                }
                if (string2.size() == i + 1) {//不是.
                    throw Err();
                }
                if (string2.size() == i + 2) {//是.x
                    if (string2[i + 1] > '9' || string2[i + 1] < '0') {
                        throw Err();
                    }
                    tf = (string2[i + 1] - '0') * 10;
                    break;
                }
                if (string2.size() == i + 3) {//是.xx
                    if (string2[i + 1] > '9' || string2[i + 1] < '0' || string2[i + 2] > '9' || string2[i + 2] < '0' ||
                        string2[i + 3] != 0) {
                        throw Err();
                    }
                    tf = (string2[i + 1] - '0') * 10 + string2[i + 2] - '0';
                }
                break;
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
//check_num_letter_
//check_no_quote(
//check_split(
//check_repeat(
//check_kyw_length(
//check(
//check_invisible(//有throw
//check_invisible_(
//Check

//throw

//
//su root sjtu
//
//
//passwd root sjd
//
//passwd 23)4#$r
//
//useradd isjf_S ds 3 dfs


//su root sjtu
//passwd root sjd
//passwd 23)4#$r
//useradd isjf_S ds 3 dfsInvalid
//passwd root 2132@#
//su s)
//su 2*_
//useradd a a 3 4
//su hfsi
//su 2:
//su a 2#
//su a a_
//delete @#
//show finance
//show finance 4
//show finance 1
//show finance 0
//show finance -1
//show finance 1 1
//select a
//import 34 34
//import 2.3 2
//import 1231 32123213
//import 00000023
//import 0000123 032.3
//show
//show finance
//show finance
//show finance
//show finance
//show finance 1
//show finance 0
//log
//show
//report finance
//show finance

//fstream


//su root sjtu
//select a
//modify -price=.
//Invalid
//modify -price=0
//modify -price=0.0
//import 10 0
//Invalid
//import 10 0.00
//Invalid
//show
//
//show


//su root sjtu
//select a
//modify -price=.
//modify -price=0
//modify -price=0.0
//import 10 0
//import 10 0.00
//show


//su root sjtu
//select a
//modify -price=10
//modify -price=10.
//Invalid
//modify -price=.10
//Invalid
//modify -price=0
//Invalid
//modify -price=.
//Invalid
//modify -price=0.0
//Invalid
//modify -price=..
//Invalid
//modify -price=10.0.0
//Invalid
//modify -price=0.00
//Invalid
//modify -price=10
//import 0 10
//Invalid
//import 1 0
//Invalid
//import 1 .
//Invalid
//import 1 .0
//Invalid
//import 1 .00
//Invalid
//import 1 0.00
//Invalid
//import 1 ..
//Invalid
//import 1 0.0.0
//Invalid



//su root sjtu
//select a
//show
//a				0.00	10
//modify -ISBN=b
//show
//b				0.00	10
//buy a 0
//Invalid
//select c
//import 100 100
//buy c 1
//0.00
//show
//b				0.00	10
//c				0.00	99
//modify -ISBN=0
//show
//0				0.00	100
//b				0.00	10
//show
//0				0.00	100
//b				0.00	10
//buy 0 1
//0.00
//show
//0				0.00	99
//b				0.00	10
//buy c 1
//Invalid

//
//su root sjtu
//select c
//import 100 100
//buy c 1
//
//modify -ISBN=0
//show
//0				0.00	100
//b				0.00	10

//buy 0 1
//0.00
//show
//0				0.00	99
//b				0.00	10
//buy c 1
//Invalid