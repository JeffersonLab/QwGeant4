
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
//#include "QweakSimUserInformation.hh"


// user classes
class QweakSimPrimaryGeneratorActionMessenger;
//class QweakSimUserInformation;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class QweakSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
   //QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI);    
   QweakSimPrimaryGeneratorAction( );    
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

  //QweakSimUserInformation*            myUserInfo;

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

