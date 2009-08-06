//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_WirePlaneEvent.hh

   $Revision: 1.3 $	
   $Date: 2006/01/06 21:33:13 $

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
   \class QweakSimUserVDC_WirePlaneEvent
    
   \brief Stores the data structure related to a VDC WirePlane Hit into the ROOT file for each event

   Region3.ChamberFront.WirePlane.xyz

   Region3.ChamberBack.WirePlane.xyz	
   
   Placeholder for a long explaination
    
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_WirePlaneEvent_h
#define QweakSimUserVDC_WirePlaneEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "cpp_include.h"
#include "Root_include.h"

#ifndef __CINT__
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_WirePlaneEvent 
{

private:

  Int_t            NbOfHits;

  vector <Int_t>   TrackID;
  vector <Float_t> GlobalTimeOfHit;

  Int_t   HasBeenHit;
 
  vector <Float_t> LocalPositionX;
  vector <Float_t> LocalPositionY;
  vector <Float_t> LocalPositionZ;
  
  vector <Float_t> GlobalPositionX;
  vector <Float_t> GlobalPositionY;
  vector <Float_t> GlobalPositionZ;


  vector <Float_t> LocalMomentumX;
  vector <Float_t> LocalMomentumY;
  vector <Float_t> LocalMomentumZ;

  vector <Float_t> GlobalMomentumX;
  vector <Float_t> GlobalMomentumY;
  vector <Float_t> GlobalMomentumZ;

  vector <Float_t> GlobalPhiAngle;
  vector <Float_t> GlobalThetaAngle;



  vector <Float_t> OriginVertexPositionX;
  vector <Float_t> OriginVertexPositionY;
  vector <Float_t> OriginVertexPositionZ;

  vector <Float_t> OriginVertexMomentumDirectionX;
  vector <Float_t> OriginVertexMomentumDirectionY;
  vector <Float_t> OriginVertexMomentumDirectionZ;

  vector <Float_t> OriginVertexThetaAngle;
  vector <Float_t> OriginVertexPhiAngle;

  vector <Float_t> OriginVertexKineticEnergy;
  vector <Float_t> OriginVertexTotalEnergy;

//   Float_t PrimaryQ2;
//   Float_t CrossSection;
//   Float_t CrossSectionWeight;
//   Int_t   PrimaryEventNumber;

  vector <TString> ParticleName;
  vector <Int_t>   ParticleType;

  vector <Float_t> TotalEnergy;
  vector <Float_t> KineticEnergy;

public:
  
  // Constructor
  QweakSimUserVDC_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_WirePlaneEvent();

  void     Initialize();
  void     Clear();

  void     StoreNbOfHits(Int_t noh)    { NbOfHits = noh; }
  Int_t      GetNbOfHits() const {return NbOfHits;}

  void     StoreTrackID(Int_t tid)    { TrackID.push_back(tid); }
  vector <Int_t>      GetTrackID() const {return TrackID;}


  void     StoreParticleName(TString pn)    { ParticleName.push_back(pn); }
  vector <TString>    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType.push_back(pt); }
  vector <Int_t>      GetParticleType() const {return  ParticleType;}
    

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit.push_back(gtime); }
  vector <Float_t>    GetGlobalTimeOfHit()  const {return GlobalTimeOfHit;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy.push_back(te); }
  vector <Float_t>    GetTotalEnergy() const {return TotalEnergy;}

  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy.push_back(ke); }
  vector <Float_t>    GetKineticEnergy() const {return KineticEnergy;}

  void     StoreHasBeenHit(Int_t nu)      { HasBeenHit = nu; }
  Int_t     GetHasBeenHit() const {return HasBeenHit;}

  //-----------------
  void     StoreLocalPositionX(Float_t lx)   { LocalPositionX.push_back(lx); }
  vector <Float_t>    GetLocalPositionX() const {return LocalPositionX;}

  void     StoreLocalPositionY(Float_t ly)   { LocalPositionY.push_back(ly); }
  vector <Float_t>    GetLocalPositionY() const {return LocalPositionY;}

  void     StoreLocalPositionZ(Float_t lz)   { LocalPositionZ.push_back(lz); }
  vector <Float_t>    GetLocalPositionZ() const {return LocalPositionZ;}
  //---
  void     StoreGlobalPositionX(Float_t lx)   { GlobalPositionX.push_back(lx); }
  vector <Float_t>    GetGlobalPositionX() const {return GlobalPositionX;}

  void     StoreGlobalPositionY(Float_t ly)   { GlobalPositionY.push_back(ly); }
  vector <Float_t>    GetGlobalPositionY() const {return GlobalPositionY;}

  void     StoreGlobalPositionZ(Float_t lz)   { GlobalPositionZ.push_back(lz); }
  vector <Float_t>    GetGlobalPositionZ() const {return GlobalPositionZ;}

  //-----------------

  void     StoreLocalMomentumX(Float_t lpx)   { LocalMomentumX.push_back(lpx); }
  vector <Float_t>    GetLocalMomentumX() const {return LocalMomentumX;}

  void     StoreLocalMomentumY(Float_t lpy)   { LocalMomentumY.push_back(lpy); }
  vector <Float_t>    GetLocalMomentumY() const {return LocalMomentumY;}

  void     StoreLocalMomentumZ(Float_t lpz)   { LocalMomentumZ.push_back(lpz); }
  vector <Float_t>    GetLocalMomentumZ() const {return LocalMomentumZ;}
  //---
  void     StoreGlobalMomentumX(Float_t gpx)   { GlobalMomentumX.push_back(gpx); }
  vector <Float_t>    GetGlobalMomentumX() const {return GlobalMomentumX;}

  void     StoreGlobalMomentumY(Float_t gpy)   { GlobalMomentumY.push_back(gpy); }
  vector <Float_t>    GetGlobalMomentumY() const {return GlobalMomentumY;}

  void     StoreGlobalMomentumZ(Float_t gpz)   { GlobalMomentumZ.push_back(gpz); }
  vector <Float_t>    GetGlobalMomentumZ() const {return GlobalMomentumZ;}


  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle.push_back(theta); }
  vector <Float_t>    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle.push_back(phi); }
  vector <Float_t>    GetGlobalPhiAngle() const {return GlobalPhiAngle;}

  //-----------------
  //-----------------
  void     StoreOriginVertexPositionX(Float_t vx)   { OriginVertexPositionX.push_back(vx); }
  vector <Float_t>    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(Float_t vy)   { OriginVertexPositionY.push_back(vy); }
  vector <Float_t>    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(Float_t vz)   { OriginVertexPositionZ.push_back(vz); }
  vector <Float_t>    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(Float_t vx)   { OriginVertexMomentumDirectionX.push_back(vx); }
  vector <Float_t>    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(Float_t vy)   { OriginVertexMomentumDirectionY.push_back(vy); }
  vector <Float_t>    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(Float_t vz)   { OriginVertexMomentumDirectionZ.push_back(vz); }
  vector <Float_t>    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(Float_t theta) { OriginVertexThetaAngle.push_back(theta); }
  vector <Float_t>    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(Float_t phi)  { OriginVertexPhiAngle.push_back(phi); }
  vector <Float_t>    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy.push_back(ekin); }
  vector <Float_t>    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy.push_back(etot); }
  vector <Float_t>    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}
  //-----------------
//   void     StorePrimaryQ2(Float_t pq2)  { PrimaryQ2 = pq2; }
//   Float_t    GetPrimaryQ2() const {return PrimaryQ2; }
// 
//   void     StoreCrossSection(Float_t cs)  {CrossSection = cs;}
//   Float_t    GetCrossSection() const {return CrossSection; }
// 
//   void     StoreCrossSectionWeight(Float_t csw)  {CrossSectionWeight = csw;}
//   Float_t    GetCrossSectionWeight() const {return CrossSectionWeight; }
// 
//   void     StorePrimaryEventNumber(Int_t pen)    { PrimaryEventNumber = pen; }
//   Int_t      GetPrimaryEventNumber() const {return PrimaryEventNumber; }
  //-----------------

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_WirePlaneEvent,1)

};  // end class QweakSimUserVDC_WirePlaneEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 
