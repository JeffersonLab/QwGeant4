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
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/01/06 21:33:13 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

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

  Int_t   TrackID;
  Float_t GlobalTimeOfHit;

  Int_t   UPlaneHasBeenHit;
  Int_t   VPlaneHasBeenHit;

  Float_t UPlaneLocalPositionX;
  Float_t UPlaneLocalPositionY;
  Float_t UPlaneLocalPositionZ;
  
  Float_t UPlaneGlobalPositionX;
  Float_t UPlaneGlobalPositionY;
  Float_t UPlaneGlobalPositionZ;


  Float_t UPlaneLocalMomentumX;
  Float_t UPlaneLocalMomentumY;
  Float_t UPlaneLocalMomentumZ;

  Float_t UPlaneGlobalMomentumX;
  Float_t UPlaneGlobalMomentumY;
  Float_t UPlaneGlobalMomentumZ;

  Float_t UPlaneGlobalPhiAngle;
  Float_t UPlaneGlobalThetaAngle;




  Float_t VPlaneLocalPositionX;
  Float_t VPlaneLocalPositionY;
  Float_t VPlaneLocalPositionZ;

  Float_t VPlaneGlobalPositionX;
  Float_t VPlaneGlobalPositionY;
  Float_t VPlaneGlobalPositionZ;


  Float_t VPlaneLocalMomentumX;
  Float_t VPlaneLocalMomentumY;
  Float_t VPlaneLocalMomentumZ;
  
  Float_t VPlaneGlobalMomentumX;
  Float_t VPlaneGlobalMomentumY;
  Float_t VPlaneGlobalMomentumZ;

  Float_t VPlaneGlobalPhiAngle;
  Float_t VPlaneGlobalThetaAngle;

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
  Float_t CrossSectionWeight;

  Int_t   PrimaryEventNumber;

  TString ParticleName;
  Int_t   ParticleType;

  Float_t TotalEnergy;
  Float_t KineticEnergy;

