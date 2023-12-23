//
// Created by qiuyuhang on 23-12-16.
//
#include "blog_system.h"
#include <iomanip>

std::ostream &operator<<(std::ostream &out, Price price1) {
    if (price1.float_ / 10 == 0) {
        out << price1.integer << '.' << 0 << price1.float_;
        return out;
    }
    out << price1.integer << '.' << price1.float_;
    return out;
}

std::ostream &operator<<(std::ostream &out, Book &book) {
    out << book.ISBN << '\t' << book.BookName << '\t' << book.Author << '\t' << book.Keyword << '\t' << book.price
        << '\t' << book.storage << '\n';
    return out;
}

Price operator+(Price &lhs, Price &rhs) {
    Price tmp;
    tmp.integer = lhs.integer + rhs.integer;
    tmp.float_ = lhs.float_ + rhs.float_;
    tmp.integer += tmp.float_ / 100;
    tmp.float_ %= 100;
    return tmp;
}

Price operator-(Price &lhs, Price &rhs) {
    Price tmp;
    tmp.integer = lhs.integer - rhs.integer;
    tmp.float_ = lhs.float_ - rhs.float_;
    if (tmp.float_ < 0) {
        tmp.float_ += 100;
        tmp.integer -= 1;
    }
    return tmp;
}

Price operator*(long long &lhs, Price &rhs) {
    Price tmp;
    tmp.integer = lhs * rhs.integer;
    tmp.float_ = lhs * rhs.float_;
    tmp.integer += tmp.float_ / 100;
    tmp.float_ %= 100;
    return tmp;
}

Price &Price::operator+=(Price &rhs) {
    this->float_ += rhs.float_;
    this->integer += rhs.integer;
    integer += float_ / 100;
    float_ %= 100;
    return *this;
}

Price &Price::operator-=(Price &rhs) {
    this->float_ -= rhs.float_;
    this->integer -= rhs.integer;
    integer += float_ / 100;
    float_ %= 100;
    return *this;
}

void IV() {
    std::cout << "Invalid\n";
}

void file_init(std::fstream &file, const char *name) {
    file.open(name, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        file.open(name, std::ios::out | std::ios::binary);
        file.close();
        file.open(name, std::ios::in | std::ios::out | std::ios::binary);
    }
}

void file_init2(std::fstream &file, const char *name) {
    file.open(name, std::ios::in | std::ios::out | std::ios::binary);
    if (!file) {
        file.open(name, std::ios::out | std::ios::binary);
        file.close();
        file.open(name, std::ios::in | std::ios::out | std::ios::binary);
        int a = 0;
        file.write(reinterpret_cast<char *>(&a), sizeof(int));
    }
}

Blog_system::Blog_system() {
    file_init2(count_file, "count_file");
    file_init(log_file, "log_file");
    file_init(report_employee_file, "report_employee_file");
    file_init(report_finance_file, "report_finance_file");
}

Count Blog_system::get_last() {
    count_file.seekg(-long(sizeof(Count)), std::ios::end);
    Count count1;
    count_file.read(reinterpret_cast<char *>(&count1), sizeof(Count));
    if (count_file.eof()) {
        count_file.close();
        count_file.open("count_file", std::ios::in | std::ios::out | std::ios::binary);
    }
    return count1;
}

Count Blog_system::get_count(int count) {
    if (count == 0) {
        Count count1;
        return count1;
    }
    count_file.seekg((long) sizeof(int) + (count - 1) * long(sizeof(Count)), std::ios::beg);
    Count count1;
    count_file.read(reinterpret_cast<char *>(&count1), sizeof(Count));
    if (count_file.eof()) {
        count_file.close();
        count_file.open("count_file", std::ios::in | std::ios::out | std::ios::binary);
    }
    return count1;
}

void Blog_system::show_finance(int count) {
    count_file.flush();
    if (count == -1) {
        int num = 0;
        count_file.seekg(0, std::ios::beg);
        count_file.read(reinterpret_cast<char *>(&num), sizeof(int));
        Count count1;
        if (num > 0) {
            count1 = get_last();
        }
        std::cout << "+ " << count1.money_in << " - " << count1.money_out << '\n';
        if (count_file.eof()) {
            count_file.close();
            count_file.open("count_file", std::ios::in | std::ios::out | std::ios::binary);
        }
        return;
    }
    if (count == 0) {
        std::cout << '\n';
        return;
    }
    int num = 0;
    count_file.seekg(0, std::ios::beg);
    count_file.read(reinterpret_cast<char *>(&num), sizeof(int));
    if (num < count) {
        IV();
        return;
    }
    Count count1;
    count1 = get_count(num - count);
    Count last = get_last();
    std::cout << "+ " << last.money_in - count1.money_in << " - " << last.money_out - count1.money_out << '\n';
    if (count_file.eof()) {
        count_file.close();
        count_file.open("count_file", std::ios::in | std::ios::out | std::ios::binary);
    }
}

