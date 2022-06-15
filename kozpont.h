#ifndef KOZPONT_H
#define KOZPONT_H

#include "jegy.h"
#include <fstream>
#include "jarat.h"
#include "memtrace.h"


class Kozpont {
    Tomb<Vonat> vonatok;
    Tomb<Jarat> jaratok;
public:
    bool ujVonat(std::string vszam);
    
    bool ujJarat();
    bool ujJarat(const char* f);

    bool jegyBekerdez();
    bool jaratListaz(std::string ih, std::string eh);
    void vonatListaz();
    void vonat_kiment();
    void jarat_kiment();
    Tomb<Vonat>* getVonatok() { return &vonatok; }
    Tomb<Jarat>* getJaratok() { return &jaratok; }

};




#endif