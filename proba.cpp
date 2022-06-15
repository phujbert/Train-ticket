#include <fstream>
#include <iostream>
#include "jarat.h"


//a szabvanyos bemenetrol olvas be
Jarat jaratBeolvas() {
    std::string ih, eh;
    int iiperc, iiora, eiperc, eiora;
    std::cin >> ih; std::cin >> eh; std::cin >> iiora; std::cin >> iiperc; std::cin >> eiora; std::cin >>eiperc;
    Ido ii(iiora, iiperc); Ido ei(eiora, eiperc);
    Jarat tmp(ih, eh, ii, ei);
    return tmp;
}

//fajlbol olvas be
//Mit csinal?
//  
Jarat jaratBeolvas(std::fstream& fajl) {
    
}

void ujJarat(const Jarat& j) {

}
