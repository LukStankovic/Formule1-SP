#ifndef PILOT_H
#define PILOT_H

#include "../round/round.h"

/** \brief Hlavickovy soubor pro strukturu Pilot
 *  \file includes/pilot/pilot.h
 */


/** \struct Pilot
 *  \brief Struktura pro uchovavani dat jezdcu z csv souboru. Uchovava jednak jmeno a prijmeni, ale i nejrychlejsi, nejpomalejsi a prumerny cas. Dale uchovava i poradi daneho jezdce.
 *  \param id_pilot             Specificke ID urcene pro identifikaci jezdce
 *  \param position             Poradi jezdce, ktere se vklada az po setrizeni jezdcu
 *  \param surname              Krestni jmeno jezdce
 *  \param prijmeni             Prijmeni jezdce
 *  \param number_of_rounds     Pocet okruhu, ktere jezdec zajel - dopocitava se automaticky podle zaznamu v souboru casy.csv
 *  \param mean_time            Celkovy prumerny cas
 *  \param best_time            Nejlepe zajety cas
 *  \param worst_time           Nejhure zajety cas
 *
 */

typedef struct{

    int id_pilot;
    int position;

    string name;
    string surname;

    int number_of_rounds;

    double mean_time;
    int best_time;
    int worst_time;

}Pilot;

/// Naplni strukturu Pilot daty z CSV souboru
void FillPilots(ifstream& f, vector<Pilot>& allPilots, const vector<Round>& allRounds,const int& numberOfRounds);

/// Prida pozici k jezdci
void AddPosition(vector<Pilot>& allPilots);

/// Vypise seznam jezdcu do konzole - pouziti i pro postupujici
void PrintPilots(const vector<Pilot>& allPilots, const int& num);

/// Vypise jednoho jezdce (popr. vice jezdcu pokud maji stejne jmeno) do konzole
void PrintPilot(const vector<Pilot>& allPilots, string name);

/// Exportuje seznam jezdcu do html
void ExportPilots(const vector<Pilot>& allPilots, const string& path, const int& num);

/// Exportuje jednoho jezdce (popr. vice jezdcu pokud maji stejne jmeno) do konzole + vypise vsechny jeho kola
void ExportPilot(const vector<Pilot>& allPilots, string name, const vector<Round>& allRounds, const string& path);

/// Setridi vsechny jezdce podle nejrychlejsiho casu (od nejrychlejsiho po nejpomalejsi)
void Sort(vector<Pilot>& allPilots);

/// Vraci, ktery jezdec je rychlejsi
bool IsFaster(const Pilot& a, const Pilot& b);

#endif
