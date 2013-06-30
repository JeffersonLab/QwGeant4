/**
 
   \file QweakSimUserCerenkov_PMTEvent.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:16:56 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserCerenkov_PMTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserCerenkov_PMTEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserCerenkov_PMTEvent::Initialize()
{
  PMTHasBeenHit.clear();

  PMTLeftNbOfHits.clear();
  PMTRightNbOfHits.clear();
  PMTTotalNbOfHits.clear();
  PMTLeftNbOfPEs.clear();
  PMTRightNbOfPEs.clear();
  PMTTotalNbOfPEs.clear();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
