#include "memtrace.h"
#include "rekord.h"


Rekord::Rekord(){veznev = ""; kernev = ""; telszam = ""; Lakcim c;} //default konstrukttor

Rekord::Rekord(std::string veznev, std::string kernev,
                std::string telszam, Lakcim& cim) //paraméterezett konstruktor
     {
        this->cim = cim;
        this->veznev = veznev;
        this->kernev = kernev;
        this->telszam = telszam;

    }

    void Rekord::setCim(const int zipcode,  const std::string telepules,
                          const std::string utca, const int hazszam)
    {
        this->cim.setZipCode(zipcode);
        this->cim.setTelepules(telepules);
        this->cim.setUtca(utca);
        this->cim.setHazszam(hazszam);
    }

    Rekord& Rekord::operator = ( const Rekord &R )
    {
        veznev = R.veznev;
        kernev = R.kernev;
        telszam = R.telszam;
        this->cim = R.cim; //Ezert fontos a Lakcimben definiálni az assign operAtort
        return *this;
      }
