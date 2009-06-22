
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimPrimaryGeneratorAction.hh
   $Revision: 1.4 $	
   $Date: 2006/05/05 21:34:59 $
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
   \class QweakSimPrimaryGeneratorAction
    
   \brief Deal with primary particle generation and inject it in the detector

   The primary particle is taken from the root file ep_elastic.root which contains the vertex and kinematic of elastic
   scattered electrons. 

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
//  Update Date:      $Date: 2006/05/05 21:34:59 $
//  CVS/RCS Revision: $Revision: 1.4 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimPrimaryGeneratorAction_h
#define QweakSimPrimaryGeneratorAction_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimPrimaryGeneratorActionMessenger.hh"
#include "QweakSimUserInformation.hh"


// user classes
class QweakSimPrimaryGeneratorActionMessenger;
class QweakSimUserInformation;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class QweakSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
   QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI);    
  ~QweakSimPrimaryGeneratorAction();
  
public:

  void GeneratePrimaries(G4Event* anEvent);
  void ResetNtupleEventCounter() {myEventCounter = 0;}
  void SetNtupleEventCounter(G4int cnt) {myEventCounter = cnt;}
  void SetActiveOctant(G4int noct) {
      G4cout << "%%==> Changing Active Octant to: " << noct << G4endl;
      kActiveOctantNumber = noct;
      }

  G4int             myEventCounter;
  
private:

  G4ParticleGun*                      particleGun;

  QweakSimUserInformation*            myUserInfo;

  QweakSimPrimaryGeneratorActionMessenger* myMessenger;  // pointer to the Messenger

  G4double myPositionX;
  G4double myPositionY;
  G4double myPositionZ;

  G4double      myNormMomentumX;
  G4double      myNormMomentumY;
  G4double      myNormMomentumZ;
  G4ThreeVector myNormMomentum;

  G4int kActiveOctantNumber;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimPrimaryGeneratorAction.hh,v $
//      Revision 1.4  2006/05/05 21:34:59  grimm
//      Added the rotation of the generated tracks into any chosen octant.
//
//      Revision 1.3  2006/01/31 20:15:27  grimm
//      Implemented the usage of the ROOT input event file generated by Michael's Eventgenerator. This will replace the usage of the Root input event file based on the Geant3 output ntuple.
//
//      Revision 1.2  2005/12/27 19:26:17  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
