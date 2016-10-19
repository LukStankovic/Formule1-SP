#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>

#include <unistd.h>

#include "includes/jezdec/jezdec.h"
#include "includes/funkce/funkce.h"

/**
 * @brief Hlavni soubor programu
 * @file main.cpp
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */




using namespace std;

int main()
{


    ifstream f_jezdci("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupniData/jezdci.csv");

    if((f_jezdci.fail())){
        cout << "Chyba pri nacitani souboru! Chyba: " << strerror(errno) << endl;
        return 0;
    }




    return 0;
}
