
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserHDC_WirePlaneEvent.cc

   $Date: Fri Jul  3 10:21:43 CDT 2009 $

   \author Klaus Hans Grimm   
   \author Jie Pan

*/
//=============================================================================
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserHDC_WirePlaneEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserHDC_WirePlaneEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserHDC_WirePlaneEvent::QweakSimUserHDC_WirePlaneEvent()   
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserHDC_WirePlaneEvent::~QweakSimUserHDC_WirePlaneEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserHDC_WirePlaneEvent::Initialize()
{
  Clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserHDC_WirePlaneEvent::Clear(const Option_t*)
{
  NbOfHits = 0;

  TrackID.clear();
  GlobalTimeOfHit.clear();

  PlaneHasBeenHit = 0;

  PlaneLocalPositionX.clear();
  PlaneLocalPositionY.clear();
  PlaneLocalPositionZ.clear();

  PlaneGlobalPositionX.clear();
  PlaneGlobalPositionY.clear();
  PlaneGlobalPositionZ.clear();

  PlaneLocalMomentumX.clear();
  PlaneLocalMomentumY.clear();
  PlaneLocalMomentumZ.clear();

  PlaneGlobalMomentumX.clear();
  PlaneGlobalMomentumY.clear();
  PlaneGlobalMomentumZ.clear();

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

  GlobalPhiAngle.clear();
  GlobalThetaAngle.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

