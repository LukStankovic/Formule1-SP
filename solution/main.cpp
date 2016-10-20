#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "includes/funkce/funkce.h"
#include "includes/jezdec/jezdec.h"

/**
 * @brief Hlavni soubor programu
 * @file main.cpp
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */

using namespace std;


int main(){


    ifstream f_jezdci("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupnidata/jezdci.csv");

    if(!(f_jezdci.is_open())){
        cout << "Chyba pri nacitani souboru! Chyba: " << strerror(errno) << endl;
        return 0;
    }


     int pocet_jezdcu = pocetZaznamu(f_jezdci);


    vector<TJEZDEC> vsichni(pocet_jezdcu);


    naplnitJezdce(f_jezdci,vsichni);
    vypisJezdcu(vsichni,pocet_jezdcu);


    return 0;
}
