#include <iostream>
#include <fstream>
#include <vector>

struct pass{
    int (*hash)(int);
    std::vector<int> password;

    pass(int (*hash)(int), const char* file_n):
    hash(hash)
    {
        std::ifstream file;
        file.open(file_n, std::ios::in);
        if(!file.is_open()){
            abort();
        }
        char x;
        while(file >> x){
            password.push_back(x);
            x = 0;
        }
        file.close();
    }

    bool check(std::vector<int> &);
};  