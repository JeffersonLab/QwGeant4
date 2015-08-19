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
  pMaterial = QweakSimMaterial::GetInstance();

  // TungstenPlug Material
  TungstenPlug_Material = pMaterial->GetMaterial("G4_W");  // For now...I thought this was an alloy....
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimTungstenPlug::~QweakSimTungstenPlug() { }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTungstenPlug::ConstructTungstenPlug(G4VPhysicalVolume* MotherVolume)
{
  // Dimensions of W-plug
  // Updated Numbers found on drawings provided by Greg Smith
  // Page 13 of 
  G4double inch = 25.4*mm;
  
  G4double WPlugOD = 3.125*inch;			// Outer Diameter of Plug
  G4double WPlugID1 = 0.508*inch; 			// Front Face Inner Diameter
  G4double WPlugID2 = 0.848*inch;			// Rear Face Inner Diameter
  G4double WPlugLength = 8.250*inch;			// Full Length of Conical Section (Upstream end)
  G4double ZLocation = -579.2895*cm+2.5*inch;	        // Global Z position of the center of the W Plug

  // Define Upstream W-plug
  G4Cons* TungstenPlugSolid = new G4Cons("TungstenPlugSolid",
				      WPlugID1/2.0,
				      WPlugOD/2.0,
				      WPlugID2/2.0,
				      WPlugOD/2.0,  
				      WPlugLength/2.0,
				      0,
				      360*degree);
  
  TungstenPlugLogical = new G4LogicalVolume(TungstenPlugSolid,
			    TungstenPlug_Material,
			    "TungstenPlugLogical");
  
  TungstenPlugPhysical = new G4PVPlacement(0,   
			     G4ThreeVector(0.0,0.0,ZLocation),		// plug position
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
