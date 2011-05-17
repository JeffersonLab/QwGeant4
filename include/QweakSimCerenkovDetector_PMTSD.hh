//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimCerenkovDetector_PMTSD_h
#define QweakSimCerenkovDetector_PMTSD_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "Geant4_include.hh" 

// user includes
#include "QweakSimCerenkovDetector_PMTHit.hh"
#include "QweakSimUserInformation.hh"
#include "QweakSimTrackInformation.hh"
#include "QweakSimTrajectory.hh"	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimCerenkovDetector_PMTSD : public G4VSensitiveDetector
{

public:
  QweakSimCerenkovDetector_PMTSD(G4String name, QweakSimUserInformation *myUserInfo);
  ~QweakSimCerenkovDetector_PMTSD();
  
  void Initialize(G4HCofThisEvent* HCE);
  G4bool ProcessHits(G4Step* /*aStep*/,G4TouchableHistory* /*ROhist*/){
    // ProcessHits_constStep(aStep, ROhist);
    return true;
  };
  G4bool ProcessHits_constStep(const G4Step* aStep,G4TouchableHistory* ROhist);
  void EndOfEvent(G4HCofThisEvent* HCE);
  QweakSimTrajectory* GetParentTrajectory(G4int parentID);


private:

  QweakSimUserInformation *myUserInfo;

  QweakSimCerenkovDetector_PMTHitsCollection*  CerenkovDetector_PMTHitsCollection;
  
  G4int CerenkovDetectorPMT_CollectionID;



};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

