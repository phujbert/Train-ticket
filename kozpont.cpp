#include "kozpont.h"
#include "memtrace.h"


//új járat hozzáadása
//bekéri a felhasználótól a járat adatait, ha olyan jaratot akar felvenni a felhasználó
//ami már létezik akkor hibaüzenetet ír ki és false-al tér vissza
//a vonat megadásánál addig kér be adatot amíg a felhasználó nem ad meg az adatbázisban lévő vonatot,
//ehhez segítségül kilistázza a vonatokat
//ezek után bekéri a kocsik adatait
//végül létrehoz egy új járatot és hozzáadja a járatok tömbhöz
bool Kozpont::ujJarat() {
    std::string ih, eh, vszam;
    int iiperc, iiora, eiperc, eiora;
    std::cout << "Adja meg az indulasi allomast: ";
    std::cin >> ih;
    std::cout << "Adja meg az erkezsi allomast: ";
    std::cin >> eh;
    std::cout << "Adja meg az indulasi orat: ";
    std::cin >> iiora;
    std::cout << "Adja meg az indulasi percet: ";
    std::cin >> iiperc;
    std::cout << "Adja meg az erkezesi orat: ";
    std::cin >> eiora;
    std::cout << "Adja meg az erkezesi percet: ";
    std::cin >>eiperc;

    Ido ii(iiora, iiperc); Ido ei(eiora, eiperc);
    Jarat tmp(ih, eh, ii, ei);

    for (size_t i = 0; i < jaratok.getMeret(); i++) {
        if (jaratok[i] == tmp) {
            std::cout << "Letezik mar ilyen jarat!" << std::endl;
            return false;
        }
    }

    bool joszam = false;
    do {
        std::cout << "Adjon meg egy letezo vonatszamot!" << std::endl << "A vonatok:" << std::endl;
        vonatListaz();
        std::cin >> vszam;

        for (size_t j = 0; j < vonatok.getMeret(); j++) {
            if (vonatok[j].getVszam() == vszam) {
                tmp.setVonat(&(vonatok[j]));
                joszam = true;
            }
        }
    } while (joszam == false);

    std::cout << "Adja meg a kocsik szamat: ";
    int kocsi_db, mh; std::cin >> kocsi_db;
    for (int k = 0; k < kocsi_db; k++) {
        std::cout << "Adja meg a " << k << ". kocsi max helyeinek szamat: ";
        std::cin >> mh;
        Kocsi kocsi(mh);
        tmp.ujKocsi(kocsi);
    }
    jaratok.ujElem(tmp);
    return true;
}

//az ujJarat függvény túlterhelése
//a szabványos bemenet helyett megnyitja a paraméterként átadott fájlt és abból olvassa be az adatokat
bool Kozpont::ujJarat(const char* f) {
    std::ifstream fajl;
    fajl.open(f);
    std::string ih, eh, vszam;
    int iiperc, iiora, eiperc, eiora;
    while (fajl >> ih) {
        fajl >> eh >> iiora >> iiperc >> eiora >> eiperc >> vszam;
        Ido ii(iiora, iiperc); Ido ei(eiora, eiperc);
        Jarat tmp(ih, eh, ii, ei);

        for (size_t i = 0; i < vonatok.getMeret(); i++)
            if (vonatok[i].getVszam() == vszam) tmp.setVonat(&(vonatok[i]));

        int kocsi_db, mh, fh;
        fajl >> kocsi_db;
        for (int j = 0; j < kocsi_db; j++) {
            fajl >> mh >> fh;
            Kocsi kocsi(mh, fh);
            tmp.ujKocsi(kocsi);
        }
        jaratok.ujElem(tmp);
    }
    

    fajl.close();
    return true;
}


