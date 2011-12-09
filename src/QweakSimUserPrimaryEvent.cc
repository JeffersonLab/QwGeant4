//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimUserPrimaryEvent.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:18:05 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//
// Structure of subtree withtin Root ntuple: 
//  Info saved of primary event
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#include "QweakSimUserPrimaryEvent.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

ClassImp(QweakSimUserPrimaryEvent)

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
  QweakSimUserPrimaryEvent::QweakSimUserPrimaryEvent()   
{
  Initialize();
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimUserPrimaryEvent::~QweakSimUserPrimaryEvent()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimUserPrimaryEvent::Initialize()
{
  TrackID                        = 0;
  GlobalTime                     = 0.0;

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
  Asymmetry                      = 0.0;

  PDGcode                        = 0;

  ReactionType                   = 1;   // assume elastic as default

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

