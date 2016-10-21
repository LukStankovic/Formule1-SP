/**
 * @brief Funkce pro praci s jezdcem
 * @mainpage STA0445 - Formule 1
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>


#include "jezdec.h"
#include "../funkce/funkce.h"


using namespace std;

/// NAPLNI STRUKTURU TJEZDEC DATY Z CSV SOUBORU
void naplnitJezdce(ifstream &f, vector<TJEZDEC> &jezdci, vector<TCAS> &casy, int pocet_casu){

    int i = 0;
    string radek;

    while(getline(f,radek)){
        /// ZJISTENI POCET BUNEK V CSV SOUBORU A NASLEDNE VYTVORENI VEKTORU
        int poc_bunek = pocetBunekVRadku(';',radek);
        vector<string> radek_v_csv(poc_bunek);

        /// ROZDELI RADEK DO BUNEK
        rozdelitString(';',radek,radek_v_csv);

        jezdci.at(i).id_j = stoi(radek_v_csv.at(2));
        jezdci.at(i).jmeno = radek_v_csv.at(0);
        jezdci.at(i).prijmeni = radek_v_csv.at(1);

        /// VKLADANI ZAJETYCH KOL ZE STRUKTURY TCAS A ZJISTOVANI NEJLEPSIHO, NEJHORSIHO A PRUMERNEHO CASU

        unsigned nejmensi_cas = 100000000, nejvetsi_cas = 0;
        unsigned long celkovy = 0;

        for(int j = 0; j < pocet_casu; j++){
            if(casy.at(j).id_j == jezdci.at(i).id_j){

                jezdci.at(i).poc_kol++;
                celkovy += casy.at(j).cas_ms;

                if(casy.at(j).cas_ms < nejmensi_cas)
                    nejmensi_cas = casy.at(j).cas_ms;

                if(casy.at(j).cas_ms > nejvetsi_cas)
                    nejvetsi_cas = casy.at(j).cas_ms;
            }

        }

        if(nejvetsi_cas != 0)
            jezdci.at(i).nejpomalejsi = nejvetsi_cas;
        else
            jezdci.at(i).nejpomalejsi = 0;

        if(nejmensi_cas != 100000000)
            jezdci.at(i).nejrychlejsi = nejmensi_cas;
        else
            jezdci.at(i).nejrychlejsi = 0;

        if(jezdci.at(i).poc_kol != 0)
            jezdci.at(i).prumerny = celkovy/jezdci.at(i).poc_kol;
        else
            jezdci.at(i).prumerny = 0;

        i++;
    }
    /// PRESUNE "KURZOR" ZPET NA ZACETEK SOUBORU
    f.clear();
    f.seekg(0);
}


/// VYPISE SEZNAM JEZDCU DO KONZOLE
void vypisJezdcu(vector<TJEZDEC> const &jezdci, int pocet){

    cout << endl << "VYPIS VSECH JEZDCU" << endl
                 << "------------------" << endl << "/Pro spravne zobrazeni je nutne si zvetsit okno konzole!/" << endl << endl;


    cout << " ID " << " | " << setw(10) << " JMENO " << " | " <<  setw(10) << " PRIJMENI " << " | " << "KOL |" << setw(13) << " NEJLEPSI |"<< setw(13) << " NEJHORSI |"<< setw(13) << " PRUMERNY"<<endl;
    for(int i = 0; i < 78; i++)
        cout << "-";
    cout << endl;


    try{
        for(int i = 0; i < pocet; i++){
            cout << setw(4) << jezdci.at(i).id_j << " | " << setw(10) << jezdci.at(i).jmeno << " | " <<  setw(10) <<  jezdci.at(i).prijmeni << " |" << setw(4) << jezdci.at(i).poc_kol << " |"
            << setw(11) << msNaCas(jezdci.at(i).nejrychlejsi) << " |" << setw(11) << msNaCas(jezdci.at(i).nejpomalejsi) << " |" << setw(13) << msNaCas(jezdci.at(i).prumerny) << endl;
        }

        cout << endl;
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }

}
