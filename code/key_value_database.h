//
// Created by qiuyuhang on 23-12-1.
//

#ifndef INC_2074_KEY_VALUE_DATABASE_H
#define INC_2074_KEY_VALUE_DATABASE_H

#include <string>
#include <fstream>
#include <vector>

const int stack_num = 1000;
const int block_num = 1000;
const int block_size = 400;
const int key_length = 65;//key长度（以\0结尾）
//栈类
struct Stack {
    int end = 0;
    unsigned long long stack[stack_num] = {0};
};
//目录类
struct Catalog {
    int num_of_element = 0;//库中元素数
    int used_block = 0;
    int element[block_num] = {0};
    unsigned long long address[block_num] = {0};
    char key[block_num][65] = {'\0'};
    int value[block_num] = {0};
};
//块类
struct Dictionary {
    int num = 0;
    char key[block_size][65] = {};
    int value[block_size] = {0};
};

class Key_value_database {
//private:
public:
    int element_max=100000;//最多多少元素
//    int element_max=500;//最多多少元素
    int num_of_block = 0;//块总数
//    long long begin_of_block=4000;//?
//    long long end_of_catalog=4000;//?
    unsigned long long end_of_dictionary = 0;
    unsigned long long head_of_stack = 0;
    unsigned long long end_of_stack = 0;
    unsigned long long begin_of_catalog = sizeof(Stack);//目录开始位置
    int block_have=0;//用到的块数
    int catalog_1_length = 77;//ll+64+1+int
    int pair_length = 69;//ll+64+1+int
//    int key_length = 65;//key长度（以\0结尾）
    int value_length = 8;
    //以元素数为单位
//    int max_of_a_block=350;//
    int merge_value = 275;//合并临界
    int split_value = 325;//分裂临界
//    int merge_value = 4;//合并临界
//    int split_value = 8;//分裂临界
    std::string catalog_file_name = "catalog";//目录文件名
    std::string dictionary_file_name = "dictionary";
    std::fstream file;

//    bool merge_check();
//    bool split_check();
    bool find_blocks(const char key[65], std::vector<unsigned long long> &maybe_have);//找到可能有key的块,保存地址（字典文件中）
    unsigned long long find_blocks_hard(const char key[65], int value, int &);//找到可能有key-value的块,保存地址（字典文件中）
//    long long find_start(char key[65],const long long &begin_block);
//    long long find_end(char key[65],const long long &begin_block);
//    void find_start_and_end(char key[65],long long &begin,long long &end,const long long &begin_block);
    void split(unsigned long long, int);//块位置(在字典中位置,在目录中顺序)
    void merge(unsigned long long, int);//块位置(在字典中位置,在目录中顺序)
    int change_num_temporary = 0;

    void open(const std::string &);
//    bool operator<(const char [65],const char [65]);
//public:
    Key_value_database();

    ~Key_value_database();

    void initialize();//建立或检查文件
    void insert(char [65], int);//插入
    void delete_(const char [65], int);//maybe not found
    void find(const char [65]);//找到
};

#endif //INC_2074_KEY_VALUE_DATABASE_H