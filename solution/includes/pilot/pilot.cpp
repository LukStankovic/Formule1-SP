/**
 * @brief Funkce pro praci s jezdcem
 * @file includes/jezdec/jezdec.cpp
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


#include "pilot.h"
#include "../functions/functions.h"


using namespace std;

/**
 * @brief Naplni strukturu TJEZDEC daty z csv souboru
 * @param f              Soubor ze ktereho se nacitaji jezdci
 * @param jezdci         Vektor struktury TJEZDEC do ktereho se bude ukladat
 * @param casy           Vektor struktury TCAS ze ktereho se nacitaji casy okruhu
 * @param jezdci         Pocet zajetych okruhu
 */
void FillPilots(ifstream& f, vector<Pilot>& allPilots, vector<Round>& allRounds,const int& numberOfRounds){

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

        i++;
    }
    /// PRESUNE "KURZOR" ZPET NA ZACETEK SOUBORU
    f.clear();
    f.seekg(0);
}

void AddPosition(vector<Pilot> &allPilots){
    try{
        for(int i = 0; i < allPilots.size(); i++){
            allPilots.at(i).position = i+1;
        }
    }
    catch (out_of_range e){
        cout << endl << " * Chyba. "<< "Jeji popis: " << e.what() << " *" << endl;
    }
}


/**
 * @brief Vypise seznam jezdcu do konzole - pouziti i pro postupujici
 * @param jezdci         Vektor struktury TJEZDEC ze ktereho se cerpa
 * @param pocet_postupujich  Kolik jich postupuje (se vypise)
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
        cout << endl << " * Chyba. "<< "Jeji popis: " << e.what() << " *" << endl;
    }

    cout << endl;
}

void PrintPilot(const vector<Pilot>& allPilots, string name){

    int numberOfCells = CountCells(' ',name), found = 0;
    vector<string> explodedName(numberOfCells);
    vector<Pilot> foundPilots;
    vector<Pilot> pilotsLowerCase(allPilots.size()); /// POMOCNY VEKTOR STRUKURY TJEZDEC PRO LOWERCASE JEZDCE
    pilotsLowerCase = allPilots;  /// PREKOPIROVANI JEZDCU

    /// ROZDELI RADEK DO BUNEK
    ExplodeString(' ',name,explodedName);

    /// NUTNO PREDELENAT NA LOWERCASE Z DUVODOU ZE UZIVATL MUZE MIT ZAPNUTY NAPR CAPS LOCK
    if(explodedName.size() == 1)
        transform(explodedName.at(0).begin(), explodedName.at(0).end(), explodedName.at(0).begin(),::tolower);

    if(explodedName.size() == 2){
        transform(explodedName.at(0).begin(), explodedName.at(0).end(), explodedName.at(0).begin(),::tolower);
        transform(explodedName.at(1).begin(), explodedName.at(1).end(), explodedName.at(1).begin(),::tolower);
    }

    try{
        for(int i = 0; i < allPilots.size(); i++){

            transform(pilotsLowerCase.at(i).name.begin(), pilotsLowerCase.at(i).name.end(), pilotsLowerCase.at(i).name.begin(),::tolower);
            transform(pilotsLowerCase.at(i).surname.begin(), pilotsLowerCase.at(i).surname.end(), pilotsLowerCase.at(i).surname.begin(),::tolower);

            if(explodedName.size() == 1){ /// POKUD JE ZADANO JEN JMENO NEBO JEN PRIJMENI

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
                cout << " * Pravdepodobne jste spatne zadal jmeno." << endl;
                break;
            }

        }
    }
    catch (out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl;
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
            for(int i = 0; i < foundPilots.size(); i++)
                cout << setw(3) << foundPilots.at(i).position <<". | " << setw(4) << foundPilots.at(i).id_pilot << " | " << setw(10) << foundPilots.at(i).name << " | " <<  setw(10) <<  foundPilots.at(i).surname << " |" << setw(4) << foundPilots.at(i).number_of_rounds << " |"
                << setw(9) << MsToTime(foundPilots.at(i).best_time) << " |" << setw(9) << MsToTime(foundPilots.at(i).worst_time) << " |" << setw(9) << MsToTime(foundPilots.at(i).mean_time) << endl;
        }
        catch (out_of_range e){
            cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl;
        }

    }
}

/**
 * @brief Exportuje seznam jezdcu do html
 * @param jezdci   Vektor struktury TJEZDEC
 * @param nazev    Nazev souboru
 */
void ExportPilots(const vector<Pilot>& allPilots, const string& path, const int& num){

    ofstream exp(path);

    exp << "<!doctype html><html lang='cs'><head><meta charset='utf-8'>" << endl
        << "<title>Vypis vsech jezdcu</title>" << endl
        << "<style>"<< endl
        << "body{font-family:sans; text-align: center;}" << endl
        << "table{margin: 30px auto; text-align: center;}" << endl
        << "th{border-bottom: 1px solid #000; background: #dcdcdc; padding: 10px 15px;}" << endl
        << "td{padding: 5px 15px;}" << endl
        << "tbody tr:nth-child(even){background: #f4f4f4;}" << endl
        << "tbody tr:nth-child(odd){background: #fff;}" << endl
        << "h1{font-size:23px}" << endl
        << "</style>" << endl
        << "<head>" << endl
        << "<body>" << endl
        << "<h1>Vypis vsech jezdcu</h1>" <<  endl
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



/**
 * @brief Vraci pro funkci sort() ktery zaznam je mensi
 * @param a        Struktura TJEZDEC - prvni jezdec
 * @param b        Struktura TJEZDEC - druhy jezdec
 * @return Vraci true pokud je a rychlejsi, false pokud je a pomalejsi
 */
bool IsPilotFaster(const Pilot& a, const Pilot& b){
    /**
        OSETRENI ZDA NEMA CAS 0 MS
            - 0ms znamena prazdna hodnota - jezdec nezajel ani jedno kolo
            - proto ulozime do pomocne promenne velkou hodnotu
    */

    unsigned aux_a, aux_b;

    if(a.best_time == 0)
        aux_a = 1000000000;
    else
        aux_a = a.best_time;

    if(b.best_time == 0)
        aux_a = 1000000000;
    else
        aux_a = b.best_time;

    /// POROVNANI
    return aux_a < aux_b;

}
