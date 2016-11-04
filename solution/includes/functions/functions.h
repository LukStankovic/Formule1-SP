#ifndef FUNKCE_H
#define FUNKCE_H

#include "../pilot/pilot.h"
#include "../round/round.h"

using namespace std;

/// ROZDELI STRING PODLE DELICE DO VEKTORU
void ExplodeString(const char& delimiter, string str, vector<string>& explodedString);

/// VRATI POCET ZAZNAMU (RADKU) V SOUBORU
int CountLines(ifstream& f);

/// VRATI POCET BUNEK V STRINGU (RADKU), ZJISTUJE POMOCI DELICE
int CountCells(const char& delimiter, const string& str);

/// VRATI CAS V MS ZE STRINGU
int TimeToMs(const vector<string>& time);

/// POSILA REFERENCI VEKTORU S CASEM ROZDELENYM NA MINUTY, VTERINY, SETINY
void MsToTime(int ms, vector<int>& time);

/// VRATI STRING S CASEM VE FORMATU MIN:SEK:SET
string MsToTime(int ms);

void ToLower(string& str);

string HTMLHead(const string& title);

/// VYPISE DO KONZOLE MENU
void PrintMenu(vector<Pilot> allPilots, vector<Round> allRounds, const int& numberOfPilots, const int& numberOfRounds);

#endif
