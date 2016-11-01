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
    int id_round;
    int id_pilot;
    string time;
    int time_ms;
}Round;

/// NAPLNI STRUKTURU DATY ZE SOUBORU
void FillRounds(ifstream& f, vector<Round>& casy);

/// VYPISE TABULKU DO KONZOLE SE VSEMI CASY
void PrintRounds(const vector<Round>& allRounds);

void ExportRounds(const vector<Round>& allRounds, const string& fileName);

/// POROVANI CASU
bool IsRoundFaster(const Round& a, const Round& b);

#endif
