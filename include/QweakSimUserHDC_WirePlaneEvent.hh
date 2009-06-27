//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserHDC_WirePlaneEvent.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:38:40 $
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
   \class QweakSimUserHDC_WirePlaneEvent
    
   \brief ROOT Subtree structure for HDC WirePlaneEvent

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserHDC_WirePlaneEvent_h
#define QweakSimUserHDC_WirePlaneEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "cpp_include.h"
#include "Root_include.h"

#ifndef __CINT__
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserHDC_WirePlaneEvent 
{

private:

  Int_t   TrackID;
  Float_t GlobalTimeOfHit;

  Int_t   PlaneHasBeenHit;

  Float_t PlaneLocalPositionX;
  Float_t PlaneLocalPositionY;
  Float_t PlaneLocalPositionZ;
  
  Float_t PlaneGlobalPositionX;
  Float_t PlaneGlobalPositionY;
  Float_t PlaneGlobalPositionZ;

  Float_t PlaneLocalMomentumX;
  Float_t PlaneLocalMomentumY;
  Float_t PlaneLocalMomentumZ;

  Float_t PlaneGlobalMomentumX;
  Float_t PlaneGlobalMomentumY;
  Float_t PlaneGlobalMomentumZ;

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

  Float_t PrimaryQ2;
  Float_t CrossSection;
  Float_t CrossSectionWeight;

  Int_t   PrimaryEventNumber;

  Float_t GlobalPhiAngle;
  Float_t GlobalThetaAngle;

  Float_t TotalEnergy;
  Float_t KineticEnergy;

public:
  
  // Constructor
  QweakSimUserHDC_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserHDC_WirePlaneEvent();

  void     Initialize();

  void     StoreTrackID(Int_t tid)    { TrackID = tid; }
  Int_t      GetTrackID() const {return TrackID;}

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit = gtime; }
  Float_t    GetGloablTimeOfHit()  const {return GlobalTimeOfHit;}

  //-----------------
  // Setter/Getter for X,U,V wire planes 

  void     StorePlaneHasBeenHit(Int_t nx)      { PlaneHasBeenHit = nx; }
  Int_t      GetPlaneHasBeenHit() const {return  PlaneHasBeenHit;}

  //-----------------
  void     StorePlaneLocalPositionX(Float_t lx)   { PlaneLocalPositionX = lx; }
  Float_t    GetPlaneLocalPositionX() const {return PlaneLocalPositionX;}

  void     StorePlaneLocalPositionY(Float_t ly)   { PlaneLocalPositionY = ly; }
  Float_t    GetPlaneLocalPositionY() const {return PlaneLocalPositionY;}

  void     StorePlaneLocalPositionZ(Float_t lz)   { PlaneLocalPositionZ = lz; }
  Float_t    GetPlaneLocalPositionZ() const {return PlaneLocalPositionZ;}
  //---
  void     StorePlaneGlobalPositionX(Float_t gx)   { PlaneGlobalPositionX = gx; }
  Float_t    GetPlaneGlobalPositionX() const {return PlaneGlobalPositionX;}

  void     StorePlaneGlobalPositionY(Float_t gy)   { PlaneGlobalPositionY = gy; }
  Float_t    GetPlaneGlobalPositionY() const {return PlaneGlobalPositionY;}

  void     StorePlaneGlobalPositionZ(Float_t gz)   { PlaneGlobalPositionZ = gz; }
  Float_t    GetPlaneGlobalPositionZ() const {return PlaneGlobalPositionZ;}

  //-----------------

  void     StorePlaneLocalMomentumX(Float_t lpx)   { PlaneLocalMomentumX = lpx; }
  Float_t    GetPlaneLocalMomentumX() const {return  PlaneLocalMomentumX;}

  void     StorePlaneLocalMomentumY(Float_t lpy)   { PlaneLocalMomentumY = lpy; }
  Float_t    GetPlaneLocalMomentumY() const {return  PlaneLocalMomentumY;}

  void     StorePlaneLocalMomentumZ(Float_t lpz)   { PlaneLocalMomentumZ = lpz; }
  Float_t    GetPlaneLocalMomentumZ() const {return  PlaneLocalMomentumZ;}
  //---
  void     StorePlaneGlobalMomentumX(Float_t gpx)   { PlaneGlobalMomentumX = gpx; }
  Float_t    GetPlaneGlobalMomentumX() const {return  PlaneGlobalMomentumX;}

  void     StorePlaneGlobalMomentumY(Float_t gpy)   { PlaneGlobalMomentumY = gpy; }
  Float_t    GetPlaneGlobalMomentumY() const {return  PlaneGlobalMomentumY;}

  void     StorePlaneGlobalMomentumZ(Float_t gpz)   { PlaneGlobalMomentumZ = gpz; }
  Float_t    GetPlaneGlobalMomentumZ() const {return  PlaneGlobalMomentumZ;}

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
  //-----------------
  void     StorePrimaryQ2(Float_t pq2)  { PrimaryQ2 = pq2; }
  Float_t    GetPrimaryQ2() const {return PrimaryQ2; }

  void     StoreCrossSection(Float_t cs)  {CrossSection = cs;}
  Float_t    GetCrossSection() const {return CrossSection; }

  void     StoreCrossSectionWeight(Float_t csw)  {CrossSectionWeight = csw;}
  Float_t    GetCrossSectionWeight() const {return CrossSectionWeight; }

  void     StorePrimaryEventNumber(Int_t pen)    { PrimaryEventNumber = pen; }
  Int_t      GetPrimaryEventNumber() const {return PrimaryEventNumber; }
  //-----------------
  void     StoreGlobalThetaAngle(Float_t theta) { GlobalThetaAngle = theta; }
  Float_t    GetGlobalThetaAngle() const  {return GlobalThetaAngle;}
  
  void     StoreGlobalPhiAngle(Float_t phi)  { GlobalPhiAngle = phi; }
  Float_t    GetGlobalPhiAngle() const {return GlobalPhiAngle;}
  //-----------------

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy = te; }
  Float_t    GetTotalEnergy() const {return TotalEnergy;}
  
  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy = ke; }
  Float_t    GetKineticEnergy() const {return KineticEnergy;}
    

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserHDC_WirePlaneEvent,1)

};  // end class QweakSimUserHDC_WirePlaneEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

