/**
 * @brief Funkce pro praci s jezdcem
 * @file main.cpp
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */
#include <fstream>
using namespace std;

int pocetZaznamu(ifstream &f){
    int pocet = 0;
    string radek;

    while(getline(f,radek)){
        pocet++;
    }

    return pocet;
}
