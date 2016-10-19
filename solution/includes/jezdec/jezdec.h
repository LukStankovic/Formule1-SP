#ifndef JEZDEC_HPP
#define JEZDEC_HPP


using namespace std;

/** @struct TJEZDEC
 *  @brief Struktura pro uchovavani dat jezdcu
 *  @param TJEZDEC.ID            Specificke ID urcene pro identifikaci jezdce
 *  @param TJEZDEC.jmeno         Krestni jmeno jezdce
 *  @param TJEZDEC.prijmeni      Prijmeni jezdce
 *  @param TJEZDEC.poc_kol       Pocet okruhu, ktere jezdec zajel

 */

typedef struct{

    int id_jezdec;

    string jmeno;
    string prijmeni;

    int poc_kol;

}TJEZDEC;


#endif
