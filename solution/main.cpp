#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "includes/functions/functions.h"
#include "includes/pilot/pilot.h"
#include "includes/round/round.h"

/** \brief Hlavni soubor programu s funkci main
 *         - Nachazi se zde funkce main, ktera otevira csv soubory s daty.
 *         - CSV soubory se oteviraji pomoci parametru funkce main.
 *               - Prvni parametr je adresa souboru s jezdci
 *               - Druhy parametr je adresa souboru s casy
 *
 * \author Lukas Stankovic - STA0445
 * \mainpage Semestralni prace k 1. semestru, Lukas Stankovic (STA0445), Formule 1
 */

using namespace std;

int main(int argc, char** argv){

/**
 OTEVRENI SOUBORU
 ----------------
    - adresy k souborum jsou v parametrech fce main (argv)
        - prvni parametr je adresa csv souboru s jezdci
        - druhy parametr je adresa csv souboru s casy
*/
    ifstream fPilots(argv[1]);
    if(fPilots.fail()){
        cout << endl << " * Chyba pri nacitani souboru s jezdci!" << endl
        << " * Nazev chyby: " << strerror(errno) << "." << endl
        << " / POZNAMKA: Prvni argument je soubor s jezdci, druhy s casy! /" << endl;
        return 0;
    }

    ifstream fRounds(argv[2]);
    if(fRounds.fail()){
        cout << endl << " * Chyba pri nacitani souboru s casy! *" << endl
        << " * Nazev chyby: " << strerror(errno) << ". *" << endl
        << " / POZNAMKA: Prvni argument je soubor s jezdci, druhy s casy! /" << endl;
        return 0;
    }

    int numberOfPilots = CountLines(fPilots);
    int numberOfRounds = CountLines(fRounds);

/**
 VYTVORENI VEKTORU STRKUTUR S CASY A JEZDCI
 ------------------------------------------
    - vector<TCAS> casy(pocet casu)
        - obsahuje struktury TCAS - ma velikost podle poctu casu v souboru
    - vector<TJEZDEC> vsichni(pocet jezdcu)
        - obsahuje struktury TJEZDEC - ma velikost podle poctu jezdcu v soubru
*/

    vector<Round> allRounds(numberOfRounds);
    FillRounds(fRounds,allRounds);

    vector<Pilot> allPilots(numberOfPilots);
    FillPilots(fPilots,allPilots,allRounds,numberOfRounds);

    fPilots.close();
    fRounds.close();
/**
 SETRIZENI JEZDCU A CASU
 -----------------------
    - Tridi se podle nejrychlejsiho casu pomoci funkce sort s pomocnou funkci bool jezdecJeRychlejsi a bool casJeRychlejsi
*/
   /* sort(allPilots.begin(),allPilots.end(),IsPilotFaster);
    sort(allRounds.begin(),allRounds.end(),IsRoundFaster);
*/
/**
 VLOZENI PORADI
 --------------
    - Poradi k jezdcum se vklada zde az po setrizeni zaznamu
*/
    AddPosition(allPilots);

    PrintMenu(allPilots,allRounds,numberOfPilots,numberOfRounds);

    return 0;
}
