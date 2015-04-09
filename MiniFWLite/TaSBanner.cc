#include "Rtypes.h"
#include "Riostream.h"
#include "TSystem.h"
#include <iostream>

const char* VTAG="02-YY-ZZ";

Int_t doBanner() {
    if (! gSystem->Getenv("WHOISTAS")) {
        std::cout << std::endl
             << "\033[1mMiniFWLite v" << VTAG
                                 << " -- A FORTRAN++ data analysis framework developed by TaS\033[0m" << std::endl;
    } else {
        std::cout << std::endl
             << "\033[1mMiniFWLite v" << VTAG
                                 << " -- A FORTRAN++ data analysis framework developed by TaS,  a.k.a. Turf and Surf,"<< std::endl
             << "                        a.k.a. West Coast Mafia,  a.k.a. Victory Squad,  a.k.a. The Beaver Stompers."<< std::endl
             << "                        Mad props to FG3 & Punizzle for carrying the load on the nTuple code. Shout-"<< std::endl
             << "                        outs to  Jmu West Psi keeping  it real  at a bird's-eye  view,  The Bristol" << std::endl
             << "                        Pistol sans-daft-izzle, and  Warren G Hardly needs characterization.  Holla" << std::endl
             << "                        at my FNAL boyz Oli Oli Oxendatenführer, Ingo's the Lingo Can Sing-Oh!, and" << std::endl
             << "                        Burkett Tracks-charged-particles-for-miles. Much respect to the rest of the" << std::endl
             << "                        UCSD, UCSB and FNAL crewz.  If your name is not explicitly mentioned, it is" << std::endl
             << "                        not for lack of love, it is due solely to lack of imagination and indolence.\033[0m" << std::endl;
    }
        std::cout << "                        http://cmssw.cvs.cern.ch/cgi-bin/cmssw.cgi/UserCode/JRibnik/CMS2" << std::endl << std::endl;

    return 0 ;
}

static Int_t dummy = doBanner();