void Blog_system::log() {
    log_file.flush();
    log_file.seekg(0, std::ios::beg);
    std::cout << std::setw(13 + 2) << "MONEYIN" << " \t" << std::setw(13 + 1) << "MONEYOUT" << " \t" << std::setw(23)
              << "UserID" << " \t" << "                            ACTION" << "\n\n";
    while (!log_file.eof()) {
        Do_table doTable;
        log_file.read(reinterpret_cast<char *>(&doTable), sizeof(Do_table));
        if (log_file.eof()) {
            break;
        }
        std::cout << "|+" << std::setw(13) << doTable.in << "|\t" << "-" << std::setw(13) << doTable.out << "|\t"
                  << std::setw(33) << doTable.UserID << "|\t" << doTable.do_ << "\n";
    }
    log_file.close();
    log_file.open("log_file", std::ios::out | std::ios::in | std::ios::binary);
}

void Blog_system::report_finance() {
    report_finance_file.flush();
    report_finance_file.seekg(0, std::ios::beg);
    std::cout << '\n' << std::setw(13) << "MONEYIN" << "\t" << std::setw(17) << "MONEYOUT" << "\t" << std::setw(23)
              << "UserID" << "\t" << std::setw(10) << "                 ACTION" << "\t" << std::setw(18) << "ISBN"
              << std::setw(20) << "Quality" << "\n\n";
    while (!report_finance_file.eof()) {
        Finance_table financeTable;
        report_finance_file.read(reinterpret_cast<char *>(&financeTable), sizeof(Finance_table));
        if (report_finance_file.eof()) {
            break;
        }
        std::cout << "|+" << std::setw(13) << financeTable.money_in << "|\t" << "-" << std::setw(13)
                  << financeTable.money_out << "|\t" << std::setw(33) << financeTable.UserID << "|\t" << std::setw(10)
                  << financeTable.do_ << "|\t" << std::setw(23) << financeTable.ISBN << '|' << std::setw(10)
                  << financeTable.Quality << "\n";
    }
    report_finance_file.close();
    report_finance_file.open("report_finance_file", std::ios::out | std::ios::in | std::ios::binary);
}

void Blog_system::report_employee() {
    report_employee_file.flush();
    report_employee_file.seekg(0, std::ios::beg);
    std::cout << '\n' << std::setw(20) << "UserID" << "\t" << "                          ACTION" << "\n\n";

    while (!report_employee_file.eof()) {
        Employee_table employeeTable;
        report_employee_file.read(reinterpret_cast<char *>(&employeeTable), sizeof(Employee_table));
        if (report_employee_file.eof()) {
            break;
        }
        std::cout << '|' << std::setw(33) << employeeTable.UserID << "|\t" << employeeTable.do_ << "\n";
    }
    report_employee_file.close();
    report_employee_file.open("report_employee_file", std::ios::out | std::ios::in | std::ios::binary);
}

void Blog_system::add_count(Count &count) {
    int num = 0;
    count_file.seekg(0, std::ios::beg);
    count_file.read(reinterpret_cast<char *>(&num), sizeof(int));
    num++;
    count_file.seekp(0, std::ios::beg);
    count_file.write(reinterpret_cast<char *>(&num), sizeof(int));
    Count last;
    if (num != 1) {
        count_file.seekg(-1 * long(sizeof(Count)), std::ios::end);
        count_file.read(reinterpret_cast<char *>(&last), sizeof(Count));
    }
    last.money_out += count.money_out;
    last.money_in += count.money_in;
    count_file.seekp(0, std::ios::end);
    count_file.write(reinterpret_cast<char *>(&last), sizeof(Count));
}

void Blog_system::add_finance(Finance_table &financeTable) {
    report_finance_file.seekp(0, std::ios::end);
    report_finance_file.write(reinterpret_cast<char *>(&financeTable), sizeof(Finance_table));
}

void Blog_system::add_employee(Employee_table &employeeTable) {
    report_employee_file.seekp(0, std::ios::end);
    report_employee_file.write(reinterpret_cast<char *>(&employeeTable), sizeof(Employee_table));
}

void Blog_system::add_log(Do_table &doTable) {
    log_file.seekp(0, std::ios::end);
    log_file.write(reinterpret_cast<char *>(&doTable), sizeof(Do_table));
}
