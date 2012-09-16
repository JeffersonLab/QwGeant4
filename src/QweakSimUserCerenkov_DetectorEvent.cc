//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserCerenkov_DetectorEvent.cc

   $Revision: 1.3 $	
   $Date: 2006/01/06 21:43:04 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimUserCerenkov_DetectorEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserCerenkov_DetectorEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserCerenkov_DetectorEvent::QweakSimUserCerenkov_DetectorEvent() 
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserCerenkov_DetectorEvent::~QweakSimUserCerenkov_DetectorEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserCerenkov_DetectorEvent::Initialize()
{
    DetectorID                     = 0;
    TrackID                        = 0;
    HasBeenHit                     = 0;
    NbOfHits                       = 0;
    GlobalTimeOfHit                = 0.0;
    EdgeEventFlag                  = 0;

    SecPartLocalOriginX.clear();
    SecPartLocalOriginY.clear();
    SecPartLocalOriginZ.clear();

    SecPartLocalMomentumX.clear();
    SecPartLocalMomentumY.clear();
    SecPartLocalMomentumZ.clear();

    SecPartLocalEnergy.clear();
    SecPartLocalType.clear();


    OpticalPhotonCount = 0;
    CerenkovPhotonEnergy.clear();

    SecondaryParticleCount = 0;
    SecondaryElectronCount = 0;
    SecondaryPhotonCount   = 0;  
    SecondaryPositronCount = 0;
  
    HitLocalPositionX.clear();
    HitLocalPositionY.clear();
    HitLocalPositionZ.clear();

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

    EdgeEventFlag                  = 0;

    ParticleName                   = "None";
    ParticleType                   = -1;
    TotalEnergy                    = 0.;
    KineticEnergy                  = 0.;

}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimUserCerenkov_DetectorEvent::AddSecondaryParticleEvent(Float_t XO, Float_t YO, Float_t ZO,
								   Float_t XM, Float_t YM, Float_t ZM,
								   Float_t energy, Int_t type)
{
  SecPartLocalOriginX.push_back(XO);
  SecPartLocalOriginY.push_back(YO);
  SecPartLocalOriginZ.push_back(ZO);
  
  SecPartLocalMomentumX.push_back(XM);
  SecPartLocalMomentumY.push_back(YM);
  SecPartLocalMomentumZ.push_back(ZM);
  
  SecPartLocalEnergy.push_back(energy);
  SecPartLocalType.push_back(type);
 
  if (type == 11)  SecondaryElectronCount++;
  if (type == 22)  SecondaryPhotonCount++;
  if (type == -11) SecondaryPositronCount++;
  SecondaryParticleCount++;  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

