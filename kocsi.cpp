#include <iostream>
#include "kocsi.h"
#include "memtrace.h"


//kiír egy kocsit
std::ostream& operator<<(std::ostream& os, Kocsi& k) {
    os << k.getMax_hely() << " " << k.getFoglalt();
    return os;
}

//összehasonlító operátor túlterhelése
bool Kocsi::operator==(const Kocsi& a) {
    return max_hely == a.max_hely && foglalt == a.foglalt;
}

