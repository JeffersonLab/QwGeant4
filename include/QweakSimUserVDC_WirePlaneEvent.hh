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

  vector <Int_t>   TrackID;
  vector <Float_t> GlobalTimeOfHit;

  vector <Int_t>   UPlaneHasBeenHit;
  vector <Int_t>   VPlaneHasBeenHit;

  vector <Float_t> UPlaneLocalPositionX;
  vector <Float_t> UPlaneLocalPositionY;
  vector <Float_t> UPlaneLocalPositionZ;
  
  vector <Float_t> UPlaneGlobalPositionX;
  vector <Float_t> UPlaneGlobalPositionY;
  vector <Float_t> UPlaneGlobalPositionZ;


  vector <Float_t> UPlaneLocalMomentumX;
  vector <Float_t> UPlaneLocalMomentumY;
  vector <Float_t> UPlaneLocalMomentumZ;

  vector <Float_t> UPlaneGlobalMomentumX;
  vector <Float_t> UPlaneGlobalMomentumY;
  vector <Float_t> UPlaneGlobalMomentumZ;

  vector <Float_t> UPlaneGlobalPhiAngle;
  vector <Float_t> UPlaneGlobalThetaAngle;




  vector <Float_t> VPlaneLocalPositionX;
  vector <Float_t> VPlaneLocalPositionY;
  vector <Float_t> VPlaneLocalPositionZ;

  vector <Float_t> VPlaneGlobalPositionX;
  vector <Float_t> VPlaneGlobalPositionY;
  vector <Float_t> VPlaneGlobalPositionZ;


  vector <Float_t> VPlaneLocalMomentumX;
  vector <Float_t> VPlaneLocalMomentumY;
  vector <Float_t> VPlaneLocalMomentumZ;
  
  vector <Float_t> VPlaneGlobalMomentumX;
  vector <Float_t> VPlaneGlobalMomentumY;
  vector <Float_t> VPlaneGlobalMomentumZ;

  vector <Float_t> VPlaneGlobalPhiAngle;
  vector <Float_t> VPlaneGlobalThetaAngle;

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

  void     StoreUPlaneHasBeenHit(Int_t nu)      { UPlaneHasBeenHit.push_back(nu); }
  vector <Int_t>      GetUPlaneHasBeenHit() const {return UPlaneHasBeenHit;}

  void     StoreVPlaneHasBeenHit(Int_t nv)      { VPlaneHasBeenHit.push_back(nv); }
  vector <Int_t>      GetVPlaneHasBeenHit() const {return VPlaneHasBeenHit;}

  //-----------------
  void     StoreUPlaneLocalPositionX(Float_t lx)   { UPlaneLocalPositionX.push_back(lx); }
  vector <Float_t>    GetUPlaneLocalPositionX() const {return UPlaneLocalPositionX;}

  void     StoreUPlaneLocalPositionY(Float_t ly)   { UPlaneLocalPositionY.push_back(ly); }
  vector <Float_t>    GetUPlaneLocalPositionY() const {return UPlaneLocalPositionY;}

  void     StoreUPlaneLocalPositionZ(Float_t lz)   { UPlaneLocalPositionZ.push_back(lz); }
  vector <Float_t>    GetUPlaneLocalPositionZ() const {return UPlaneLocalPositionZ;}
  //---
  void     StoreUPlaneGlobalPositionX(Float_t lx)   { UPlaneGlobalPositionX.push_back(lx); }
  vector <Float_t>    GetUPlaneGlobalPositionX() const {return UPlaneGlobalPositionX;}

  void     StoreUPlaneGlobalPositionY(Float_t ly)   { UPlaneGlobalPositionY.push_back(ly); }
  vector <Float_t>    GetUPlaneGlobalPositionY() const {return UPlaneGlobalPositionY;}

  void     StoreUPlaneGlobalPositionZ(Float_t lz)   { UPlaneGlobalPositionZ.push_back(lz); }
  vector <Float_t>    GetUPlaneGlobalPositionZ() const {return UPlaneGlobalPositionZ;}

  //-----------------

  void     StoreUPlaneLocalMomentumX(Float_t lpx)   { UPlaneLocalMomentumX.push_back(lpx); }
  vector <Float_t>    GetUPlaneLocalMomentumX() const {return UPlaneLocalMomentumX;}

  void     StoreUPlaneLocalMomentumY(Float_t lpy)   { UPlaneLocalMomentumY.push_back(lpy); }
  vector <Float_t>    GetUPlaneLocalMomentumY() const {return UPlaneLocalMomentumY;}

  void     StoreUPlaneLocalMomentumZ(Float_t lpz)   { UPlaneLocalMomentumZ.push_back(lpz); }
  vector <Float_t>    GetUPlaneLocalMomentumZ() const {return UPlaneLocalMomentumZ;}
  //---
  void     StoreUPlaneGlobalMomentumX(Float_t gpx)   { UPlaneGlobalMomentumX.push_back(gpx); }
  vector <Float_t>    GetUPlaneGlobalMomentumX() const {return UPlaneGlobalMomentumX;}

  void     StoreUPlaneGlobalMomentumY(Float_t gpy)   { UPlaneGlobalMomentumY.push_back(gpy); }
  vector <Float_t>    GetUPlaneGlobalMomentumY() const {return UPlaneGlobalMomentumY;}

  void     StoreUPlaneGlobalMomentumZ(Float_t gpz)   { UPlaneGlobalMomentumZ.push_back(gpz); }
  vector <Float_t>    GetUPlaneGlobalMomentumZ() const {return UPlaneGlobalMomentumZ;}


  void     StoreUPlaneGlobalThetaAngle(Float_t theta) { UPlaneGlobalThetaAngle.push_back(theta); }
  vector <Float_t>    GetUPlaneGlobalThetaAngle() const  {return UPlaneGlobalThetaAngle;}

  void     StoreUPlaneGlobalPhiAngle(Float_t phi)  { UPlaneGlobalPhiAngle.push_back(phi); }
  vector <Float_t>    GetUPlaneGlobalPhiAngle() const {return UPlaneGlobalPhiAngle;}

  //-----------------

  void     StoreVPlaneLocalPositionX(Float_t lx)   { VPlaneLocalPositionX.push_back(lx); }
  vector <Float_t>    GetVPlaneLocalPositionX() const {return VPlaneLocalPositionX;}

  void     StoreVPlaneLocalPositionY(Float_t ly)   { VPlaneLocalPositionY.push_back(ly); }
  vector <Float_t>    GetVPlaneLocalPositionY() const {return VPlaneLocalPositionY;}

  void     StoreVPlaneLocalPositionZ(Float_t lz)   { VPlaneLocalPositionZ.push_back(lz); }
  vector <Float_t>    GetVPlaneLocalPositionZ() const {return VPlaneLocalPositionZ;}

  void     StoreVPlaneGlobalPositionX(Float_t lx)   { VPlaneGlobalPositionX.push_back(lx); }
  vector <Float_t>    GetVPlaneGlobalPositionX() const {return VPlaneGlobalPositionX;}

  void     StoreVPlaneGlobalPositionY(Float_t ly)   { VPlaneGlobalPositionY.push_back(ly); }
  vector <Float_t>    GetVPlaneGlobalPositionY() const {return VPlaneGlobalPositionY;}

  void     StoreVPlaneGlobalPositionZ(Float_t lz)   { VPlaneGlobalPositionZ.push_back(lz); }
  vector <Float_t>    GetVPlaneGlobalPositionZ() const {return VPlaneGlobalPositionZ;}

  //-----------------

  void     StoreVPlaneLocalMomentumX(Float_t lpx)   { VPlaneLocalMomentumX.push_back(lpx); }
  vector <Float_t>    GetVPlaneLocalMomentumX() const {return VPlaneLocalMomentumX;}

  void     StoreVPlaneLocalMomentumY(Float_t lpy)   { VPlaneLocalMomentumY.push_back(lpy); }
  vector <Float_t>    GetVPlaneLocalMomentumY() const {return VPlaneLocalMomentumY;}

  void     StoreVPlaneLocalMomentumZ(Float_t lpz)   { VPlaneLocalMomentumZ.push_back(lpz); }
  vector <Float_t>    GetVPlaneLocalMomentumZ() const {return VPlaneLocalMomentumZ;}
  //---
  void     StoreVPlaneGlobalMomentumX(Float_t gpx)   { VPlaneGlobalMomentumX.push_back(gpx); }
  vector <Float_t>    GetVPlaneGlobalMomentumX() const {return VPlaneGlobalMomentumX;}

  void     StoreVPlaneGlobalMomentumY(Float_t gpy)   { VPlaneGlobalMomentumY.push_back(gpy); }
  vector <Float_t>    GetVPlaneGlobalMomentumY() const {return VPlaneGlobalMomentumY;}

  void     StoreVPlaneGlobalMomentumZ(Float_t gpz)   { VPlaneGlobalMomentumZ.push_back(gpz); }
  vector <Float_t>    GetVPlaneGlobalMomentumZ() const {return VPlaneGlobalMomentumZ;}


  void     StoreVPlaneGlobalThetaAngle(Float_t theta) { VPlaneGlobalThetaAngle.push_back(theta); }
  vector <Float_t>    GetVPlaneGlobalThetaAngle() const  {return VPlaneGlobalThetaAngle;}

  void     StoreVPlaneGlobalPhiAngle(Float_t phi)  { VPlaneGlobalPhiAngle.push_back(phi); }
  vector <Float_t>    GetVPlaneGlobalPhiAngle() const {return VPlaneGlobalPhiAngle;}

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
