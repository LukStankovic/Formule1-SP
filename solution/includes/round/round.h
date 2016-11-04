#ifndef ROUND_H
#define ROUND_H


/** \brief Hlavickovy soubor pro strukturu Round
 *  \file includes/round/round.h
 */

using namespace std;

/** \struct Round
 *  \brief Struktura pro uchovavani dat zajetych kol. Uchovova cas jak ve stringu ve tvaru m:s,ms tak i ciste v ms.
 *  \param id_round          Specificke ID urcene pro identifikaci casu - PK
 *  \param id_pilot          Specificke ID urcene pro identifikaci jezdce - FK
 *  \param time              Cas kola v retezci
 *  \param time_ms           Cas kola prevedeny na ms
 *  \param position          Pozice casu
 *
 */

typedef struct{

    int id_round;
    int id_pilot;

    string time;
    int time_ms;

    int position;
}Round;

/// Naplni strukturu Round datdy z csv souboru
void FillRounds(ifstream& f, vector<Round>& casy);

/// Prida pozici k casu
void AddPosition(vector<Round>& allRounds);

/// Vypise seznam casu okruhu do konzole
void PrintRounds(const vector<Round>& allRounds);

/// Exportuje seznam casu do html
void ExportRounds(const vector<Round>& allRounds, const string& path);

/// Setridi vsechny casy podle nejrychlejsiho casu (od nejrychlejsiho po nejpomalejsi)
void Sort(vector<Round>& allRounds);

/// Vraci, ktery cas je rychlejsi
bool IsFaster(const Round& a, const Round& b);

#endif
