#include "Writer.h"

 using namespace std;

 void writer::Open() {
    out.open(name, ofstream::app);
 }

 void writer::Close() {
    out.close();
 }

 void writer::Print(string &line) const {
    out << line;
 }
