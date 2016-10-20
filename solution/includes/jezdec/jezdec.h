#ifndef JEZDEC_H
#define JEZDEC_H

#include "../cas/cas.h"
using namespace std;

/** @struct TJEZDEC
 *  @brief Struktura pro uchovavani dat jezdcu
 *  @param TJEZDEC.ID            Specificke ID urcene pro identifikaci jezdce
 *  @param TJEZDEC.jmeno         Krestni jmeno jezdce
 *  @param TJEZDEC.prijmeni      Prijmeni jezdce
 *  @param TJEZDEC.poc_kol       Pocet okruhu, ktere jezdec zajel

 */

typedef struct{

    int id_j;

    string jmeno;
    string prijmeni;

    int poc_kol;


}TJEZDEC;

void naplnitJezdce(ifstream &f, vector<TJEZDEC> &jezdci, vector<TCAS> &casy, int pocet_casu);
void vypisJezdcu(vector<TJEZDEC> const &jezdci, int pocet);

#endif
