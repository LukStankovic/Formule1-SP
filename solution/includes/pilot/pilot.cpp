#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <ctype.h>

#include "pilot.h"
#include "../functions/functions.h"

/**
 * \brief Funkce pro praci se strukturou Pilot
 * \file includes/pilot/pilot.cpp
 *
 */

using namespace std;


/** \brief Naplni strukturu Pilot daty z CSV souboru
 *  \param[in]  f               Soubor ze ktereho se nacitaji jezdci
 *  \param[out] allPilots       Vektor struktury Pilot do ktereho se bude ukladat
 *  \param[in]  allRounds       Vektor struktury Round ze ktereho se nacitaji casy okruhu
 *  \param[in]  numberOfRounds  Pocet zajetych okruhu
 *
 */

void FillPilots(ifstream& f, vector<Pilot>& allPilots, const vector<Round>& allRounds,const int& numberOfRounds){

    int i = 0;
    string line;

    while(getline(f,line)){
        /// ZJISTENI POCET BUNEK V CSV SOUBORU A NASLEDNE VYTVORENI VEKTORU
        int numberOfCells = CountCells(';',line);
        vector<string> lineInCSV(numberOfCells);

        /// ROZDELI RADEK DO BUNEK
        ExplodeString(';',line,lineInCSV);

        allPilots.at(i).id_pilot = stoi(lineInCSV.at(2));
        allPilots.at(i).name = lineInCSV.at(0);
        allPilots.at(i).surname = lineInCSV.at(1);

        /// VKLADANI ZAJETYCH KOL ZE STRUKTURY TCAS A ZJISTOVANI NEJLEPSIHO, NEJHORSIHO A PRUMERNEHO CASU

        int bestTime = 100000000, worstTime = 0;
        unsigned long overallTime = 0;

        try{
            for(int j = 0; j < numberOfRounds; j++){
                if(allRounds.at(j).id_pilot == allPilots.at(i).id_pilot){

                    allPilots.at(i).number_of_rounds++;
                    overallTime += allRounds.at(j).time_ms;

                    if(allRounds.at(j).time_ms < bestTime)
                        bestTime = allRounds.at(j).time_ms;

                    if(allRounds.at(j).time_ms > worstTime)
                        worstTime = allRounds.at(j).time_ms;
                }

            }

            if(worstTime != 0)
                allPilots.at(i).worst_time = worstTime;
            else
                allPilots.at(i).worst_time = 0;

            if(bestTime != 100000000)
                allPilots.at(i).best_time = bestTime;
            else
                allPilots.at(i).best_time = 0;

            if(allPilots.at(i).number_of_rounds != 0)
                allPilots.at(i).mean_time = overallTime/allPilots.at(i).number_of_rounds;
            else
                allPilots.at(i).mean_time = 0;

        }
        catch (out_of_range e){
            cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl << " * Program bude ukoncen. *" << endl;
            exit(0);
        }

        i++;
    }
    /// PRESUNE "KURZOR" V SOUBORU ZPET NA ZACETEK SOUBORU
    f.clear();
    f.seekg(0);
}


/** \brief Prida pozici k jezdci
 *  \param[out] allPilots    Vektor jezdcu, kterym bude zapisovano poradi
 *
 */
void AddPosition(vector<Pilot> &allPilots){
    try{
        for(int i = 0; i < allPilots.size(); i++){
            allPilots.at(i).position = i+1;
        }
    }
    catch (out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl << " * Program bude ukoncen. *" << endl;
        exit(0);
    }
}


/** \brief Vypise seznam jezdcu do konzole - pouziti i pro postupujici
 *  \param[in] allPilots    Vektor struktury Pilot ze ktereho se cerpa
 *  \param[in] num          Pocet vypsanych jezdcu
 *
 */
