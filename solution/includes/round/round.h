#ifndef CASY_H
#define CASY_H

using namespace std;

/** \struct Round
 *  \brief Struktura pro uchovavani dat jezdcu
 *  \param id_round          Specificke ID urcene pro identifikaci casu - PK
 *  \param id_pilot          Specificke ID urcene pro identifikaci jezdce - FK
 *  \param time              Cas kola v retezci
 *  \param time_ms           Cas kola prevedeny na ms
 *
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

void ExportRounds(const vector<Round>& allRounds, const string& path);

void Sort(vector<Round>& allRounds);

/// POROVANI CASU
bool IsFaster(const Round& a, const Round& b);

#endif
