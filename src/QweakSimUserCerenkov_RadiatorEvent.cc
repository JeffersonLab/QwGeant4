#include "QweakSimUserCerenkov_RadiatorEvent.hh"

ClassImp(QweakSimUserCerenkov_RadiatorEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserCerenkov_RadiatorEvent::QweakSimUserCerenkov_RadiatorEvent()
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserCerenkov_RadiatorEvent::~QweakSimUserCerenkov_RadiatorEvent() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserCerenkov_RadiatorEvent::Initialize()
{
    DetectorID.clear();
    TrackID                        = 0;
    HasBeenHit                     = 0;
    NbOfHits                       = 0;
    GlobalTimeOfHit.clear();
    EdgeEventFlag.clear();
  
    HitLocalPositionX.clear();
    HitLocalPositionY.clear();
    HitLocalPositionZ.clear();

    PolarizationX.clear();
    PolarizationY.clear();
    PolarizationZ.clear();
    LongitudinalPolarization.clear();
    TransversePolarization.clear();
    TransversePolarizationX.clear();
    TransversePolarizationY.clear();
    TransversePolarizationZ.clear();
    TransversePolarizationPhiAngle.clear();

    HitLocalExitPositionX.clear();
    HitLocalExitPositionY.clear();
    HitLocalExitPositionZ.clear();

    HitGlobalPositionX.clear();
    HitGlobalPositionY.clear();
    HitGlobalPositionZ.clear();
    
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
    
    LocalMomentumX.clear();
    LocalMomentumY.clear();
    LocalMomentumZ.clear();
    LocalThetaAngle.clear();
    LocalPhiAngle.clear();

    GlobalMomentumX.clear();
    GlobalMomentumY.clear();
    GlobalMomentumZ.clear();
    GlobalThetaAngle.clear();
    GlobalPhiAngle.clear();

    EdgeEventFlag.clear();

    ParticleName.clear();
    CreatorProcessName.clear();
    ParticleID.clear();
    ParentID.clear();
    ParticleType.clear();

    TotalEnergy.clear();
    KineticEnergy.clear();

}	
