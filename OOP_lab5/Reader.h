#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED

#include <fstream>
#include <exception>

using namespace std;

class reader{
public:
    reader(ifstream &_in) :
        in(_in) {};

    uint64_t Read() const;

    bool IsFileEnd() const;

    void Close();
private:
    ifstream &in;
};



#endif // READER_H_INCLUDED
