#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

#include "round.h"
#include "../pilot/pilot.h"
#include "../functions/functions.h"


/** \brief Funkce pro praci se strukturou Round
 *  \file includes/round/round.cpp
 *
 */

/** \brief Naplni strukturu Round datdy z csv souboru
 *  \param[in]  f          Soubor ze ktereho se nacitaji jezdci
 *  \param[out] allRounds  Vektor struktury Round do ktereho se vkladaji casy okruhu
 */
void FillRounds(ifstream& f, vector<Round>& allRounds){

    int i = 0;
    string line;

    while(getline(f,line)){
        /// ZJISTENI POCET BUNEK V CSV SOUBORU A NASLEDNE VYTVORENI VEKTORU
        int numberOfCells = CountCells(';',line);

        try{

            vector<string> lineInCSV(numberOfCells);

            /// ROZDELI RADEK DO BUNEK
            ExplodeString(';',line,lineInCSV);

            allRounds.at(i).time = lineInCSV.at(0);
                        allRounds.at(i).id_pilot = stoi(lineInCSV.at(1));
            allRounds.at(i).id_round = stoi(lineInCSV.at(2));

            /// ROZBITI STRINGU NA CASti

            vector<string> onlyTime(3);
            ExplodeString(':',lineInCSV.at(0),onlyTime);    /// Rozbiti casu 1:36,569 --> {1, 36,569}

            /**
                JE NUTNO ROZDELIT SEKUNDY A SETINY
                    - Opet se rozdeluje pomoci funkce ExplodeString s delicem ','
                    - 36,569 --> {36,569}
            */

            vector<string> explodedSecs(2);

            ExplodeString(',',onlyTime.at(1),explodedSecs);

            /// PREKOPIROVANI ZPET DO HLAVNIHO VEKTORU S CASEM - Vypada nasledovne: {1,36,569}

            onlyTime.at(1) = explodedSecs.at(0);
            onlyTime.at(2) = explodedSecs.at(1);

            /// PREVOD NA MS
            allRounds.at(i).time_ms = TimeToMs(onlyTime);
        }
        catch (out_of_range e){
            cout << endl << " * Chyba. "<< "Jeji popis: " << e.what() << " *" << endl;
            exit(0);
        }

        i++;
    }
    /// PRESUNUTI "KURZORU" NA ZACATEK SOUBORU
    f.clear();
    f.seekg(0);
}


/** \brief Prida pozici k casu
 *  \param[out] allRounds    Vektor Round, kterym bude zapisovano poradi
 *
 */
void AddPosition(vector<Round>& allRounds){
    try{
        for(int i = 0; i < allRounds.size(); i++){
            allRounds.at(i).position = i+1;
        }
    }
    catch (out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl << " * Program bude ukoncen. *" << endl;
        exit(0);
    }
}


/** \brief Vypise seznam casu okruhu do konzole
 *  \param[in] allRounds         Vektor struktury Round ze ktereho se cerpa
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
            cout << setw(3) <<  allRounds.at(i).position << "." << " | " << setw(11) << allRounds.at(i).id_pilot << " | " << setw(15) << allRounds.at(i).time << " | " <<  setw(15) <<  allRounds.at(i).time_ms << " |"<< endl;
        cout << endl;
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }

}


/** \brief Exportuje seznam casu do html
 *  \param[in] allRounds    Vektor struktury Round, ktery bude exportovan
 *  \param[in] path         Nazev a cesta souboru
 */
void ExportRounds(const vector<Round>& allRounds, const string& path){

    ofstream exp(path);

    exp << HTMLHead("Vsechny zajete casy");
    exp << "<body>" << endl
        << "<h1>Vsechny zajete casy</h1>" <<  endl
        << "<table cellspacing='0'>"<< endl
        << "<thead><tr>" << endl
        << "<th>Poradi</th><th>ID casu</th><th>ID jezdce</th><th>Cas</th><th>Cas v milisekundach</th>" << endl
        << "<tr></thead><tbody>" << endl;

    try{
        for(int i = 0; i < allRounds.size(); i++){
            exp << "<tr>" << endl;
                exp << "<td>" << allRounds.at(i).position << ". </td>" << endl
                    << "<td>" << allRounds.at(i).id_round << "</td>" << endl
                    << "<td>" << allRounds.at(i).id_pilot << "</td>" << endl
                    << "<td>" << allRounds.at(i).time << "</td>" << endl
                    << "<td>" << allRounds.at(i).time_ms << "</td>" << endl;
            exp << "</tr>" << endl;
        }
    }
    catch(out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl;
        exit(0);
    }

    exp << "</tbody></table></body></html>" << endl;

    exp.close();

    /// KONTROLA ZDA SE SOUBOR VYTVORIL

    ifstream check(path);

    if(check.fail()){
        cout << endl << " * Neco se pokazilo... Soubor nebyl vytvoren.*" << endl
             << " * Mozna chyba: Neexistujici adresar nebo edostatecna prava. *" << endl;
    }
    else{
        cout << endl << " * Soubor byl uspesne vytvoren. *" << endl;
        check.close();
    }
}


/** \brief Setridi vsechny casy podle nejrychlejsiho casu (od nejrychlejsiho po nejpomalejsi)
 *          - Kontroluje pokud cas = 0 --> cas da na konec seznamu
 *  \param[out] allRounds    Vektor struktury Round ktery se tridi
 *
 */
void Sort(vector<Round>& allRounds){
    try{
        for (int i = 0; i < allRounds.size(); i++){
		int j = i;

            while (j > 0 && IsFaster(allRounds.at(j),allRounds.at(j-1))){
                Round temp = allRounds.at(j);
                allRounds.at(j) = allRounds.at(j-1);
                allRounds.at(j-1) = temp;
                j--;
            }
		}
    }
    catch(out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl;
        exit(0);
    }


}

/**
 * \brief Vraci, ktery cas je rychlejsi
 * \param[in] a        Struktura Round - prvni jezdec
 * \param[in] b        Struktura Round - druhy jezdec
 * \return    bool     Vraci true pokud je a rychlejsi, false pokud je a pomalejsi
 */

bool IsFaster(const Round& a, const Round& b){
    /**
        OSETRENI ZDA NEMA CAS 0 MS
            - 0ms znamena prazdna hodnota - jezdec nezajel ani jedno kolo
            - proto ulozime do pomocne promenne velkou hodnotu
    */

    int tmp_a, tmp_b;

    if(a.time_ms == 0)
        tmp_a = 1000000000;
    else
        tmp_a = a.time_ms;

    if(b.time_ms == 0)
        tmp_b = 1000000000;
    else
        tmp_b = b.time_ms;

    /// POROVNANI
    return tmp_a < tmp_b;

}
