//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserHDC_WirePlaneEvent.hh

   $Date: Fri Jul  3 10:16:54 CDT 2009$

   \author Klaus Hans Grimm
   \author Jie Pan
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimUserHDC_WirePlaneEvent
    
   \brief ROOT Subtree structure for HDC WirePlaneEvent

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserHDC_WirePlaneEvent_h
#define QweakSimUserHDC_WirePlaneEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>

// root includes
#include "TObject.h"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserHDC_WirePlaneEvent : public TObject
{

private:

  Int_t            NbOfHits;

  std::vector <Int_t>   TrackID;
  std::vector <Float_t> GlobalTimeOfHit;

  Int_t   PlaneHasBeenHit;

  std::vector <Float_t> PlaneLocalPositionX;
  std::vector <Float_t> PlaneLocalPositionY;
  std::vector <Float_t> PlaneLocalPositionZ;
  
  std::vector <Float_t> PlaneGlobalPositionX;
  std::vector <Float_t> PlaneGlobalPositionY;
  std::vector <Float_t> PlaneGlobalPositionZ;

  std::vector <Float_t> PlaneLocalMomentumX;
  std::vector <Float_t> PlaneLocalMomentumY;
  std::vector <Float_t> PlaneLocalMomentumZ;

  std::vector <Float_t> PlaneGlobalMomentumX;
  std::vector <Float_t> PlaneGlobalMomentumY;
  std::vector <Float_t> PlaneGlobalMomentumZ;

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

  std::vector <Float_t> GlobalPhiAngle;
  std::vector <Float_t> GlobalThetaAngle;

  std::vector <Float_t> TotalEnergy;
  std::vector <Float_t> KineticEnergy;

public:
  
  // Constructor
  QweakSimUserHDC_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserHDC_WirePlaneEvent();

  void     Initialize();
  void     Clear(const Option_t* = 0);

  void     StoreNbOfHits(Int_t noh)    { NbOfHits = noh; }
  Int_t      GetNbOfHits() const {return NbOfHits;}

  void     StoreTrackID(Int_t tid)    { TrackID.push_back(tid); }
  std::vector <Int_t>      GetTrackID() const {return TrackID;}

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit.push_back(gtime); }
  std::vector <Float_t>    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}

  //-----------------
  // Setter/Getter for X,U,V wire planes 

  void     StorePlaneHasBeenHit(Int_t nx)      { PlaneHasBeenHit = nx; }
  Int_t    GetPlaneHasBeenHit() const {return  PlaneHasBeenHit;}

  //-----------------
  void     StorePlaneLocalPositionX(Float_t lx)   { PlaneLocalPositionX.push_back(lx); }
  std::vector <Float_t>    GetPlaneLocalPositionX() const {return PlaneLocalPositionX;}

  void     StorePlaneLocalPositionY(Float_t ly)   { PlaneLocalPositionY.push_back(ly); }
  std::vector <Float_t>    GetPlaneLocalPositionY() const {return PlaneLocalPositionY;}

  void     StorePlaneLocalPositionZ(Float_t lz)   { PlaneLocalPositionZ.push_back(lz); }
  std::vector <Float_t>    GetPlaneLocalPositionZ() const {return PlaneLocalPositionZ;}
  //---
  void     StorePlaneGlobalPositionX(Float_t gx)   { PlaneGlobalPositionX.push_back(gx); }
  std::vector <Float_t>    GetPlaneGlobalPositionX() const {return PlaneGlobalPositionX;}

  void     StorePlaneGlobalPositionY(Float_t gy)   { PlaneGlobalPositionY.push_back(gy); }
  std::vector <Float_t>    GetPlaneGlobalPositionY() const {return PlaneGlobalPositionY;}

  void     StorePlaneGlobalPositionZ(Float_t gz)   { PlaneGlobalPositionZ.push_back(gz); }
  std::vector <Float_t>    GetPlaneGlobalPositionZ() const {return PlaneGlobalPositionZ;}

  //-----------------

  void     StorePlaneLocalMomentumX(Float_t lpx)   { PlaneLocalMomentumX.push_back(lpx); }
  std::vector <Float_t>    GetPlaneLocalMomentumX() const {return  PlaneLocalMomentumX;}

  void     StorePlaneLocalMomentumY(Float_t lpy)   { PlaneLocalMomentumY.push_back(lpy); }
  std::vector <Float_t>    GetPlaneLocalMomentumY() const {return  PlaneLocalMomentumY;}

  void     StorePlaneLocalMomentumZ(Float_t lpz)   { PlaneLocalMomentumZ.push_back(lpz); }
  std::vector <Float_t>    GetPlaneLocalMomentumZ() const {return  PlaneLocalMomentumZ;}
  //---
  void     StorePlaneGlobalMomentumX(Float_t gpx)   { PlaneGlobalMomentumX.push_back(gpx); }
  std::vector <Float_t>    GetPlaneGlobalMomentumX() const {return  PlaneGlobalMomentumX;}

  void     StorePlaneGlobalMomentumY(Float_t gpy)   { PlaneGlobalMomentumY.push_back(gpy); }
  std::vector <Float_t>    GetPlaneGlobalMomentumY() const {return  PlaneGlobalMomentumY;}

  void     StorePlaneGlobalMomentumZ(Float_t gpz)   { PlaneGlobalMomentumZ.push_back(gpz); }
  std::vector <Float_t>    GetPlaneGlobalMomentumZ() const {return  PlaneGlobalMomentumZ;}

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
  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle.push_back(theta); }
  std::vector <Float_t>    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}
  
  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle.push_back(phi); }
  std::vector <Float_t>    GetGlobalPhiAngle() const {return GlobalPhiAngle;}
  //-----------------

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy.push_back(te); }
  std::vector <Float_t>    GetTotalEnergy() const {return TotalEnergy;}
  
  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy.push_back(ke); }
  std::vector <Float_t>    GetKineticEnergy() const {return KineticEnergy;}
    

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserHDC_WirePlaneEvent,1)

};  // end class QweakSimUserHDC_WirePlaneEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