void PrintPilots(const vector<Pilot>& allPilots, const int& num){

    cout << endl << "VYPIS JEZDCU" << endl
                 << "============" << endl
                 << " / Pro spravne zobrazeni je nutne si zvetsit okno konzole! / " << endl << endl;
    /// HLAVICKA TABULKY
    cout << setw(4) << "P " << " | "<< " ID " << " | " << setw(10) << " JMENO " << " | " <<  setw(10) << " PRIJMENI " << " | " << "KOL |" << setw(11) << " NEJLEPSI |"<< setw(11) << " NEJHORSI |"<< setw(9) << " PRUMERNY"<<endl;
    for(int i = 0; i < 78; i++)
        cout << "=";
    cout << endl;

    /// TELO TABULKY
    try{
        for(int i = 0; i < num; i++){
            cout << setw(3) << allPilots.at(i).position <<". | " << setw(4) << allPilots.at(i).id_pilot << " | " << setw(10) << allPilots.at(i).name << " | " <<  setw(10) <<  allPilots.at(i).surname << " |" << setw(4) << allPilots.at(i).number_of_rounds << " |"
            << setw(9) << MsToTime(allPilots.at(i).best_time) << " |" << setw(9) << MsToTime(allPilots.at(i).worst_time) << " |" << setw(9) << MsToTime(allPilots.at(i).mean_time) << endl;
        }
    }
    catch (out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl << " * Program bude ukoncen. *" << endl;
        exit(0);
    }

    cout << endl;
}

/** \brief Vypise jednoho jezdce (popr. vice jezdcu pokud maji stejne jmeno) do konzole
 *  \param[in] allPilots    Vektor struktury Pilot ze ktereho se cerpa
 *  \param[in] name         Jmeno hledaneho jezdce. Muze byt zadano: Jmeno Prijmeni, Prijmeni, Jmeno
 *
 */
void PrintPilot(const vector<Pilot>& allPilots, string name){

    int numberOfCells = CountCells(' ',name);
    int found = 0;
    vector<string> explodedName(numberOfCells);
    vector<Pilot> foundPilots;
    vector<Pilot> pilotsLowerCase(allPilots.size()); /// POMOCNY VEKTOR STRUKURY Pilot PRO LOWERCASE JEZDCE
    pilotsLowerCase = allPilots;  /// PREKOPIROVANI JEZDCU DO POMOCNEHO VEKTORU

    /// ROZDELI RADEK DO BUNEK
    ExplodeString(' ',name,explodedName);

    try{

        /// NUTNO PREDELENAT NA LOWERCASE Z DUVODOU ZE UZIVATL MUZE MIT ZAPNUTY NAPR CAPS LOCK
        if(explodedName.size() == 1){
            ToLower(explodedName.at(0));
        }

        if(explodedName.size() == 2){
            ToLower(explodedName.at(0));
            ToLower(explodedName.at(1));
        }

        for(int i = 0; i < allPilots.size(); i++){

            ToLower(pilotsLowerCase.at(i).name);
            ToLower(pilotsLowerCase.at(i).surname);

            if(explodedName.size() == 1){ /// POKUD JE ZADANO JEN JMENO NEBO JEN PRIJMENI

                /// POKUD JE ZADANO POUZE ID
                if(isdigit(explodedName.at(0).at(0)) && stoi(explodedName.at(0)) == allPilots.at(i).id_pilot){
                    found = 1;
                    foundPilots.push_back(allPilots.at(i));
                }

                if(explodedName.at(0) == pilotsLowerCase.at(i).name || explodedName.at(0) == pilotsLowerCase.at(i).surname){
                    found = 1;
                    foundPilots.push_back(allPilots.at(i));
                }
            }
            else if(explodedName.size() == 2){
                if( (explodedName.at(0) == pilotsLowerCase.at(i).name || explodedName.at(0) == pilotsLowerCase.at(i).surname) && (explodedName.at(1) == pilotsLowerCase.at(i).name || explodedName.at(1) == pilotsLowerCase.at(i).surname)){
                    found = 1;
                    foundPilots.push_back(allPilots.at(i));
                }
            }
            else{
                cout << " * Pravdepodobne jste spatne zadal jmeno. *" << endl;
                break;
            }

        }

    }
    catch (out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl << " * Program bude ukoncen. *" << endl;
        exit(0);
    }


    /// VYKRESLENI TABULKY AZ TED Z DUVODU KDYBY BYLO NALEZENO VICE JEZDCU
    if(found == 0)
        cout << " * Zadny jezdec nebyl nalezen. *" << endl;

    else{
        cout << setw(4) << "P " << " | "<< " ID " << " | " << setw(10) << " JMENO " << " | " <<  setw(10) << " PRIJMENI " << " | " << "KOL |" << setw(11) << " NEJLEPSI |"<< setw(11) << " NEJHORSI |"<< setw(9) << " PRUMERNY"<<endl;
        for(int i = 0; i < 78; i++)
            cout << "=";
        cout << endl;

        try{

            for(int i = 0; i < foundPilots.size(); i++){

                cout << setw(3) << foundPilots.at(i).position <<". | " << setw(4) << foundPilots.at(i).id_pilot << " | " << setw(10) << foundPilots.at(i).name << " | " <<  setw(10) <<  foundPilots.at(i).surname << " |" << setw(4) << foundPilots.at(i).number_of_rounds << " |"
                << setw(9) << MsToTime(foundPilots.at(i).best_time) << " |" << setw(9) << MsToTime(foundPilots.at(i).worst_time) << " |" << setw(9) << MsToTime(foundPilots.at(i).mean_time) << endl;

            }

        }
        catch (out_of_range e){
            cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl << " * Program bude ukoncen. *" << endl;
            exit(0);
        }

    }
}


