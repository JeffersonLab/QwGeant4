//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimCerenkov_DetectorSD.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:22:33 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimCerenkov_DetectorSD
    
   \brief Storing hit information of the Cerenkov detector

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:22:33 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimCerenkov_DetectorSD_h
#define QweakSimCerenkov_DetectorSD_h 

// system includes
#include "cpp_include.h"
//#include "Root_include.h"
#include "Geant4_include.hh"


// user classes
#include "QweakSimCerenkov_DetectorHit.hh"
#include "QweakSimTrackInformation.hh"

// user classes


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimCerenkov_DetectorSD : public G4VSensitiveDetector
{

public:
  QweakSimCerenkov_DetectorSD(G4String name);
  ~QweakSimCerenkov_DetectorSD();
  
  void Initialize(G4HCofThisEvent* HCE);
  G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist);
  void EndOfEvent(G4HCofThisEvent* HCE);

private:
  
  QweakSimCerenkovDetectorHitsCollection*  CerenkovDetector_HitsCollection;
  
  G4int CerenkovDetector_CollectionID;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimCerenkov_DetectorSD.hh,v $
//      Revision 1.2  2005/12/27 19:22:33  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

