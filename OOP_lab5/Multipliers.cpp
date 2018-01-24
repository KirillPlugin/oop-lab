#include "Multipliers.h"

#include <math.h>
#include <memory>
#include <sstream>
#include <iostream>

using namespace std;

multipliers::multipliers() {};

multipliers::~multipliers() {};

void multipliers::ChangeNum(const uint64_t& _num) {
    if (num != _num)
        change_num = true;
    num = _num;
}

void multipliers::Factorization() {
    factor_data.clear();
    uint64_t x = num;
    while (x % 2 == 0){
        factor_data.push_back(2);
        x /= 2;
    }
    uint64_t n = sqrt(num);
    for (uint64_t i = 3; i <= n; i += 2){
        while (x % i == 0){
            factor_data.push_back(i);
            x /= i;
        }
    }
    if (x != 1)
        factor_data.push_back(x);
    change_num = false;
}

uint64_t multipliers::Get_Num_From_Factorization() {
    if (change_num)
        Factorization();
    uint64_t n = 1;
    for (auto& i : factor_data)
        n *= i;
    return n;
}

string multipliers::Get_Factorization_Str() {
    if (change_num)
        Factorization();
    string line;
    line += To_String(num) + " = ";
    for (auto& i : factor_data){
        line += To_String(i) + " * ";
    }
    line.pop_back();
    line.pop_back();
    return line;
}

vector<uint64_t> multipliers::Get_Factorization() {
    if (change_num)
        Factorization();
    return factor_data;
}

string multipliers::To_String(const uint64_t& n) const {
    stringstream str;
    str << n;
    return str.str();
}
