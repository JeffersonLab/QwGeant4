
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserTriggerScintillator_DetectorEvent.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:18:12 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:18:12 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserTriggerScintillator_DetectorEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserTriggerScintillator_DetectorEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserTriggerScintillator_DetectorEvent::QweakSimUserTriggerScintillator_DetectorEvent() 
{
  SecondaryElectronCount         = 0;
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserTriggerScintillator_DetectorEvent::~QweakSimUserTriggerScintillator_DetectorEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserTriggerScintillator_DetectorEvent::Initialize()
{
    TrackID                        = 0;
    HasBeenHit                     = 0;
    NbOfHits                       = 0;
    GlobalTimeOfHit                = 0.0;
    EdgeEventFlag                  = 0;


//     if(SecondaryElectronCount){
//       delete[] SecElecLocalOriginX;
//       delete[] SecElecLocalOriginY;
//       delete[] SecElecLocalOriginZ;
//
//       delete[] SecElecLocalMomentumX;
//       delete[] SecElecLocalMomentumY;
//       delete[] SecElecLocalMomentumZ;
//
//       delete[] SecElecLocalEnergy;
//     }

//     if(SecondaryElectronCount){
//
//         SecElecLocalOriginX.clear();
//         SecElecLocalOriginY.clear();
//         SecElecLocalOriginZ.clear();
//
//         SecElecLocalMomentumX.clear();
//         SecElecLocalMomentumY.clear();
//         SecElecLocalMomentumZ.clear();
//
//         SecElecLocalEnergy.clear();
//     }
//
    SecondaryElectronCount = 0;
  
    HitLocalPositionX              = 0.0;
    HitLocalPositionY              = 0.0;
    HitLocalPositionZ              = 0.0;

    HitGlobalPositionX             = 0.0;
    HitGlobalPositionY             = 0.0;
    HitGlobalPositionZ             = 0.0;
    
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

    EdgeEventFlag                  = 0;

    GlobalPhiAngle                 = 0.;
    GlobalThetaAngle               = 0.;
}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
// void QweakSimUserTriggerScintillator_DetectorEvent::AddSecondaryElectronEvent(Float_t XO, Float_t YO, Float_t ZO,
//                                                                               Float_t XM, Float_t YM, Float_t ZM,
//                                                                               Float_t Eng)
// {
//   G4int cnt = SecondaryElectronCount;
//
//   Float_t *tmp1X = NULL;
//   Float_t *tmp1Y = NULL;
//   Float_t *tmp1Z = NULL;
//
//   Float_t *tmp2X = NULL;
//   Float_t *tmp2Y = NULL;
//   Float_t *tmp2Z = NULL;
//
//   Float_t *tmp3 = NULL;
//
//   if(cnt){
//     tmp1X = new Float_t[cnt];
//     tmp1Y = new Float_t[cnt];
//     tmp1Z = new Float_t[cnt];
//
//     tmp2X = new Float_t[cnt];
//     tmp2Y = new Float_t[cnt];
//     tmp2Z = new Float_t[cnt];
//
//     tmp3 = new Float_t[cnt];
//   }
//
//   for(Int_t i = 0; i < cnt; i++){
//     tmp1X[i] = SecElecLocalOriginX[i];
//     tmp1Y[i] = SecElecLocalOriginY[i];
//     tmp1Z[i] = SecElecLocalOriginZ[i];
//
//     tmp2X[i] = SecElecLocalMomentumX[i];
//     tmp2Y[i] = SecElecLocalMomentumY[i];
//     tmp2Z[i] = SecElecLocalMomentumZ[i];
//
//     tmp3[i]  = SecElecLocalEnergy[i];
//   }
//
//   if(cnt && SecElecLocalOriginX) delete[] SecElecLocalOriginX;
//   if(cnt && SecElecLocalOriginY) delete[] SecElecLocalOriginY;
//   if(cnt && SecElecLocalOriginZ) delete[] SecElecLocalOriginZ;
//
//   if(cnt && SecElecLocalMomentumX) delete[] SecElecLocalMomentumX;
//   if(cnt && SecElecLocalMomentumX) delete[] SecElecLocalMomentumY;
//   if(cnt && SecElecLocalMomentumX) delete[] SecElecLocalMomentumZ;
//
//   if(cnt && SecElecLocalEnergy) delete[] SecElecLocalEnergy;
//
//   SecElecLocalOriginX   = new Float_t[cnt+1];
//   SecElecLocalOriginY   = new Float_t[cnt+1];
//   SecElecLocalOriginZ   = new Float_t[cnt+1];
//
//   SecElecLocalMomentumX = new Float_t[cnt+1];
//   SecElecLocalMomentumY = new Float_t[cnt+1];
//   SecElecLocalMomentumZ = new Float_t[cnt+1];
//
//   SecElecLocalEnergy    = new Float_t[cnt+1];
//
//   for(Int_t i = 0; i < cnt; i++) {
//     SecElecLocalOriginX[i]   = tmp1X[i];
//     SecElecLocalOriginY[i]   = tmp1Y[i];
//     SecElecLocalOriginZ[i]   = tmp1Z[i];
//
//     SecElecLocalMomentumX[i] = tmp2X[i];
//     SecElecLocalMomentumY[i] = tmp2Y[i];
//     SecElecLocalMomentumZ[i] = tmp2Z[i];
//
//     SecElecLocalEnergy[i]    = tmp3[i] ;
//   }

//   SecElecLocalOriginX.push_back(XO);
//   SecElecLocalOriginY.push_back(YO);
//   SecElecLocalOriginZ.push_back(YO);
//
//   SecElecLocalMomentumX.push_back(XM);
//   SecElecLocalMomentumY.push_back(YM);
//   SecElecLocalMomentumZ.push_back(ZM);
//
//   SecElecLocalEnergy.push_back(Eng);
 
//   if(cnt){
//     delete[] tmp1X;
//     delete[] tmp1Y;
//     delete[] tmp1Z;
//
//     delete[] tmp2X;
//     delete[] tmp2Y;
//     delete[] tmp2Z;
//
//     delete[] tmp3;
//   }
//
//   SecondaryElectronCount++;
// }
//


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserTriggerScintillator_DetectorEvent.cc,v $
//      Revision 1.2  2005/12/27 19:18:12  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//

