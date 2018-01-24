#include <iostream>
#include "MultipliersWorker.h"
#include <cstdlib>
#include <exception>

int main(int argc, char* argv[]) {
    if (argc == 4) {
        ifstream fin(argv[1]);
        ofstream fout(argv[2]);
        if (!fin.good() || !fout.good()){
            cerr << "I/O file error";
            exit(1);
        }
        reader r(fin);
        writer w(argv[2], fout);
        worker work(r, w, atoi(argv[3]));
        work.Go();
    }
}
