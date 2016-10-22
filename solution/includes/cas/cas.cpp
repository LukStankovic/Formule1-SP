/**
 * @brief Funkce pro praci s casem
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


/// NAPLNI STRUKTURU DATY ZE SOUBORU
/**
 * @brief Naplni strukturu TCAS datdy z csv souboru
 * @param f              Soubor ze ktereho se nacitaji jezdci
 * @param casy           Vektor struktury TCAS do ktereho se vkladaji casy okruhu
 */
void naplnitCas(ifstream &f, vector<TCAS> &casy){

    int i = 0;
    string radek;

    while(getline(f,radek)){
        /// ZJISTENI POCET BUNEK V CSV SOUBORU A NASLEDNE VYTVORENI VEKTORU
        int poc_bunek = pocetBunekVRadku(';',radek);
        vector<string> radek_v_csv(poc_bunek);

        /// ROZDELI RADEK DO BUNEK
        rozdelitString(';',radek,radek_v_csv);

        casy.at(i).cas = radek_v_csv.at(0);
        casy.at(i).id_j = stoi(radek_v_csv.at(1));
        casy.at(i).id_c = stoi(radek_v_csv.at(2));

        /// PREPOCET ZE STRINGU NA MS
        vector<string> pouze_cas(3);
        rozdelitString(':',radek_v_csv.at(0),pouze_cas);
        casy.at(i).cas_ms = casNaMs(pouze_cas);

        i++;
    }
    /// PRESUNUTI "KURZORU" NA ZACATEK SOUBORU
    f.clear();
    f.seekg(0);
}


/**
 * @brief Vypise seznam okruhu do konzole
 * @param casy         Vektor struktury TCAS ze ktereho se cerpa
 */
void vypisCasu(const vector<TCAS> &casy){

    cout << endl << "VYPIS VSECH CASU" << endl
                 << "----------------" << endl << " / Pro spravne zobrazeni je nutne si zvetsit okno konzole! /" << endl << endl;

    cout << setw(4) << " P " << " | "<< setw(10) << " ID JEZDCE " << " | " << setw(15) << " CAS " << " | " <<  setw(15) << " CAS V MS " << endl;
    for(int i = 0; i < 57; i++)
        cout << "=";
    cout << endl;

    try{
        for(int i = 0; i < casy.size(); i++)
            cout << setw(3) <<  i+1 << "." << " | " << setw(11) << casy.at(i).id_j << " | " << setw(15) << casy.at(i).cas << " | " <<  setw(15) <<  casy.at(i).cas_ms << " |"<< endl;
        cout << endl;
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }

}


/**
 * @brief Vraci pro funkci sort() ktery zaznam je mensi
 * @param a        Struktura TCAS - prvni cas
 * @param b        Struktura TCAS - druhy cas
 * @return Vraci true pokud je a rychlejsi, false pokud je a pomalejsi
 */
bool casJeRychlejsi(const TCAS &a, const TCAS &b){
    /**
        OSETRENI ZDA NEMA CAS 0 MS
            - 0ms znamena prazdna hodnota - jezdec nezajel ani jedno kolo
            - proto ulozime do pomocne promenne velkou hodnotu
    */

    unsigned pom_a, pom_b;

    if(a.cas_ms == 0)
        pom_a = 1000000000;
    else
        pom_a = a.cas_ms;

    if(b.cas_ms == 0)
        pom_b = 1000000000;
    else
        pom_b = b.cas_ms;

    /// POROVNANI
    return pom_a < pom_b;

}
