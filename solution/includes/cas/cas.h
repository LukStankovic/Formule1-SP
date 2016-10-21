#ifndef CASY_H
#define CASY_H


using namespace std;

/** @struct TCAS
 *  @brief Struktura pro uchovavani dat jezdcu
 *  @param TJEZDEC.id_j          Specificke ID urcene pro identifikaci jezdce
 *  @param TJEZDEC.cas           Cas kola v retezci
 *  @param TJEZDEC.cas_ms        Cas kola prevedeny na ms

 */

typedef struct{
    int id_c;
    int id_j;
    string cas;
    unsigned int cas_ms;
}TCAS;

void naplnitCas(ifstream &f, vector<TCAS> &casy);
void vypisCasu(vector<TCAS> const &casy, int pocet);

#endif
