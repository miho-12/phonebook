#ifndef REKORD_H_INCLUDED
#define REKORD_H_INCLUDED
#include "memtrace.h"
#include "string.h"
#include "lakcim.h"
#include <ostream>


class Rekord {
    std::string  veznev;
    std::string kernev;
    std::string telszam;
    Lakcim cim; //Lehetne itt tárolni azt a 4 adattagot,
                //ami a Lakcim osztályban van, de így jóval átláthatóbb

public:

    Rekord();

    Rekord(std::string veznev, std::string kernev, std::string telszam, Lakcim& cim);

    int getCimZipCode()const {return cim.getZipCode();}

    std::string getCimTelepules() const {return cim.getTelepules();}

    std::string getCimUtca()const {return cim.getUtca();}

    int getCimHazszam()const {return cim.getHazszam();}

    std::string getVeznev()const {return veznev;}

    std::string getKernev()const {return kernev;}

    std::string getTelszam()const {return telszam;}

    void setVeznev(const std::string sztring)
    {
        veznev = sztring;
    }

    void setKernev( const std::string sztring)
    {
        kernev = sztring;
    }

    void setTelszam( std::string sztring)
    {
        telszam = sztring;
    }

    void setCimZip(const int zipcode){cim.setZipCode(zipcode);}

    void setCimTelep( const std::string telepules){cim.setTelepules(telepules); }

    void setCimUtca( const std::string utca){cim.setUtca(utca); }

    void setCimHazszam(const int hazszam){cim.setHazszam(hazszam);}

    void setCim(const int zipcode,  const std::string telepules,
                  const std::string utca, const int hazszam);

    //A dinamikusan foglalt memória miatt rengeteg átmásolást kell végezni a telefonkönyvünkben, amihez "elengedhetetlen" az assign operator
    Rekord &operator = ( const Rekord &R );

};

//Megkönnyíti a kiírást
 inline std::ostream& operator<<(std::ostream& os,  Rekord& r)
{
    os << " "<< r.getVeznev() << " " << r.getKernev()
    << "| Priv. telefonszama: " << r.getTelszam()
    << "| Lakcime: " << r.getCimZipCode() <<" "
    << r.getCimTelepules() <<" "
    << r.getCimUtca() <<" "
    << r.getCimHazszam() << "\n";
    return os;
}


#endif // REKORD_H_INCLUDED
