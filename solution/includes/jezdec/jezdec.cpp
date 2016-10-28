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

/**
 * @brief Naplni strukturu TJEZDEC daty z csv souboru
 * @param f              Soubor ze ktereho se nacitaji jezdci
 * @param jezdci         Vektor struktury TJEZDEC do ktereho se bude ukladat
 * @param casy           Vektor struktury TCAS ze ktereho se nacitaji casy okruhu
 * @param jezdci         Pocet zajetych okruhu
 */
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

void vlozitPoradi(vector<TJEZDEC> &jezdci){
    try{
        for(int i = 0; i < jezdci.size(); i++){
            jezdci.at(i).poradi = i+1;
        }
    }
    catch (out_of_range e){
        cout << endl << "Zachycena vyjimka! "<< endl;
        cout << "Jeji popis: " << e.what() <<endl;
    }
}


/**
 * @brief Vypise seznam jezdcu do konzole - pouziti i pro postupujici
 * @param jezdci         Vektor struktury TJEZDEC ze ktereho se cerpa
 * @param pocet_postupujich  Kolik jich postupuje (se vypise)
 */
void vypisJezdcu(const vector<TJEZDEC> &jezdci, const int &pocet){

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
        for(int i = 0; i < pocet; i++){
            cout << setw(3) << jezdci.at(i).poradi <<". | " << setw(4) << jezdci.at(i).id_j << " | " << setw(10) << jezdci.at(i).jmeno << " | " <<  setw(10) <<  jezdci.at(i).prijmeni << " |" << setw(4) << jezdci.at(i).poc_kol << " |"
            << setw(9) << msNaCas(jezdci.at(i).nejrychlejsi) << " |" << setw(9) << msNaCas(jezdci.at(i).nejpomalejsi) << " |" << setw(9) << msNaCas(jezdci.at(i).prumerny) << endl;
        }
    }
    catch (out_of_range e){
        cout << endl << " * Chyba. "<< "Jeji popis: " << e.what() << " *" << endl;
    }

    cout << endl;
}

