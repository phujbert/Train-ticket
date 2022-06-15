#include <iostream>
#include "jarat.h"
#include "memtrace.h"


//összehasonlító operátor túlterhelése
bool Jarat::operator==(Jarat& a) {
    if (ind_hely == a.getInd_hely() && erk_hely == a.getErk_hely() && a.getInd_ido() == ind_ido) return true;
    return false;
}

//kiíró operátor túlterhelése
std::ostream& operator<<(std::ostream& os,Jarat& j) {
    os << j.getInd_hely() << " - "
    << j.getErk_hely() << " , "
    << j.getInd_ido() << " - "
    << j.getErk_ido() << " "
    << j.getVonat()->getVszam();
    return os;
}

//segédfüggvény a járatok fájlba történő kiírásához
void Jarat::kiment(std::ostream& os) {
    os << ind_hely << " " << erk_hely << " "
    << ind_ido.getOra() << " " << ind_ido.getPerc() << " "
    << erk_ido.getOra() << " " << erk_ido.getPerc() << " "
    << vonat->getVszam() << " " << kocsik.getMeret();
    for (size_t i = 0; i < kocsik.getMeret(); i++) os << " " << kocsik[i];
    os << std::endl;
}
