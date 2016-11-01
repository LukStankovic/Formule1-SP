/**
 * @brief Vseobecne funkce
 * @author Lukas Stankovic
 * @file includes/funkce/funkce.cpp
 */

#include <fstream>
#include <vector>
#include <iostream>
#include <string>

#include "../pilot/pilot.h"
#include "../round/round.h"

using namespace std;

/**
 * @brief Rozdeli string podle delice do vektoru stringu
 * @param delic          Znak, pomoci ktereho se rozdeluje string
 * @param retezec        String, ktery se bude delit
 * @param pole           Vektor s rozdelenym stringem, vraci se pomoci reference
 */
void ExplodeString(const char& delimiter, string str, vector<string>& explodedString){

    int indexOfLastDelimeter = 0;
    int numberOfCells = 0;
    /// PRIDA DELIC NA KONEC STRINGU PRO SNADNEJSI PRACI SE STRINGEM
    if(str.back() != delimiter)
        str += delimiter;

    try{
        for(int i = 0; i < str.length()+1; i++){

            if(str[i] == delimiter){

                for(int k = indexOfLastDelimeter; k < i; k++){
                    explodedString.at(numberOfCells) += str[k];
                }

                indexOfLastDelimeter = i+1;
                numberOfCells++;
            }

        }
    }
    catch (out_of_range e){
        cout << endl << " * Chyba. "<< "Jeji popis: " << e.what() << " *" << endl;
    }

}

/**
 * @brief Vrati pocet bunek v stringu (radku), zjistuje pomoci delice
 * @param delic          Znak, pomoci ktereho se rozdeluje string
 * @param retezec        String, ktery se bude delit
 * @return Funkce vraci pocet bunek oddelenych delicem
 */
int CountCells(const char& delimiter, const string& str){

    int num = 0;

    for(int i = 0; i < str.length(); i++)
        if(str[i] == delimiter)
            num++;

    return num+1; /// +1 KVULI POSLEDNI BUNCE

}

/**
 * @brief Vrati pocet zaznamu (radku) v souboru
 * @param f          Soubor ve kterem se pocitaji radky
 * @return Vraci pocet zaznamu v danem souboru
 */