void vypisJezdce(const vector<TJEZDEC> &jezdci, string jmeno){

    int poc_bunek = pocetBunekVRadku(' ',jmeno), nalezen = 0;
    vector<string> rozdelene_jmeno(poc_bunek);
    vector<TJEZDEC> nalezeni_jezdci;
    vector<TJEZDEC> jezdci_malym(jezdci.size()); /// POMOCNY VEKTOR STRUKURY TJEZDEC PRO LOWERCASE JEZDCE
    jezdci_malym = jezdci;  /// PREKOPIROVANI JEZDCU

    /// ROZDELI RADEK DO BUNEK
    rozdelitString(' ',jmeno,rozdelene_jmeno);

    /// NUTNO PREDELENAT NA LOWERCASE Z DUVODOU ZE UZIVATL MUZE MIT ZAPNUTY NAPR CAPS LOCK
    if(rozdelene_jmeno.size() == 1)
        transform(rozdelene_jmeno.at(0).begin(), rozdelene_jmeno.at(0).end(), rozdelene_jmeno.at(0).begin(),::tolower);

    if(rozdelene_jmeno.size() == 2){
        transform(rozdelene_jmeno.at(0).begin(), rozdelene_jmeno.at(0).end(), rozdelene_jmeno.at(0).begin(),::tolower);
        transform(rozdelene_jmeno.at(1).begin(), rozdelene_jmeno.at(1).end(), rozdelene_jmeno.at(1).begin(),::tolower);
    }

    try{
        for(int i = 0; i < jezdci.size(); i++){

            transform(jezdci_malym.at(i).jmeno.begin(), jezdci_malym.at(i).jmeno.end(), jezdci_malym.at(i).jmeno.begin(),::tolower);
            transform(jezdci_malym.at(i).prijmeni.begin(), jezdci_malym.at(i).prijmeni.end(), jezdci_malym.at(i).prijmeni.begin(),::tolower);

            if(rozdelene_jmeno.size() == 1){ /// POKUD JE ZADANO JEN JMENO NEBO JEN PRIJMENI

                if(rozdelene_jmeno.at(0) == jezdci_malym.at(i).jmeno || rozdelene_jmeno.at(0) == jezdci_malym.at(i).prijmeni){
                    nalezen = 1;
                    nalezeni_jezdci.push_back(jezdci.at(i));
                }
            }
            else if(rozdelene_jmeno.size() == 2){
                if( (rozdelene_jmeno.at(0) == jezdci_malym.at(i).jmeno || rozdelene_jmeno.at(0) == jezdci_malym.at(i).prijmeni) && (rozdelene_jmeno.at(1) == jezdci_malym.at(i).jmeno || rozdelene_jmeno.at(1) == jezdci_malym.at(i).prijmeni)){
                    nalezen = 1;
                    nalezeni_jezdci.push_back(jezdci.at(i));
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
    if(nalezen == 0)
        cout << " * Zadny jezdec nebyl nalezen. *" << endl;
    else{
        cout << setw(4) << "P " << " | "<< " ID " << " | " << setw(10) << " JMENO " << " | " <<  setw(10) << " PRIJMENI " << " | " << "KOL |" << setw(11) << " NEJLEPSI |"<< setw(11) << " NEJHORSI |"<< setw(9) << " PRUMERNY"<<endl;
        for(int i = 0; i < 78; i++)
            cout << "=";
        cout << endl;

        try{
            for(int i = 0; i < nalezeni_jezdci.size(); i++)
                cout << setw(3) << nalezeni_jezdci.at(i).poradi <<". | " << setw(4) << nalezeni_jezdci.at(i).id_j << " | " << setw(10) << nalezeni_jezdci.at(i).jmeno << " | " <<  setw(10) <<  nalezeni_jezdci.at(i).prijmeni << " |" << setw(4) << nalezeni_jezdci.at(i).poc_kol << " |"
                << setw(9) << msNaCas(nalezeni_jezdci.at(i).nejrychlejsi) << " |" << setw(9) << msNaCas(nalezeni_jezdci.at(i).nejpomalejsi) << " |" << setw(9) << msNaCas(nalezeni_jezdci.at(i).prumerny) << endl;
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
void exportJezdcu(const vector<TJEZDEC> &jezdci, string nazev){

    ofstream exp(nazev);

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
        for(int i = 0; i < jezdci.size(); i++){
            exp << "<tr>" << endl;
                exp << "<td>" << jezdci.at(i).poradi << ". </td>" << endl
                    << "<td>" << jezdci.at(i).id_j << "</td>" << endl
                    << "<td>" << jezdci.at(i).jmeno << "</td>" << endl
                    << "<td>" << jezdci.at(i).prijmeni << "</td>" << endl
                    << "<td>" << jezdci.at(i).poc_kol << "</td>" << endl
                    << "<td>" << msNaCas(jezdci.at(i).nejrychlejsi) << "</td>" << endl
                    << "<td>" << msNaCas(jezdci.at(i).nejpomalejsi) << "</td>" << endl
                    << "<td>" << msNaCas(jezdci.at(i).prumerny) << "</td>" << endl;
            exp << "</tr>" << endl;
        }
    }
    catch(out_of_range e){
        cout << endl << " * Chyba! "<< "Jeji popis: " << e.what() << " *" << endl;
    }

    exp << "</tbody></table></body></html>" << endl;

}



/**
 * @brief Vraci pro funkci sort() ktery zaznam je mensi
 * @param a        Struktura TJEZDEC - prvni jezdec
 * @param b        Struktura TJEZDEC - druhy jezdec
 * @return Vraci true pokud je a rychlejsi, false pokud je a pomalejsi
 */
bool jezdecJeRychlejsi(const TJEZDEC &a, const TJEZDEC &b){
    /**
        OSETRENI ZDA NEMA CAS 0 MS
            - 0ms znamena prazdna hodnota - jezdec nezajel ani jedno kolo
            - proto ulozime do pomocne promenne velkou hodnotu
    */

    unsigned pom_a, pom_b;

    if(a.nejrychlejsi == 0)
        pom_a = 1000000000;
    else
        pom_a = a.nejrychlejsi;

    if(b.nejrychlejsi == 0)
        pom_b = 1000000000;
    else
        pom_b = b.nejrychlejsi;

    /// POROVNANI
    return pom_a < pom_b;

}
