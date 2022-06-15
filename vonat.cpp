#include <iostream>
#include "vonat.h"
#include "memtrace.h"

//kiír egy vonatot
std::ostream& operator<<(std::ostream& os, Vonat& v) {
    os << v.getVszam();
    return os;
}