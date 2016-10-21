#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>


#include "includes/funkce/funkce.h"
#include "includes/jezdec/jezdec.h"
#include "includes/cas/cas.h"

/**
 * @brief Hlavni soubor programu
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */

using namespace std;

int main(){


    ifstream f_jezdci("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupnidata/jezdci.csv");
    if(f_jezdci.fail()){
        cout << endl << "Chyba pri nacitani souboru s jezdci! " << "Nazev chyby: " << strerror(errno) << endl;
        return 0;
    }

    ifstream f_casy("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupnidata/casy.csv");
    if(f_casy.fail()){
        cout << endl << "Chyba pri nacitani souboru s casy! " << "Nazev chyby: " << strerror(errno) << endl;
        return 0;
    }


    int pocet_jezdcu = pocetZaznamu(f_jezdci);
    int pocet_casu = pocetZaznamu(f_casy);

    /// VYTVORENI VEKTORU STRUKTUR S CASY A JEZDCI

    vector<TCAS> casy(pocet_casu);
    naplnitCas(f_casy,casy);

    vector<TJEZDEC> vsichni(pocet_jezdcu);
    naplnitJezdce(f_jezdci,vsichni,casy,pocet_casu);

    int volba;

    while(true){

        vypisMenu();

        cout << "Vase volba: ";
        cin >> volba;

        switch(volba){
            case 1:{
                vypisJezdcu(vsichni,pocet_jezdcu);
            }break;
            case 2:{
                vypisCasu(casy,pocet_casu);
            }break;
            case 0:{
                return 0;
            }break;

            default:{
                cout << "Neexistujici polozka menu." << endl;
            }

        }

    }
    return 0;
}
