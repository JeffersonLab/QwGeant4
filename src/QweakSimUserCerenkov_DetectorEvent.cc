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
  SecondaryParticleCount         = 0;
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

    if(SecondaryParticleCount){
      delete[] SecPartLocalOriginX;  
      delete[] SecPartLocalOriginY;  
      delete[] SecPartLocalOriginZ;  
                            
      delete[] SecPartLocalMomentumX;
      delete[] SecPartLocalMomentumY;
      delete[] SecPartLocalMomentumZ;
                            
      delete[] SecPartLocalEnergy;   
      delete[] SecPartLocalCharge;   
    }


    SecPartLocalOriginX = NULL; 
    SecPartLocalOriginY = NULL;
    SecPartLocalOriginZ = NULL; 
    
    SecPartLocalMomentumX = NULL;
    SecPartLocalMomentumY = NULL;
    SecPartLocalMomentumZ = NULL;
    
    SecPartLocalEnergy = NULL;
    SecPartLocalCharge = NULL;

    OpticalPhotonCount = 0;
    CerenkovPhotonEnergy.clear();
    CerenkovPhotonEnergy.resize(0);

    SecondaryParticleCount = 0;
    SecondaryElectronCount = 0;
    SecondaryPhotonCount   = 0;  
    SecondaryPositronCount = 0;
  
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
    
//     PrimaryQ2                      = 0.0;
//     CrossSection                   = 0.0;
//     CrossSectionWeight             = 0.0;

    EdgeEventFlag                  = 0;

    ParticleName                   = "None";
    ParticleType                   = -1;
    TotalEnergy                    = 0.;
    KineticEnergy                  = 0.;

}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimUserCerenkov_DetectorEvent::AddSecondaryParticleEvent(Float_t XO, Float_t YO, Float_t ZO,
								   Float_t XM, Float_t YM, Float_t ZM,
								   Float_t Eng, Float_t charge)
{
  Int_t cnt = SecondaryParticleCount;
  Float_t *tmp1X = NULL;
  Float_t *tmp1Y = NULL;
  Float_t *tmp1Z = NULL;
                   
  Float_t *tmp2X = NULL;
  Float_t *tmp2Y = NULL;
  Float_t *tmp2Z = NULL;
                   
  Float_t *tmp3 = NULL;
  Float_t *tmp4 = NULL;
 
  if(cnt){
    tmp1X = new Float_t[cnt];
    tmp1Y = new Float_t[cnt];
    tmp1Z = new Float_t[cnt];
    
    tmp2X = new Float_t[cnt];
    tmp2Y = new Float_t[cnt];
    tmp2Z = new Float_t[cnt];

    tmp3 = new Float_t[cnt];
    tmp4 = new Float_t[cnt];
  }

  for(Int_t i = 0; i < cnt; i++){
    tmp1X[i] = SecPartLocalOriginX[i]; 
    tmp1Y[i] = SecPartLocalOriginY[i];
    tmp1Z[i] = SecPartLocalOriginZ[i]; 
		                      
    tmp2X[i] = SecPartLocalMomentumX[i];
    tmp2Y[i] = SecPartLocalMomentumY[i];
    tmp2Z[i] = SecPartLocalMomentumZ[i];
         	                      
    tmp3[i]  = SecPartLocalEnergy[i];
    tmp4[i]  = SecPartLocalCharge[i];
  }
  
  if(cnt && SecPartLocalOriginX) delete[] SecPartLocalOriginX;
  if(cnt && SecPartLocalOriginY) delete[] SecPartLocalOriginY;
  if(cnt && SecPartLocalOriginZ) delete[] SecPartLocalOriginZ;
	                         
  if(cnt && SecPartLocalMomentumX) delete[] SecPartLocalMomentumX;
  if(cnt && SecPartLocalMomentumX) delete[] SecPartLocalMomentumY;
  if(cnt && SecPartLocalMomentumX) delete[] SecPartLocalMomentumZ;
	                         
  if(cnt && SecPartLocalEnergy) delete[] SecPartLocalEnergy;
  if(cnt && SecPartLocalCharge) delete[] SecPartLocalCharge;

  SecPartLocalOriginX   = new Float_t[cnt+1];
  SecPartLocalOriginY   = new Float_t[cnt+1];
  SecPartLocalOriginZ   = new Float_t[cnt+1];
                    
  SecPartLocalMomentumX = new Float_t[cnt+1];
  SecPartLocalMomentumY = new Float_t[cnt+1];
  SecPartLocalMomentumZ = new Float_t[cnt+1];

  SecPartLocalEnergy    = new Float_t[cnt+1];
  SecPartLocalCharge    = new Float_t[cnt+1];

  for(Int_t i = 0; i < cnt; i++) {
    SecPartLocalOriginX[i]   = tmp1X[i];
    SecPartLocalOriginY[i]   = tmp1Y[i];
    SecPartLocalOriginZ[i]   = tmp1Z[i];
    
    SecPartLocalMomentumX[i] = tmp2X[i];
    SecPartLocalMomentumY[i] = tmp2Y[i];
    SecPartLocalMomentumZ[i] = tmp2Z[i];
    
    SecPartLocalEnergy[i]    = tmp3[i] ;
    SecPartLocalCharge[i]    = tmp4[i] ;
  }

  SecPartLocalOriginX[cnt]   =  XO;
  SecPartLocalOriginY[cnt]   =  YO;
  SecPartLocalOriginZ[cnt]   =  ZO;
  
  SecPartLocalMomentumX[cnt] =  XM;
  SecPartLocalMomentumY[cnt] =  YM;
  SecPartLocalMomentumZ[cnt] =  ZM;
  
  SecPartLocalEnergy[cnt]    =  Eng;
  SecPartLocalCharge[cnt]    =  charge;
 
  if(cnt){
    delete[] tmp1X;
    delete[] tmp1Y;
    delete[] tmp1Z;
    
    delete[] tmp2X;
    delete[] tmp2Y;
    delete[] tmp2Z;
    
    delete[] tmp3;
    delete[] tmp4;
  }

  if(charge == -1)  SecondaryElectronCount++;  
  if(charge == 0)   SecondaryPhotonCount++;  
  if(charge == 1)   SecondaryPositronCount++;  
  SecondaryParticleCount++;  
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

