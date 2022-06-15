#include <iostream>
#include <string>
#include <fstream>
#include "gtest_lite.h"
#include "kozpont.h"
#include "vonat.h"
#include "jegy.h"
#include "jarat.h"
#include "memtrace.h"
#include <sstream>


#define TESZT 0

void vonatot_hozzaad(Kozpont* kozpont);
void vonatot_beolvas(Kozpont* kozpont);
void jaratot_hozzaad(Kozpont* kozpont);
void jaratot_kiir(Kozpont *kozpont);
void jegy_vasarlas(Kozpont *kozpont);

namespace cp {      //cross-platform getline
 
  std::istream& getline(std::istream& is, std::string& str) {
    std::getline(is, str);
    if (str.size() && *str.rbegin() == '\r')
        str.erase(str.size()-1);
    return is;
  }
}       

int main() {

#if TESZT == 1

    Kozpont kozpont;

    Tomb<Jarat> *jaratok = kozpont.getJaratok();
    Tomb<Vonat> *vonatok = kozpont.getVonatok();


    //vonat_beolvas() függvény tesztelése
    //megnézi, hogy a legutoljára beolvasott vonat tényleg az elvárt e
    TEST(Vonatok, beolvas) {
        vonatot_beolvas(&kozpont);
        int meret = vonatok->getMeret();
        std::string elvart = "Alpokalja";
        EXPECT_TRUE(elvart == vonatok->operator[](meret - 1).getVszam());
        EXPECT_EQ(meret, 3);
    } END

    //jarat_beolvas() függvény tesztelése
    //megnézi, hogy a legutoljára beolvasott járat tényleg az elvárt e
    TEST(Jaratok, beolvas) {
        kozpont.ujJarat("jaratok.txt");
        int meret = jaratok->getMeret();
        Jarat elvart("Debrecen", "Pecs", Ido(16, 0), Ido(18, 15));
        EXPECT_TRUE(elvart == jaratok->operator[](meret - 1));
        EXPECT_EQ(2, meret);
    } END

    //egy vonat hozzáadását teszteli
    //megnézi, hogy a vonatok tömb legutolsó eleme tényleg a hozzáadott vonat
    TEST(Vonatok, hozzaad) {
        std::string id = "RABAIC";
        kozpont.ujVonat(id);
        size_t meret = vonatok->getMeret();
        std::string aktual = vonatok->operator[](meret - 1).getVszam();
        EXPECT_EQ(id, aktual) << "Nem jol adott hozza vonatot" << std::endl;
    } END

    //egy járat hozzáadását teszteli
    //meghívja az újJarat() függvényt és beolvas a szabványos bemenetre irányított txt fájlból egy járatot
    //megnézi, hogy a jaratok tömb legutolsó eleme tényleg a hozzáadott járat
    TEST(Jaratok, hozzaad) {
        Jarat elvart("Gyor", "Tata", Ido(10, 0), Ido(8, 4));
        kozpont.ujJarat();
        int meret = jaratok->getMeret();
        EXPECT_TRUE(elvart == jaratok->operator[](meret - 1));
        Tomb<Kocsi> *kocsik = jaratok->operator[](meret - 1).getKocsik();
        size_t kszam = kocsik->getMeret();
        for (size_t i = 0; i < kszam; i++) {
            Kocsi l(i + 1, 0);
            EXPECT_TRUE(l == kocsik->operator[](i));
        }
        std::string id = "RABAIC";
        EXPECT_TRUE(id == jaratok->operator[](meret - 1).getVonat()->getVszam());
    } END

    //a jegyvásárlást teszteli
    //létrehoz egy új járatot kocsikkal együtt, hozzáadja ezt a jaratok tömbhöz
    //létrehoz egy új jegyet az előbbi járattal, majd erre meghívja a foglalas() függvényt
    //megnézi, egyezik e a lefoglalt jegy az elvárttal
    TEST(Jegyek, vasarlas) {
        Jarat jar("Szhely", "Sztg", Ido(16, 0), Ido(17, 10));
        Kocsi k(20, 20);
        jar.ujKocsi(k);
        Kocsi p(15, 4);
        jar.ujKocsi(p);
        jaratok->ujElem(jar);
        int meret = jaratok->getMeret();
        Jegy elvart(&(jaratok->operator[](meret - 1)), 2, 5);
        Jegy aktual(&(jaratok->operator[](meret - 1)));
        aktual.foglalas();
        EXPECT_TRUE(aktual == elvart);
    } END

#endif

#if TESZT == 0

Kozpont kozpont;

vonatot_beolvas(&kozpont);
kozpont.ujJarat("jaratok.txt");

int n;

do {
    std::cout <<
    "1. Vonat hozzaadasa\n" <<
    "2. Jarat hozzaadasa\n" <<
    "3. Vonatok kilistazasa\n" <<
    "4. Jaratok kilistazasa\n" <<
    "5. Jegy vasarlas\n" <<
    "6. Kilepes" << std::endl;
    std::cin >> n;
    switch (n) {
        case 1: 
            vonatot_hozzaad(&kozpont); break;
        case 2:
            jaratot_hozzaad(&kozpont); break;
        case 3: kozpont.vonatListaz(); break;
        case 4: 
            jaratot_kiir(&kozpont); break;
        case 5:
            jegy_vasarlas(&kozpont); break;
    }
} while (n != 6);

kozpont.jarat_kiment();
kozpont.vonat_kiment();

#endif

return 0;
}

//bekér egy vonatszámot, ezzel meghívja az ujVonat függvényt
void vonatot_hozzaad(Kozpont* kozpont) {
    std::cout << "Adjon meg egy vonatszamot:";
    std::string vszam;
    std::cin >> vszam;
    if (kozpont->ujVonat(vszam) == true) std::cout << "Sikeres vonat hozzaadas!" << std::endl;
    else std::cout << "Sikertelen vonat hozzaadasa!" << std::endl;
}

//meghívja az ujJarat függvényt
void jaratot_hozzaad(Kozpont* kozpont) {
    if (kozpont->ujJarat() == true) std::cout << "Sikeres jarat hozzaadas!" << std::endl;
    else std::cout << "Sikertelen jarat hozzaadasa!" <<std::endl;
}

//bekéri az indulési és érkezési állomást, ezekkel meghívja a jaratListaz függvényt
void jaratot_kiir(Kozpont *kozpont) {
    std::string ih, eh;
    std::cout << "Adja meg az indulasi allomast: ";
    std::cin >> ih;
    std::cout << "Adja meg az erkezesi allomast: ";
    std::cin >> eh;
    if (!(kozpont->jaratListaz(ih, eh))) std::cout << "Nincsenek itt kozlekedo jaratok!" << std::endl;
}

//meghívja a jegyBekerdez függvényt
void jegy_vasarlas(Kozpont *kozpont) {
    if (kozpont->jegyBekerdez() == true) std::cout << "Sikeres jegy vasarlas!" << std::endl;
    else std::cout << "Sikertelen jegy vasarlas!" <<std::endl;
}

//megnyitja a vonatok.txt fájlt és beolvassa onnan a vonatokat, és ezekkel meghívja az ujVonat függvényt
void vonatot_beolvas(Kozpont* kozpont) {
    std::ifstream fajl;
    fajl.open("vonatok.txt");
    std::string vszam;
    while (cp::getline(fajl, vszam)) {
        kozpont->ujVonat(vszam);
    }
    fajl.close();
}

