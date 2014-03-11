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

// Oct. 2011. Added in details of target geometry. -peiqing

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTarget.hh"

// user classes
class QweakSimMaterial;
class QweakSimTargetMessenger;

// geant4 includes
#include "G4UserLimits.hh"

// user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimTargetMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTarget::QweakSimTarget(QweakSimUserInformation *myUI)
{
    G4cout << G4endl << "###### Calling QweakSimTarget::QweakTarget() " << G4endl << G4endl;

    myUserInfo = myUI;

    TargetContainer_Logical      = NULL;
    TargetContainer_Physical     = NULL;
    TargetContainer_Material     = NULL;

    TargetCell_Logical      = NULL;
    TargetCell_Physical     = NULL;
    TargetCell_Material     = NULL;

    TargetEntranceWindow_Logical      = NULL;
    TargetEntranceWindow_Physical     = NULL;
    TargetEntranceWindow_Material     = NULL;

    TargetExitWindow_Logical      = NULL;
    TargetExitWindow_Physical     = NULL;
    TargetExitWindow_Material     = NULL;

    TargetExitWindowNipple_Logical  = NULL;
    TargetExitWindowNipple_Physical = NULL;
    TargetExitWindowNipple_Material = NULL;

    TargetMaterial_Logical  = NULL;
    TargetMaterial_Physical = NULL;
    Target_Material         = NULL;


    // definition of a mil = inch/1000
    static const G4double mil = 0.001*2.54*cm;
    static const G4double inch = 2.54*cm;

    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();

    TargetContainer_Material      = pMaterial->GetMaterial("Vacuum");
    TargetCell_Material           = pMaterial->GetMaterial("Aluminum");
    TargetEntranceWindow_Material = pMaterial->GetMaterial("Aluminum");
    TargetExitWindow_Material     = pMaterial->GetMaterial("Aluminum");
    TargetExitWindowNipple_Material = pMaterial->GetMaterial("Aluminum");
    Target_Material               = pMaterial->GetMaterial("H2Liquid");

    // define target geometry values

    targetCellEntranceWindowThickness =  3.8*mil; // from Katherine's A&S ELOG 893
    //    targetCellEntranceWindowThickness =  5*mil;
    //targetCellEntranceWindowThickness =  0.89*mm;
    targetCellExitWindowThickness =  20*mil;
    targetCellExitWindowNippleThickness =  5*mil;
    targetCellWallThickness   = 10.0*mil;

    targetCellExitWindowNippleRadius = 0.5*0.622*inch;

    //    targetCellInnerLength     = 34.346*cm;
    targetCellInnerLength     = myUserInfo->TargetLength;
    targetCellOuterLength     = targetCellInnerLength
                                + targetCellEntranceWindowThickness
                                + targetCellExitWindowThickness;  // Full length of Target

    targetCellFrontRadiusMin        =  0.0*cm;
    targetCellFrontOuterRadiusMax   =  0.5*2.730*inch;
    targetCellFrontInnerRadiusMax   = targetCellFrontOuterRadiusMax - targetCellWallThickness;

    targetCellBackRadiusMin        =  targetCellExitWindowNippleRadius;  //0.0*cm;
    targetCellBackOuterRadiusMax   =  0.5*7.5*inch;
    targetCellBackInnerRadiusMax   = targetCellBackOuterRadiusMax - targetCellWallThickness;

    targetCellStartingPhi =  0.0*deg;
    targetCellDeltaPhi    = 360*deg;

    //targetZPos        = -650.0*cm - 3.77*cm;
    targetZPos        = myUserInfo->TargetCenterPositionZ; //-650.0*cm;

    ScatteringChamberWindowRadius = 0.5*23.5*inch;
    ScatteringChamberWindowThickness = 35*mil;

    myUserInfo->TargetLength = targetCellInnerLength;
    myUserInfo->TargetEntranceWindowThickness = targetCellEntranceWindowThickness;
    myUserInfo->TargetExitWindowThickness = targetCellExitWindowThickness;
    myUserInfo->TargetExitWindowNippleThickness = targetCellExitWindowNippleThickness;

    // Thicknesses taken from 2012 target survey (https://qweak.jlab.org/elog/Target/21)
    myUserInfo->TargetThicknessUSALDummy1    = 0.8812*mm;
    myUserInfo->TargetThicknessUSALDummy2    = 1.7987*mm;
    myUserInfo->TargetThicknessUSALDummy4    = 3.6030*mm;
    myUserInfo->TargetThicknessDSALDummy2    = 1.8637*mm;
    myUserInfo->TargetThicknessDSALDummy4    = 3.6828*mm;
    myUserInfo->TargetThicknessDSALDummy8    = 7.1980*mm;
    myUserInfo->TargetThicknessUSCDummy      = 0.9973*mm;
    myUserInfo->TargetThicknessDSCDummy      = 3.1876*mm;

    G4double densityLH2 = 0.0713 /(cm*cm*cm);  // [g/cm^3] 
    G4double densityAL  = 2.80   /(cm*cm*cm);  // From 2012 target survey
    G4double densityUSC = 1.70   /(cm*cm*cm);  //
    G4double densityDSC = 2.205  /(cm*cm*cm); //

    // Molar masses taken from PDG:  
    // J. Beringer et al. (Particle Data Group), Phys. Rev. D86, 010001 (2012).
    G4double massLH2 = 1.00794;    // [g/mol]
    G4double massAL  = 26.9815386; // [g/mol]
    G4double massC   = 12.0107;    // [g/mol]

    myUserInfo->TargetLuminosityLH2 = CalculateLuminosity(massLH2, densityLH2, myUserInfo->TargetLength);
    myUserInfo->TargetLuminosityUSALWindow = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetEntranceWindowThickness);
    myUserInfo->TargetLuminosityDSALWindow = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetExitWindowNippleThickness);
    myUserInfo->TargetLuminosityUSALDummy1 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessUSALDummy1);
    myUserInfo->TargetLuminosityUSALDummy2 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessUSALDummy2);
    myUserInfo->TargetLuminosityUSALDummy4 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessUSALDummy4);
    myUserInfo->TargetLuminosityDSALDummy2 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessDSALDummy2);
    myUserInfo->TargetLuminosityDSALDummy4 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessDSALDummy4);
    myUserInfo->TargetLuminosityDSALDummy8 = CalculateLuminosity(massAL, densityAL, myUserInfo->TargetThicknessDSALDummy8);
    myUserInfo->TargetLuminosityUSCDummy = CalculateLuminosity(massC, densityUSC, myUserInfo->TargetThicknessUSCDummy);
    myUserInfo->TargetLuminosityDSCDummy = CalculateLuminosity(massC, densityDSC, myUserInfo->TargetThicknessDSCDummy);

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

    G4ThreeVector positionTarget = G4ThreeVector(0,0,0);
    G4ThreeVector positionTargetEntranceWindow = G4ThreeVector(0,0,-0.5*targetCellInnerLength - 0.5*targetCellEntranceWindowThickness);
    G4ThreeVector positionTargetExitWindow = G4ThreeVector(0,0, 0.5*targetCellInnerLength + 0.5*targetCellExitWindowThickness);
    G4ThreeVector positionScatteringChamberWindow = G4ThreeVector(0,0,0.5*targetCellInnerLength + 0.5*targetCellExitWindowThickness + 45.0*cm); // Peiqing: should be located at z=-583.41 cm

    G4Tubs* TargetContainer_Solid    = new G4Tubs("TargetContainer_Sol",
            0, //targetCellRadiusMin, jpan@nuclear.uwinnipeg.ca
            ScatteringChamberWindowRadius+0.1*cm,
            0.5*targetCellOuterLength+50.0*cm,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    TargetContainer_Logical  = new G4LogicalVolume(TargetContainer_Solid,
            TargetContainer_Material,
            "TargetContainer_Log",
            0,0,0);

    TargetContainer_Physical   = new G4PVPlacement(0,
            positionTarget,
            "TargetContainer",
            TargetContainer_Logical,
            MotherVolume,
            false,
            0,
            pSurfChk);


    // define target solid volume
    G4cout << G4endl << "###### QweakSimTarget: Define TargetCell_Solid " << G4endl << G4endl;
    G4Cons* TargetCell_Solid = new G4Cons("QweakTargetCell_Sol",
                                          targetCellFrontInnerRadiusMax+0.000001*cm,// G4double  pRmin1,
                                          targetCellFrontOuterRadiusMax, // G4double  pRmax1,
                                          targetCellBackInnerRadiusMax+0.000001*cm, //G4double  pRmin2,
                                          targetCellBackOuterRadiusMax, //G4double  pRmax2,
                                          0.5*targetCellOuterLength,    //G4double  pDz,
                                          targetCellStartingPhi, //G4double  pSPhi,
                                          targetCellDeltaPhi);   //G4double  pDPhi)

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
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);

