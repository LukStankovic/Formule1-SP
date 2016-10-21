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

    // PRO SNADNEJSI PRACI SE STRINGEM
    if(retezec.back() != delic)
        retezec += delic;

    try{
        for(int i = 0; i < delka_retezce+1; i++){

            if(retezec[i] == delic){

                for(int k = index_minuly_delic; k < i; k++){
                    pole.at(poc_bunek) += retezec[k];

                }

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

unsigned casNaMs(vector<string> cas){
    return ( ( stoi(cas.at(0)) *60 + stoi(cas.at(1)) ) * 1000 + stoi(cas.at(2)) );
}

void msNaCasRozdelene(unsigned ms, vector<int> &cas){
    int tmp;

    tmp = ms/1000;

    cas.at(0) = tmp/60;
    cas.at(1) = (tmp%1000) - cas.at(0)*60;
    cas.at(2) = ms%1000;
}

string msNaCas(unsigned ms){
    int tmp, minuty = 0, sekundy = 0, setiny = 0;

    tmp = ms/1000;

    minuty = tmp/60;
    sekundy = (tmp%1000) - minuty*60;
    setiny = ms%1000;

    string retezec = to_string(minuty) + ":" + to_string(sekundy) + ":" + to_string(setiny);

    return retezec;
}

void vypisMenu(){
    cout << endl;
    for (int i = 0; i < 30; i++)
        cout << "=";
    cout << endl;
    cout << "1  -  Vypis vsech jezdcu " << endl
         << "2  -  Vypis vsech zajetych kol" << endl
         << "0  -  Ukonceni programu" << endl;


    for (int i = 0; i < 30; i++)
        cout << "=";
    cout << endl;
}
