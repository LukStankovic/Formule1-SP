#ifndef JEZDEC_H
#define JEZDEC_H

#include "../cas/cas.h"

/** @struct TJEZDEC
 *  @brief Struktura pro uchovavani dat jezdcu
 *  @param TJEZDEC.ID            Specificke ID urcene pro identifikaci jezdce
 *  @param TJEZDEC.jmeno         Krestni jmeno jezdce
 *  @param TJEZDEC.prijmeni      Prijmeni jezdce
 *  @param TJEZDEC.poc_kol       Pocet okruhu, ktere jezdec zajel - dopocitava se automaticky podle zaznamu v souboru casy.csv
 */

typedef struct{

    int id_j;

    string jmeno;
    string prijmeni;

    int poc_kol;

    double prumerny;
    unsigned nejrychlejsi;
    unsigned nejpomalejsi;

    int poradi;

}TJEZDEC;

/// NAPLNI STRUKTURU TJEZDEC DATY Z CSV SOUBORU
void naplnitJezdce(ifstream &f, vector<TJEZDEC> &jezdci, vector<TCAS> &casy, int pocet_casu);

void vlozitPoradi(vector<TJEZDEC> &jezdci);

/// VYPISE SEZNAM JEZDCU DO KONZOLE - POUZITI I PRO POSTUPUJICI
void vypisJezdcu(const vector<TJEZDEC> &jezdci, const int &pocet);

/// VYPIS JEDNOHO JEZDCE
void vypisJezdce(const vector<TJEZDEC> &jezdci, string jmeno);

void exportJezdcu(const vector<TJEZDEC> &jezdci, string nazev, int pocet);

/// POROVNAVANI CASU
bool jezdecJeRychlejsi(const TJEZDEC &a, const TJEZDEC &b);

#endif
