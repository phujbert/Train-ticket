#ifndef kOCSI_H
#define KOCSI_H

#include <iostream>
#include "memtrace.h"


class Kocsi {
    int max_hely;
    int foglalt;
public:
    Kocsi() {}
    Kocsi(int max, int foglalt = 0) : max_hely(max), foglalt(foglalt) {}
    int getMax_hely() { return max_hely; }
    int getFoglalt() { return foglalt; }
    void setFoglalt(int f) { foglalt = f; }
    bool operator==(const Kocsi& a);
};

std::ostream& operator<<(std::ostream& os, Kocsi& k);



#endif