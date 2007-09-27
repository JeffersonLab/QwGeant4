//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMagnet_MiniTorusCoilParameterisation.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:12:41 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:12:41 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimMagnet_MiniTorusCoilParameterisation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMagnet_MiniTorusCoilParameterisation::QweakSimMagnet_MiniTorusCoilParameterisation( G4double RadialDistanceToBeamLine )
{
   myRadialDistanceToBeamLine  =  RadialDistanceToBeamLine;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMagnet_MiniTorusCoilParameterisation::~QweakSimMagnet_MiniTorusCoilParameterisation()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMagnet_MiniTorusCoilParameterisation::ComputeTransformation (const G4int copyNo, G4VPhysicalVolume* physVol) const
{

  G4double Angle_Coil = ((45.0*copyNo) + 22.5) *degree;

  // confusion: angle def is different to ShieldingWall OctantCuts
  G4double myPositionInX = sin(Angle_Coil)*myRadialDistanceToBeamLine;
  G4double myPositionInY = cos(Angle_Coil)*myRadialDistanceToBeamLine;
  G4double myPositionInZ = 0.0*cm;

  G4ThreeVector origin(myPositionInX , myPositionInY, myPositionInZ);

  G4RotationMatrix* Rotation_Coil = new G4RotationMatrix();  

  Rotation_Coil->rotateY(90.0*degree);
  physVol->SetRotation(Rotation_Coil);

  physVol->SetTranslation(origin);

  Rotation_Coil->rotateX(Angle_Coil);
  physVol->SetRotation(Rotation_Coil);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagnet_MiniTorusCoilParameterisation.cc,v $
//      Revision 1.2  2005/12/27 19:12:41  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
