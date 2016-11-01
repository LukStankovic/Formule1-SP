#ifndef JEZDEC_H
#define JEZDEC_H

#include "../round/round.h"

/** @struct TJEZDEC
 *  @brief Struktura pro uchovavani dat jezdcu z csv souboru. Uchovava jednak jmeno a prijmeni, ale i nejrychlejsi, nejpomalejsi a prumerny cas. Dale uchovava i poradi daneho jezdce.
 *  @param id_j          Specificke ID urcene pro identifikaci jezdce
 *  @param poradi        Poradi jezdce, ktere se vklada az po setrizeni jezdcu
 *  @param jmeno         Krestni jmeno jezdce
 *  @param prijmeni      Prijmeni jezdce
 *  @param poc_kol       Pocet okruhu, ktere jezdec zajel - dopocitava se automaticky podle zaznamu v souboru casy.csv
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

void ExportPilots(const vector<Pilot>& allPilots, string fileName, const int& num);

/// POROVNAVANI CASU
bool IsPilotFaster(const Pilot& a, const Pilot& b);

#endif
