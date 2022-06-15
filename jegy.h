#ifndef JEGY_H
#define JEGY_H

#include <iostream>
#include "jarat.h"
#include "memtrace.h"


class Jegy {
    Jarat* jarat;
    int kocsiszam, hely;
public:
    Jegy(Jarat* j) : jarat(j) {}
    Jegy(Jarat* j, int k, int h) : jarat(j), kocsiszam(k), hely(h) {}
    Jarat* getJarat() { return jarat; }
    int getKszam() { return kocsiszam; }
    int getHely() { return hely; }
    bool foglalas();
    void ment();
    bool operator==(const Jegy& a);
};

#endif