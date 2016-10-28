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

int main(int argc,char** argv){

    ifstream f_jezdci(argv[1]);

    if(f_jezdci.fail()){
        cout << endl << " * Chyba pri nacitani souboru s jezdci!" << endl
        << " * Nazev chyby: " << strerror(errno) << "." << endl
        << " / POZNAMKA: Prvni argument je soubor s jezdci, druhy s casy! /" << endl;
        return 0;
    }
    ifstream f_casy(argv[2]);

    if(f_casy.fail()){
        cout << endl << " * Chyba pri nacitani souboru s casy! *" << endl
        << " * Nazev chyby: " << strerror(errno) << ". *" << endl
        << " / POZNAMKA: Prvni argument je soubor s jezdci, druhy s casy! /" << endl;
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
                getline(cin, jmeno,'\n'); /// NACTENI JMENA TIMTO ZPUSOBEM Z DUVODU BILYCH ZNAKU

                vypisJezdce(vsichni,jmeno);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            case 5:{    /// EXPORT VSECH JEZDCU
                string adresa;
                cout <<  endl
                     << "EXPORT JZDCU" << endl
                     << "============" << endl << endl
                     << " / Mozny tvar: /Users/Jmeno/programs/formule/vypis_vsech_jezdcu.html /"<< endl
                     << " / SOUBOR JE VE FORMATU HTML! /"<< endl << endl
                     << "Zadejte adresu a nazev souboru: ";
                getline(cin, adresa,'\n');
                exportJezdcu(vsichni,adresa);
                cout << endl << " * Soubor byl uspesne vytvoren. *" << endl;
                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            case 6:{    /// EXPORT VSECH KOL
                string adresa;
                cout <<  endl
                     << "EXPORT CASU" << endl
                     << "===========" << endl << endl
                     << " / Mozny tvar: /Users/Jmeno/programs/formule/vypis_vsech_jezdcu.html /"<< endl
                     << " / SOUBOR JE VE FORMATU HTML! /"<< endl << endl
                     << "Zadejte adresu a nazev souboru: ";
                getline(cin, adresa,'\n');
                exportCasu(casy,adresa);
                cout << endl << " * Soubor byl uspesne vytvoren. *" << endl;
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
