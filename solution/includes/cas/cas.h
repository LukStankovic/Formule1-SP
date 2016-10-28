#ifndef CASY_H
#define CASY_H

using namespace std;

/** @struct TCAS
 *  @brief Struktura pro uchovavani dat jezdcu
 *  @param TJEZDEC.id_c          Specificke ID urcene pro identifikaci casu - PK
 *  @param TJEZDEC.id_j          Specificke ID urcene pro identifikaci jezdce - FK
 *  @param TJEZDEC.cas           Cas kola v retezci
 *  @param TJEZDEC.cas_ms        Cas kola prevedeny na ms
 */

typedef struct{
    int id_c;
    int id_j;
    string cas;
    unsigned int cas_ms;
}TCAS;

/// NAPLNI STRUKTURU DATY ZE SOUBORU
void naplnitCas(ifstream &f, vector<TCAS> &casy);

/// VYPISE TABULKU DO KONZOLE SE VSEMI CASY
void vypisCasu(const vector<TCAS> &casy);

void exportCasu(const vector<TCAS> &casy, string nazev);

/// POROVANI CASU
bool casJeRychlejsi(const TCAS &a, const TCAS &b);

#endif
