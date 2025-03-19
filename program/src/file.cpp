#include "file.h"
#include <iostream>

bool pass::check(std::vector<int> &p){
    if(p == password)
        return true;
    return false;
}