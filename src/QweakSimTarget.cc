//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTarget.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:15:13 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:15:13 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTarget.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTarget::QweakSimTarget()
{
G4cout << G4endl << "###### Calling QweakSimTarget::QweakTarget() " << G4endl << G4endl;

    TargetCell_Logical      = NULL;
    TargetCell_Physical     = NULL;
    TargetCell_Material     = NULL;
    TargetMaterial_Logical  = NULL;
    TargetMaterial_Physical = NULL;
    Target_Material         = NULL;


// definition of a mil = inch/1000
static const G4double mil = 0.001*2.54*cm;

 pMaterial = new QweakSimMaterial();
 pMaterial->DefineMaterials();

  // get target cell material
  TargetCell_Material = pMaterial->GetMaterial("Aluminum");  

  // get target material
  Target_Material = pMaterial->GetMaterial("H2Liquid");  


  // define target geometry values

  targetCellWindowThickness =  3.5*mil;  //  3.5*mil
  targetCellWallThickness   = 20.0*mil;  // 20.0*mil

  targetCellInnerLength     = 37.0*cm;
  targetCellOuterLength     = targetCellInnerLength + 2.0*targetCellWindowThickness;  // Full length of Target

  targetCellRadiusMin        =  0.0*cm;
  targetCellOuterRadiusMax   =  2.54*cm;
  targetCellInnerRadiusMax   = targetCellOuterRadiusMax - targetCellWallThickness;

  targetCellStartingPhi =  0.0*deg;
  targetCellDeltaPhi    = 360*deg;

  targetCellZPos        = -650.0*cm;

  targetMessenger = new QweakSimTargetMessenger(this);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTarget::~QweakSimTarget()
{
  delete pMaterial;
  delete targetMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
G4cout << G4endl << "###### Calling QweakSimTarget::ConstructComponent() " << G4endl << G4endl;

  
  // define Target position
  G4ThreeVector positionTarget = G4ThreeVector(0,0,targetCellZPos);

  
  // define target solid volume
  G4cout << G4endl << "###### QweakSimTarget: Define TargetCell_Solid " << G4endl << G4endl;
  
  G4Tubs* TargetCell_Solid    = new G4Tubs("QweakTargetCell_Sol",
				       targetCellRadiusMin,
				       targetCellOuterRadiusMax,
				   0.5*targetCellOuterLength,
				       targetCellStartingPhi,
				       targetCellDeltaPhi);
 
  // define Target logical volume
  G4cout << G4endl << "###### QweakSimTarget: Define TargetCell_Logical " << G4endl << G4endl;
  
  TargetCell_Logical  = new G4LogicalVolume(TargetCell_Solid,
					TargetCell_Material,
					"QweakTargetCell_Log",
					0,0,0);
  // define Target physical volume
  G4cout << G4endl << "###### QweakSimTarget: Define TargetCell_Physical " << G4endl << G4endl;
  TargetCell_Physical   = new G4PVPlacement(0, 
				       positionTarget, 
				       "QweakTargetCell", 
				       TargetCell_Logical,
				       MotherVolume, 
				       false, 
				       0);

//--------------------------------------


   // define target material solid volume
  G4cout << G4endl << "###### QweakSimTarget: Define TargetMaterial_Solid " << G4endl << G4endl;
  
  G4Tubs* TargetMaterial_Solid    = new G4Tubs("QweakTargetMaterial_Sol",
				       targetCellRadiusMin,
				       targetCellInnerRadiusMax,
				   0.5*targetCellInnerLength,
				       targetCellStartingPhi,
				       targetCellDeltaPhi);
 
  // define Target logical volume
  G4cout << G4endl << "###### QweakSimTarget: Define Target_Logical " << G4endl << G4endl;
  
  TargetMaterial_Logical  = new G4LogicalVolume(TargetMaterial_Solid,
					Target_Material,
					"QweakTargetMaterial_Log",
					0,0,0);
  // define Target material physical volume
  G4cout << G4endl << "###### QweakSimTarget: Define TargetMaterial_Physical " << G4endl << G4endl;
  TargetMaterial_Physical   = new G4PVPlacement(0, 
				       G4ThreeVector(0,0,0), 
				       "QweakTargetMaterial", 
				       TargetMaterial_Logical,
				       TargetCell_Physical, 
				       false, 
				       0);


//--------------------------------------

G4cout << G4endl << "###### QweakSimTarget: Setting Attributes " << G4endl << G4endl;

  G4Colour  blue  (0.,0.,1.);
  G4Colour  red   (1.,0.,0.);


  G4VisAttributes* TargetCell_VisAtt = new G4VisAttributes(blue);
  TargetCell_VisAtt -> SetVisibility(true);
  //TargetVisAtt -> SetForceWireframe(true);
  TargetCell_Logical -> SetVisAttributes(TargetCell_VisAtt); 


  G4VisAttributes* TargetMaterial_VisAtt = new G4VisAttributes(red);
  TargetMaterial_VisAtt -> SetVisibility(true);
  //TargetVisAtt -> SetForceWireframe(true);
  TargetMaterial_Logical -> SetVisAttributes(TargetMaterial_VisAtt); 


G4cout << G4endl << "###### Leaving QweakSimTarget::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimTarget::ConstructComponent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing Target Material: Looking up Material  " << G4endl; 
                TargetMaterial_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing Target Material:  Now the Target is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing Target Material failed" << G4endl; 
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetCellMaterial(G4String materialName)
{
  // search the material by its name 
  G4Material* pttoMaterial = G4Material::GetMaterial(materialName);  
  if (pttoMaterial)
     {
  G4cout << "==== Changing Target Cell Material: Looking up Material  " << G4endl; 
                TargetCell_Logical->SetMaterial(pttoMaterial);
  G4cout << "==== Changing Target Cell Material:  Now the Target Cell is made of " << materialName << G4endl; 
     }
  else {
      G4cerr << "==== ERROR: Changing Target Cell Material failed" << G4endl; 
  }

}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetCenterPositionInZ(G4double zPos)
{
G4cout << G4endl << "###### Calling QweakSimTarget::SetTargetCenterPositionInZ() " << G4endl << G4endl;

 TargetCell_Physical->SetTranslation(G4ThreeVector(0.,0., zPos));
 //targetZPos = zPos; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTarget.cc,v $
//      Revision 1.2  2005/12/27 19:15:13  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
