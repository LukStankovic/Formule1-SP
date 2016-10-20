/**
 * @brief Funkce pro praci s jezdcem
 * @file main.cpp
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "cas.h"
#include "../jezdec/jezdec.h"
#include "../funkce/funkce.h"

void naplnitCas(ifstream &f, vector<TCAS> &casy){

    int i = 0;
    int velikost;
    string radek;

    while(getline(f,radek)){
        int poc_bunek = pocetBunekVRadku(';',radek);
        vector<string> radek_v_csv(poc_bunek);

        rozdelitString(';',radek,radek_v_csv);

        casy.at(i).cas = radek_v_csv.at(0);
        casy.at(i).id_j = stoi(radek_v_csv.at(1));
        casy.at(i).cas_ms = 0;

        // PREPOCET NA MS


        i++;
    }
    // NA ZACATEK SOUBORU
    f.clear();
    f.seekg(0);
}


void vypisCasu(vector<TCAS> const &casy, int pocet){

    cout << endl << "VYPIS VSECH CASU" << endl;
    cout << "------------------" << endl << endl;

    cout << setw(10) << " ID JEZDCE " << " | " << setw(15) << " CAS " << " | " <<  setw(15) << " CAS V MS " << endl;
    for(int i = 0; i < 57; i++)
        cout << "-";
    cout << endl;


    try{
        for(int i = 0; i < pocet; i++)
            cout << setw(11) << casy.at(i).id_j << " | " << setw(15) << casy.at(i).cas << " | " <<  setw(15) <<  casy.at(i).cas_ms << " |"<< endl;
        cout << endl;
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }

}
