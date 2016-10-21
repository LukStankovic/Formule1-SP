#ifndef FUNKCE_H
#define FUNKCE_H

using namespace std;

void rozdelitString(char delic, string retezec,vector<string>& pole);
int pocetZaznamu(ifstream &f);
int pocetBunekVRadku(char delic, string retezec);
unsigned casNaMs(vector<string> cas);
void msNaCas(unsigned ms, vector<int> &cas);
string msNaCas(unsigned ms);
void vypisMenu();
#endif
