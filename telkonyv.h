#ifndef TELKONYV_H_INCLUDED
#define TELKONYV_H_INCLUDED
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include "memtrace.h"
#include "rekord.h"
#include "string.h"


class Telkonyv {
    Rekord* rekordok; //Rekordokból álló tömb, amit dinamikusan kezelünk
    int rekordokSzama; //aktuális méret

public:

Telkonyv() {rekordok = NULL; rekordokSzama = 0;} //default konstruktor

int getRekordokSzama(){return rekordokSzama;}

//A tesztesetek miatt kellett bevezetnem, így egyszerûbb a mainben Testeket használni
std::string getPhoneNumOfAnElement(int index){return rekordok[index].getTelszam();}

//Jelenleg felesleges, de visszaadja a paraméterként kapott indexű elemet a telefonkönyvből
//Rekord& getRekordByIndex(int index) {return rekordok[index];}


void addRekord (const Rekord& ujrekord); //Új elem hozzáadása a telkönyvhöz

void printTelkonyv() const; //Kiírja a telkönyv tartalmát

void keresByVeznev (const std::string keresendo, const int choice); //Kereső funkció: veznevre, kernevre, telszamra, településre lehet keresni részsztringek alapján is

void torolByVeznev (const std::string keresendo); //Egy nem kívánt elem törlése

void modositVeznev (const std::string keresendo); //Módosítja a vezetéknevét az adott elemnek

void modositKernev (const std::string keresendo); //Módosítja a keresztnevét az adott elemnek

void modositTelszam (const std::string keresendo); //Módosítja a telefonszamat az adott elemnek

void modositCim (const std::string keresendo); //Módosítja a címét az adott elemnke

void saveToFile(); //Fileba menti a telefonkönyvet, soronként lesz egy rekord

void readFromFile(); //Fileból soronként olvassa a rekordokat

~Telkonyv(){delete[] rekordok;}

};

#endif // TELKONYV_H_INCLUDED
