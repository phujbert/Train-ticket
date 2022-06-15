#include <iostream>
#include <fstream>
#include "jegy.h"
#include "memtrace.h"


//végigmegy a jarat kocsik tömbjén, a legelső nem foglalt helyet "legoglalja" (megnöveli a foglalt helyk számát)
//ha az összes kocsiban az összes hely foglalt akkor false-al tér vissza, egyébként true-val 
bool Jegy::foglalas() {
    Tomb<Kocsi> *kocsik = jarat->getKocsik();
    for (size_t i = 0; i < kocsik->getMeret(); i++) {
        int f = kocsik->operator[](i).getFoglalt();
        if (f < kocsik->operator[](i).getMax_hely()) {
            kocsik->operator[](i).setFoglalt(f + 1);
            kocsiszam = i + 1;
            hely = f + 1;
            return true;
        }
    }
    return false;
}

//összehasonlító operátor túlterhelése
bool Jegy::operator==(const Jegy& a) {
    return jarat == a.jarat && kocsiszam == a.kocsiszam && hely == a.hely;
}

//megnyitja a jegy.txt fájlt és kiírja oda a jegy adatait
void Jegy::ment() {
    std::ofstream fajl;
    fajl.open("jegy.txt");
    
    fajl << "Menetjegy:" << std::endl
    << jarat->getInd_hely() << "\t" << jarat->getInd_ido() << std::endl
    << jarat->getErk_hely() << "\t" << jarat->getErk_ido() << std::endl
    << "Vonat: " << jarat->getVonat()->getVszam() << std::endl
    << std::endl
    << "Helyjegy:" << std::endl
    << kocsiszam << ". kocsi, " << hely << ". hely";

    fajl.close();
}

