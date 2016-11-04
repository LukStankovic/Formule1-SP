#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../pilot/pilot.h"
#include "../round/round.h"

/** \brief Hlavickovy soubor pro vseobecne funkce pouzivane v programu
 *  \file includes/functions/functions.h
 */

using namespace std;

/// Rozdeli string podle delice do vektoru stringu
void ExplodeString(const char& delimiter, string str, vector<string>& explodedString);

/// Vrati pocet bunek v stringu (radku), zjistuje pomoci delice
int CountLines(ifstream& f);

/// Vrati pocet radku (zaznamu) v souboru
int CountCells(const char& delimiter, const string& str);

/// Prevadi a vrati cas na ms ze stringu
int TimeToMs(const vector<string>& time);

/// Vraci pomoci reference vektoru cass rozdeleny na minuty, vteriny, setiny
void MsToTime(int ms, vector<int>& time);

/// Vrati string s casem ve tvaru min:s,ms
string MsToTime(int ms);

/// Prepise string na mala pismena
void ToLower(string& str);

/// Vrati ve stringu HTML hlavicku se styly
string HTMLHead(const string& title);

/// Vypise do konzole menu vcetne zadavani volby
void PrintMenu(vector<Pilot> allPilots, vector<Round> allRounds, const int& numberOfPilots, const int& numberOfRounds);

#endif
