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
            5.0*cm, //RadiusMax, BeamlineCutoutDiameter = 8.3*cm
            900*cm, //length
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
            900*cm,
            0,
            360*degree);

    // define BeamLine window logical volume (front, upstream)
    G4cout << G4endl << "###### QweakSimBeamLine: Define BeamPipe_Logical " << G4endl << G4endl;

    BeamPipe_Logical  = new G4LogicalVolume(BeamPipe_Solid,
            BeamPipe_Material,
            "QweakBeamPipe_Log",
            0,0,0);

    // define BeamPipe physical volume
    G4cout << G4endl << "###### QweakSimBeamLine: Define BeamPipe_Physical " << G4endl << G4endl;
    BeamPipe_Physical   = new G4PVPlacement(0,
            positionBeamPipe,
            "QweakBeamPipe",
            BeamPipe_Logical,
            BeamLineContainer_Physical, //MotherVolume,
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

