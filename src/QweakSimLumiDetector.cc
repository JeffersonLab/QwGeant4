/*

   \file QweakSimLumiDetector.cc
   \author Wade Duvall

*/

#include "QweakSimLumiDetector.hh"
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimLumi_DetectorSD.hh"
#include "QweakSimLumiMessenger.hh"


QweakSimLumiDetector::QweakSimLumiDetector(G4String tag)
{

    // Initialize pointers to objects
    LumiMessenger = NULL;
    Lumi_Rot      = NULL;
    Lumi_Solid    = NULL;
    Lumi_Logical  = NULL;
    Lumi_Physical = NULL;

    // Set the tag number in the class, 0 for USLumi, 1 for DSLumi
    Lumi_Tag      = tag;

    /* Geometries are for the detector in the 1 slot:
     * https://qweak.jlab.org/wiki/images/Qweak-Coordinate-Systems.png
     *
     * FIXME: These need to be double checked by me.
     */

    // Create lumi messenger
    LumiMessenger = new QweakSimLumiMessenger(this, Lumi_Tag);

    // Access to material definition
    pMaterial = QweakSimMaterial::GetInstance();

    // Get quartz for lumi bars
    QuartzBar = pMaterial->GetMaterial("Quartz");
}

QweakSimLumiDetector::~QweakSimLumiDetector() { }

void QweakSimLumiDetector::ConstructComponent(G4VPhysicalVolume* MotherVolume,
                                              G4double length_X, G4double length_Y,
                                              G4double length_Z, G4double rot, G4double pos_X,
                                              G4double pos_Y, G4double pos_Z)
{
    /* Lumi geometries */
    Lumi_Length_X = length_X;
    Lumi_Length_Y = length_Y;
    Lumi_Length_Z = length_Z;

    // Lumi positions
    Lumi_Position_X = pos_X;
    Lumi_Position_Y = pos_Y;
    Lumi_Position_Z = pos_Z;

    // Create G4RotationMatrix and set rotation to zero for now
    Lumi_Rot = new G4RotationMatrix();
    Lumi_Rot->rotateX(rot);

    // Create G4ThreeVector for lumi positions
    Lumi_XYZ = G4ThreeVector(Lumi_Position_X, Lumi_Position_Y, Lumi_Position_Z);


    // Create upstream lumi bar
    Lumi_Solid = new G4Box("Lumi",              // Object name
                            Lumi_Length_X/2.0,  // X size
                            Lumi_Length_Y/2.0,  // Y size
                            Lumi_Length_Z/2.0); // Z Size

    // Place the lumi bar into a quartz lv
    Lumi_Logical = new G4LogicalVolume(Lumi_Solid,        // Solid placed in lv
                                         QuartzBar,       // Material for lv
                                         "Lumi_Logical",  // Name for object
                                         0,0,0);          // Set all options to zero for now

    // Create G4PVPlacement with lumi position
    Lumi_Physical = new G4PVPlacement(Lumi_Rot,
                                        Lumi_XYZ,
                                        "Lumi_Physical",
                                        Lumi_Logical,
                                        MotherVolume,
                                        false,
                                        0,
                                        pSurfChk);

    // Define sensitive detector
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    LumiSD = new QweakSimLumi_DetectorSD(G4String("/" + Lumi_Tag + "SD"), Lumi_Tag);
    SDman->AddNewDetector(LumiSD);
    Lumi_Logical->SetSensitiveDetector(LumiSD);

    //Make it pretty...
    G4Colour  red   (1.,0.,0.);
    G4Colour  blue  (0.,0.,1.);

    Lumi_VisAtt = new G4VisAttributes(red);
    Lumi_VisAtt->SetVisibility(true);
    Lumi_Logical->SetVisAttributes(Lumi_VisAtt);

}

void QweakSimLumiDetector::SetLumi_PositionInX(G4double xPos) {
    /* Set Lumi X position. */

    G4cout << "=== Calling QweakSimLumi::SetLumi_PositionInX() " << G4endl;
    Lumi_Position_X = xPos;                                                               
    Lumi_Physical->SetTranslation(G4ThreeVector(Lumi_Position_X,
                Lumi_Position_Y,
                Lumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetLumi_PositionInX() " << G4endl << G4endl;
}

void QweakSimLumiDetector::SetLumi_PositionInY(G4double yPos) {
    /* Set Lumi Y position. */

    G4cout << "=== Calling QweakSimLumi::SetLumi_PositionInY() " << G4endl;
    Lumi_Position_Y = yPos;                                                               
    Lumi_Physical->SetTranslation(G4ThreeVector(Lumi_Position_Y,
                Lumi_Position_Y,
                Lumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetLumi_PositionInY() " << G4endl << G4endl;
}

void QweakSimLumiDetector::SetLumi_PositionInZ(G4double zPos) {
    /* Set Lumi Z position. */

    G4cout << "=== Calling QweakSimLumi::SetLumi_PositionInZ() " << G4endl;
    Lumi_Position_Z = zPos;                                                               
    Lumi_Physical->SetTranslation(G4ThreeVector(Lumi_Position_Z,
                Lumi_Position_Y,
                Lumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetLumi_PositionInZ() " << G4endl << G4endl;
}

void QweakSimLumiDetector::SetLumi_Material(G4String materialName) {
    //--- Set Lumi Material
    
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    
    if (pttoMaterial)
    {
        G4cout << "=== Changing Lumi material: Look up material " << G4endl;
        Lumi_Logical -> SetMaterial(pttoMaterial);
        G4cout << "=== Changing Lumi material: Now the material is " << materialName << G4endl;
    }
    else 
        G4cerr << "=== Error: Changing Lumi material FAILED! " << G4endl << G4endl;

}

void QweakSimLumiDetector::SetLumi_Enabled() {
    //--- Enable the Lumi
    
    G4cout << "=== Calling QweakSimLumi::SetLumi_Enabled() " << G4endl;
    Lumi_VisAtt->SetVisibility(true);
    SetLumi_Material(QuartzBar -> GetName());
    Lumi_Physical->SetTranslation(G4ThreeVector(Lumi_Position_X,
                                                  Lumi_Position_Y, 
                                                  Lumi_Position_Z));
    G4cout << "=== Leaving QweakSimLumi::SetLumi_Enabled() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimLumiDetector::SetLumi_Disabled() {
    //--- Disable the Lumi
    
    G4cout << "=== Calling QweakSimLumi::SetLumi_Disabled() " << G4endl;
    Lumi_VisAtt -> SetVisibility(false);
    SetLumi_Material("Air");
    Lumi_Physical->SetTranslation(G4ThreeVector(Lumi_Position_X,
                                                  Lumi_Position_Y, 
                                                  Lumi_Position_Z + 400*cm));
    G4cout << "=== Leaving QweakSimLumi::SetLumi_Disabled() " << G4endl << G4endl;
}
