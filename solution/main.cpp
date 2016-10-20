#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#include "includes/funkce/funkce.h"
#include "includes/jezdec/jezdec.h"
#include "includes/cas/cas.h"

/**
 * @brief Hlavni soubor programu
 * @file main.cpp
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */

using namespace std;


int main(){
    int volba;

    ifstream f_jezdci("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupnidata/jezdci.csv");

    if(!(f_jezdci.is_open())){
        cout << "Chyba pri nacitani souboru s jezdci! Chyba: " << strerror(errno) << endl;
        return 0;
    }

    ifstream f_casy("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupnidata/casy.csv");

    if(!(f_casy.is_open())){
        cout << "Chyba pri nacitani souboru s casy! Chyba: " << strerror(errno) << endl;
        return 0;
    }


    int pocet_jezdcu = pocetZaznamu(f_jezdci);
    int pocet_casu = pocetZaznamu(f_casy);



    vector<TCAS> casy(pocet_casu);
    naplnitCas(f_casy,casy);

    vector<TJEZDEC> vsichni(pocet_jezdcu);
    naplnitJezdce(f_jezdci,vsichni,casy,pocet_casu);





    cout << "1 - Vypis vsech jezdcu | 2 - vypis casu" << endl;
    for (int i = 0; i < 50; i++)
        cout << "-";
    cout << endl;
    cout << "Vase volba: ";
    cin >> volba;

    switch(volba){
        case 1:{
            vypisJezdcu(vsichni,pocet_jezdcu);
        }break;
        case 2:{
            vypisCasu(casy,pocet_casu);
        }

    }




    return 0;
}
