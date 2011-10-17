#ifndef QweakSimUserInformation_h
#define QweakSimUserInformation_h 

// system includes
//#include "cpp_include.h"
//#include "Root_include.h"
//#include "Geant4_include.hh" 

#include <vector>

//user includes
#include "QweakSimCerenkovDetector_PMTHit.hh"
#include "QweakSimUserPrimaryEvent.hh"

#include "G4MaterialPropertyVector.hh"

// geant4 classes
class G4MaterialPropertyVector;


class QweakSimUserInformation 
{
public:
  
   QweakSimUserInformation();
  ~QweakSimUserInformation();
  
  G4double TargetCenterPositionZ;
  G4double TargetLength;
  G4double TargetEntranceWindowThickness;
  G4double TargetExitWindowThickness;

  G4int    ReactionType;         // assign a number to which kind of reaction,e.g. 1 = elastic ep,
  G4int    ReactionRegion;
  G4int    EvtGenStatus;
    
private:

  G4int    PrimaryEventNumber;
  G4int    PDGcode;              // particle data code/number for the primary particle, e.g. 3=electron
  G4int    TrackID;
  G4double GlobalTime;
  G4double PrimaryQ2;
  G4double CrossSection;
  G4double CrossSectionWeight;
  G4double Asymmetry;
  G4double OriginVertexPositionX;
  G4double OriginVertexPositionY;
  G4double OriginVertexPositionZ;
  G4double OriginVertexThetaAngle;
  G4double OriginVertexPhiAngle;
  G4double OriginVertexMomentumDirectionX;
  G4double OriginVertexMomentumDirectionY;
  G4double OriginVertexMomentumDirectionZ;
  G4double OriginVertexKineticEnergy;
  G4double OriginVertexTotalEnergy;


  G4double CerEngDep;

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

  std::vector <G4double> CerenkovPhotonEnergy;

  QweakSimCerenkovDetector_PMTHit *PMTHit;
  G4int PMTSide;

 public:

  void Print() const;
  void Initialize();

  void     StoreTrackID(G4int tid)    { TrackID = tid; }
  G4int    GetTrackID() const {return TrackID;}

  void     StoreGlobalTime(G4double gtime) { GlobalTime = gtime; }
  G4double    GetGlobalTime()  const {return GlobalTime;}

  //-----------------
  void     StoreOriginVertexPositionX(G4double vx)   { OriginVertexPositionX = vx; }
  G4double    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(G4double vy)   { OriginVertexPositionY = vy; }
  G4double    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(G4double vz)   { OriginVertexPositionZ = vz; }
  G4double    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(G4double vx)   { OriginVertexMomentumDirectionX = vx; }
  G4double    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(G4double vy)   { OriginVertexMomentumDirectionY = vy; }
  G4double    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(G4double vz)   { OriginVertexMomentumDirectionZ = vz; }
  G4double    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(G4double theta) { OriginVertexThetaAngle = theta; }
  G4double    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(G4double phi)  { OriginVertexPhiAngle = phi; }
  G4double    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(G4double ekin) { OriginVertexKineticEnergy = ekin; }
  G4double    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(G4double etot) { OriginVertexTotalEnergy = etot; }
  G4double    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}
  //-----------------
  void     StorePrimaryQ2(G4double pq2)  { PrimaryQ2 = pq2; }
  G4double    GetPrimaryQ2() const {return PrimaryQ2; }

  void     StoreCrossSection(G4double cs)  {CrossSection = cs;}
  G4double    GetCrossSection() const {return CrossSection; }

  void     StoreCrossSectionWeight(G4double csw)  {CrossSectionWeight = csw;}
  G4double    GetCrossSectionWeight() const {return CrossSectionWeight; }

  void     StoreAsymmetry(G4double asym)  {Asymmetry = asym;}
  G4double    GetAsymmetry() const {return Asymmetry; }

  void     StorePrimaryEventNumber(G4int pen)    { PrimaryEventNumber = pen; }
  G4int      GetPrimaryEventNumber() const {return PrimaryEventNumber; }
  //-----------------

  void     StoreReactionType(G4int rt)  { ReactionType = rt; }
  G4int      GetReactionType() const {return ReactionType; }

  void     StorePDGcode(G4int code)  { PDGcode = code; }
  G4int      GetPDGcode() const {return PDGcode; }




  void     IncrementCerenkovOpticalPhotonCount() {cerenkovOpticalPhotonCount++;}
  G4int    GetCerenkovOpticalPhotonCount() {return cerenkovOpticalPhotonCount;}

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