/** \brief Exportuje seznam jezdcu do html
 *  \param[in] allPilots     Vektor struktury Pilot
 *  \param[in] path          Nazev souboru + cesta
 *  \param[in] num           Pocet jezdcu na vypsani
 *
 */
void ExportPilots(const vector<Pilot>& allPilots, const string& path, const int& num){

    ofstream exp(path);

    exp << HTMLHead("Piloti F1");
    exp << "<body>" << endl
        << "<h1>Jezdci F1</h1>" <<  endl
        << "<table cellspacing='0'>"<< endl
        << "<thead><tr>" << endl
        << "<th>Poradi</th><th>ID</th><th>Jmeno</th><th>Prijmeni</th><th>Pocet kol</th><th>Nejrychlejsi kolo</th><th>Nejpomalejsi kolo</th><th>Prumerny cas kola</th>" << endl
        << "<tr></thead><tbody>" << endl;

    try{
        for(int i = 0; i < num; i++){
            exp << "<tr>" << endl;
                exp << "<td>" << allPilots.at(i).position << ". </td>" << endl
                    << "<td>" << allPilots.at(i).id_pilot << "</td>" << endl
                    << "<td>" << allPilots.at(i).name << "</td>" << endl
                    << "<td>" << allPilots.at(i).surname << "</td>" << endl
                    << "<td>" << allPilots.at(i).number_of_rounds << "</td>" << endl
                    << "<td>" << MsToTime(allPilots.at(i).best_time) << "</td>" << endl
                    << "<td>" << MsToTime(allPilots.at(i).worst_time) << "</td>" << endl
                    << "<td>" << MsToTime(allPilots.at(i).mean_time) << "</td>" << endl;
            exp << "</tr>" << endl;
        }
    }
    catch(out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl;
    }

    exp << "</tbody></table></body></html>" << endl;

    exp.close();

    /// KONTROLA ZDA SE SOUBOR VYTVORIL

    ifstream check(path);

    if(check.fail()){
        cout << endl << " * Neco se pokazilo... Soubor nebyl vytvoren.*" << endl
             << " * Mozna chyba: Neexistujici adresar nebo nedostatecna prava. *" << endl;
    }
    else{
        cout << endl << " * Soubor byl uspesne vytvoren. *" << endl;
        check.close();
    }
}


/** \brief Exportuje jednoho jezdce (popr. vice jezdcu pokud maji stejne jmeno) do konzole + vypise vsechny jeho kola
 *  \param[in] allPilots    Vektor struktury Pilot ze ktereho se cerpa
 *  \param[in] name         Jmeno hledaneho jezdce. Muze byt zadano: Jmeno Prijmeni, Prijmeni, Jmeno, ID
 *  \param[in] path         Nazev souboru + cesta
 *
 */
