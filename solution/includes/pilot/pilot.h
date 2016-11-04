#ifndef JEZDEC_H
#define JEZDEC_H

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

/// NAPLNI STRUKTURU TJEZDEC DATY Z CSV SOUBORU
void FillPilots(ifstream& f, vector<Pilot>& allPilots, vector<Round>& allRounds,const int& numberOfRounds);

/// PRIDA POZICI
void AddPosition(vector<Pilot>& allPilots);

/// VYPISE SEZNAM JEZDCU DO KONZOLE - POUZITI I PRO POSTUPUJICI
void PrintPilots(const vector<Pilot>& allPilots, const int& num);

/// VYPIS JEDNOHO JEZDCE
void PrintPilot(const vector<Pilot>& allPilots, string name);

void ExportPilots(const vector<Pilot>& allPilots, const string& path, const int& num);

void ExportPilot(const vector<Pilot>& allPilots, string name, const string& path);

void Sort(vector<Pilot>& allPilots);

bool IsFaster(const Pilot& a, const Pilot& b);

#endif
