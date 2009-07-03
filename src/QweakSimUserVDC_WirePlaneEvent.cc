//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserVDC_WirePlaneEvent.cc

   $Revision: 1.3 $	
   $Date: 2006/01/06 21:42:29 $

   \author Klaus Hans Grimm   

*/
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserVDC_WirePlaneEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserVDC_WirePlaneEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserVDC_WirePlaneEvent::QweakSimUserVDC_WirePlaneEvent()   
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserVDC_WirePlaneEvent::~QweakSimUserVDC_WirePlaneEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserVDC_WirePlaneEvent::Initialize()
{
  TrackID.clear();
  GlobalTimeOfHit.clear();

  UPlaneHasBeenHit.clear();
  VPlaneHasBeenHit.clear();

  UPlaneLocalPositionX.clear();
  UPlaneLocalPositionY.clear();
  UPlaneLocalPositionZ.clear();
  UPlaneGlobalPositionX.clear();
  UPlaneGlobalPositionY.clear();
  UPlaneGlobalPositionZ.clear();

  UPlaneLocalMomentumX.clear();
  UPlaneLocalMomentumY.clear();
  UPlaneLocalMomentumZ.clear();
  UPlaneGlobalMomentumX.clear();
  UPlaneGlobalMomentumY.clear();
  UPlaneGlobalMomentumZ.clear();

  VPlaneLocalPositionX.clear();
  VPlaneLocalPositionY.clear();
  VPlaneLocalPositionZ.clear();
  VPlaneGlobalPositionX.clear();
  VPlaneGlobalPositionY.clear();
  VPlaneGlobalPositionZ.clear();

  VPlaneLocalMomentumX.clear();
  VPlaneLocalMomentumY.clear();
  VPlaneLocalMomentumZ.clear();
  VPlaneGlobalMomentumX.clear();
  VPlaneGlobalMomentumY.clear();
  VPlaneGlobalMomentumZ.clear();

  OriginVertexPositionX.clear();
  OriginVertexPositionY.clear();
  OriginVertexPositionZ.clear();
  OriginVertexMomentumDirectionX.clear();
  OriginVertexMomentumDirectionY.clear();
  OriginVertexMomentumDirectionZ.clear();
  OriginVertexThetaAngle.clear();
  OriginVertexPhiAngle.clear();
  OriginVertexKineticEnergy.clear();
  OriginVertexTotalEnergy.clear();

//   PrimaryQ2                      = 0.0;
//   CrossSection                   = 0.0;
//   CrossSectionWeight             = 0.0;

  UPlaneGlobalPhiAngle.clear();
  UPlaneGlobalThetaAngle.clear();

  VPlaneGlobalPhiAngle.clear();
  VPlaneGlobalThetaAngle.clear();

  ParticleName.clear();
  ParticleType.clear();         //   = -1;
  TotalEnergy.clear();
  KineticEnergy.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