//--------------------------------------
    // define target window solid volume (front, upstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetEntranceWindow_Solid " << G4endl << G4endl;

    G4Tubs* TargetEntranceWindow_Solid    = new G4Tubs("TargetEntranceWindow_Sol",
            targetCellFrontRadiusMin,
            targetCellFrontInnerRadiusMax,
            0.5*targetCellEntranceWindowThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define Target window logical volume (front, upstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetEntranceWindow_Logical " << G4endl << G4endl;

    TargetEntranceWindow_Logical  = new G4LogicalVolume(TargetEntranceWindow_Solid,
            TargetEntranceWindow_Material,
            "QweakTargetEntranceWindow_Log",
            0,0,0);

    // define Target window physical volume (front, upstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetEntranceWindow_Physical " << G4endl << G4endl;
    TargetEntranceWindow_Physical   = new G4PVPlacement(0,
            positionTargetEntranceWindow,
            "QweakTargetEntranceWindow",
            TargetEntranceWindow_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);

//--------------------------------------

    // define target window solid volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindow_Solid " << G4endl << G4endl;

    G4Tubs* TargetExitWindow_Solid    = new G4Tubs("TargetExitWindow_Sol",
            targetCellBackRadiusMin,
            targetCellBackInnerRadiusMax,
            0.5*targetCellExitWindowThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define Target window logical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindow_Logical " << G4endl << G4endl;

    TargetExitWindow_Logical  = new G4LogicalVolume(TargetExitWindow_Solid,
            TargetExitWindow_Material,
            "QweakTargetExitWindow_Log",
            0,0,0);

    // define Target window physical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindow_Physical " << G4endl << G4endl;
    TargetExitWindow_Physical   = new G4PVPlacement(0,
            positionTargetExitWindow,
            "QweakTargetExitWindow",
            TargetExitWindow_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);

    
    // define target window Nipple solid volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindowNipple_Solid " << G4endl << G4endl;

    G4Tubs* TargetExitWindowNipple_Solid    = new G4Tubs("TargetExitWindowNipple_Sol",
            0.,
            targetCellExitWindowNippleRadius-0.00001*mm,
            0.5*targetCellExitWindowNippleThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define Target window logical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindowNipple_Logical " << G4endl << G4endl;

    TargetExitWindowNipple_Logical  = new G4LogicalVolume(TargetExitWindowNipple_Solid,
            TargetExitWindowNipple_Material,
            "QweakTargetExitWindowNipple_Log",
            0,0,0);

    // define Target window nipple physical volume (back, downstream)
    G4cout << G4endl << "###### QweakSimTarget: Define TargetExitWindowNipple_Physical " << G4endl << G4endl;
    TargetExitWindowNipple_Physical   = new G4PVPlacement(0,
            positionTargetExitWindow,
            "QweakTargetExitWindowNipple_Physical",
            TargetExitWindowNipple_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);

    //*********************** Define Target scattering chamber Vacuum Window ************************

    G4Tubs* ScatteringChamberWindow_Solid    = new G4Tubs("ScatteringChamberWindow_Sol",
            0.,
            ScatteringChamberWindowRadius,
            0.5*ScatteringChamberWindowThickness,
            targetCellStartingPhi,
            targetCellDeltaPhi);

    // define ScatteringChamberWindow logical volume
    G4cout << G4endl << "###### QweakSimTarget: Define ScatteringChamberWindow_Logical " << G4endl << G4endl;

    ScatteringChamberWindow_Logical  = new G4LogicalVolume(ScatteringChamberWindow_Solid,
            TargetCell_Material,
            "ScatteringChamberWindow_Log",
            0,0,0);

    // define Target vacuum window physical volume
    G4cout << G4endl << "###### QweakSimTarget: Define ScatteringChamberWindow_Physical " << G4endl << G4endl;
    ScatteringChamberWindow_Physical   = new G4PVPlacement(0,
            positionScatteringChamberWindow,
            "ScatteringChamberWindow",
            ScatteringChamberWindow_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);

//*************************End of Target Vacuum Window *****************************

// Set max step size for a certain volume, see
//         http://geant4.web.cern.ch/geant4/G4UsersDocuments/UsersGuides/
//         ForApplicationDeveloper/html/TrackingAndPhysics/thresholdVScut.html

    G4double MaxStepInEntranceWindow = 0.1*targetCellEntranceWindowThickness;
    G4double MaxStepInExitWindow = 0.1*targetCellExitWindowThickness;
    TargetEntranceWindow_Logical->SetUserLimits(new G4UserLimits(MaxStepInEntranceWindow));
    TargetExitWindow_Logical->SetUserLimits(new G4UserLimits(MaxStepInExitWindow));

//--------------------------------------

    // define target material solid volume
    G4cout << G4endl << "###### QweakSimTarget: Define TargetMaterial_Solid " << G4endl << G4endl;

//   G4Tubs* TargetMaterial_Solid    = new G4Tubs("QweakTargetMaterial_Sol",
// 				       targetCellFrontRadiusMin,
// 				       targetCellFrontInnerRadiusMax,
// 				   0.5*targetCellInnerLength,
// 				       targetCellStartingPhi,
// 				       targetCellDeltaPhi);

    G4Cons* TargetMaterial_Solid = new G4Cons("QweakTargetMaterial_Sol",
            0., //targetCellFrontRadiusMin, // G4double  pRmin1,
            targetCellFrontInnerRadiusMax, // G4double  pRmax1,
            0., //targetCellBackRadiusMin, //G4double  pRmin2,
            targetCellBackInnerRadiusMax, //G4double  pRmax2,
            0.5*targetCellInnerLength,    //G4double  pDz,
            targetCellStartingPhi, //G4double  pSPhi,
            targetCellDeltaPhi);   //G4double  pDPhi)


    // define Target logical volume
    G4cout << G4endl << "###### QweakSimTarget: Define Target_Logical " << G4endl << G4endl;

    TargetMaterial_Logical  = new G4LogicalVolume(TargetMaterial_Solid,
            Target_Material,
            "QweakTargetMaterial_Log",
            0,0,0);

    // set max step size for LH2 target
    G4double MaxStepInTarget = 0.05*targetCellInnerLength; //step size < 20% of target length
    TargetMaterial_Logical->SetUserLimits(new G4UserLimits(MaxStepInTarget));

    // define Target material physical volume
    G4cout << G4endl << "###### QweakSimTarget: Define TargetMaterial_Physical " << G4endl << G4endl;
    TargetMaterial_Physical   = new G4PVPlacement(0,
            positionTarget,
            "QweakTargetMaterial",
            TargetMaterial_Logical,
            TargetContainer_Physical, //MotherVolume,
            false,
            0,
            pSurfChk);


//--------------------------------------

    G4cout << G4endl << "###### QweakSimTarget: Setting Attributes " << G4endl << G4endl;

    G4Colour  blue  (0.,0.,1.);
    G4Colour  red   (1.,0.,0.);

    G4VisAttributes* TargetContainer_VisAtt = new G4VisAttributes(red);
    TargetContainer_VisAtt -> SetVisibility(false);
    //TargetContainer_VisAtt -> SetForceWireframe(true);
    TargetContainer_Logical -> SetVisAttributes(TargetContainer_VisAtt);

    G4VisAttributes* TargetCell_VisAtt = new G4VisAttributes(blue);
    TargetCell_VisAtt -> SetVisibility(true);
    //TargetCell_VisAtt -> SetForceWireframe(true);
    TargetCell_Logical -> SetVisAttributes(TargetCell_VisAtt);

    G4VisAttributes* TargetWindow_VisAtt = new G4VisAttributes(blue);
    TargetWindow_VisAtt -> SetVisibility(true);
    //TargetWindow_VisAtt -> SetForceWireframe(true);
    TargetEntranceWindow_Logical -> SetVisAttributes(TargetWindow_VisAtt);
    TargetExitWindow_Logical -> SetVisAttributes(TargetWindow_VisAtt);

    G4VisAttributes* ScatteringChamberWindow_VisAtt = new G4VisAttributes(red);
    ScatteringChamberWindow_VisAtt -> SetVisibility(true);
    //ScatteringChamberWindow_VisAtt -> SetForceWireframe(true);
    ScatteringChamberWindow_Logical -> SetVisAttributes(ScatteringChamberWindow_VisAtt);

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

void QweakSimTarget::SetTargetEntranceWindowMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Entrance Window Material: Looking up Material  " << G4endl;
        TargetEntranceWindow_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Entrance Window Material:  Now the Target Entrance Window is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Entrance Window Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetExitWindowMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Exit Window Material: Looking up Material  " << G4endl;
        TargetExitWindow_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Exit Window Material:  Now the Target Exit Window is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Exit Window Material failed" << G4endl;
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTarget::SetTargetExitWindowNippleMaterial(G4String materialName)
{
    // search the material by its name
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    if (pttoMaterial)
    {
        G4cout << "==== Changing Target Exit Window Nipple Material: Looking up Material  " << G4endl;
        TargetExitWindowNipple_Logical->SetMaterial(pttoMaterial);
        G4cout << "==== Changing Target Exit Window Nipple Material:  Now the Target Exit Window Nipple is made of " << materialName << G4endl;
    }
    else {
        G4cerr << "==== ERROR: Changing Target Exit Window Nipple Material failed" << G4endl;
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

    targetZPos = zPos;
    myUserInfo->TargetCenterPositionZ = zPos;
//TargetCell_Physical->SetTranslation(G4ThreeVector(0.,0., zPos));
    TargetContainer_Physical->SetTranslation(G4ThreeVector(0.,0., zPos));
}

G4double QweakSimTarget::GetTargetCenterPositionInZ()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::GetTargetCenterPositionInZ() " << G4endl << G4endl;
    return targetZPos;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimTarget::SetTargetLength(G4double len)
{
    G4cout << G4endl << "###### Calling QweakSimTarget::SetTargetLength() " << G4endl << G4endl;

    targetLen = len;
    myUserInfo->TargetLength = len;
}

G4double QweakSimTarget::GetTargetLength()
{
    G4cout << G4endl << "###### Calling QweakSimTarget::GetTargetLength() " << G4endl << G4endl;
    return targetLen;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4double QweakSimTarget::CalculateLuminosity(G4double mass, G4double density, G4double length)
{
  G4double Lum = 0.0;            // Luminosity
  G4double N_b = 6.241e12;       // [Hz/uA] # of particles in the beam (from definition of ampere)
  G4double N_A = 6.02214129e23;  // Avagadro's number

  Lum = N_b*length*density*N_A/mass;  //  units [Hz/(uA*mm^2)]

  Lum *= 1e-31;  //  Conversion from [Hz/(uA*mm^2)] -> [kHz/(uA*ub)]

  return Lum;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
