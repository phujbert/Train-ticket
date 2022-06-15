#ifndef IDO_H
#define IDO_H

#include <iostream>
#include "memtrace.h"



class Ido {
    int ora, perc;
public:
    Ido(int ora = 0, int perc = 0) : ora(ora), perc(perc) {}
    int getOra() { return ora; }
    int getPerc() { return perc; }
    bool operator==(Ido& i);

};
std::ostream& operator<<(std::ostream& os, Ido& i);




#endif