//Paraméterkén átvesz egy stringet (ez a vonatszám), majd ezzel létrehoz egy új vonatot
//Mielőtt ezt hozzáadja a vonatok tömbhöz még eltárolja egy tömbben, hogy a járatokhoz melyik vonatok tartoznak
//ez azért fontos mert amikor hozzáadja az új vonatot akkor teljesen új memóriaterületet foglal a teljes tömbnek
//vagyis a járatok vonat pointere rossz helyre fog mutatni
//a vonat hozzáadása után ezt frissíti a segédtömb használatával
bool Kozpont::ujVonat(std::string vszam) {

    for (size_t i = 0; i < vonatok.getMeret(); i++) {
        if (vonatok[i].getVszam() == vszam) {
            return false;
        }
    }
    Vonat v(vszam);

    Tomb<std::string> v_az;
    for (size_t i = 0; i < jaratok.getMeret(); i++) {
        std::string v = jaratok[i].getVonat()->getVszam();
        v_az.ujElem(v);
    }

    vonatok.ujElem(v);

    for (size_t j = 0; j < v_az.getMeret(); j++) {
        for (size_t k = 0; k < vonatok.getMeret(); k++)
            if (vonatok[k].getVszam() == v_az[j]) jaratok[j].setVonat(&(vonatok[k]));
    }


    return true;
}


//végigmegy a vonatok tömbbjén és kilistázza a azt a szabványos kimenetre
void Kozpont::vonatListaz() {
    std::cout << "Vonatok:" << std::endl;
    for (size_t i = 0; i < vonatok.getMeret(); i++) {
        std::cout << vonatok[i] << std::endl;
    }
}

//végogmegy a jaratok tömbön és kilistázza a paraméterként megadott adatok alapján a megfelelő járatokat
//ha talál legalább egy ilyet akkor true-val tér vissza, egyébként false a visszatérési értéke
bool Kozpont::jaratListaz(std::string ih, std::string eh) {
    bool van_ilyen = false;

    for (size_t i = 0; i < jaratok.getMeret(); i++) {
        if (ih == jaratok[i].getInd_hely() && eh == jaratok[i].getErk_hely()) {
            std::cout << jaratok[i] << std::endl;
            van_ilyen = true;
        }

    }
    return van_ilyen;
}

//bekérdezi a felhasználótól az adatokt a jegyvásárláshoz
//Először bekéri az indulási és érkezési állomást majd ezek alapján kilistázza a megfelelő járatokat, ha nincs egy se új adatokat kér be
//majd bekéri az indulási időt, ismét addig amíg nem talál egyezést
//létrehoz egy temporális járatot a bekérdezett adatokkal
//létrehoz egy Jegy objektumot a tmp járattal
//meghívja rá a foglalás függvényt, ha ez sikeres akkor kimenti a jegyet a jegy.txt-be és true-val tér vissza
//ha nem akkor false-al tér vissza
bool Kozpont::jegyBekerdez() {

    std::string ih, eh;

    do {
        std::cout << "Adja meg az indulasi allomast: ";
        std::cin >> ih;
        std::cout << "Adja meg az erkezesi allomast: ";
        std::cin >> eh;
    } while (!(this->jaratListaz(ih, eh)));

    bool van_ilyen = false;
    int iiperc, iiora;
    Jarat tmp;
    do {
        std::cout << "Adja meg az indulasi orat: ";
        std::cin >> iiora;
        std::cout << "Adja meg az indulasi percet: ";
        std::cin >> iiperc;
        Ido ii(iiora, iiperc);

        for (size_t i = 0; i < jaratok.getMeret(); i++) {
            if (ih == jaratok[i].getInd_hely() && eh == jaratok[i].getErk_hely() && ii == jaratok[i].getInd_ido()) {
                tmp = jaratok[i];
                van_ilyen = true;
            }
        }
    } while (van_ilyen == false);
    Jegy jegy(&tmp);
    if (jegy.foglalas() == true) {
        jegy.ment();
        std::cout << "Megkapta a jegyet!" << std::endl;
        return true;
    }
    return false;
}

//megnyitja a vonatok.txt fájlt és kiírja oda a vonatokat
void Kozpont::vonat_kiment() {
    std::ofstream fajl;
    fajl.open("vonatok.txt");
    for (size_t i = 0; i < vonatok.getMeret(); i++) {
        fajl << vonatok[i] << std::endl;
    }
    fajl.close();
}

//megnyitja a jaratok.txt fájlt és kiírja oda a járatokat
void Kozpont::jarat_kiment() {
    std::ofstream fajl;
    fajl.open("jaratok.txt");
    for (size_t i = 0; i < jaratok.getMeret(); i++) {
        jaratok[i].kiment(fajl);
    }
    fajl.close();
}

