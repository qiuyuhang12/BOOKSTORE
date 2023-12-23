//
// Created by qiuyuhang on 23-12-1.
//

#ifndef INC_2074_KEY_VALUE_DATABASE_H
#define INC_2074_KEY_VALUE_DATABASE_H

#include <string>
#include <fstream>
#include <vector>

const int stack_num = 500;
const int block_num = 500;
const int block_size = 301;
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
private:
//public:
    int element_max = 100000;//最多多少元素
    int num_of_block = 0;//块总数
    unsigned long long begin_of_catalog = sizeof(Stack);//目录开始位置
    int block_have = 0;//用到的块数
    //以元素数为单位
    int merge_value = 280;//合并临界
    int split_value = 300;//分裂临界
    std::string catalog_file_name = "catalog";//目录文件名
    std::string dictionary_file_name = "dictionary";
    std::fstream file;

    bool find_blocks(const char key[65], std::vector<unsigned long long> &maybe_have);//找到可能有key的块,保存地址（字典文件中）
    unsigned long long find_blocks_hard(const char key[65], int value, int &);//找到可能有key-value的块,保存地址（字典文件中）
    void split(unsigned long long, int);//块位置(在字典中位置,在目录中顺序)
    void merge(unsigned long long, int);//块位置(在字典中位置,在目录中顺序)
    void open(const std::string &);

public:
    Key_value_database();

    explicit Key_value_database(const std::string &filename);

    ~Key_value_database();

    std::vector<unsigned long long> get_th_to_posi_map();

    std::vector<int> get_whole_block(unsigned long long i);

    void initialize(std::string);//建立或检查文件
    void insert(char [65], int);//插入
    void delete_(const char [65], int);//maybe not found
    void find(const char [65]);//找到
    std::vector<int> find_no_output(const char [65]);//找到
};

#endif //INC_2074_KEY_VALUE_DATABASE_H