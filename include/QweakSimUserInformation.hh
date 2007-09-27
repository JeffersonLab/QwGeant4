#ifndef QweakSimUserInformation_h
#define QweakSimUserInformation_h 

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 
#include "QweakSimCerenkovDetector_PMTHit.hh"

class QweakSimUserInformation 
{
public:
  
   QweakSimUserInformation();
  ~QweakSimUserInformation();

private:

  G4double primaryQ2;
  G4double crossSectionWeight;
  G4double CerEngDep;

  G4int    primaryEventNumber;
  G4int    edgeEventDetected;
  G4int    leftPMTHitValid;
  G4int    rightPMTHitValid;

  G4int    cerenkovSecondaryParticleCount;
  G4int    cerenkovSecondaryElectronCount;
  G4int    cerenkovSecondaryPhotonCount;
  G4int    cerenkovSecondaryPositronCount;
  G4int    cerenkovOpticalPhotonCount;

  G4MaterialPropertyVector* PMTQE_XP4572;
  G4MaterialPropertyVector* PMTQED753WKBS20;

  G4String StepVolumeName;
  G4ThreeVector cerenkovEventExitPos;
  G4ThreeVector *cerenkovSecondaryPartOrig;
  G4ThreeVector *cerenkovSecondaryPartMom;
  G4double *cerenkovSecondaryPartEng;
  G4double *cerenkovSecondaryPartCharge;

  vector <G4double> CerenkovPhotonEnergy;

  QweakSimCerenkovDetector_PMTHit *PMTHit;
  G4int PMTSide;

 public:

  void Print() const;
  void Initialize();

  void     IncrementCerenkovOpticalPhotonCount() {cerenkovOpticalPhotonCount++;}
  G4int    GetCerenkovOpticalPhotonCount() {return cerenkovOpticalPhotonCount;}
  
  void     SetPrimaryQ2(G4double q2)   {primaryQ2 = q2;}
  G4double GetPrimaryQ2() const {return primaryQ2;}

  void     SetCrossSectionWeight(G4double csw)   {crossSectionWeight = csw;}
  G4double GetCrossSectionWeight() const {return crossSectionWeight;}

  void     SetPrimaryEventNumber(G4int en)      {primaryEventNumber = en;}
  G4int    GetPrimaryEventNumber() const {return primaryEventNumber;}

  G4double GetNumberOfPhotoelectrons(G4double eng);
  G4double GetNumberOfPhotoelectronsS20(G4double eng);

  void     SetLeftPMTHitValid(G4int state) {leftPMTHitValid = state;};
  G4int    GetLeftPMTHitValid() {return leftPMTHitValid; leftPMTHitValid = 0;};
  void     SetRightPMTHitValid(G4int state){rightPMTHitValid = state;};
  G4int    GetRightPMTHitValid() {return rightPMTHitValid; rightPMTHitValid = 0;};

  void     StoreStepVolumeName(G4String name) {StepVolumeName = name;};
  G4String GetStoredStepVolumeName() {return StepVolumeName;};

  void     SetEdgeEventDetected(G4int det){edgeEventDetected = det;};
  G4int    GetEdgeEventDetected(){return edgeEventDetected;};

  void     StoreLocalCerenkovExitPosition(G4ThreeVector ep) {cerenkovEventExitPos = ep;};
  G4ThreeVector GetLocalCerenkovExitPosition() {return cerenkovEventExitPos;};

  void     StoreCerenkovSecondaryParticleInfo(G4ThreeVector ep, G4ThreeVector ee, G4double eng, G4double charge);
  void     ResetCerenkovSecondaryParticleInfo();
  G4ThreeVector GetCerenkovSecondaryParticleOrigin(G4int indx);
  G4ThreeVector GetCerenkovSecondaryParticleMomentum(G4int indx);
  G4double GetCerenkovSecondaryParticleEnergy(G4int indx);
  G4double GetCerenkovSecondaryParticleCharge(G4int indx);
  G4int    GetCerenkovSecondaryParticleCount() {return  cerenkovSecondaryParticleCount;};
  G4int    GetCerenkovSecondaryElectronCount() {return  cerenkovSecondaryElectronCount;};
  G4int    GetCerenkovSecondaryPhotonCount() {return  cerenkovSecondaryPhotonCount;};
  G4int    GetCerenkovSecondaryPositronCount() {return  cerenkovSecondaryPositronCount;};
  
  void SetCurrentPMTHit(QweakSimCerenkovDetector_PMTHit* hit, G4int side){PMTHit = hit; PMTSide = side;};
  QweakSimCerenkovDetector_PMTHit *GetCurrentPMTHit(){return PMTHit;};
  G4int GetCurrentPMTSide() {return PMTSide;};

  void     AddCerenkovEnergyDeposit(G4double eng){CerEngDep += eng;};
  G4double GetCerenkovEnergyDeposit(G4bool zero = true){G4double tmp = CerEngDep; if(zero) CerEngDep = 0.0; return tmp;};


  void StoreCerenkovPhotonEnergy(G4double eng) {CerenkovPhotonEnergy.push_back(eng);};
  G4double GetCerenkovPhotonEnergyAtIndex(G4int ind) {return CerenkovPhotonEnergy[ind];};

};

#endif
