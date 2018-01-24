#ifndef WRITER_H_INCLUDED
#define WRITER_H_INCLUDED

#include <fstream>
#include <iostream>

using namespace std;

class writer{
public:
    writer(const char* _name, ofstream &_out) :
        name(_name), out(_out) {};

    void Open();

    void Close();

    void Print(string &) const;

private:
    string name;
    ofstream &out;
};


#endif // WRITER_H_INCLUDED