int CountLines(ifstream &f){
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

/**
 * @brief Prevadi cas na ms ze stringu
 * @param cas          Vector stringu ze ktereho se bere cas
 * @return Vraci milisekundy
 */
int TimeToMs(const vector<string>& time){
    return ( ( stoi(time.at(0)) *60 + stoi(time.at(1)) ) * 1000 + stoi(time.at(2)) );
}


/**
 * @brief Posila referenci vektoru s casem rozdelenym na minuty, vteriny, setiny
 * @param ms           Cas v milisekundach
 * @param cas          Vektor intu do ktereho se posila
 */
void MsToTime(int ms, vector<int>& time){
    int tmp;

    tmp = ms/1000;

    time.at(0) = tmp/60;
    time.at(1) = (tmp%1000) - time.at(0)*60;
    time.at(2) = ms%1000;
}

/**
 * @brief Vrati string s casem
 * @param ms           Cas v milisekundach
 * @return Vrati string s casem ve formatu min:sek:set
 */
string MsToTime(int ms){
    int tmp, mins = 0, secs = 0, milisecs = 0;

    tmp = ms/1000;

    mins = tmp/60;
    secs = (tmp%1000) - mins*60;
    milisecs = ms%1000;

    string str = to_string(mins) + ":" + to_string(secs) + ":" + to_string(milisecs);

    return str;
}

/**
 * @brief Vypise do konzole menu
 */
void PrintMenu(vector<Pilot> allPilots, vector<Round> allRounds, const int& numberOfPilots, const int& numberOfRounds){

    int option;

    while(true){

    cout << endl;
    for (int i = 0; i < 30; i++)
        cout << "=";
    cout << endl;

    /// NADPIS V MENU + ODDELOVAC
    cout << "Zakladni vypisy do konzole" << endl;
    for (int i = 0; i < 30; i++)
        cout << "-";
    cout << endl;

    cout << "1  -  Vypis vsech jezdcu " << endl
         << "2  -  Vypis vsech zajetych kol" << endl
         << "3  -  Vypis postupujicich jezdcu" << endl
         << "4  -  Vypis detailu pro zadaneho jezdce" << endl;

    /// NADPIS V MENU + ODDELOVAC
    cout << endl << "Exporty do HTML" << endl;
    for (int i = 0; i < 30; i++)
        cout << "-";
    cout << endl;

    cout  << "5  -  Export vsech jezdcu" << endl
          << "6  -  Export vsech zajetych kol" << endl
          << "7  -  Export postupujicich jezdcu " << endl
          << "8  -  Export casu daneho jezdce" << endl
          << "9  -  Export stupne vitezu" << endl;

    cout << endl << "0  -  Ukonceni programu" << endl;

    for (int i = 0; i < 30; i++)
        cout << "=";
        cout << endl;


        cout << endl << "Zadejte volbu: ";
        cin >> option;

        /**
         ZADAVANI DOKUD NEZADA INT
         -------------------------
            - Cyklus while, ktery se opakuje tak dlouho dokud uzivatel nezada cele cislo
            - Funkce cin.ignore() je pouzita z duvodu vycisteni enteru z cin
        */

        while(cin.fail()){
           cin.clear();
           cout << " * Spatne zadana volba. Jsou povoleny pouze cela cisla z menu. *" << endl;
           cin.ignore(numeric_limits<streamsize>::max(), '\n' );
           cout << "Zadejte volbu: ";
           cin >> option;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n' );

        /**
            MENU S VOLBAMI
            --------------
        */
        switch(option){

            /**
             ### 1. VYPIS VSECH JEZDCU ###
                - Vypise do konzole tabulku vsech jezdcu a ceka dokud uzivatel nezmackne ENTER
            */
            case 1:{
                PrintPilots(allPilots,numberOfPilots);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            /**
             ### 2. VYPIS VSECH CASU ###
                - Vypise do konzole tabulku vsech zajetych casu a ceka dokud uzivatel nezmackne ENTER
            */
            case 2:{
                PrintRounds(allRounds);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            /**
             ### 3. VYPIS POSTUPUJICH ###
                - Uzivatel zada kolik jezdcu ma postupovat a tolik se vykresli do konzole do tabulky
                - Case obsahuje cyklus, ktery se opakuje dokud uzivatel spravne nezeada pocet postupujicich
                - Osetrene komplikace:
                    - Zada cislo mensi nez 1
                    - Zada cislo vetsi nez doopravdy existuje jezdcu
                    - Zada znak
            */
            case 3:{
                int numberOfQualified;

                do{

                    cout << "Zadejte kolik jezdcu postupuje: ";
                    cin >> numberOfQualified;

                    if(cin.fail()){
                        cout << " * Nemuzete zadat znak. Zadejte pouze kladne cele cislo! *" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n' );
                    }
                    else if(numberOfQualified > numberOfPilots)
                        cout << " * Nemuze postoupit vice jezdcu nez jich doopravdy existuje! *" << endl;
                    else if(numberOfQualified < 1)
                        cout << " * Zadejte pouze kladne cele cislo! *" << endl;

                }while( (numberOfQualified > numberOfPilots) || (numberOfQualified < 1) || cin.fail());

                cin.ignore(numeric_limits<streamsize>::max(), '\n' );

                PrintPilots(allPilots, numberOfQualified);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            /**
             ### 4. ZOBRAZENI JEDNOHO (VICE) JEZDCU ###
                - Uzivatel zada jmeno jezdce a ten se vypise (pokud existuje)
                - Mozne tvary zadani jmena:
                    - Jmeno
                    - Jmeno Prijmeni
                    - Prijmeni
                - Je mozne ze se vypise i vice jezdcu pokud existuji jmenovci!
                - Nacita se pomoci getline() z duvodu cteni bilych znaku
                - Pote se opet ceka na zmacknuti ENTER pomoci funkce cin.ignore()
            */
            case 4:{
                string name;
                cout <<  endl
                     << "HLEDANI JEZDCE" << endl
                     << "==============" << endl << endl
                     << " / Mozne tvary: \"Jmeno Prijmeni\", nebo \"Jmeno\", nebo \"Prijmeni\" /"<< endl << endl
                     << "Zadejte jmeno: ";

                cin.clear();
                getline(cin, name,'\n');

                PrintPilot(allPilots,name);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            /**
             ### 5. EXPORT VSECH JEZDCU DO HTML ###
                - Exportuje a vygeneruje tabulku vsech jezdcu do HTML
                - Uzivatel musi zadat cestu a jmeno souboru
                - Program kontroluje zda se soubor vytvoril
            */
            case 5:{
                string fileName;
                cout <<  endl
                     << "EXPORT JZDCU" << endl
                     << "============" << endl << endl
                     << " / Mozny tvar: /Users/Jmeno/programs/formule/vypis_vsech_jezdcu.html /"<< endl
                     << " / SOUBOR JE VE FORMATU HTML! /"<< endl << endl
                     << "Zadejte adresu a nazev souboru: ";
                getline(cin, fileName,'\n');
                ExportPilots(allPilots,fileName,numberOfPilots);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            /**
             ### 6. EXPORT VSECH ZAJETYCH KOL DO HTML
                - Exportuje a vygeneruje tabulku vsech zajetych kol do HTML
                - Uzivatel musi zadat cestu a jmeno souboru
                - Program kontroluje zda se soubor vytvoril
            */
            case 6:{
                string fileName;
                cout <<  endl
                     << "EXPORT CASU" << endl
                     << "===========" << endl << endl
                     << " / Mozny tvar: /Users/Jmeno/programs/formule/vypis_vsech_jezdcu.html /"<< endl
                     << " / SOUBOR JE VE FORMATU HTML! /"<< endl << endl
                     << "Zadejte adresu a nazev souboru: ";
                getline(cin, fileName,'\n');
                ExportRounds(allRounds,fileName);

                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
            }break;

            /**
             ### 7. EXPORT POSTUPUJICICH JEZDCU DO HTML ###
                - Exportuje a vygeneruje tabulku vsech zajetych kol do HTML
                - Uzivatel musi zadat cestu a jmeno souboru
                - Program kontroluje zda se soubor vytvoril

                - Uzivatel zada kolik jezdcu ma postupovat
                - Case obsahuje cyklus, ktery se opakuje dokud uzivatel spravne nezeada pocet postupujicich
                - Osetrene komplikace:
                    - Zada cislo mensi nez 1
                    - Zada cislo vetsi nez doopravdy existuje jezdcu
                    - Zada znak
            */
            case 7:{
                string fileName;
                int numberOfQualified;

                cout <<  endl
                     << "EXPORT POSTUPUJICICH JZDCU" << endl
                     << "==========================" << endl << endl
                     << " / Mozny tvar: /Users/Jmeno/programs/formule/vypis_vsech_jezdcu.html /"<< endl
                     << " / SOUBOR JE VE FORMATU HTML! /"<< endl << endl
                     << "Zadejte adresu a nazev souboru: ";
                getline(cin, fileName,'\n');

                do{

                    cout << "Zadejte kolik jezdcu postupuje: ";
                    cin >> numberOfQualified;

                    if(cin.fail()){
                        cout << " * Nemuzete zadat znak. Zadejte pouze kladne cele cislo! *" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n' );
                    }
                    else if(numberOfQualified > numberOfPilots)
                        cout << " * Nemuze postoupit vice jezdcu nez jich doopravdy existuje! *" << endl;
                    else if(numberOfQualified < 1)
                        cout << " * Zadejte pouze kladne cele cislo! *" << endl;

                }while( (numberOfQualified > numberOfPilots) || (numberOfQualified < 1) || cin.fail());

                ExportPilots(allPilots,fileName,numberOfQualified);
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );
                cout << endl << " / Pro zobrazeni menu stiskente ENTER. /";
                cin.ignore(numeric_limits<streamsize>::max(), '\n' );

            }break;

            /**
             ### 8. EXPORT ZADANEHO JEZDCE ###
                - Uzivatel zada jmeno jezdce a ten se exportuje (pokud existuje)
                - Mozne tvary zadani jmena:
                    - Jmeno
                    - Jmeno Prijmeni
                    - Prijmeni
                - Je mozne ze se vypise i vice jezdcu pokud existuji jmenovci!
                - Nacita se pomoci getline() z duvodu cteni bilych znaku
                - Program kontroluje zda se soubor vytvoril
            */
            case 8:{

            }break;

            /**
             ### 9. Export stupne vitezu ###
                - Exportuje prvni 3 nejrychlejsi jezdce
                - Vypise k nim detailnejsi info
                - Program kontroluje zda se soubor vytvoril
            */
            case 9:{

            }break;

            /**
             ### 0 - UKONCENI PROGRAMU ###
                - Po zvoleni 0 v menu ihned ukonci program.
            */
            case 0:{
                exit(0);
            }break;

            default:{
                cout << endl << " * Neexistujici polozka menu. *" << endl;
            }

        }

    }

}