
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimTrackingAction.hh
   $Revision: 1.3 $	
   $Date: 2006/01/06 21:34:40 $
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
   \class QweakSimTrackingAction
    
   \brief Adds additional information to primary/secondary track before track starts stepping.

   Creates user track info using current primary track pointer as an input.
   Fills user track info with data stored in myUserInfo (class QweakUserInformation)

   Placeholder for a long explaination
    
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimTrackingAction_h
#define QweakSimTrackingAction_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimUserInformation.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimTrackingActionMessenger.hh"
#include "QweakSimTrajectory.hh"

// user class
class QweakSimTrackInformation;
class QweakSimUserInformation;
class QweakSimTrackingActionMessenger;
class QweakSimTrajectory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimTrackingAction : public G4UserTrackingAction
{

public:

   QweakSimTrackingAction(QweakSimUserInformation*);
  ~QweakSimTrackingAction();

  void  PreUserTrackingAction(const G4Track* aTrack);
  void PostUserTrackingAction(const G4Track* aTrack);

  void SetTrackingPrimaryOnlyFlag(G4bool myflag) {TrackingPrimaryOnlyFlag = myflag;}

private:

  QweakSimTrackingActionMessenger* pTrackingActionMessenger;  // pointer to the Messenger

  QweakSimUserInformation*         myUserInfo;


  G4bool TrackingPrimaryOnlyFlag;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

