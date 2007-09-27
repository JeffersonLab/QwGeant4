//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserCerenkov_PMTEvent.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:16:56 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:16:56 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserCerenkov_PMTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserCerenkov_PMTEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserCerenkov_PMTEvent::QweakSimUserCerenkov_PMTEvent() 
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserCerenkov_PMTEvent::~QweakSimUserCerenkov_PMTEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimUserCerenkov_PMTEvent::Initialize()
{
  DetectorID                     = 0;
  TrackID                        = 0;

  PMTHasBeenHit                  = 0;
  PMTLeftNbOfHits                = 0;
  PMTRightNbOfHits               = 0;
  PMTTotalNbOfHits               = 0;
  PMTLeftNbOfPEs                 = 0;
  PMTRightNbOfPEs                = 0;
  PMTTotalNbOfPEs                = 0;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserCerenkov_PMTEvent.cc,v $
//      Revision 1.2  2005/12/27 19:16:56  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
