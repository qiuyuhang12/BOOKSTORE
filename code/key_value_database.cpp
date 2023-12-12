//
// Created by qiuyuhang on 23-12-1.
//
#include "key_value_database.h"
#include <iostream>
#include <cstring>

template<class T>
void array_insert(T *array, int size_before_insert, int position) {
    for (int i = size_before_insert; i > position; --i) {
        array[i] = array[i - 1];
    }
}

template<class T>
void array_delete(T *array, int size_before_delete, int position) {
    for (int i = position; i < size_before_delete; ++i) {
        array[i] = array[i + 1];
    }
}

Key_value_database::Key_value_database() = default;

Key_value_database::~Key_value_database() = default;

void Key_value_database::initialize() {
    file.open(dictionary_file_name, std::ios::out | std::ios::in | std::ios::binary);
    if (!file) {//目标文件存在吗？
        //新建目标文件：
        file.open(dictionary_file_name, std::ios::out | std::ios::binary);
        file.close();
        open(dictionary_file_name);
        Dictionary dictionary;
        for (int i = 0; i < block_num; ++i) {
            file.write(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        }
        file.close();

    }
    if (!file) {
        std::cerr << dictionary_file_name << " when init" << std::endl;
        exit(1);
    }
    file.close();

    file.open(catalog_file_name, std::ios::out | std::ios::in | std::ios::binary);
    if (!file) {//目标文件存在吗？
        file.open(catalog_file_name, std::ios::out | std::ios::binary);
        file.close();
        open(catalog_file_name);
        //新建目标文件：
        Stack stack;
        Catalog catalog;
        for (int i = 0; i < stack_num; ++i) {
            stack.stack[i] = (stack_num - i) * sizeof(Dictionary);
        }
        stack.end = stack_num - 1;
        file.write(reinterpret_cast<char *>(&stack), sizeof(Stack));
        file.write(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
        file.close();
    }
    if (!file) {
        std::cerr << catalog_file_name << " when init" << std::endl;
        exit(1);
    }
    file.close();

//    open(catalog_file_name);
//    Stack stack;
//    Catalog catalog;
//    for (int i = 0; i < 2 * element_max / merge_value ; ++i) {
//        stack.stack[i] = (2 * element_max / merge_value - i)* sizeof(Dictionary);
//    }
//    stack.end = 2 * element_max / merge_value-1;
//    file.write(reinterpret_cast<char *>(&stack), sizeof(Stack));
//    file.write(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
//    file.close();
//    open(dictionary_file_name);
//    Dictionary dictionary;
//    for (int i = 0; i < 2 * element_max / merge_value + 1; ++i) {
//        file.write(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
//    }
//    file.close();
}

void Key_value_database::open(const std::string &file_name) {
    if (file) {
        file.close();
    }
    file.open(file_name, std::ios::out | std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << file_name << " when open" << std::endl;
        exit(1);
    }
}

void Key_value_database::find(const char key[65]) {
    std::vector<unsigned long long> maybe;
    bool find = find_blocks(key, maybe);
    if (!find) {
        std::cout << "null" << std::endl;
        return;
    }
    Dictionary dictionary;
    if (maybe.size() == 1) {
        open(dictionary_file_name);
        file.seekg(maybe[0]);
        file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        file.close();
        bool flag = false;
        for (int i = 0; i < dictionary.num; ++i) {
            int cmp = strcmp(key, dictionary.key[i]);
            if (cmp < 0) {
                break;
            }
            if (i==178){
                std::cout<<"h";
            }
            if (cmp == 0) {
                flag = true;
                std::cout << dictionary.value[i] << ' ';
            }
        }
        if (flag)std::cout << std::endl;
        else std::cout << "null\n";
        return;
    }
    if (maybe.size() == 2) {
        open(dictionary_file_name);
        file.seekg(maybe[0]);
        file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        for (int i = 0; i < dictionary.num; ++i) {
            int cmp = strcmp(key, dictionary.key[i]);
            if (cmp < 0) {
                break;
            }
            if (cmp == 0) {
                for (int j = i; j < dictionary.num; ++j) {
                    std::cout << dictionary.value[j] << ' ';
                }
                break;
            }
        }
        file.seekg(maybe[1]);
        file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        for (int i = 0; i < dictionary.num; ++i) {
            int cmp = strcmp(key, dictionary.key[i]);
            if (cmp < 0) {
                break;
            }
            if (cmp == 0) {
                std::cout << dictionary.value[i] << ' ';
            }
        }
        std::cout << '\n';
        file.close();
        return;
    }
    if (maybe.size() > 2) {
        open(dictionary_file_name);
        auto iter = maybe.begin();
        file.seekg(*iter);
        iter++;
        file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        for (int i = 0; i < dictionary.num; ++i) {
            int cmp = strcmp(key, dictionary.key[i]);
            if (cmp < 0) {
                break;
            }
            if (cmp == 0) {
                for (int j = i; j < dictionary.num; ++j) {
                    std::cout << dictionary.value[j] << ' ';
                }
                break;
            }
        }
        while (iter != maybe.end() - 1) {
            file.seekg(*iter);
            iter++;
            file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
            for (int i = 0; i < dictionary.num; ++i) {
                std::cout << dictionary.value[i] << ' ';
            }
        }
        file.seekg(*iter);
        file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        for (int i = 0; i < dictionary.num; ++i) {
            int cmp = strcmp(key, dictionary.key[i]);
            if (cmp < 0) {
                break;
            }
            if (cmp == 0) {
                std::cout << dictionary.value[i] << ' ';
            }
        }
        std::cout << '\n';
        file.close();
        return;
    }
}

bool Key_value_database::find_blocks(const char key[65], std::vector<unsigned long long> &maybe_have) {
//    if (block_have == 0)return false;
    open(catalog_file_name);
    file.seekg(begin_of_catalog);
    Catalog catalog;
    file.read(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
    if (catalog.used_block == 0)return false;

    for (int i = 0; i < catalog.used_block; ++i) {
        int cmp = strcmp(key, catalog.key[i]);
        if (i == 0) {
            cmp = 1;
        }
        if (cmp < 0) {
//            if (i == 0) {
//                break;
//            }
            maybe_have.push_back(catalog.address[i - 1]);
            break;
        } else if (cmp == 0) {
//            if (i == 0){
//                maybe_have.push_back(catalog.address[0]);
//                continue;
//            }
            maybe_have.push_back(catalog.address[i - 1]);
            if (i == catalog.used_block - 1) {
                maybe_have.push_back(catalog.address[i]);
            }
        } else {
            if (i == catalog.used_block - 1) {
                maybe_have.push_back(catalog.address[i]);
            }
        }
    }
    if (maybe_have.empty()) {
        file.close();
        return false;
    }
    file.close();
    return true;
}

//long long Key_value_database::find_start(char key[65], const long long &begin_block) {}

//long long Key_value_database::find_end(char key[65], const long long &begin_block) {}

//void
//Key_value_database::find_start_and_end(char key[65], long long &begin, long long &end, const long long &begin_block) {}

unsigned long long Key_value_database::find_blocks_hard(const char key[65], int value, int &x_th_in_dictionary) {
//    if (block_have == 0) {
//        x_th_in_dictionary = 0;
//        return -1;
//    }
    open(catalog_file_name);
    file.seekg(begin_of_catalog);
    Catalog catalog;
    file.read(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
    if (catalog.used_block == 0) {
        x_th_in_dictionary = 0;
        return -1ull;
    }
//    int cmp = strcmp(key, catalog.key[0]);
//    if (cmp < 0 || (cmp == 0 && value < catalog.value[0])) {
//        x_th_in_dictionary = 0;
//        return -1ull;
//    }
    for (int i = 0; i < catalog.used_block; ++i) {
        int cmp = strcmp(key, catalog.key[i]);
        if (i == 0) {
            cmp = 1;
        }
        if (cmp < 0) {
            x_th_in_dictionary = i - 1;
            return catalog.address[i - 1];
        }
        if (cmp == 0 && catalog.value[i] > value) {
            x_th_in_dictionary = i - 1;
            return catalog.address[i - 1];
        }
    }
    file.close();
    x_th_in_dictionary = catalog.used_block - 1;
    return catalog.address[catalog.used_block - 1];
}

void Key_value_database::insert(char key[65], int value) {
    //优化！
//    if (num_of_element==0){
//
//        return;
//    }
//    if (value==60){
//        std::cout<<"insert"<<std::endl;
//    }


    int x_th_in_catalog = 0;
    unsigned long long block_address = find_blocks_hard(key, value, x_th_in_catalog);
    open(catalog_file_name);
    Catalog catalog;
//    std::cout<<file.tellg();

    file.seekg(begin_of_catalog);

    file.read(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
//    std::cout<<file.tellg();
//    file.close();
//    open(catalog_file_name);
    if (catalog.num_of_element == 0) {
        block_have++;
        catalog.used_block++;
        catalog.element[0]++;
        catalog.value[0] = value;
        for (int i = 0; i < key_length; ++i) {
            catalog.key[0][i] = key[i];
        }
    } else if (x_th_in_catalog == -1ull) {
        catalog.element[0]++;
        catalog.value[0] = value;
        for (int i = 0; i < key_length; ++i) {
            catalog.key[0][i] = key[i];
        }
    } else {
//        catalog.num_of_element++;
        catalog.element[x_th_in_catalog]++;
    }
    catalog.num_of_element++;
    file.seekp(begin_of_catalog);
    file.write(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
    file.close();
    if (block_address == -1ull) {//只能在第一个块里
        open(dictionary_file_name);
        Dictionary dictionary;
        file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        dictionary.num++;
        for (int j = dictionary.num - 1; j >= 1; --j) {
            dictionary.value[j] = dictionary.value[j - 1];
            std::swap(dictionary.key[j], dictionary.key[j - 1]);
        }
        dictionary.value[0] = value;
//        std::swap(dictionary.key[0],key);
        for (int i = 0; i < key_length; ++i) {
            dictionary.key[0][i] = key[i];
        }
        file.seekp(0);
        file.write(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
        file.close();
        if (dictionary.num > split_value) {
            split(0, x_th_in_catalog);
        }
        return;
    }
    open(dictionary_file_name);
    file.seekg(block_address);
    Dictionary dictionary;
    file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
    for (int i = 0; i < dictionary.num; ++i) {
        int cmp = strcmp(key, dictionary.key[i]);
        if (cmp < 0 || (cmp == 0 && value < dictionary.value[i])) {
//            num_of_element++;
            dictionary.num++;
            for (int j = dictionary.num - 1; j > i; --j) {
                dictionary.value[j] = dictionary.value[j - 1];
                std::swap(dictionary.key[j], dictionary.key[j - 1]);
            }
            dictionary.value[i] = value;
            for (int j = 0; j < key_length; ++j) {
                dictionary.key[i][j] = key[j];
            }
            file.seekp(block_address);
            file.write(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
            file.close();
            if (dictionary.num > split_value) {
                split(block_address, x_th_in_catalog);
            }
            return;
        }
    }
//    num_of_element++;
    dictionary.num++;
    dictionary.value[dictionary.num - 1] = value;
    for (int j = 0; j < key_length; ++j) {
        dictionary.key[dictionary.num - 1][j] = key[j];
    }
    file.seekp(block_address);
    file.write(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
    file.close();
    if (dictionary.num > split_value) {
        split(block_address, x_th_in_catalog);
    }
}


void Key_value_database::delete_(const char key[65], int value) {
    int x_th_in_catalog = 0;
    unsigned long long block_address = find_blocks_hard(key, value, x_th_in_catalog);
    if (block_address == -1ull) {
        return;
    }
    open(dictionary_file_name);
    file.seekg(block_address);
    Dictionary dictionary;
    bool change_first_factor = false;
    bool delete_to_empty = false;
    file.read(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
    for (int i = 0; i < dictionary.num; ++i) {
        int cmp = strcmp(key, dictionary.key[i]);
        if (cmp == 0) {
            if (dictionary.value[i] == value) {
//                num_of_element--;
                dictionary.num--;
                char empty[key_length] = {0};
                std::swap(empty, dictionary.key[i]);
                for (int j = i; j < dictionary.num; ++j) {
                    dictionary.value[j] = dictionary.value[j + 1];
                    std::swap(dictionary.key[j], dictionary.key[j + 1]);
                }
                dictionary.value[dictionary.num] = 0;
                file.seekp(block_address);
                file.write(reinterpret_cast<char *>(&dictionary), sizeof(Dictionary));
                file.close();
                if (dictionary.num == 0) {
                    delete_to_empty = true;
                }

                //改头
                open(catalog_file_name);
                Catalog catalog;
                file.seekg(begin_of_catalog);
                file.read(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
                catalog.num_of_element--;
                catalog.element[x_th_in_catalog]--;
                if (i == 0) {
//                    change_first_factor= true;
                    catalog.value[x_th_in_catalog] = dictionary.value[0];
//                    char new_key[key_length]={0};
                    for (int j = 0; j < key_length; ++j) {
                        catalog.key[x_th_in_catalog][j] = dictionary.key[0][j];
                    }
                }
                file.seekp(begin_of_catalog);
                file.write(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
                file.close();
                if (dictionary.num < merge_value / 2 && catalog.used_block > 1) {
                    merge(block_address, x_th_in_catalog);
                }
                return;
            }
        }
        if (cmp < 0) {
            break;
        }
    }
}


void Key_value_database::merge(unsigned long long block_position_in_dictionary, int x_th_in_catalog) {
    open(catalog_file_name);
    file.seekg(begin_of_catalog);
    Catalog catalog;
    file.read(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
    int l, r;
    bool should_merge = false;
    if (catalog.used_block == 1) {
        return;
    }
    if (x_th_in_catalog == 0) {
        if (catalog.element[x_th_in_catalog] + catalog.element[x_th_in_catalog + 1] < merge_value) {
            l = 0;
            r = 1;
            should_merge = true;
        }
    } else if (x_th_in_catalog == catalog.used_block - 1) {
        if (catalog.element[x_th_in_catalog] + catalog.element[x_th_in_catalog - 1] < merge_value) {
            l = x_th_in_catalog - 1;
            r = x_th_in_catalog;
            should_merge = true;
        }
    } else {
        if (catalog.element[x_th_in_catalog] + catalog.element[x_th_in_catalog - 1] < merge_value) {
            l = x_th_in_catalog - 1;
            r = x_th_in_catalog;
            should_merge = true;
        } else if (catalog.element[x_th_in_catalog] + catalog.element[x_th_in_catalog + 1] < merge_value) {
            l = x_th_in_catalog;
            r = x_th_in_catalog + 1;
            should_merge = true;
        }
    }
    if (!should_merge)return;
    block_have--;
    Stack stack;
    file.seekg(0);
    file.read(reinterpret_cast<char *>(&stack), sizeof(Stack));
    unsigned long long l_address = catalog.address[l], r_address = catalog.address[r];
    if (catalog.element[l]==0){
        catalog.value[l]=catalog.value[r];
        std::swap(catalog.key[l],catalog.key[r]);
    }
    catalog.element[l] += catalog.element[r];

    array_delete(catalog.element, catalog.used_block, r);
    array_delete(catalog.address, catalog.used_block, r);
    array_delete(catalog.value, catalog.used_block, r);
    for (int i = r; i < catalog.used_block; ++i) {
        std::swap(catalog.key[i], catalog.key[i + 1]);
    }
    catalog.used_block--;
    file.seekp(begin_of_catalog);
    file.write(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
    stack.end++;
    stack.stack[stack.end] = r_address;
    file.seekp(0);
    file.write(reinterpret_cast<char *>(&stack), sizeof(Stack));
    file.close();
    open(dictionary_file_name);
    Dictionary dl, dr;
    file.seekg(l_address);
    file.read(reinterpret_cast<char *>(&dl), sizeof(Dictionary));
    file.seekg(r_address);
    file.read(reinterpret_cast<char *>(&dr), sizeof(Dictionary));
    for (int i = 0; i < dr.num; ++i) {
        dl.value[dl.num + i] = dr.value[i];
        std::swap(dl.key[dl.num + i], dr.key[i]);
    }
    dl.num += dr.num;
    file.seekp(l_address);
    file.write(reinterpret_cast<char *>(&dl), sizeof(Dictionary));
    Dictionary empty;
    file.seekp(r_address);
    file.write(reinterpret_cast<char *>(&empty), sizeof(Dictionary));
    file.close();
}

//bool Key_value_database::merge_check() {}

void Key_value_database::split(unsigned long long block_position_in_dictionary, int x_th_in_catalog) {



//
//    std::fstream f0;
//    f0.open(catalog_file_name,std::ios::in|std::ios::out|std::ios::binary);
//    Catalog catalog00;
//    f0.seekg(begin_of_catalog,std::ios::beg);
//    f0.read(reinterpret_cast<char*>(&catalog00), sizeof(Catalog));
//    f0.close();
//    f0.open(dictionary_file_name,std::ios::in|std::ios::out|std::ios::binary);
//    Dictionary dictionary00,dictionary01,dictionary02;
//    f0.read(reinterpret_cast<char*>(&dictionary00), sizeof(Dictionary));
//    f0.read(reinterpret_cast<char*>(&dictionary01), sizeof(Dictionary));
//    f0.read(reinterpret_cast<char*>(&dictionary02), sizeof(Dictionary));
//    f0.close();





    block_have++;
    Stack stack;
    Catalog catalog;
    Dictionary ld, rd;
    open(catalog_file_name);
    file.read(reinterpret_cast<char *>(&stack), sizeof(Stack));
    file.read(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
    file.close();
    open(dictionary_file_name);
    file.seekg(block_position_in_dictionary);
    file.read(reinterpret_cast<char *>(&ld), sizeof(Dictionary));
    unsigned long long empty_block_position = stack.stack[stack.end];
    stack.stack[stack.end] = 0;
    stack.end--;
    int mid_value = ld.value[ld.num / 2];//!
//    char mid_key[key_length]=ld.key[ld.num/2+1];
    char mid_key[key_length] = {'\0'};
    for (int i = 0; i < ld.num - ld.num / 2; ++i) {
        mid_key[i] = ld.key[ld.num / 2][i];
    }
    for (int i = 0; i < ld.num - ld.num / 2; ++i) {
        rd.value[i] = ld.value[i + ld.num / 2];
        ld.value[i + ld.num / 2] = 0;
        std::swap(ld.key[i + ld.num / 2], rd.key[i]);
    }
    rd.num = ld.num - ld.num / 2;
    ld.num = ld.num / 2;
    array_insert(catalog.element, catalog.used_block, x_th_in_catalog);
    array_insert(catalog.address, catalog.used_block, x_th_in_catalog);
    array_insert(catalog.value, catalog.used_block, x_th_in_catalog);
    for (int i = catalog.used_block; i > x_th_in_catalog+1; --i) {
        std::swap(catalog.key[i], catalog.key[i - 1]);
    }
    catalog.value[x_th_in_catalog + 1] = mid_value;
    catalog.element[x_th_in_catalog] = ld.num;
    catalog.element[x_th_in_catalog + 1] = rd.num;
    catalog.address[x_th_in_catalog + 1] = empty_block_position;
    std::swap(catalog.key[x_th_in_catalog + 1], mid_key);
    catalog.used_block++;
    file.seekp(block_position_in_dictionary);
    file.write(reinterpret_cast<char *>(&ld), sizeof(Dictionary));
    file.seekp(empty_block_position);
    file.write(reinterpret_cast<char *>(&rd), sizeof(Dictionary));
    file.close();
    open(catalog_file_name);
    file.write(reinterpret_cast<char *>(&stack), sizeof(Stack));
    file.write(reinterpret_cast<char *>(&catalog), sizeof(Catalog));
    file.close();

//
//    std::fstream f;
//    f.open(catalog_file_name,std::ios::in|std::ios::out|std::ios::binary);
//    Catalog catalog0;
//    f.seekg(begin_of_catalog,std::ios::beg);
//    f.read(reinterpret_cast<char*>(&catalog0), sizeof(Catalog));
//    f.close();
//    f.open(dictionary_file_name,std::ios::in|std::ios::out|std::ios::binary);
//    Dictionary dictionary0,dictionary1,dictionary2;
//    f.read(reinterpret_cast<char*>(&dictionary0), sizeof(Dictionary));
//    f.read(reinterpret_cast<char*>(&dictionary1), sizeof(Dictionary));
//    f.read(reinterpret_cast<char*>(&dictionary2), sizeof(Dictionary));
//    f.close();


    //是否要合并一下？
    if (catalog.used_block == 2) {
        return;
    }
    if (x_th_in_catalog == 0) {
        if (catalog.element[x_th_in_catalog + 1 + 1] < merge_value / 2) {
            merge(catalog.address[x_th_in_catalog + 2], x_th_in_catalog + 2);
        }
    } else if (x_th_in_catalog == catalog.used_block - 2) {
        if (catalog.element[x_th_in_catalog - 1] < merge_value / 2) {
            merge(catalog.address[x_th_in_catalog - 1], x_th_in_catalog - 1);
        }
    } else {
        if (catalog.element[x_th_in_catalog + 1 + 1] < merge_value / 2) {
            merge(catalog.address[x_th_in_catalog + 2], x_th_in_catalog + 2);
        }
        if (catalog.element[x_th_in_catalog - 1] < merge_value / 2) {
            merge(catalog.address[x_th_in_catalog - 1], x_th_in_catalog - 1);
        }
    }


}

//bool Key_value_database::split_check() {}
