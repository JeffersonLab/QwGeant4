
//=============================================================================
//
//  File     QweakSimPionWall.cc
//  Revision 1.0
//  Date     07/05/2012
//  Author   James Dowd
//
//=============================================================================

//  Pion Wall z=?

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimPionWall.hh"

static const G4double inch = 2.54*cm;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimPionWall::QweakSimPionWall()
{
  PionWall_Logical  = NULL;
  PionWall_Physical = NULL;
  PionWall_Solid    = NULL;
  PionWall_Material = NULL;
  PionWall_VisAtt   = NULL;
  
  PionWall_Length_X        = 22*4*inch;  //  22 bricks wide  (8" x 4" x 2")
  PionWall_Length_Y        =   10*inch;  //  8" tall brick + another on its side
  PionWall_Length_Z        =    4*inch;  //  4" thick (2 bricks)

  MD7_CenterYPosition = -335.17*cm;
  MD7_CenterZPosition = 577.88*cm;
  
  PionWall_CenterXPosition = 0*cm;
  PionWall_CenterYPosition = MD7_CenterYPosition + 1*inch;  //  MD7 center Y position + 1"
  PionWall_CenterZPosition = MD7_CenterZPosition - 6.5*cm - 1*inch - 0.5*PionWall_Length_Z;
  //                      MDZpos - MDPbCenter - 0.5*MDPbThick - 0.5*PionWallThickness
  //  This position places the PionWall flush with the Pb PMT shielding of MD7
  //  in both Z and Y. (Flush along bottom of Pb PMT shielding)
  
  
  PionWall_Messenger = new QweakSimPionWallMessenger(this);
  
 // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimPionWall::~QweakSimPionWall()
{
  if (pMaterial)  delete pMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::ConstructPionWall(G4VPhysicalVolume* MotherVolume)
{
//-----------------------------------------------------------------------------
//!  Creates the Pion Wall
/*
  \param G4VPhysicalVolume* - The physical volume in which the pion wall will be placed
*/
//-----------------------------------------------------------------------------

  //  assign material
  PionWall_Material = pMaterial->GetMaterial("Lead");
  
  G4ThreeVector positionPionWall;
  
  
  //  Construct pion wall volume
  PionWall_Solid = new G4Box("PionWall_Sol", 
                    PionWall_Length_X*0.5, PionWall_Length_Y*0.5, PionWall_Length_Z*0.5);
  
  //***************************************************************************
  //  Define pion wall logical and physical volumes
  
  PionWall_Logical = new G4LogicalVolume(PionWall_Solid, 
                                         PionWall_Material,
                                         "PionWall_Log",
                                         0,0,0);
  
  positionPionWall = G4ThreeVector(PionWall_CenterXPosition,
                                   PionWall_CenterYPosition,
                                   PionWall_CenterZPosition);
  
  PionWall_Physical = new G4PVPlacement(0,
                                        positionPionWall,
                                        "PionWall",
                                        PionWall_Logical,
                                        MotherVolume,
                                        false,
                                        0);
  //***************************************************************************
  
  //  Formating
  G4Color blue (0.,0.,1.);
  
  PionWall_VisAtt = new G4VisAttributes(blue);
  PionWall_VisAtt->SetVisibility(true);
  PionWall_Logical->SetVisAttributes(PionWall_VisAtt);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWallMaterial(G4String materialName)
{
  //  Sets pion wall material
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
  if (pttoMaterial)
    PionWall_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_CenterPositionInX(G4double xPos)
{
  //  Sets X position of the pion wall
  PionWall_CenterXPosition = xPos;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition,
                                                  PionWall_CenterYPosition,
                                                  PionWall_CenterZPosition));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_CenterPositionInY(G4double yPos)
{
  //  Sets Y position of the pion wall
  PionWall_CenterYPosition = yPos;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition,
                                                  PionWall_CenterYPosition,
                                                  PionWall_CenterZPosition));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_CenterPositionInZ(G4double zPos)
{
  //  Sets Z position of the pion wall
  PionWall_CenterZPosition = zPos;
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition,
                                                  PionWall_CenterYPosition,
                                                  PionWall_CenterZPosition));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimPionWall::SetPionWall_LengthInZ(G4double dim)
{
  // Sets thickness in Z of the Pion Wall and moves the Pion Wall to be flush with Pb MD7 PMT shielding blocks
  if (dim >0.){
    G4double oldDim = PionWall_Length_Z;
    PionWall_Length_Z = dim;
    PionWall_Solid->SetZHalfLength(0.5*PionWall_Length_Z);
    SetPionWall_CenterPositionInZ(PionWall_CenterZPosition + 0.5*oldDim - 0.5*dim);
  } 
  else 
    G4cout << "Pion Wall:  Invalid thickness value" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPionWall::SetPionWall_Material(G4String materialName)
{
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName); 
  PionWall_Logical->SetMaterial(pttoMaterial);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPionWall::SetEnabled()
{
  //  Enables the Pion Wall
  PionWall_VisAtt->SetVisibility(true);
  SetPionWall_Material(PionWall_Material->GetName());
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition,
                                                  PionWall_CenterYPosition,
                                                  PionWall_CenterZPosition));

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPionWall::SetDisabled()
{
  // Disables the Pion Wall by changing the material to air, 
  // moving the wall 5m into the floor and hiding it.
  PionWall_VisAtt->SetVisibility(true);
  SetPionWall_Material("Air");
  PionWall_Physical->SetTranslation(G4ThreeVector(PionWall_CenterXPosition,
                                                  PionWall_CenterYPosition,
                                                  PionWall_CenterZPosition + 400*cm));

}





