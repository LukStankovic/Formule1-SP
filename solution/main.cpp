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
 *         - Dale se zde nachazi funkce pro vypsani menu, ktere je v nekonecnem cyklu z duvodu vraceni do menu
 *  \mainpage Semestralni prace k 1. semestru, Lukas Stankovic (STA0445), Formule 1
 */

using namespace std;

int main(int argc, char** argv){

/**
 OTEVRENI SOUBORU
 ----------------
    - adresy k souborum jsou v parametrech fce main (argv)
        - prvni parametr (argv[1]) je adresa CSV souboru s jezdci
        - druhy parametr (argv[2])  je adresa CSV souboru s casy
*/

    if(!IsCSV(argv[1])){
        cout << endl << " * Chyba pri nacitani souboru s jezdci!" << endl
        << " * Nazev chyby: Soubor neni ve formatu CSV." << endl
        << " / POZNAMKA: Prvni argument je CSV soubor s jezdci, druhy s casy! /" << endl;
        return -1;
    }

    ifstream fPilots(argv[1]);

    if(fPilots.fail()){
        cout << endl << " * Chyba pri nacitani souboru s jezdci!" << endl
        << " * Nazev chyby: " << strerror(errno) << "." << endl
        << " / POZNAMKA: Prvni argument je CSV soubor s jezdci, druhy s casy! /" << endl;
        return -1;
    }


    if(!IsCSV(argv[2])){
        cout << endl << " * Chyba pri nacitani souboru s casy!" << endl
        << " * Nazev chyby: Soubor neni ve formatu CSV." << endl
        << " / POZNAMKA: Prvni argument je CSV soubor s jezdci, druhy s casy! /" << endl;
        return -1;
    }

    ifstream fRounds(argv[2]);

    if(fRounds.fail()){
        cout << endl << " * Chyba pri nacitani souboru s casy! *" << endl
        << " * Nazev chyby: " << strerror(errno) << ". *" << endl
        << " / POZNAMKA: Prvni argument je CSV soubor s jezdci, druhy s casy! /" << endl;
        return -1;
    }

    int numberOfPilots = CountLines(fPilots);
    int numberOfRounds = CountLines(fRounds);

/**
 VYTVORENI VEKTORU STRKUTUR S CASY A JEZDCI
 ------------------------------------------
    - vector<Round> allRounds(numberOfRounds)
        - obsahuje struktury Round - ma velikost podle poctu kol v CSV souboru
    - vector<Pilot> allPilots(numberOfPilots)
        - obsahuje struktury Pilot - ma velikost podle poctu jezdcu v CSV soubru
    - Po vytvoreni vektoru se prace se soubory ukonci, protoze uz je nebudeme potrebovat
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
    - Tridi podle nejrychlejsiho casu
    - Tridi pomoci bublinkoveho algoritmu - Insertion sort
    - Vlastni pretizene funkce Sort (pro strukturu Pilot a Round)
*/
   Sort(allPilots);
   Sort(allRounds);

/**
 VLOZENI PORADI
 --------------
    - Poradi k jezdcum a casum se vklada zde az po setrizeni zaznamu
    - Pretizena funkce AddPosition pro strukturu Pilot a Round
*/
    AddPosition(allPilots);
    AddPosition(allRounds);

/**
 VYKRESLENI MENU
 ---------------
    - Vykresli kompletni menu
    - Obsahuje i zadavani volby
    - Menu se vypisuje dokud uzivatel neukonci program pomoci volby 0
*/

    PrintMenu(allPilots,allRounds,numberOfPilots,numberOfRounds);

    return 0;
}
