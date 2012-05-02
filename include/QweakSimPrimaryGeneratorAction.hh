
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
#include "QweakSimEPEvent.hh"

// geant4 classes
class G4ParticleGun;

// user classes
class QweakSimPrimaryGeneratorActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
class QweakSimPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
   QweakSimPrimaryGeneratorAction( QweakSimUserInformation* myUI, QweakSimEPEvent* myEPEvent);    
  ~QweakSimPrimaryGeneratorAction();
  
public:

  void SetBeamPositionX(G4double x) { fPositionX = x; };
  void SetBeamPositionY(G4double y) { fPositionY = y; };
  void SetBeamDirectionX(G4double x) { fNormMomentumX = x; };
  void SetBeamDirectionY(G4double y) { fNormMomentumY = y; };

  void SetBeamRasteringRegion(G4double X_min = -2.0*mm,
                              G4double X_max =  2.0*mm,
                              G4double Y_min = -2.0*mm,
                              G4double Y_max =  2.0*mm) {
    if (X_max < X_min) X_max = X_min;
    if (Y_max < Y_min) Y_max = Y_min;
    fPositionX_min = X_min;
    fPositionX_max = X_max;
    fPositionY_min = Y_min;
    fPositionY_max = Y_max;
  }

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
  
  QweakSimEPEvent* myEvent;

  QweakSimPrimaryGeneratorActionMessenger* myMessenger;  // pointer to the Messenger

  G4double fPositionX;
  G4double fPositionY;
  G4double fNormMomentumX;
  G4double fNormMomentumY;

  G4double fPositionX_min;
  G4double fPositionX_max;
  G4double fPositionY_min;
  G4double fPositionY_max;

  G4int kActiveOctantNumber;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

