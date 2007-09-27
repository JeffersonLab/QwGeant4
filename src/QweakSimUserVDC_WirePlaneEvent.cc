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

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/01/06 21:42:29 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================


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
  TrackID                        = 0;
  GlobalTimeOfHit                = 0.0;

  UPlaneHasBeenHit               = 0;
  VPlaneHasBeenHit               = 0;

  UPlaneLocalPositionX           = 0.0;
  UPlaneLocalPositionY           = 0.0;
  UPlaneLocalPositionZ           = 0.0;
  UPlaneGlobalPositionX          = 0.0;
  UPlaneGlobalPositionY          = 0.0;
  UPlaneGlobalPositionZ          = 0.0;

  UPlaneLocalMomentumX           = 0.0;
  UPlaneLocalMomentumY           = 0.0;
  UPlaneLocalMomentumZ           = 0.0;
  UPlaneGlobalMomentumX          = 0.0;
  UPlaneGlobalMomentumY          = 0.0;
  UPlaneGlobalMomentumZ          = 0.0;

  VPlaneLocalPositionX           = 0.0;
  VPlaneLocalPositionY           = 0.0;
  VPlaneLocalPositionZ           = 0.0;
  VPlaneGlobalPositionX          = 0.0;
  VPlaneGlobalPositionY          = 0.0;
  VPlaneGlobalPositionZ          = 0.0;

  VPlaneLocalMomentumX           = 0.0;
  VPlaneLocalMomentumY           = 0.0;
  VPlaneLocalMomentumZ           = 0.0;
  VPlaneGlobalMomentumX          = 0.0;
  VPlaneGlobalMomentumY          = 0.0;
  VPlaneGlobalMomentumZ          = 0.0;

  OriginVertexPositionX          = 0.0;
  OriginVertexPositionY          = 0.0;
  OriginVertexPositionZ          = 0.0;
  OriginVertexMomentumDirectionX = 0.0;
  OriginVertexMomentumDirectionY = 0.0;
  OriginVertexMomentumDirectionZ = 0.0;
  OriginVertexThetaAngle         = 0.0;
  OriginVertexPhiAngle           = 0.0;
  OriginVertexKineticEnergy      = 0.0;
  OriginVertexTotalEnergy        = 0.0;

  PrimaryQ2                      = 0.0;
  CrossSectionWeight             = 0.0;

  UPlaneGlobalPhiAngle           = 0.;
  UPlaneGlobalThetaAngle         = 0.;

  VPlaneGlobalPhiAngle           = 0.;
  VPlaneGlobalThetaAngle         = 0.;

  ParticleName                   = "None";
  ParticleType                   = -1;
  TotalEnergy                    = 0.;
  KineticEnergy                  = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_WirePlaneEvent.cc,v $
//      Revision 1.3  2006/01/06 21:42:29  grimm
//       Added initialization of:
//
//        ParticleName                   = "None";
//        ParticleType                   = -1;
//        TotalEnergy                    = 0.;
//        KineticEnergy                  = 0.;
//
//      Revision 1.2  2005/12/27 19:19:01  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
