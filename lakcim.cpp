#include "lakcim.h"
#include "memtrace.h"



Lakcim::Lakcim(const int zipcode, const std::string telepules,
                const std::string utca, const int hazszam)
    {
        this->telepules = telepules;
        this->utca = utca;
        this->zipcode = zipcode;
        this->hazszam = hazszam;

    }

void Lakcim::setTelepules( const std::string sztring)
    {
       telepules = sztring;
    }

void Lakcim::setUtca( const std::string sztring){
        utca = sztring;
    }

Lakcim& Lakcim::operator = ( const Lakcim &cim ) {
        telepules = cim.telepules;
        utca = cim.utca;
        zipcode = cim.zipcode;
        hazszam = cim.hazszam;
        return *this;
      }
