
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_DetectorEvent.hh
   $Revision: 1.3 $	
   $Date: 2006/01/06 20:31:24 $
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
   \class QweakSimUserCerenkov_DetectorEvent 
    
   \brief ROOT Subtree structure for Cerenkov DetectorEvent

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
//  Update Date:      $Date: 2006/01/06 20:31:24 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserCerenkov_DetectorEvent_h
#define QweakSimUserCerenkov_DetectorEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include "cpp_include.h"
#include "Root_include.h"
// #include "QweakSimUserCerenkov_SecondaryParticleEvent.hh"

#ifndef __CINT__
#include "Geant4_include.hh" 
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserCerenkov_DetectorEvent 
{

private:

//   TTree   *DataTree;
//   TBranch *secondaryElectronBranch;

  Int_t   DetectorID;

  Float_t TrackID;
  Float_t GlobalTimeOfHit;

  Int_t HasBeenHit;
  Int_t EdgeEventFlag;
  Int_t NbOfHits;
  Int_t SecondaryParticleCount;
  Int_t SecondaryElectronCount;
  Int_t SecondaryPhotonCount;  
  Int_t SecondaryPositronCount;
  Int_t OpticalPhotonCount;

//   QweakSimUserCerenkov_SecondaryParticleEvent *secondaryElectronEvent;

  Float_t *SecPartLocalOriginX; //[SecondaryParticleCount]
  Float_t *SecPartLocalOriginY; //[SecondaryParticleCount]
  Float_t *SecPartLocalOriginZ; //[SecondaryParticleCount]

  Float_t *SecPartLocalMomentumX; //[SecondaryParticleCount]
  Float_t *SecPartLocalMomentumY; //[SecondaryParticleCount]
  Float_t *SecPartLocalMomentumZ; //[SecondaryParticleCount]

  Float_t *SecPartLocalEnergy; //[SecondaryParticleCount]
  Float_t *SecPartLocalCharge; //[SecondaryParticleCount]

  vector <Double_t> CerenkovPhotonEnergy;
  
  Float_t HitLocalPositionX;
  Float_t HitLocalPositionY;
  Float_t HitLocalPositionZ;
  Float_t HitLocalExitPositionX;
  Float_t HitLocalExitPositionY;
  Float_t HitLocalExitPositionZ;
  Float_t HitGlobalPositionX;
  Float_t HitGlobalPositionY;
  Float_t HitGlobalPositionZ;

  Float_t OriginVertexPositionX;
  Float_t OriginVertexPositionY;
  Float_t OriginVertexPositionZ;

  Float_t OriginVertexMomentumDirectionX;
  Float_t OriginVertexMomentumDirectionY;
  Float_t OriginVertexMomentumDirectionZ;

  Float_t OriginVertexThetaAngle;
  Float_t OriginVertexPhiAngle;

  Float_t OriginVertexKineticEnergy;
  Float_t OriginVertexTotalEnergy;

  Float_t LocalVertexTotalEnergy;

  Float_t PrimaryQ2;
  Float_t CrossSectionWeight;

  Float_t GlobalPhiAngle;
  Float_t GlobalThetaAngle;

  TString ParticleName;
  Int_t   ParticleType;

  Float_t TotalEnergy;
  Float_t KineticEnergy;

public:
  
  // Constructor
  QweakSimUserCerenkov_DetectorEvent();
  // Destructor 
  virtual ~QweakSimUserCerenkov_DetectorEvent();

   void Initialize();

  //-----------------
  void     StoreDetectorID(Int_t did)  { DetectorID = did; }
  Int_t    GetDetectorID() const {return DetectorID;}
  //-----------------

  void     StoreTrackID(Float_t tid)  { TrackID = tid; }
  Float_t    GetTrackID() const {return TrackID;}

  void     StoreParticleName(TString pn)    { ParticleName = pn; }
  TString    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType = pt; }
  Int_t      GetParticleType() const {return  ParticleType;}


  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit = gtime; }
  Float_t    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy = te; }
  Float_t    GetTotalEnergy() const {return TotalEnergy;}

  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy = ke; }
  Float_t    GetKineticEnergy() const {return KineticEnergy;}


  //-----------------
  void     StoreDetectorHasBeenHit(Int_t n)      { HasBeenHit = n; }
  Int_t      GetDetectorHasBeenHit() const {return HasBeenHit;}
  //-----------------
  void     StoreDetectorNbOfHits(Int_t nd)      { NbOfHits = nd; }
  Int_t      GetDetectorNbOfHits() const {return  NbOfHits;}
  //-----------------
  void     StoreDetectorLocalPositionX(Float_t lx)   { HitLocalPositionX = lx; }
  Float_t    GetDetectorLocalPositionX() const {return HitLocalPositionX;}

  void     StoreDetectorLocalPositionY(Float_t ly)   { HitLocalPositionY = ly; }
  Float_t    GetDetectorLocalPositionY() const {return HitLocalPositionY;}

  void     StoreDetectorLocalPositionZ(Float_t lz)   { HitLocalPositionZ = lz; }
  Float_t    GetDetectorLocalPositionZ() const {return HitLocalPositionZ;}
  //-----------------
  void     StoreDetectorLocalExitPositionX(Float_t lx)   { HitLocalExitPositionX = lx; }
  Float_t    GetDetectorLocalExitPositionX() const {return HitLocalExitPositionX;}

  void     StoreDetectorLocalExitPositionY(Float_t ly)   { HitLocalExitPositionY = ly; }
  Float_t    GetDetectorLocalExitPositionY() const {return HitLocalExitPositionY;}

  void     StoreDetectorLocalExitPositionZ(Float_t lz)   { HitLocalExitPositionZ = lz; }
  Float_t    GetDetectorLocalExitPositionZ() const {return HitLocalExitPositionZ;}
  //---
  void     StoreDetectorGlobalPositionX(Float_t lx)   { HitGlobalPositionX = lx; }
  Float_t    GetDetectorGlobalPositionX() const {return HitGlobalPositionX;}

  void     StoreDetectorGlobalPositionY(Float_t ly)   { HitGlobalPositionY = ly; }
  Float_t    GetDetectorGlobalPositionY() const {return HitGlobalPositionY;}

  void     StoreDetectorGlobalPositionZ(Float_t lz)   { HitGlobalPositionZ = lz; }
  Float_t    GetDetectorGlobalPositionZ() const {return HitGlobalPositionZ;}
  //-----------------
  void     StoreOriginVertexPositionX(Float_t vx)   { OriginVertexPositionX = vx; }
  Float_t    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(Float_t vy)   { OriginVertexPositionY = vy; }
  Float_t    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(Float_t vz)   { OriginVertexPositionZ = vz; }
  Float_t    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(Float_t vx)   { OriginVertexMomentumDirectionX = vx; }
  Float_t    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(Float_t vy)   { OriginVertexMomentumDirectionY = vy; }
  Float_t    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(Float_t vz)   { OriginVertexMomentumDirectionZ = vz; }
  Float_t    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(Float_t theta) { OriginVertexThetaAngle = theta; }
  Float_t    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(Float_t phi)  { OriginVertexPhiAngle = phi; }
  Float_t    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy = ekin; }
  Float_t    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy = etot; }
  Float_t    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}

  void     StoreDetectorLocalVertexTotalEnergy(Float_t etot) { LocalVertexTotalEnergy = etot; };
  Float_t    GetDetectorLocalVertexTotalEnergy() {return LocalVertexTotalEnergy;};
  //----------------

  void     StorePrimaryQ2(Float_t pq2)  { PrimaryQ2 = pq2; }
  Float_t    GetPrimaryQ2() const {return PrimaryQ2; }
  //-----------------
  void     StoreCrossSectionWeight(Float_t csw)
   {     CrossSectionWeight = csw;}


  Float_t    GetCrossSectionWeight() const {return CrossSectionWeight; }
  //-----------------

  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle = theta; }
  Float_t    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle = phi; }
  Float_t    GetGlobalPhiAngle() const {return GlobalPhiAngle;}


  void AddSecondaryParticleEvent(Float_t XO, Float_t YO, Float_t ZO,
				 Float_t XM, Float_t YM, Float_t ZM,
				 Float_t Eng, Float_t Charge);

  void     StoreEdgeEventFlag(Int_t flag) {EdgeEventFlag = flag;};
  Int_t    GetEdgeEventFlag() {return EdgeEventFlag;};

  void     StoreOpticalPhotonCount(Int_t cnt){OpticalPhotonCount = cnt;};

  void StoreCerenkovPhotonEnergy(Double_t eng) {CerenkovPhotonEnergy.push_back(eng);};

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserCerenkov_DetectorEvent,1)

};  // end class QweakSimUserCerenkov_DetectorEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserCerenkov_DetectorEvent.hh,v $
//      Revision 1.3  2006/01/06 20:31:24  grimm
//      Added KineticEnergy, TotalEnergy, ParticleType, and ParticleName into the root tree
//
//      Revision 1.2  2005/12/27 19:28:31  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

