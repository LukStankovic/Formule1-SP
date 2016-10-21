#ifndef FUNKCE_H
#define FUNKCE_H

using namespace std;

/// ROZDELI STRING PODLE DELICE DO VEKTORU
void rozdelitString(char delic, string retezec,vector<string> &pole);

/// VRATI POCET ZAZNAMU (RADKU) V SOUBORU
int pocetZaznamu(ifstream &f);

/// VRATI POCET BUNEK V STRINGU (RADKU), ZJISTUJE POMOCI DELICE
int pocetBunekVRadku(char delic, string retezec);

/// VRATI CAS V MS ZE STRINGU
unsigned casNaMs(vector<string> cas);

/// POSILA REFERENCI VEKTORU S CASEM ROZDELENYM NA MINUTY, VTERINY, SETINY
void msNaCas(unsigned ms, vector<int> &cas);

/// VRATI STRING S CASEM VE FORMATU MIN:SEK:SET
string msNaCas(unsigned ms);

/// VYPISE DO KONZOLE MENU
void vypisMenu();

#endif
