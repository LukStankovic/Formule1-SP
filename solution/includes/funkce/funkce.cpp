/**
 * @brief Funkce pro praci s jezdcem
 * @file main.cpp
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "../jezdec/jezdec.h"

using namespace std;

void rozdelitString(char delic, string retezec,vector<string>& pole){

    int delka_retezce = retezec.length();
    int index_minuly_delic = 0;
    int poc_bunek = 0;

    if(retezec[delka_retezce] != ';')
        retezec += ";";

    try{
        for(int i = 0; i < delka_retezce+1; i++){

            if(retezec[i] == delic){

                for(int k = index_minuly_delic; k < i; k++)
                    pole.at(poc_bunek) += retezec[k];

                index_minuly_delic = i+1;
                poc_bunek++;
            }

        }
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }

}

int pocetBunekVRadku(char delic, string retezec){

    int pocet = 0;

    for(int i = 0; i < retezec.length(); i++)
        if(retezec[i] == delic)
            pocet++;

    return pocet+1; // +1 kvuli posledni bunce

}

int pocetZaznamu(ifstream &f){
    int pocet = 0;
    string radek;

    while(getline(f,radek)){
        pocet++;
    }
    // NA ZACATEK SOUBORU
    f.clear();
    f.seekg(0);

    return pocet;
}