public:
  
  // Constructor
  QweakSimUserVDC_WirePlaneEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_WirePlaneEvent();

  void     Initialize();

  void     StoreTrackID(Int_t tid)    { TrackID = tid; }
  Int_t      GetTrackID() const {return TrackID;}


  void     StoreParticleName(TString pn)    { ParticleName = pn; }
  TString    GetParticleName() const {return  ParticleName;}

  void     StoreParticleType(Int_t pt)      { ParticleType = pt; }
  Int_t      GetParticleType() const {return  ParticleType;}
    

  void     StoreGlobalTimeOfHit(Float_t gtime) { GlobalTimeOfHit = gtime; }
  Float_t    GetGlobalTimeOfHit()  const {return GlobalTimeOfHit;}

  void     StoreTotalEnergy(Float_t te)   { TotalEnergy = te; }
  Float_t    GetTotalEnergy() const {return TotalEnergy;}

  void     StoreKineticEnergy(Float_t ke)   { KineticEnergy = ke; }
  Float_t    GetKineticEnergy() const {return KineticEnergy;}

  void     StoreUPlaneHasBeenHit(Int_t nu)      { UPlaneHasBeenHit = nu; }
  Int_t      GetUPlaneHasBeenHit() const {return UPlaneHasBeenHit;}

  void     StoreVPlaneHasBeenHit(Int_t nv)      { VPlaneHasBeenHit = nv; }
  Int_t      GetVPlaneHasBeenHit() const {return VPlaneHasBeenHit;}

  //-----------------
  void     StoreUPlaneLocalPositionX(Float_t lx)   { UPlaneLocalPositionX = lx; }
  Float_t    GetUPlaneLocalPositionX() const {return UPlaneLocalPositionX;}

  void     StoreUPlaneLocalPositionY(Float_t ly)   { UPlaneLocalPositionY = ly; }
  Float_t    GetUPlaneLocalPositionY() const {return UPlaneLocalPositionY;}

  void     StoreUPlaneLocalPositionZ(Float_t lz)   { UPlaneLocalPositionZ = lz; }
  Float_t    GetUPlaneLocalPositionZ() const {return UPlaneLocalPositionZ;}
  //---
  void     StoreUPlaneGlobalPositionX(Float_t lx)   { UPlaneGlobalPositionX = lx; }
  Float_t    GetUPlaneGlobalPositionX() const {return UPlaneGlobalPositionX;}

  void     StoreUPlaneGlobalPositionY(Float_t ly)   { UPlaneGlobalPositionY = ly; }
  Float_t    GetUPlaneGlobalPositionY() const {return UPlaneGlobalPositionY;}

  void     StoreUPlaneGlobalPositionZ(Float_t lz)   { UPlaneGlobalPositionZ = lz; }
  Float_t    GetUPlaneGlobalPositionZ() const {return UPlaneGlobalPositionZ;}

  //-----------------

  void     StoreUPlaneLocalMomentumX(Float_t lpx)   { UPlaneLocalMomentumX = lpx; }
  Float_t    GetUPlaneLocalMomentumX() const {return UPlaneLocalMomentumX;}

  void     StoreUPlaneLocalMomentumY(Float_t lpy)   { UPlaneLocalMomentumY = lpy; }
  Float_t    GetUPlaneLocalMomentumY() const {return UPlaneLocalMomentumY;}

  void     StoreUPlaneLocalMomentumZ(Float_t lpz)   { UPlaneLocalMomentumZ = lpz; }
  Float_t    GetUPlaneLocalMomentumZ() const {return UPlaneLocalMomentumZ;}
  //---
  void     StoreUPlaneGlobalMomentumX(Float_t gpx)   { UPlaneGlobalMomentumX = gpx; }
  Float_t    GetUPlaneGlobalMomentumX() const {return UPlaneGlobalMomentumX;}

  void     StoreUPlaneGlobalMomentumY(Float_t gpy)   { UPlaneGlobalMomentumY = gpy; }
  Float_t    GetUPlaneGlobalMomentumY() const {return UPlaneGlobalMomentumY;}

  void     StoreUPlaneGlobalMomentumZ(Float_t gpz)   { UPlaneGlobalMomentumZ = gpz; }
  Float_t    GetUPlaneGlobalMomentumZ() const {return UPlaneGlobalMomentumZ;}


  void     StoreUPlaneGlobalThetaAngle(Float_t theta) { UPlaneGlobalThetaAngle = theta; }
  Float_t    GetUPlaneGlobalThetaAngle() const  {return UPlaneGlobalThetaAngle;}

  void     StoreUPlaneGlobalPhiAngle(Float_t phi)  { UPlaneGlobalPhiAngle = phi; }
  Float_t    GetUPlaneGlobalPhiAngle() const {return UPlaneGlobalPhiAngle;}

  //-----------------

  void     StoreVPlaneLocalPositionX(Float_t lx)   { VPlaneLocalPositionX = lx; }
  Float_t    GetVPlaneLocalPositionX() const {return VPlaneLocalPositionX;}

  void     StoreVPlaneLocalPositionY(Float_t ly)   { VPlaneLocalPositionY = ly; }
  Float_t    GetVPlaneLocalPositionY() const {return VPlaneLocalPositionY;}

  void     StoreVPlaneLocalPositionZ(Float_t lz)   { VPlaneLocalPositionZ = lz; }
  Float_t    GetVPlaneLocalPositionZ() const {return VPlaneLocalPositionZ;}

  void     StoreVPlaneGlobalPositionX(Float_t lx)   { VPlaneGlobalPositionX = lx; }
  Float_t    GetVPlaneGlobalPositionX() const {return VPlaneGlobalPositionX;}

  void     StoreVPlaneGlobalPositionY(Float_t ly)   { VPlaneGlobalPositionY = ly; }
  Float_t    GetVPlaneGlobalPositionY() const {return VPlaneGlobalPositionY;}

  void     StoreVPlaneGlobalPositionZ(Float_t lz)   { VPlaneGlobalPositionZ = lz; }
  Float_t    GetVPlaneGlobalPositionZ() const {return VPlaneGlobalPositionZ;}

  //-----------------

  void     StoreVPlaneLocalMomentumX(Float_t lpx)   { VPlaneLocalMomentumX = lpx; }
  Float_t    GetVPlaneLocalMomentumX() const {return VPlaneLocalMomentumX;}

  void     StoreVPlaneLocalMomentumY(Float_t lpy)   { VPlaneLocalMomentumY = lpy; }
  Float_t    GetVPlaneLocalMomentumY() const {return VPlaneLocalMomentumY;}

  void     StoreVPlaneLocalMomentumZ(Float_t lpz)   { VPlaneLocalMomentumZ = lpz; }
  Float_t    GetVPlaneLocalMomentumZ() const {return VPlaneLocalMomentumZ;}
  //---
  void     StoreVPlaneGlobalMomentumX(Float_t gpx)   { VPlaneGlobalMomentumX = gpx; }
  Float_t    GetVPlaneGlobalMomentumX() const {return VPlaneGlobalMomentumX;}

  void     StoreVPlaneGlobalMomentumY(Float_t gpy)   { VPlaneGlobalMomentumY = gpy; }
  Float_t    GetVPlaneGlobalMomentumY() const {return VPlaneGlobalMomentumY;}

  void     StoreVPlaneGlobalMomentumZ(Float_t gpz)   { VPlaneGlobalMomentumZ = gpz; }
  Float_t    GetVPlaneGlobalMomentumZ() const {return VPlaneGlobalMomentumZ;}


  void     StoreVPlaneGlobalThetaAngle(Float_t theta) { VPlaneGlobalThetaAngle = theta; }
  Float_t    GetVPlaneGlobalThetaAngle() const  {return VPlaneGlobalThetaAngle;}

  void     StoreVPlaneGlobalPhiAngle(Float_t phi)  { VPlaneGlobalPhiAngle = phi; }
  Float_t    GetVPlaneGlobalPhiAngle() const {return VPlaneGlobalPhiAngle;}

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

  void     StoreCrossSectionWeight(Float_t csw)  {CrossSectionWeight = csw;}
  Float_t    GetCrossSectionWeight() const {return CrossSectionWeight; }

  void     StorePrimaryEventNumber(Int_t pen)    { PrimaryEventNumber = pen; }
  Int_t      GetPrimaryEventNumber() const {return PrimaryEventNumber; }
  //-----------------

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_WirePlaneEvent,1)

};  // end class QweakSimUserVDC_WirePlaneEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_WirePlaneEvent.hh,v $
//      Revision 1.3  2006/01/06 21:33:13  grimm
//      Storing ParticleName and ParticleType
//
//      Revision 1.2  2005/12/27 19:31:44  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

