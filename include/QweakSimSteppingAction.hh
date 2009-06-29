
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimSteppingAction_h
#define QweakSimSteppingAction_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 
#include "QweakSimUserInformation.hh"
#include "QweakSimSteppingVerbose.hh"
#include "QweakSimTrackInformation.hh"

#include "QweakSimEPEvent.hh"

// system classes
//class G4Step;

class QweakSimEPEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimSteppingAction : public G4UserSteppingAction
{
  
public:
  QweakSimSteppingAction(QweakSimUserInformation* myUInfo, QweakSimEPEvent* myEPEvent);
  ~QweakSimSteppingAction(){};
  
  void UserSteppingAction(const G4Step*);

  G4int GetNumOfAtRestSecondaries(){return fpSteppingManager->GetfN2ndariesAtRestDoIt();};
  G4int GetNumOfAlongStepSecondaries(){return fpSteppingManager->GetfN2ndariesAlongStepDoIt();};
  G4int GetNumOfPostStepSecondaries(){return fpSteppingManager->GetfN2ndariesPostStepDoIt();};
  G4int GetTotalNumOfSecondaries(){return GetNumOfAtRestSecondaries() + GetNumOfAlongStepSecondaries() + GetNumOfPostStepSecondaries();};

  G4int GetTrackVectorStartIndex();
  G4int GetTrackVectorSize();

  G4ParticleDefinition *GetSecondaryParticleDefinition(G4int idx); 
  G4String              GetSecondaryParticleName(G4int idx); 
  G4double              GetSecondaryParticleTotalEnergy(G4int idx);
  G4double              GetSecondaryParticleKineticEnergy(G4int idx);
  G4double              GetSecondaryParticleXOrigin(G4int idx);
  G4double              GetSecondaryParticleYOrigin(G4int idx);
  G4double              GetSecondaryParticleZOrigin(G4int idx);    
  G4ThreeVector         GetSecondaryParticleOrigin(G4int idx);    
  G4ThreeVector         GetSecondaryParticleMomentum(G4int idx);    
  G4String              GetSecondaryCreatorProcessName(G4int idx);

private:

  G4int evtGenStatus;
  G4int myEventCounter;
  G4TrackVector *fSecondary;
  QweakSimUserInformation* myUserInfo;

  QweakSimEPEvent *myEvent;
  G4double RandomPositionZ;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

