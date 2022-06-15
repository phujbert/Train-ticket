#ifndef TOMB_H
#define TOMB_H

#include "memtrace.h"

template<typename T>
class Tomb {
    T *adat;
    size_t meret;
public:
    Tomb(size_t meret = 0) : adat(new T[meret]), meret(meret) {}
    Tomb(const Tomb<T>& t);
    void ujElem(T& uj_ertek);
    size_t getMeret() { return meret; }
    T& operator[](size_t idx) { return adat[idx]; }
    Tomb<T>& operator=(const Tomb<T>& t);
    ~Tomb() { delete[] adat; }
};

//új elem hozzáadása a tömbhöz
//lefoglal egy új memóriateröletet eggyel nagyobb méretű tömbhöz
//átmásolja az adatokat, hozzáadja az újat
//majd felszabadítja a régi memóriaterületet
template<typename T>
void Tomb<T>::ujElem(T& uj_ertek) {
    T *uj_adat = new T[meret + 1];
    for (size_t i = 0; i < meret; i++) uj_adat[i] = adat[i];
    uj_adat[meret] = uj_ertek;
    delete[] adat;
    adat = uj_adat;
    meret++;
}

//másoló operátor túlterhelése
template<typename T>
Tomb<T>& Tomb<T>::operator=(const Tomb<T>& t) {
    if (this != &t) {
        delete[] adat;
        meret = t.meret;
        adat = new T[meret];
        for (size_t i = 0; i < meret; i++) adat[i] = t.adat[i];
    }
    return *this;
}

template<typename T>
Tomb<T>::Tomb(const Tomb<T>& t) {
    meret = t.meret;
    adat = new T[meret];
    for (size_t i = 0; i < meret; i++) adat[i] = t.adat[i];
}




#endif