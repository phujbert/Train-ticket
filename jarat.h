#ifndef JARAT_H
#define JARAT_H

#include <string>
#include <iostream>
#include "vonat.h"
#include "ido.h"
#include "tomb.hpp"
#include "kocsi.h"
#include "memtrace.h"

class Jarat {
    Vonat* vonat;
    std::string ind_hely, erk_hely;
    Ido ind_ido, erk_ido;
    Tomb<Kocsi> kocsik;
public:
    Jarat() {}
    Jarat(const std::string& ih, const std::string& eh, const Ido& ii, const Ido& ei)
        : ind_hely(ih), erk_hely(eh), ind_ido(ii), erk_ido(ei) {}
    void ujKocsi(Kocsi& k) { kocsik.ujElem(k); }
    void setVonat(Vonat* v) { vonat = v; }
    std::string getInd_hely() { return ind_hely; }
    std::string getErk_hely() { return erk_hely; }
    Ido& getInd_ido() { return ind_ido; }
    Ido& getErk_ido() { return erk_ido; }
    Tomb<Kocsi>* getKocsik() { return &kocsik; }
    Vonat* getVonat() { return vonat; }
    bool operator==(Jarat& a);
    void kiment(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os,Jarat& j);


#endif