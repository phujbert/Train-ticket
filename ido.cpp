#include <iostream>
#include <iomanip>
#include "ido.h"
#include "memtrace.h"


//kiíró operátor túlterhelése
std::ostream& operator<<(std::ostream& os, Ido& i) {
    os << std::setfill('0') << std::setw(2) << std::right << i.getOra()
    << ":"
    << std::setfill('0') << std::setw(2) << std::right << i.getPerc();
    return os;
}

//összehasonlító operátor túlterhelése
bool Ido::operator==(Ido& i) {
    if (ora == i.getOra() && perc == i.getPerc()) return true;
    return false;
}
