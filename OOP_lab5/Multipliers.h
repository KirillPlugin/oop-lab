#ifndef MULTIPLIERS_H_INCLUDED
#define MULTIPLIERS_H_INCLUDED

#include <vector>
#include <string>

class multipliers{
private:
    std::string To_String (const uint64_t&) const;
public:
    multipliers(const uint64_t& _num) : num(_num), change_num(true) {};
    multipliers();
    ~multipliers();

    void ChangeNum(const uint64_t&);
    void Factorization();

    uint64_t Get_Num_From_Factorization();
    std::string Get_Factorization_Str();
    std::vector<uint64_t> Get_Factorization();
private:
    std::vector<uint64_t> factor_data;
    uint64_t num = 1;
    bool change_num = false;
};

#endif
