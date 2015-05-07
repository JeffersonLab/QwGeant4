/**
 
   \file QweakSimTungstenPlug.cc

   \author Wouter Deconinck

*/
//=============================================================================

#include "QweakSimTungstenPlug.hh"
#include "QweakSimTungstenPlug_DetectorSD.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTungstenPlug::QweakSimTungstenPlug()
{
  // W-Plug
  TungstenPlugLogical      = NULL;
  TungstenPlugPhysical     = NULL;

  // get access to material definition
  pMaterial = new QweakSimMaterial();
  pMaterial->DefineMaterials();

  // TungstenPlug Material
  TungstenPlug_Material = pMaterial->GetMaterial("G4_W");  // For now...I thought this was an alloy....
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTungstenPlug::~QweakSimTungstenPlug()
{
  if (pMaterial) delete pMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTungstenPlug::ConstructTungstenPlug(G4VPhysicalVolume* MotherVolume)
{
  // Dimensions of W-plug
  // Numbers found on drawings at https://qweak.jlab.org/doc-private/ShowDocument?docid=903
  G4double inch = 25.4*mm;
  
  G4double WPlugOD = 3.125*inch;			// Outer Diameter of Plug
  G4double WPlugID1 = 0.588*inch; 			// Front Face Inner Diameter
  G4double WPlugID2 = 0.691*inch;			// Cone Transition ending Inner Diameter
  G4double WPlugID3 = WPlugOD/2;			// Rear Face Inner Diameter

  G4double WPlugLength1 = 3.250*inch;			// Full Length of Conical Section (Upstream end)
  G4double WPlugLength2 = 5.000*inch;			// Full Length of Cylindrical Section
  
  G4double FrontSectionZLocation = -579.2895*cm;	// Global Z position of the center of the conical section.

  // Define Upstream W-plug
  G4Cons* TungstenPlug_US_Solid = new G4Cons("TungstenPlug_Solid_US",
				      WPlugID1/2.0,
				      WPlugOD/2.0,
				      WPlugID2/2.0,
				      WPlugOD/2.0,  
				      WPlugLength1/2.0,
				      0,
				      360*degree);
  // Downstream W-plug  
  G4Tubs* TungstenPlug_DS_Solid = new G4Tubs("TungstenPlug_Solid_DS",
				      WPlugID3/2.0,
				      WPlugOD/2.0,
				      WPlugLength2/2.0,
				      0,
				      360*degree);
  // Add them together end on end
  G4ThreeVector unionTranslation( 0.0, 0.0, WPlugLength1/2.0 + WPlugLength2/2.0 );
  G4UnionSolid* TungstenPlugSolid = new G4UnionSolid(
					"TungstenPlugSolid",
					TungstenPlug_US_Solid,
					TungstenPlug_DS_Solid,
					0,
					unionTranslation);
  
  TungstenPlugLogical = new G4LogicalVolume(TungstenPlugSolid,
			    TungstenPlug_Material,
			    "TungstenPlugLogical");
  
  TungstenPlugPhysical = new G4PVPlacement(0,   
			     G4ThreeVector(0.0,0.0,FrontSectionZLocation),   // plug position
			     "TungstenPlugPhysical",
			     TungstenPlugLogical,
			     MotherVolume,
			     false,
			     0,
			     pSurfChk);

  ////////////////////////////////////
  // Define Visulization Attributes //
  ////////////////////////////////////

  G4Colour red(1.,0.,0.);
  G4VisAttributes* TungstenPlug_VisAtt = new G4VisAttributes(red);
  TungstenPlug_VisAtt->SetVisibility(true);
  TungstenPlugLogical->SetVisAttributes(TungstenPlug_VisAtt);

  ////////////////////////////////////
  //   Define Sensitive Detectors   //
  ////////////////////////////////////

  G4SDManager* SDman = G4SDManager::GetSDMpointer();

  TungstenPlugSD = new QweakSimTungstenPlug_DetectorSD("TungstenPlugSD");
  SDman->AddNewDetector(TungstenPlugSD);
  TungstenPlugLogical->SetSensitiveDetector(TungstenPlugSD);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
