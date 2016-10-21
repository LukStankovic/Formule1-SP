/**
 * @brief Vseobecne funkce
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

/// ROZDELI STRING PODLE DELICE DO VEKTORU
void rozdelitString(char delic, string retezec,vector<string>& pole){

    int delka_retezce = retezec.length();
    int index_minuly_delic = 0;
    int poc_bunek = 0;

    /// PRIDA DELIC NA KONEC STRINGU PRO SNADNEJSI PRACI SE STRINGEM
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


/// VRATI POCET ZAZNAMU (RADKU) V SOUBORU
int pocetBunekVRadku(char delic, string retezec){

    int pocet = 0;

    for(int i = 0; i < retezec.length(); i++)
        if(retezec[i] == delic)
            pocet++;

    return pocet+1; /// +1 KVULI POSLEDNI BUNCE

}

/// VRATI POCET BUNEK V STRINGU (RADKU), ZJISTUJE POMOCI DELICE
int pocetZaznamu(ifstream &f){
    int pocet = 0;
    string radek;

    while(getline(f,radek)){
        pocet++;
    }
    /// PRESUNTUI "KURZORU" NA ZACATEK SOUBORU
    f.clear();
    f.seekg(0);

    return pocet;
}

/// VRATI CAS V MS ZE STRINGU
unsigned casNaMs(vector<string> cas){
    return ( ( stoi(cas.at(0)) *60 + stoi(cas.at(1)) ) * 1000 + stoi(cas.at(2)) );
}

/// POSILA REFERENCI VEKTORU S CASEM ROZDELENYM NA MINUTY, VTERINY, SETINY
void msNaCasRozdelene(unsigned ms, vector<int> &cas){
    int tmp;

    tmp = ms/1000;

    cas.at(0) = tmp/60;
    cas.at(1) = (tmp%1000) - cas.at(0)*60;
    cas.at(2) = ms%1000;
}

/// VRATI STRING S CASEM VE FORMATU MIN:SEK:SET
string msNaCas(unsigned ms){
    int tmp, minuty = 0, sekundy = 0, setiny = 0;

    tmp = ms/1000;

    minuty = tmp/60;
    sekundy = (tmp%1000) - minuty*60;
    setiny = ms%1000;

    string retezec = to_string(minuty) + ":" + to_string(sekundy) + ":" + to_string(setiny);

    return retezec;
}

/// VYPISE DO KONZOLE MENU
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
