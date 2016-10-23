#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

#include "includes/funkce/funkce.h"
#include "includes/jezdec/jezdec.h"
#include "includes/cas/cas.h"

/**
 * @brief Hlavni soubor programu
 * @author Lukas Stankovic
 * @mainpage STA0445 - Formule 1
 */

using namespace std;

int main(){
    string adresa_f_jezdci, adresa_f_casy;
/*

    cout << "Zadejte adresu souboru pro nacteni jezdcu: " << endl;
    cin >> adresa_f_jezdci;
*/
    ifstream f_jezdci("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupnidata/jezdci.csv");
    if(f_jezdci.fail()){
        cout << endl << " * Chyba pri nacitani souboru s jezdci!" << endl << " * Nazev chyby: " << strerror(errno) << "." << endl;
        return 0;
    }
/*
    cout << "Zadejte adresu souboru pro nacteni casu: " << endl;
    cin >> adresa_f_casy;
*/
    ifstream f_casy("Skola/VS/1_sem_z/PRG1/SEMESTRALNI_PRACE/sta0445/vstupnidata/casy.csv");
    if(f_casy.fail()){
        cout << endl << " * Chyba pri nacitani souboru s casy! *" << endl << " * Nazev chyby: " << strerror(errno) << ". *" << endl;
        return 0;
    }

    int pocet_jezdcu = pocetZaznamu(f_jezdci);
    int pocet_casu = pocetZaznamu(f_casy);

    /// VYTVORENI VEKTORU STRUKTUR S CASY A JEZDCI
    vector<TCAS> casy(pocet_casu);
    naplnitCas(f_casy,casy);

    vector<TJEZDEC> vsichni(pocet_jezdcu);
    naplnitJezdce(f_jezdci,vsichni,casy,pocet_casu);

    /// SETRIZENI JEZDCU
    sort(vsichni.begin(),vsichni.end(),jezdecJeRychlejsi);

    /// VLOZENI PORADI
    vlozitPoradi(vsichni);

    /// SETRIZENI CASU
    sort(casy.begin(),casy.end(),casJeRychlejsi);

    int volba;
    while(true){
        vypisMenu();

        cout << endl << "Zadejte volbu: ";
        cin >> volba;
        while(cin.fail()){ /// POKUD UZIVATEL NEZADA INT
           cin.clear();
           cout << " * Spatne zadana volba. Jsou povoleny pouze cela cisla z menu. *" << endl;
           cin.ignore(numeric_limits<streamsize>::max(), '\n' );
           cout << "Zadejte volbu: ";
           cin >> volba;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n' ); /// KVULI ZADAVANI JMENA VE 4 VOLBE - "VYPRAZDNI" ENTER

        switch(volba){
            case 1:{    /// VYPIS VSECH JEZDCU
                vypisJezdcu(vsichni,pocet_jezdcu);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            case 2:{    /// VYPIS VSECH CASU
                vypisCasu(casy);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            case 3:{    /// VYPIS POSTUPUJICICH - UZIVATEL ZADA KOLIK JEZDCU POSTUPUJE
                int pocet_postupujicich;
                do{
                    cout << "Zadejte kolik jezdcu postupuje: ";
                    cin >> pocet_postupujicich;
                    if(pocet_postupujicich > pocet_jezdcu)
                        cout << " * Nemuze postoupit vice jezdcu nez jich doopravdy existuje! *" << endl;
                }while(pocet_postupujicich > pocet_jezdcu);

                cin.ignore(numeric_limits<streamsize>::max(), '\n' );

                vypisJezdcu(vsichni, pocet_postupujicich);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            case 4:{    /// VYPIS ZADANEHO JEZDCE
                string jmeno;
                cout <<  endl
                     << "HLEDANI JEZDCE" << endl
                     << "==============" << endl << endl
                     << " / Mozne tvary: \"Jmeno Prijmeni\", nebo \"Jmeno\", nebo \"Prijmeni\" /"<< endl << endl
                     << "Zadejte jmeno: ";

                cin.clear();
                getline(cin, jmeno); /// NACTENI JMENA TIMTO ZPUSOBEM Z DUVODU BILYCH ZNAKU

                vypisJezdce(vsichni,jmeno);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            case 0:{
                return 0;
            }break;

            default:{
                cout << endl << " * Neexistujici polozka menu. *" << endl;
            }

        }

    }
    return 0;
}
