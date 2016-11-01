/**
 * @brief Funkce pro praci s casem
 * @author Lukas Stankovic
 */

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "round.h"
#include "../pilot/pilot.h"
#include "../functions/functions.h"


/// NAPLNI STRUKTURU DATY ZE SOUBORU
/**
 * @brief Naplni strukturu TCAS datdy z csv souboru
 * @param f              Soubor ze ktereho se nacitaji jezdci
 * @param casy           Vektor struktury TCAS do ktereho se vkladaji casy okruhu
 */
void FillRounds(ifstream &f, vector<Round> &allRounds){

    int i = 0;
    string line;

    while(getline(f,line)){
        /// ZJISTENI POCET BUNEK V CSV SOUBORU A NASLEDNE VYTVORENI VEKTORU
        int numberOfCells = CountCells(';',line);
        vector<string> lineInCSV(numberOfCells);

        /// ROZDELI RADEK DO BUNEK
        ExplodeString(';',line,lineInCSV);

        allRounds.at(i).time = lineInCSV.at(0);
        allRounds.at(i).id_pilot = stoi(lineInCSV.at(1));
        allRounds.at(i).id_round = stoi(lineInCSV.at(2));

        /// PREPOCET ZE STRINGU NA MS
        vector<string> onlyTime(3);
        ExplodeString(':',lineInCSV.at(0),onlyTime);
        allRounds.at(i).time_ms = TimeToMs(onlyTime);

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
void PrintRounds(const vector<Round>& allRounds){

    cout << endl << "VYPIS VSECH CASU" << endl
                 << "================" << endl
                 << " / Pro spravne zobrazeni je nutne si zvetsit okno konzole! /" << endl << endl;

    cout << setw(4) << " P " << " | "<< setw(10) << " ID JEZDCE " << " | " << setw(15) << " CAS " << " | " <<  setw(15) << " CAS V MS " << endl;
    for(int i = 0; i < 57; i++)
        cout << "=";
    cout << endl;

    try{
        for(int i = 0; i < allRounds.size(); i++)
            cout << setw(3) <<  i+1 << "." << " | " << setw(11) << allRounds.at(i).id_pilot << " | " << setw(15) << allRounds.at(i).time << " | " <<  setw(15) <<  allRounds.at(i).time_ms << " |"<< endl;
        cout << endl;
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }

}


/**
 * @brief Exportuje seznam casu do html
 * @param jezdci   Vektor struktury TJEZDEC
 * @param nazev    Nazev souboru
 */
void ExportRounds(const vector<Round>& allRounds, const string& fileName){

    ofstream exp(fileName);

    exp << "<!doctype html><html lang='cs'><head><meta charset='utf-8'>" << endl
        << "<title>Vypis vsech casu</title>" << endl
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
        << "<th>Poradi</th><th>ID casu</th><th>ID jezdce</th><th>Cas</th><th>Cas v milisekundach</th>" << endl
        << "<tr></thead><tbody>" << endl;

    try{
        for(int i = 0; i < allRounds.size(); i++){
            exp << "<tr>" << endl;
                exp << "<td>" << i+1 << ". </td>" << endl
                    << "<td>" << allRounds.at(i).id_round << "</td>" << endl
                    << "<td>" << allRounds.at(i).id_pilot << "</td>" << endl
                    << "<td>" << allRounds.at(i).time << "</td>" << endl
                    << "<td>" << allRounds.at(i).time_ms << "</td>" << endl;
            exp << "</tr>" << endl;
        }
    }
    catch(out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl;
    }

    exp << "</tbody></table></body></html>" << endl;

    exp.close();

    /// KONTROLA ZDA SE SOUBOR VYTVORIL

    ifstream check(fileName);

    if(check.fail()){
        cout << endl << " * Neco se pokazilo... Soubor nebyl vytvoren.*" << endl
             << " * Mozna chyba: Neexistujici adresar nebo edostatecna prava. *" << endl;
    }
    else{
        cout << endl << " * Soubor byl uspesne vytvoren. *" << endl;
        check.close();
    }
}


/**
 * @brief Vraci pro funkci sort() ktery zaznam je mensi
 * @param a        Struktura TCAS - prvni cas
 * @param b        Struktura TCAS - druhy cas
 * @return Vraci true pokud je a rychlejsi, false pokud je a pomalejsi
 */
bool IsRoundFaster(const Round& a, const Round& b){
    /**
        OSETRENI ZDA NEMA CAS 0 MS
            - 0ms znamena prazdna hodnota - jezdec nezajel ani jedno kolo
            - proto ulozime do pomocne promenne velkou hodnotu
    */

    unsigned aux_a, aux_b;

    if(a.time_ms == 0)
        aux_a = 1000000000;
    else
        aux_a = a.time_ms;

    if(b.time_ms == 0)
        aux_b = 1000000000;
    else
        aux_b = b.time_ms;

    /// POROVNANI
    return aux_a < aux_b;

}