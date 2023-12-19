//
// Created by qiuyuhang on 23-12-16.
//
#include "blog_system.h"

void IV() {
    std::cout << "Invalid\n";
}
void file_init(std::fstream &file, const char *name){
    file.open(name,std::ios::in|std::ios::out|std::ios::binary);
    if (!file){
        file.open(name,std::ios::out|std::ios::binary);
        file.close();
        file.open(name,std::ios::in|std::ios::out|std::ios::binary);
    }
}
void file_init2(std::fstream &file, const char *name){
    file.open(name,std::ios::in|std::ios::out|std::ios::binary);
    if (!file){
        file.open(name,std::ios::out|std::ios::binary);
        file.close();
        file.open(name,std::ios::in|std::ios::out|std::ios::binary);
        int a=0;
        file.write(reinterpret_cast<char*>(&a),sizeof(int ));
    }
}
Blog_system::Blog_system() {
    file_init2(count_file,"count_file");
    file_init(log_file,"log_file");
    file_init(report_employee_file,"report_employee_file");
    file_init(report_finance_file,"report_finance_file");

}//todo记得count写个0
void Blog_system::show_finance(int count){
    if (count==-1){
        count_file.seekg(-long(sizeof(Count)),std::ios::end);
        Count count1;
        count_file.write(reinterpret_cast<char*>(&count1), sizeof(Count));
        std::cout<<"+ "<<count1.money_in<<" - "<<count1.money_out<<'\n';
    }
    if (count==0){
        std::cout<<'\n';
    }
    int num=0;
    count_file.seekg(std::ios::beg);
    count_file.read(reinterpret_cast<char*>(&num), sizeof(int));
    if (num<count){
        IV();
        return;
    }
    count_file.seekg((count-1)*long(sizeof(Count)));
    Count count1;
    count_file.write(reinterpret_cast<char*>(&count1), sizeof(Count));
    std::cout<<"+ "<<count1.money_in<<" - "<<count1.money_out<<'\n';
}

void Blog_system::log(){
    //todo:-1了seek还有用吗
}

void Blog_system::report_finance(){}

void Blog_system::report_employee(){}

void Blog_system::add_count(Count &count){
    int num=0;
    count_file.seekg(std::ios::beg);
    count_file.read(reinterpret_cast<char*>(&num), sizeof(int));
    num++;
    count_file.seekp(std::ios::beg);
    count_file.write(reinterpret_cast<char*>(&num), sizeof(int));
    count_file.seekg(-1*long(sizeof(Count)),std::ios::end);
    Count last;
    count_file.read(reinterpret_cast<char*>(&last), sizeof(Count));
    last.money_out+=count.money_out;
    last.money_in+=count.money_in;
    count_file.seekp(std::ios::end);
    count_file.write(reinterpret_cast<char*>(&last), sizeof(Count));
}
void Blog_system::add_finance(Finance_table&financeTable){
    report_finance_file.seekp(std::ios::end);
    report_finance_file.write(reinterpret_cast<char*>(&financeTable), sizeof(Finance_table));
}
void Blog_system::add_employee(Employee_table&employeeTable){
    report_employee_file.seekp(std::ios::end);
    report_employee_file.write(reinterpret_cast<char*>(&employeeTable), sizeof(Employee_table));
}
void Blog_system::add_log(Do_table&doTable){
    log_file.seekp(std::ios::end);
    log_file.write(reinterpret_cast<char*>(&doTable), sizeof(Do_table));
}