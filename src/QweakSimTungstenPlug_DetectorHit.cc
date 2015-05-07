
// QweakSimTungstenPlug_DetectorHit.cc
// Martin McHugh
// 2015-05-04

/////// --------------------------------------------------------------------

#include "QweakSimTungstenPlug_DetectorHit.hh"

//--- geant4 includes
#include "G4Circle.hh"



/////// --------------------------------------------------------------------

G4Allocator<QweakSimTungstenPlug_DetectorHit> QweakSimTungstenPlug_DetectorHitAllocator;

/////// --------------------------------------------------------------------

QweakSimTungstenPlug_DetectorHit::QweakSimTungstenPlug_DetectorHit()
{
    detectorID                    = -1;
	
    primaryEventNumber            = -1;
	
    trackID                       = -1.;
	
    particleName                  = "None";
    particleType                  = -1;
	
    time                          = 0.;
	
    hasBeenHit                    = 0;
    edgeEventFlag                 = 0;
    nbOfHits                      = 0;
	
    worldPos                      = G4ThreeVector(0.0,0.0,0.0);
    localPos                      = G4ThreeVector(0.0,0.0,0.0);
    localExitPos                  = G4ThreeVector(0.0,0.0,0.0);
    originVertexPosition          = G4ThreeVector(0.0,0.0,0.0);
	
    worldMomentum                 = G4ThreeVector(0.0,0.0,0.0);
    localMomentum                 = G4ThreeVector(0.0,0.0,0.0);
    currentMomentumDirection      = G4ThreeVector(0.0,0.0,0.0);
    originVertexMomentumDirection = G4ThreeVector(0.0,0.0,0.0);
	
    originVertexKineticEnergy     = 0.;
    originVertexTotalEnergy       = 0.;

    currentKineticEnergy          = 0.;
    currentTotalEnergy            = 0.;
	
    //--- TungstenPlug deposited energy
    depositedEnergy               = 0.;
	
    pLogV                         = 0;
}



/////// --------------------------------------------------------------------

QweakSimTungstenPlug_DetectorHit::QweakSimTungstenPlug_DetectorHit(G4int detector_id)
{
    detectorID = detector_id;
    time       = 0.;
    pLogV      = 0;
	
}



/////// --------------------------------------------------------------------

QweakSimTungstenPlug_DetectorHit::~QweakSimTungstenPlug_DetectorHit()
{;}



/////// --------------------------------------------------------------------

QweakSimTungstenPlug_DetectorHit::QweakSimTungstenPlug_DetectorHit(const QweakSimTungstenPlug_DetectorHit &right)
: G4VHit() 
{
    detectorID     = right.detectorID;
	
    primaryEventNumber = right.primaryEventNumber;
	
    trackID        = right.trackID;

    particleName   = right.particleName;
    particleType   = right.particleType;
	
    time           = right.time;
	
    hasBeenHit     = right.hasBeenHit;
    edgeEventFlag  = right.edgeEventFlag;
    nbOfHits       = right.nbOfHits;
	
    worldPos       = right.worldPos;
    localPos       = right.localPos;
    localExitPos   = right.localExitPos;
    originVertexPosition          = right.originVertexPosition;
	
    worldMomentum                 = right.worldMomentum;
    localMomentum                 = right.localMomentum;
    currentMomentumDirection      = right.currentMomentumDirection;
    originVertexMomentumDirection = right.originVertexMomentumDirection;
    
    originVertexKineticEnergy     = right.originVertexKineticEnergy;
    originVertexTotalEnergy       = right.originVertexTotalEnergy;
	
    currentKineticEnergy          = right.currentKineticEnergy;
    currentTotalEnergy            = right.currentTotalEnergy;
	
    //--- TungstenPlug deposited energy
    depositedEnergy               = right.depositedEnergy;
	
    cellPos        = right.cellPos;
    cellRot        = right.cellRot;
    pLogV          = right.pLogV;
	
}



/////// --------------------------------------------------------------------

const QweakSimTungstenPlug_DetectorHit& QweakSimTungstenPlug_DetectorHit::operator=(const QweakSimTungstenPlug_DetectorHit &right)
{
    detectorID     = right.detectorID;
	
    primaryEventNumber = right.primaryEventNumber;
	
    trackID        = right.trackID;
	
    particleName   = right.particleName;
    particleType   = right.particleType;
	
    time           = right.time;
	
    hasBeenHit     = right.hasBeenHit;
    edgeEventFlag  = right.edgeEventFlag;
    nbOfHits       = right.nbOfHits;
	
    worldPos       = right.worldPos;
    localPos       = right.localPos;
    localExitPos   = right.localExitPos;
    originVertexPosition          = right.originVertexPosition;

    worldMomentum                 = right.worldMomentum;
    localMomentum                 = right.localMomentum;
    currentMomentumDirection      = right.currentMomentumDirection;
    originVertexMomentumDirection = right.originVertexMomentumDirection;
	
    //originVertexThetaAngle      = right.originVertexthetaAngle;
    //originVertexPhiAngle        = right.originVertexPhiAngle;
    
    originVertexKineticEnergy     = right.originVertexKineticEnergy;
    originVertexTotalEnergy       = right.originVertexTotalEnergy;
	
    currentKineticEnergy          = right.currentKineticEnergy;
    currentTotalEnergy            = right.currentTotalEnergy;
	
    //primaryQ2                   = right.primaryQ2;
    //crossSection                = right.crossSection;
    //crossSectionWeight          = right.crossSectionWeight;
	
    //globalThetaAngle            = right.globalThetaAngle;
    //globalPhiAngle              = right.globalPhiAngle;
	
    //--- TungstenPlug deposited energy
    depositedEnergy               = right.depositedEnergy;
	
    cellPos        = right.cellPos;
    cellRot        = right.cellRot;
    pLogV          = right.pLogV;
	
    return *this;
	
}



/////// --------------------------------------------------------------------

int QweakSimTungstenPlug_DetectorHit::operator==(const QweakSimTungstenPlug_DetectorHit & ) const
{
    //return (this==&right) ? 1 : 0;
    return 0;
}



/////// --------------------------------------------------------------------

void QweakSimTungstenPlug_DetectorHit::Draw()
{
    G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
	
    if (pVVisManager)
    {
        //--- draw small yellow balls for the impact point
		
        G4Colour colourHit (255/255., 255/255., 0/255.);  // yellow
		
        G4VisAttributes attribs(colourHit);
		
        G4Circle circle(worldPos);
        circle.SetScreenSize(0.01);
        circle.SetFillStyle(G4Circle::filled);
        circle.SetVisAttributes(attribs);
		
        pVVisManager->Draw(circle);
		
        //--- draw/overlay a white drift cell for a hit
		
        // G4Transform3D trans(cellRot.inverse(),cellPos);
        // const G4VisAttributes* pVA = pLogV->GetVisAttributes();
        // if(pVA) attribs = *pVA;
        // G4Colour colourCell (1.,1.,1.);    // white
        // attribs.SetColour(colourCell);
        // attribs.SetForceSolid(true);
        // attribs.SetVisibility(true);
        // pVVisManager->Draw(*pLogV,attribs,trans);
		
    }
	
}



/////// --------------------------------------------------------------------

void QweakSimTungstenPlug_DetectorHit::Print()
{
    // G4cout << " TungstenPlug[" << DetectorID << "] : time " << time/ns
	//    << " (nsec) --- local (x,y,z) [cm] " 
	//    << localPos.x()/cm << ", " 
	//    << localPos.y()/cm << ", " 
	//    << localPos.z()/cm << ", " 
	//    << G4endl;
}



/////// --------------------------------------------------------------------



