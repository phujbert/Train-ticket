#ifndef VONAT_H
#define VONAT_H

#include <string>
#include <iostream>
#include "memtrace.h"


class Vonat {
    std::string vonatszam;
public:
    Vonat() {}
    Vonat(std::string s) : vonatszam(s) {}
    std::string& getVszam() { return vonatszam; }

};

std::ostream& operator<<(std::ostream& os, Vonat& v);


#endif