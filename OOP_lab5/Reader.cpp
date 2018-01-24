#include "Reader.h"

using namespace std;

bool reader::IsFileEnd() const {
    return in.eof();
}

uint64_t reader::Read() const {
    uint64_t x;
    in >> x;
    return x;
}

void reader::Close() {
    in.close();
}
