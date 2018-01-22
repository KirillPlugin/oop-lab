#include <iostream>
#include <string>
#include <memory>
#include <sstream>
#include "MyVector.h"

using namespace std;

string to_string(int i){
    stringstream str;
    str << i;
    return str.str();
}

myVector<string> Create(size_t size){
    myVector<string> v(size);
    for (size_t i = 0; i < size; i++)
        v[i] = "Create " + to_string(i);
    v.push_back("Create " + to_string(size));
    return v;
}

int main()
{
    myVector<string> v1(6);
    for (int i = 0; i < 6; i++){
        v1[i] = "string " + to_string(i+1);
    }
    myVector<string> v2;
    v2 = v1;
    cout << "~~~~~Vector 1~~~~~~\n";
    for (int i = 0; i < 5; i++) {
        cout << v1[i] << endl;
    }
    for (int i = 6; i < 10; i++){
        v2.push_back("Other string " + to_string(i+1));
    }
    cout << "~~~~~Vector 2~~~~~~\n";
    try{
        for (int i = 0; i < 10; i++) {
            cout << v2.at(i) << endl;
        }
    }
    catch (out_of_range ex) {
        cout << ex.what();
    }
    myVector<string> v3(2);
    v3 = Create(5);
    myVector<string> v4 = move(Create(4));
    v4.resize(3);
    cout << "~~~~~Vector 4~~~~~~\n";
    for (int i = 0; i < 3; i++) {
        cout << v4[i] << endl;
    }
    myVector<string> v5;
    v5.reserve(3);
    for (int i = 0; i < 3; i++){
        v5.push_back(to_string(i));
    }
    cout << "~~~~~Vector 5~~~~~~\n";
    for (int i = 0; i < 3; i++) {
        cout << v5[i] << endl;
    }
}
