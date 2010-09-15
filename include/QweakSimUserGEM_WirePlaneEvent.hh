//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserGEM_WirePlaneEvent.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:38:33 $
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
   \class QweakSimUserGEM_WirePlaneEvent
    
   \brief ROOT Subtree structure for GEM WirePlaneEvent

   Placeholder for a long explaination
    
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserGEM_WirePlaneEvent_h
#define QweakSimUserGEM_WirePlaneEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include <vector>
using std::vector;


#include "Rtypes.h"

#ifndef __CINT__
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserGEM_WirePlaneEvent 
{

private:

  Int_t            NbOfHits;
  vector <Int_t>   TrackID;
  vector <Float_t> GlobalTimeOfHit;

  Int_t   PlaneHasBeenHit;

  vector <Float_t> PlaneLocalPositionX;
  vector <Float_t> PlaneLocalPositionY;
  vector <Float_t> PlaneLocalPositionZ;
  
  vector <Float_t> PlaneGlobalPositionX;
  vector <Float_t> PlaneGlobalPositionY;
  vector <Float_t> PlaneGlobalPositionZ;

  vector <Float_t> PlaneLocalMomentumX;
  vector <Float_t> PlaneLocalMomentumY;
  vector <Float_t> PlaneLocalMomentumZ;

  vector <Float_t> PlaneGlobalMomentumX;
  vector <Float_t> PlaneGlobalMomentumY;
  vector <Float_t> PlaneGlobalMomentumZ;

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

  vector <Float_t> GlobalPhiAngle;
  vector <Float_t> GlobalThetaAngle;

  vector <Float_t> TotalEnergy;
  vector <Float_t> KineticEnergy;


public:
  
  // Constructor
  QweakSimUserGEM_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserGEM_WirePlaneEvent();

  void     Initialize();
  void     Clear();

  void     StoreNbOfHits(Int_t noh)    { NbOfHits = noh; }
  Int_t      GetNbOfHits() const {return NbOfHits;}

  void     StoreTrackID(Int_t tid)    { TrackID.push_back(tid); }
  vector <Int_t>      GetTrackID() const {return TrackID;}

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit.push_back(gtime); }
  vector <Float_t>    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}

  //-----------------
  // Setter/Getter for X,U,V wire planes 

  void     StorePlaneHasBeenHit(Int_t nx)      { PlaneHasBeenHit = nx; }
  Int_t      GetPlaneHasBeenHit() const {return  PlaneHasBeenHit;}

  //-----------------
  void     StorePlaneLocalPositionX(Float_t lx)   { PlaneLocalPositionX.push_back(lx); }
  vector <Float_t>    GetPlaneLocalPositionX() const {return PlaneLocalPositionX;}

  void     StorePlaneLocalPositionY(Float_t ly)   { PlaneLocalPositionY.push_back(ly); }
  vector <Float_t>    GetPlaneLocalPositionY() const {return PlaneLocalPositionY;}

  void     StorePlaneLocalPositionZ(Float_t lz)   { PlaneLocalPositionZ.push_back(lz); }
  vector <Float_t>    GetPlaneLocalPositionZ() const {return PlaneLocalPositionZ;}
  //---
  void     StorePlaneGlobalPositionX(Float_t gx)   { PlaneGlobalPositionX.push_back(gx); }
  vector <Float_t>    GetPlaneGlobalPositionX() const {return PlaneGlobalPositionX;}

  void     StorePlaneGlobalPositionY(Float_t gy)   { PlaneGlobalPositionY.push_back(gy); }
  vector <Float_t>    GetPlaneGlobalPositionY() const {return PlaneGlobalPositionY;}

  void     StorePlaneGlobalPositionZ(Float_t gz)   { PlaneGlobalPositionZ.push_back(gz); }
  vector <Float_t>    GetPlaneGlobalPositionZ() const {return PlaneGlobalPositionZ;}

  //-----------------

  void     StorePlaneLocalMomentumX(Float_t lpx)   { PlaneLocalMomentumX.push_back(lpx); }
  vector <Float_t>    GetPlaneLocalMomentumX() const {return  PlaneLocalMomentumX;}

  void     StorePlaneLocalMomentumY(Float_t lpy)   { PlaneLocalMomentumY.push_back(lpy); }
  vector <Float_t>    GetPlaneLocalMomentumY() const {return  PlaneLocalMomentumY;}

  void     StorePlaneLocalMomentumZ(Float_t lpz)   { PlaneLocalMomentumZ.push_back(lpz); }
  vector <Float_t>    GetPlaneLocalMomentumZ() const {return  PlaneLocalMomentumZ;}
  //---
  void     StorePlaneGlobalMomentumX(Float_t gpx)   { PlaneGlobalMomentumX.push_back(gpx); }
  vector <Float_t>    GetPlaneGlobalMomentumX() const {return  PlaneGlobalMomentumX;}

  void     StorePlaneGlobalMomentumY(Float_t gpy)   { PlaneGlobalMomentumY.push_back(gpy); }
  vector <Float_t>    GetPlaneGlobalMomentumY() const {return  PlaneGlobalMomentumY;}

  void     StorePlaneGlobalMomentumZ(Float_t gpz)   { PlaneGlobalMomentumZ.push_back(gpz); }
  vector <Float_t>    GetPlaneGlobalMomentumZ() const {return  PlaneGlobalMomentumZ;}

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
  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle.push_back(theta); }
  vector <Float_t>    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}

  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle.push_back(phi); }
  vector <Float_t>    GetGlobalPhiAngle() const {return GlobalPhiAngle;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy.push_back(te); }
  vector <Float_t>    GetTotalEnergy() const {return TotalEnergy;}
  
  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy.push_back(ke); }
  vector <Float_t>    GetKineticEnergy() const {return KineticEnergy;}
  

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserGEM_WirePlaneEvent,1)

};  // end class QweakSimUserGEM_WirePlaneEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 


