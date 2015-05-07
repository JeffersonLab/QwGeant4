
// QweakSimUserTungstenPlug_DetectorEvent.cc
// Martin McHugh
// 2015-05-04

/////// --------------------------------------------------------------------

#include "QweakSimUserTungstenPlug_DetectorEvent.hh"

/////// --------------------------------------------------------------------

ClassImp(QweakSimUserTungstenPlug_DetectorEvent)

/////// --------------------------------------------------------------------

QweakSimUserTungstenPlug_DetectorEvent::QweakSimUserTungstenPlug_DetectorEvent() 
{
    SecondaryElectronCount         = 0;
    Initialize();
} 



/////// --------------------------------------------------------------------

QweakSimUserTungstenPlug_DetectorEvent::~QweakSimUserTungstenPlug_DetectorEvent()
{
}



/////// --------------------------------------------------------------------

void QweakSimUserTungstenPlug_DetectorEvent::Initialize()
{
    //DetectorID                   = 0.0;
	
    PrimaryEventNumber             = 0;
	
    TrackID.clear();
	
    ParticleName.clear();
    ParticleType.clear();
	
    GlobalTimeOfHit.clear();
	
    HasBeenHit                     = 0;
    EdgeEventFlag.clear();
    NbOfHits                       = 0;
	
    HitGlobalPositionX.clear();
    HitGlobalPositionY.clear();
    HitGlobalPositionZ.clear();
	
    HitLocalPositionX.clear();
    HitLocalPositionY.clear();
    HitLocalPositionZ.clear();
	
    HitLocalExitPositionX.clear();
    HitLocalExitPositionY.clear();
    HitLocalExitPositionZ.clear();
    
    OriginVertexPositionX.clear();
    OriginVertexPositionY.clear(); 
    OriginVertexPositionZ.clear();

    LocalVertexMomentumDirectionX.clear();
    LocalVertexMomentumDirectionY.clear();
    LocalVertexMomentumDirectionZ.clear();
	
    OriginVertexMomentumDirectionX.clear();
    OriginVertexMomentumDirectionY.clear();
    OriginVertexMomentumDirectionZ.clear();
    
    OriginVertexThetaAngle.clear();
    OriginVertexPhiAngle.clear();
	
    OriginVertexKineticEnergy.clear(); 
    OriginVertexTotalEnergy.clear(); 
	
    LocalVertexKineticEnergy.clear();  
    LocalVertexTotalEnergy.clear();   
    	
    GlobalPhiAngle.clear(); 
    GlobalThetaAngle.clear();
	
    //--- deposited energy in the TungstenPlug in one step
    DepositedEnergy.clear(); 
    //--- total deposited energy in the TungstenPlug in one event
    TotalDepositedEnergy             = 0.0;
}



