//=============================================================================
//
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
//
/**

   \file QweakSimBeamLine.cc
   $Revision: 1.2 $	
   $Date: 2011/10/19 12:44 $
   \author Peiqing Wang

*/
//=============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimBeamLine.hh"

// user classes
class QweakSimMaterial;
class QweakSimBeamLineMessenger;

// geant4 includes
#include "G4UserLimits.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimBeamLineMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimBeamLine::QweakSimBeamLine(QweakSimUserInformation *myUI)
{
    G4cout << G4endl << "###### Calling QweakSimBeamLine::QweakBeamLine() " << G4endl << G4endl;

    myUserInfo = myUI;

    BeamLineContainer_Logical      = NULL;
    BeamLineContainer_Physical     = NULL;
    BeamLineContainer_Material     = NULL;

    BeamPipe_Logical  = NULL;
    BeamPipe_Physical = NULL;
    BeamPipe_Material         = NULL;


    // definition of a mil = inch/1000
    // static const G4double mil = 0.001*2.54*cm;
    // static const G4double inch = 2.54*cm;

    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();

    BeamLineContainer_Material      = pMaterial->GetMaterial("Vacuum");
    BeamPipe_Material               = pMaterial->GetMaterial("Lead");

    // define geometry values

    beamlineMessenger = new QweakSimBeamLineMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimBeamLine::~QweakSimBeamLine()
{
    delete pMaterial;
    delete beamlineMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimBeamLine::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
    G4cout << G4endl << "###### Calling QweakSimBeamLine::ConstructComponent() " << G4endl << G4endl;


    // define BeamLine position

    G4ThreeVector positionBeamLine = G4ThreeVector(0,0,0);
    G4ThreeVector positionBeamPipe = G4ThreeVector(0,0,0);

    G4Tubs* BeamLineContainer_Solid    = new G4Tubs("BeamLineContainer_Sol",
            0, //RadiusMin
            32*cm, //5.0*cm, //RadiusMax, BeamlineCutoutDiameter = 8.3*cm
            870*cm, //length
            0, //StartingPhi,
            360*degree); //DeltaPhi

    BeamLineContainer_Logical  = new G4LogicalVolume(BeamLineContainer_Solid,
            BeamLineContainer_Material,
            "BeamLineContainer_Log",
            0,0,0);

    BeamLineContainer_Physical   = new G4PVPlacement(0,
            positionBeamLine,
            "BeamLineContainer",
            BeamLineContainer_Logical,
            MotherVolume,
            false,
            0);

//--------------------------------------
    // define beampipe solid volume
    G4cout << G4endl << "###### QweakSimBeamLine: Define BeamPipe_Solid " << G4endl << G4endl;

    G4Tubs* BeamPipe_Solid    = new G4Tubs("BeamPipe_Sol",
            3*cm,
            4*cm,
            10*cm,
            0,
            360*degree);

    BeamPipe_Logical  = new G4LogicalVolume(BeamPipe_Solid,
            BeamPipe_Material,
            "QweakBeamPipe_Log",
            0,0,0);

    BeamPipe_Physical   = new G4PVPlacement(0,
            positionBeamPipe,
            "QweakBeamPipe",
            BeamPipe_Logical,
            MotherVolume, // BeamLineContainer_Physical,
            false,
            0);

    // define R1 - GEM Region pipe
    G4double collimator_center = -422.0195*cm;
    G4Tubs* R1_Pipe_Solid    = new G4Tubs("R1_Pipe_Solid",
            2.0447*cm,   
	    2.413*cm,
            24.9174*cm,
            0,
            360*degree);

    G4LogicalVolume* R1_Pipe_Logical  = new G4LogicalVolume(R1_Pipe_Solid,
            BeamPipe_Material,
            "R1_Pipe_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center-115.4186*cm),
            "R1_Pipe",
            R1_Pipe_Logical,
            MotherVolume,
            false,
            0);
    
    // define R1 - GEM Region flange
    G4Tubs* R1_Flange_Solid    = new G4Tubs("R1_Flange_Solid",
            2.0447*cm,   
	    2.413*cm,
            24.9174*cm,
            0,
            360*degree);

    G4LogicalVolume* R1_Flange_Logical  = new G4LogicalVolume(R1_Flange_Solid,
            BeamPipe_Material,
            "R1_Flange_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center-139.636*cm),
            "R1_Flange",
            R1_Flange_Logical,
            MotherVolume,
            false,
            0);
    
    // define Downstream R1 - GEM Region pipe
    G4Tubs* DS_R1_Pipe_Solid    = new G4Tubs("DS_R1_Pipe_Solid",
            3.8862*cm,     
	    4.445*cm,
            63.45085*cm,
            0,
            360*degree);

    G4LogicalVolume* DS_R1_Pipe_Logical  = new G4LogicalVolume(DS_R1_Pipe_Solid,
            BeamPipe_Material,
            "DS_R1_Pipe_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center-27.15035*cm),
            "DS_R1_Pipe",
            DS_R1_Pipe_Logical,
            MotherVolume,
            false,
            0);
    
    // define Downstream R1 - GEM Region flange
    G4Tubs* DS_R1_Flange_Solid    = new G4Tubs("DS_R1_Flange_Solid",
            2.413*cm,       
	    4.445*cm,
            0.5588*cm,
            0,
            360*degree);

    G4LogicalVolume* DS_R1_Flange_Logical  = new G4LogicalVolume(DS_R1_Flange_Solid,
            BeamPipe_Material,
            "DS_R1_Flange_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center-90.0424*cm),
            "DS_R1_Flange",
            DS_R1_Flange_Logical,
            MotherVolume,
            false,
            0);
    
    // define Downstream R1 - GEM Region bellow
    G4Tubs* DS_R1_Bellow_Solid    = new G4Tubs("DS_R1_Bellow_Solid",
            4.445*cm,         
	    13.5*cm,
            7.5*cm,
            0,
            360*degree);

    G4LogicalVolume* DS_R1_Bellow_Logical  = new G4LogicalVolume(DS_R1_Bellow_Solid,
            BeamPipe_Material,
            "DS_R1_Bellow_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center-27.15035*cm),
            "DS_R1_Bellow",
            DS_R1_Bellow_Logical,
            MotherVolume,
            false,
            0);

    // define R2 - inside primary collimator pipe
    G4Tubs* R2_Pipe_Solid    = new G4Tubs("R2_Pipe_Solid",
            10.0711*cm,       
	    10.9479*cm,
            7.5*cm,
            0,
            360*degree);

    G4LogicalVolume* R2_Pipe_Logical  = new G4LogicalVolume(R2_Pipe_Solid,
            BeamPipe_Material,
            "R2_Pipe_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center+43.8005*cm),
            "R2_Pipe",
            R2_Pipe_Logical,
            MotherVolume,
            false,
            0);
    
    // define R2 - inside primary collimator flange
    G4Tubs* R2_Flange_Solid    = new G4Tubs("R2_Flange_Solid",
            4.445*cm,         
	    10.9479*cm,
            0.4384*cm,
            0,
            360*degree);

    G4LogicalVolume* R2_Flange_Logical  = new G4LogicalVolume(R2_Flange_Solid,
            BeamPipe_Material,
            "R2_Flange_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center+43.8005*cm-7.0616*cm),
            "R2_Flange",
            R2_Flange_Logical,
            MotherVolume,
            false,
            0);

    // define downstream R2 pipe
    G4Tubs* DS_R2_Pipe_Solid    = new G4Tubs("DS_R2_Pipe_Solid",
            10.0711*cm,     
	    10.9479*cm,
            49.43*cm,
            0,
            360*degree);

    G4LogicalVolume* DS_R2_Pipe_Logical  = new G4LogicalVolume(DS_R2_Pipe_Solid,
            BeamPipe_Material,
            "DS_R2_Pipe_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center+100.7305*cm),
            "DS_R2_Pipe",
            DS_R2_Pipe_Logical,
            MotherVolume,
            false,
            0);
 
    // define R2 - rotator pipe
    G4Tubs* R2_RotatorPipe_Solid    = new G4Tubs("R2_RotatorPipe_Solid",
            15.1613*cm,           
	    16.1925*cm,
            42.4307*cm,
            0,
            360*degree);

    G4LogicalVolume* R2_RotatorPipe_Logical  = new G4LogicalVolume(R2_RotatorPipe_Solid,
            BeamPipe_Material,
            "R2_RotatorPipe_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center+107.7298*cm),
            "R2_RotatorPipe",
            R2_RotatorPipe_Logical,
            MotherVolume,
            false,
            0);

    
    // define R3 - inside collimator pipe
    G4Tubs* R3_Pipe_Solid    = new G4Tubs("R3_Pipe_Solid",
            12.7381*cm,         
	    13.6525*cm,
            5.615*cm,
            0,
            360*degree);

    G4LogicalVolume* R3_Pipe_Logical  = new G4LogicalVolume(R3_Pipe_Solid,
            BeamPipe_Material,
            "R3_Pipe_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center+155.7755*cm),
            "R3_Pipe",
            R3_Pipe_Logical,
            MotherVolume,
            false,
            0);
    
    // define R3 - inside collimator flange
    G4Tubs* R3_Flange_Solid    = new G4Tubs("R3_Flange_Solid",
            10.9479*cm,           
	    13.6525*cm,
            0.4572*cm,
            0,
            360*degree);

    G4LogicalVolume* R3_Flange_Logical  = new G4LogicalVolume(R3_Flange_Solid,
            BeamPipe_Material,
            "R3_Flange_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,collimator_center+43.8005*cm-5.1578*cm),
            "R3_Flange",
            R3_Flange_Logical,
            MotherVolume,
            false,
            0);
    
    // define Downstream 18" pipe within lead box
    G4Tubs* DS_18inch_Pipe1_Solid    = new G4Tubs("DS_18inch_Pipe1_Solid",
            21.9075*cm,
	    22.86*cm,
            121.3125*cm,
            0,
            360*degree);

    G4LogicalVolume* DS_18inch_Pipe1_Logical  = new G4LogicalVolume(DS_18inch_Pipe1_Solid,
            BeamPipe_Material,
            "DS_18inch_Pipe1_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,501.3125*cm),
            "DS_18inch_Pipe1",
            DS_18inch_Pipe1_Logical,
            MotherVolume,
            false,
            0);
    
    // define Downstream 18" pipe after lead box
    G4Tubs* DS_18inch_Pipe2_Solid    = new G4Tubs("DS_18inch_Pipe2_Solid",
            21.9075*cm,
	    22.86*cm,
            7.568*cm,
            0,
            360*degree);

    G4LogicalVolume* DS_18inch_Pipe2_Logical  = new G4LogicalVolume(DS_18inch_Pipe2_Solid,
            BeamPipe_Material,
            "DS_18inch_Pipe2_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,630.193*cm),
            "DS_18inch_Pipe2",
            DS_18inch_Pipe2_Logical,
            MotherVolume,
            false,
            0);
    
    // define Downstream 24" pipe
    G4Tubs* DS_24inch_Pipe_Solid    = new G4Tubs("DS_24inch_Pipe_Solid",
            29.5275*cm,
	    30.48*cm,
            31.1195*cm,
            0,
            360*degree);

    G4LogicalVolume* DS_24inch_Pipe_Logical  = new G4LogicalVolume(DS_24inch_Pipe_Solid,
            BeamPipe_Material,
            "DS_24inch_Pipe_Log",
            0,0,0);

    new G4PVPlacement(0,
            G4ThreeVector(0,0,668.8805*cm),
            "DS_24inch_Pipe",
            DS_24inch_Pipe_Logical,
            MotherVolume,
            false,
            0);
    
//--------------------------------------

    G4cout << G4endl << "###### QweakSimBeamLine: Setting Attributes " << G4endl << G4endl;

    G4Colour  red   (1.,0.,0.);
    G4Colour  orange    ( 255/255., 127/255.,   0/255.);
    G4Colour  blue      (   0/255.,   0/255., 255/255.);
    G4Colour  magenta   ( 255/255.,   0/255., 255/255.);
    G4Colour  grey      ( 127/255., 127/255., 127/255.);
    G4Colour  lightblue   ( 139/255., 208/255., 255/255.);
    G4Colour  lightorange ( 255/255., 189/255., 165/255.);
    G4Colour  khaki3    ( 205/255., 198/255., 115/255.);
    G4Colour  brown     (178/255., 102/255., 26/255.);
    
    G4VisAttributes* BeamLineContainer_VisAtt = new G4VisAttributes(red);
    BeamLineContainer_VisAtt -> SetVisibility(false);
    //BeamLineContainer_VisAtt -> SetForceWireframe(true);
    BeamLineContainer_Logical -> SetVisAttributes(BeamLineContainer_VisAtt);


    G4VisAttributes* BeamPipe_VisAtt = new G4VisAttributes(red);
    BeamPipe_VisAtt -> SetVisibility(true);
    //BeamPipe_VisAtt -> SetForceWireframe(true);
    BeamPipe_Logical -> SetVisAttributes(BeamPipe_VisAtt);


    G4cout << G4endl << "###### Leaving QweakSimBeamLine::ConstructComponent() " << G4endl << G4endl;

} // end of  QweakSimBeamLine::ConstructComponent()

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimBeamLine::SetBeamLineMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing BeamLine Material: Looking up Material  " << G4endl;
        BeamPipe_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing BeamLine Material:  Now the BeamLine is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing BeamLine Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimBeamLine::DestroyComponent()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimBeamLine::SetBeamLineCenterPositionInZ(G4double zPos)
{
    G4cout << G4endl << "###### Calling QweakSimBeamLine::SetBeamLineCenterPositionInZ() " << G4endl << G4endl;

    beamline_ZPos = zPos;
    BeamLineContainer_Physical->SetTranslation(G4ThreeVector(0.,0., zPos));
}

G4double QweakSimBeamLine::GetBeamLineCenterPositionInZ()
{
    G4cout << G4endl << "###### Calling QweakSimBeamLine::GetBeamLineCenterPositionInZ() " << G4endl << G4endl;
    return beamline_ZPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

