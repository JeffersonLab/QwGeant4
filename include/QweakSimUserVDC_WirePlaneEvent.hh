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

// system includes
#include <vector>

// root includes
#include "TObject.h"
#include "TString.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_WirePlaneEvent : public TObject
{

private:

  Int_t            NbOfHits;

  std::vector <Int_t>   TrackID;
  std::vector <Float_t> GlobalTimeOfHit;

  Int_t   HasBeenHit;
 
  std::vector <Float_t> LocalPositionX;
  std::vector <Float_t> LocalPositionY;
  std::vector <Float_t> LocalPositionZ;
  
  std::vector <Float_t> GlobalPositionX;
  std::vector <Float_t> GlobalPositionY;
  std::vector <Float_t> GlobalPositionZ;


  std::vector <Float_t> LocalMomentumX;
  std::vector <Float_t> LocalMomentumY;
  std::vector <Float_t> LocalMomentumZ;

  std::vector <Float_t> GlobalMomentumX;
  std::vector <Float_t> GlobalMomentumY;
  std::vector <Float_t> GlobalMomentumZ;

  std::vector <Float_t> GlobalPhiAngle;
  std::vector <Float_t> GlobalThetaAngle;



  std::vector <Float_t> OriginVertexPositionX;
  std::vector <Float_t> OriginVertexPositionY;
  std::vector <Float_t> OriginVertexPositionZ;

  std::vector <Float_t> OriginVertexMomentumDirectionX;
  std::vector <Float_t> OriginVertexMomentumDirectionY;
  std::vector <Float_t> OriginVertexMomentumDirectionZ;

  std::vector <Float_t> OriginVertexThetaAngle;
  std::vector <Float_t> OriginVertexPhiAngle;

  std::vector <Float_t> OriginVertexKineticEnergy;
  std::vector <Float_t> OriginVertexTotalEnergy;

//   Float_t PrimaryQ2;
//   Float_t CrossSection;
//   Float_t CrossSectionWeight;
//   Int_t   PrimaryEventNumber;

  std::vector <TString> ParticleName;
  std::vector <Int_t>   ParticleType;

  std::vector <Float_t> TotalEnergy;
  std::vector <Float_t> KineticEnergy;

public:
  
  // Constructor
  QweakSimUserVDC_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_WirePlaneEvent();

  void     Initialize();
  void     Clear(const Option_t* = 0);

  void     StoreNbOfHits(Int_t noh)    { NbOfHits = noh; }
  Int_t      GetNbOfHits() const {return NbOfHits;}

  void     StoreTrackID(Int_t tid)    { TrackID.push_back(tid); }
  std::vector <Int_t>      GetTrackID() const {return TrackID;}


  void     StoreParticleName(TString pn)    { ParticleName.push_back(pn); }
  std::vector <TString>    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType.push_back(pt); }
  std::vector <Int_t>      GetParticleType() const {return  ParticleType;}
    

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit.push_back(gtime); }
  std::vector <Float_t>    GetGlobalTimeOfHit()  const {return GlobalTimeOfHit;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy.push_back(te); }
  std::vector <Float_t>    GetTotalEnergy() const {return TotalEnergy;}

  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy.push_back(ke); }
  std::vector <Float_t>    GetKineticEnergy() const {return KineticEnergy;}

  void     StoreHasBeenHit(Int_t nu)      { HasBeenHit = nu; }
  Int_t     GetHasBeenHit() const {return HasBeenHit;}

  //-----------------
  void     StoreLocalPositionX(Float_t lx)   { LocalPositionX.push_back(lx); }
  std::vector <Float_t>    GetLocalPositionX() const {return LocalPositionX;}

  void     StoreLocalPositionY(Float_t ly)   { LocalPositionY.push_back(ly); }
  std::vector <Float_t>    GetLocalPositionY() const {return LocalPositionY;}

  void     StoreLocalPositionZ(Float_t lz)   { LocalPositionZ.push_back(lz); }
  std::vector <Float_t>    GetLocalPositionZ() const {return LocalPositionZ;}
  //---
  void     StoreGlobalPositionX(Float_t lx)   { GlobalPositionX.push_back(lx); }
  std::vector <Float_t>    GetGlobalPositionX() const {return GlobalPositionX;}

  void     StoreGlobalPositionY(Float_t ly)   { GlobalPositionY.push_back(ly); }
  std::vector <Float_t>    GetGlobalPositionY() const {return GlobalPositionY;}

  void     StoreGlobalPositionZ(Float_t lz)   { GlobalPositionZ.push_back(lz); }
  std::vector <Float_t>    GetGlobalPositionZ() const {return GlobalPositionZ;}

  //-----------------

  void     StoreLocalMomentumX(Float_t lpx)   { LocalMomentumX.push_back(lpx); }
  std::vector <Float_t>    GetLocalMomentumX() const {return LocalMomentumX;}

  void     StoreLocalMomentumY(Float_t lpy)   { LocalMomentumY.push_back(lpy); }
  std::vector <Float_t>    GetLocalMomentumY() const {return LocalMomentumY;}

  void     StoreLocalMomentumZ(Float_t lpz)   { LocalMomentumZ.push_back(lpz); }
  std::vector <Float_t>    GetLocalMomentumZ() const {return LocalMomentumZ;}
  //---
  void     StoreGlobalMomentumX(Float_t gpx)   { GlobalMomentumX.push_back(gpx); }
  std::vector <Float_t>    GetGlobalMomentumX() const {return GlobalMomentumX;}

  void     StoreGlobalMomentumY(Float_t gpy)   { GlobalMomentumY.push_back(gpy); }
  std::vector <Float_t>    GetGlobalMomentumY() const {return GlobalMomentumY;}

  void     StoreGlobalMomentumZ(Float_t gpz)   { GlobalMomentumZ.push_back(gpz); }
  std::vector <Float_t>    GetGlobalMomentumZ() const {return GlobalMomentumZ;}


  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle.push_back(theta); }
  std::vector <Float_t>    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle.push_back(phi); }
  std::vector <Float_t>    GetGlobalPhiAngle() const {return GlobalPhiAngle;}

  //-----------------
  //-----------------
  void     StoreOriginVertexPositionX(Float_t vx)   { OriginVertexPositionX.push_back(vx); }
  std::vector <Float_t>    GetOriginVertexPositionX() const {return OriginVertexPositionX;}

  void     StoreOriginVertexPositionY(Float_t vy)   { OriginVertexPositionY.push_back(vy); }
  std::vector <Float_t>    GetOriginVertexPositionY() const {return OriginVertexPositionY;}

  void     StoreOriginVertexPositionZ(Float_t vz)   { OriginVertexPositionZ.push_back(vz); }
  std::vector <Float_t>    GetOriginVertexPositionZ() const {return OriginVertexPositionZ;}
  //-----------------
  void     StoreOriginVertexMomentumDirectionX(Float_t vx)   { OriginVertexMomentumDirectionX.push_back(vx); }
  std::vector <Float_t>    GetOriginVertexMomentumDirectionX() const {return OriginVertexMomentumDirectionX;}

  void     StoreOriginVertexMomentumDirectionY(Float_t vy)   { OriginVertexMomentumDirectionY.push_back(vy); }
  std::vector <Float_t>    GetOriginVertexMomentumDirectionY() const {return OriginVertexMomentumDirectionY;}

  void     StoreOriginVertexMomentumDirectionZ(Float_t vz)   { OriginVertexMomentumDirectionZ.push_back(vz); }
  std::vector <Float_t>    GetOriginVertexMomentumDirectionZ() const {return OriginVertexMomentumDirectionZ;}
  //-----------------
  void     StoreOriginVertexThetaAngle(Float_t theta) { OriginVertexThetaAngle.push_back(theta); }
  std::vector <Float_t>    GetOriginVertexThetaAngle() const  {return OriginVertexThetaAngle;}

  void     StoreOriginVertexPhiAngle(Float_t phi)  { OriginVertexPhiAngle.push_back(phi); }
  std::vector <Float_t>    GetOriginVertexPhiAngle() const {return OriginVertexPhiAngle;}
  //-----------------
  void     StoreOriginVertexKineticEnergy(Float_t ekin) { OriginVertexKineticEnergy.push_back(ekin); }
  std::vector <Float_t>    GetOriginVertexKineticEnergy() const {return OriginVertexKineticEnergy;}

  void     StoreOriginVertexTotalEnergy(Float_t etot) { OriginVertexTotalEnergy.push_back(etot); }
  std::vector <Float_t>    GetOriginVertexTotalEnergy() const {return OriginVertexTotalEnergy;}
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
