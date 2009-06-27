//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserGEM_WirePlaneEvent.cc

   $Revision: 1.3 $	
   $Date: 2006/05/05 21:51:16 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:51:16 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserGEM_WirePlaneEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserGEM_WirePlaneEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserGEM_WirePlaneEvent::QweakSimUserGEM_WirePlaneEvent()   
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserGEM_WirePlaneEvent::~QweakSimUserGEM_WirePlaneEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserGEM_WirePlaneEvent::Initialize()
{
  TrackID                        = 0;
  GlobalTimeOfHit                = 0.0;

  PlaneHasBeenHit                = 0;

  PlaneLocalPositionX            = 0.0;
  PlaneLocalPositionY            = 0.0;
  PlaneLocalPositionZ            = 0.0;

  PlaneGlobalPositionX           = 0.0;
  PlaneGlobalPositionY           = 0.0;
  PlaneGlobalPositionZ           = 0.0;

  PlaneLocalMomentumX            = 0.0;
  PlaneLocalMomentumY            = 0.0;
  PlaneLocalMomentumZ            = 0.0;

  PlaneGlobalMomentumX           = 0.0;
  PlaneGlobalMomentumY           = 0.0;
  PlaneGlobalMomentumZ           = 0.0;

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
  CrossSection                   = 0.0;
  CrossSectionWeight             = 0.0;

  GlobalPhiAngle                 = 0.;
  GlobalThetaAngle               = 0.;

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
//      $Log: QweakSimUserGEM_WirePlaneEvent.cc,v $
//      Revision 1.3  2006/05/05 21:51:16  grimm
//      Records now the kinetic and total energy of track/particle
//
//      Revision 1.2  2005/12/27 19:17:21  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//

