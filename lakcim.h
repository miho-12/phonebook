#ifndef LAKCIM_H_INCLUDED
#define LAKCIM_H_INCLUDED
#include <cstddef>
#include <cstring>
#include <string>
#include "memtrace.h"


class Lakcim {
    int zipcode;
    std::string telepules;
    std::string utca;
    int hazszam;
public:
    Lakcim() {zipcode = 0;  telepules = "";  utca = "";  hazszam = 0;}

    Lakcim(const int zipcode, const std::string telepules,
            const std::string utca, const int hazszam);

    int getZipCode()const {return zipcode;}

    std::string getTelepules()const {return telepules;}

    std::string getUtca()const {return utca;}

    int getHazszam()const {return hazszam;}

    void setZipCode(const int zipcode){this->zipcode = zipcode;}

    void setTelepules( const std::string sztring);

    void setUtca( const std::string sztring);

    void setHazszam(const int hazszam){this->hazszam = hazszam;}

    //Az értékadás miatt kellett bevezetni az assign operatort a Rekord-hoz hasonlóan
     Lakcim &operator = ( const Lakcim &cim );



};

#endif // LAKCIM_H_INCLUDED
