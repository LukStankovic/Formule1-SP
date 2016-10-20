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


#include "jezdec.h"
#include "../funkce/funkce.h"


using namespace std;

void naplnitJezdce(ifstream &f, vector<TJEZDEC> &jezdci, vector<TCAS> &casy, int pocet_casu){

    int i = 0;
    int velikost;
    string radek;

    while(getline(f,radek)){
        int poc_bunek = pocetBunekVRadku(';',radek);
        vector<string> radek_v_csv(poc_bunek);

        rozdelitString(';',radek,radek_v_csv);

        jezdci.at(i).id_j = stoi(radek_v_csv.at(2));
        jezdci.at(i).jmeno = radek_v_csv.at(0);
        jezdci.at(i).prijmeni = radek_v_csv.at(1);

        // POCET KOL

        for(int j = 0; j < pocet_casu; j++){
            if(casy.at(j).id_j == jezdci.at(i).id_j)
                jezdci.at(i).poc_kol++;
        }




        i++;
    }
    // NA ZACATEK SOUBORU
    f.clear();
    f.seekg(0);
}



void vypisJezdcu(vector<TJEZDEC> const &jezdci, int pocet){

    cout << endl << "VYPIS VSECH JEZDCU" << endl;
    cout << "------------------" << endl << endl;

    cout << " ID " << " | " << setw(15) << " JMENO " << " | " <<  setw(15) << " PRIJMENI " << " | " <<  setw(15) << " ZAJETYCH KOL " << endl;
    for(int i = 0; i < 57; i++)
        cout << "-";
    cout << endl;


    try{
        for(int i = 0; i < pocet; i++)
            cout << setw(4) << jezdci.at(i).id_j << " | " << setw(15) << jezdci.at(i).jmeno << " | " <<  setw(15) <<  jezdci.at(i).prijmeni << " |" << setw(13) << jezdci.at(i).poc_kol << " |"<< endl;
        cout << endl;
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }

}
