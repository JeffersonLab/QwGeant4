
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

// geant4 includes
#include "G4ios.hh"
#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

#include "QweakSimUserInformation.hh"

// geant4 classes
class G4ParticleGun;

// user classes
class QweakSimPrimaryGeneratorActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class QweakSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
   QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI);    
   //QweakSimPrimaryGeneratorAction( );    
  ~QweakSimPrimaryGeneratorAction();
  
public:

  void SetBeamRasteringRegion(G4double X_min, G4double X_max, G4double Y_min, G4double Y_max);
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

  G4double PositionX_min;
  G4double PositionX_max;
  G4double PositionY_min;
  G4double PositionY_max;
	
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

