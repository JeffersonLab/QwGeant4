//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTriggerScintillator_DetectorHit.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:15:59 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:15:59 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTriggerScintillator_DetectorHit.hh"

// geant4 includes
#include "G4Circle.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4Allocator<QweakSimTriggerScintillator_DetectorHit> QweakSimTriggerScintillator_DetectorHitAllocator;

QweakSimTriggerScintillator_DetectorHit::QweakSimTriggerScintillator_DetectorHit()
{
  DetectorID  = -1;
  pLogV       = 0;
  time        = 0.;

  originVertexPosition            = G4ThreeVector(0.0,0.0,0.0);
  originVertexMomentumDirection   = G4ThreeVector(0.0,0.0,0.0);
  originVertexKineticEnergy       = 0.;
  originVertexTotalEnergy         = 0.;

  currentMomentumDirection        = G4ThreeVector(0.0,0.0,0.0);
  currentKineticEnergy            = 0.;
  currentTotalEnergy              = 0.;

  primaryQ2                       = 0.;
  crossSection                    = 0.;
  crossSectionWeight              = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator_DetectorHit::QweakSimTriggerScintillator_DetectorHit(G4int detector_id)
{

  DetectorID = detector_id;
  time       = 0.;
  pLogV      = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator_DetectorHit::~QweakSimTriggerScintillator_DetectorHit()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTriggerScintillator_DetectorHit::QweakSimTriggerScintillator_DetectorHit(const QweakSimTriggerScintillator_DetectorHit &right)
    : G4VHit() {

  DetectorID     = right.DetectorID;

  cellPos        = right.cellPos;
  cellRot        = right.cellRot;
  pLogV          = right.pLogV;

  worldPos       = right.worldPos;
  localPos       = right.localPos;
  worldMomentum  = right.worldMomentum;
  localMomentum  = right.localMomentum;
  time           = right.time;

  originVertexPosition          = right.originVertexPosition;
  originVertexMomentumDirection = right.originVertexMomentumDirection;
  originVertexKineticEnergy     = right.originVertexKineticEnergy;
  originVertexTotalEnergy       = right.originVertexTotalEnergy;

  currentMomentumDirection = right.currentMomentumDirection;
  currentKineticEnergy     = right.currentKineticEnergy;
  currentTotalEnergy       = right.currentTotalEnergy;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
const QweakSimTriggerScintillator_DetectorHit& QweakSimTriggerScintillator_DetectorHit::operator=(const QweakSimTriggerScintillator_DetectorHit &right)
{
  DetectorID     = right.DetectorID;

  cellPos        = right.cellPos;
  cellRot        = right.cellRot;
  pLogV          = right.pLogV;

  worldPos       = right.worldPos;
  localPos       = right.localPos;
  worldMomentum  = right.worldMomentum;
  localMomentum  = right.localMomentum;
  time           = right.time;

  originVertexPosition          = right.originVertexPosition;
  originVertexMomentumDirection = right.originVertexMomentumDirection;
  originVertexKineticEnergy     = right.originVertexKineticEnergy;
  originVertexTotalEnergy       = right.originVertexTotalEnergy;

  currentMomentumDirection = right.currentMomentumDirection;
  currentKineticEnergy     = right.currentKineticEnergy;
  currentTotalEnergy       = right.currentTotalEnergy;

  return *this;
}

int QweakSimTriggerScintillator_DetectorHit::operator==(const QweakSimTriggerScintillator_DetectorHit & ) const
{
  //return (this==&right) ? 1 : 0;

return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator_DetectorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    // draw small yellow balls for the impact point
    G4Circle circle(worldPos);
    circle.SetScreenSize(0.01);
    circle.SetFillStyle(G4Circle::filled);

    G4Colour colourHit(1.,1.,0.);  // yellow

    G4VisAttributes attribs(colourHit);
    circle.SetVisAttributes(attribs);

    pVVisManager->Draw(circle);

//     // draw/overlay a white drift cell for a hit
//     G4Transform3D trans(cellRot.inverse(),cellPos);
//     const G4VisAttributes* pVA = pLogV->GetVisAttributes();
//     if(pVA) attribs = *pVA;
//     G4Colour colourCell(1.,1.,1.);
//     attribs.SetColour(colourCell);
//     attribs.SetForceSolid(true);
//     attribs.SetVisibility(true);
//     pVVisManager->Draw(*pLogV,attribs,trans);

  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTriggerScintillator_DetectorHit::Print()
{
//   G4cout << " TriggerScintillator[" << DetectorID << "] : time " << time/ns
//          << " (nsec) --- local (x,y,z) [cm] " 
// 	 << localPos.x()/cm << ", " 
// 	 << localPos.y()/cm << ", " 
// 	 << localPos.z()/cm << ", " 
// 	 << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillator_DetectorHit.cc,v $
//      Revision 1.2  2005/12/27 19:15:59  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