void ExportPilot(const vector<Pilot>& allPilots, string name, const string& path){

    int numberOfCells = CountCells(' ',name);
    int found = 0;
    vector<string> explodedName(numberOfCells);
    vector<Pilot> foundPilots;
    vector<Pilot> pilotsLowerCase(allPilots.size()); /// POMOCNY VEKTOR STRUKURY Pilot PRO LOWERCASE JEZDCE
    pilotsLowerCase = allPilots;  /// PREKOPIROVANI JEZDCU DO POMOCNEHO VEKTORU

    /// ROZDELI RADEK DO BUNEK
    ExplodeString(' ',name,explodedName);

    try{

        /// NUTNO PREDELENAT NA LOWERCASE Z DUVODOU ZE UZIVATL MUZE MIT ZAPNUTY NAPR CAPS LOCK
        if(explodedName.size() == 1){
            ToLower(explodedName.at(0));
        }

        if(explodedName.size() == 2){
            ToLower(explodedName.at(0));
            ToLower(explodedName.at(1));
        }

        for(int i = 0; i < allPilots.size(); i++){

            ToLower(pilotsLowerCase.at(i).name);
            ToLower(pilotsLowerCase.at(i).surname);

            if(explodedName.size() == 1){ /// POKUD JE ZADANO JEN JMENO NEBO JEN PRIJMENI

                /// POKUD JE ZADANO POUZE ID
                if(isdigit(explodedName.at(0).at(0)) && stoi(explodedName.at(0)) == allPilots.at(i).id_pilot){
                    found = 1;
                    foundPilots.push_back(allPilots.at(i));
                }

                if(explodedName.at(0) == pilotsLowerCase.at(i).name || explodedName.at(0) == pilotsLowerCase.at(i).surname){
                    found = 1;
                    foundPilots.push_back(allPilots.at(i));
                }
            }
            else if(explodedName.size() == 2){
                if( (explodedName.at(0) == pilotsLowerCase.at(i).name || explodedName.at(0) == pilotsLowerCase.at(i).surname) && (explodedName.at(1) == pilotsLowerCase.at(i).name || explodedName.at(1) == pilotsLowerCase.at(i).surname)){
                    found = 1;
                    foundPilots.push_back(allPilots.at(i));
                }
            }
            else{
                cout << " * Pravdepodobne jste spatne zadal jmeno. *" << endl;
                break;
            }

        }

    }
    catch (out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl << " * Program bude ukoncen. *" << endl;
        exit(0);
    }


    /// VYKRESLENI TABULKY AZ TED Z DUVODU KDYBY BYLO NALEZENO VICE JEZDCU
    if(found == 0)
        cout << " * Zadny jezdec nebyl nalezen. *" << endl;

    else{

    }

}


/** \brief Setridi vsechny jezdce podle nejrychlejsiho casu (od nejrychlejsiho po nejpomalejsi)
 *          - Kontroluje pokud cas = 0 --> jezdce da na konec seznamu
 *  \param[out] allPilots    Vektor struktury Pilot ktery se tridi
 *
 */
void Sort(vector<Pilot>& allPilots){

    for(int j = 0; j < allPilots.size()-1; j++){
        for(int i = 0; i < allPilots.size()-1; i++){
            if(IsFaster(allPilots.at(i),allPilots.at(i+1))){
                Pilot tmp = allPilots.at(i);
                allPilots.at(i) = allPilots.at(i+1);
                allPilots.at(i+1) = tmp;
            }

        }
    }

}

/**
 * \brief Vraci, ktery jezdec je rychlejsi
 * \param a        Struktura Pilot - prvni jezdec
 * \param b        Struktura Pilot - druhy jezdec
 * \return Vraci false pokud je a rychlejsi, true pokud je a pomalejsi
 */
bool IsFaster(const Pilot& a, const Pilot& b){
    /**
        OSETRENI ZDA NEMA CAS 0 MS
            - 0 ms znamena prazdna hodnota - jezdec nezajel ani jedno kolo
            - proto ulozime do pomocne promenne velkou hodnotu
    */

    int tmp_a, tmp_b;

    if(a.best_time == 0)
        tmp_a = 1000000000;
    else
        tmp_a = a.best_time;

    if(b.best_time == 0)
        tmp_b = 1000000000;
    else
        tmp_b = b.best_time;

    /// POROVNANI
    return tmp_a > tmp_b;

}

