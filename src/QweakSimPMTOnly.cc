
// QweakSimPMTOnly.cc
// Marty McHugh 
// 2013-06-11

/////// --------------------------------------------------------------------

#include "QweakSimPMTOnly.hh"

//--- geant4 includes
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"

//--- user includes
#include "QweakSimSolids.hh"
#include "QweakSimMaterial.hh"
#include "QweakSimPMTOnlyMessenger.hh"
#include "QweakSimPMTOnly_DetectorSD.hh"
#include "QweakSimPMTOnly_PMTSD.hh"
#include "QweakSimUserInformation.hh"

/////// --------------------------------------------------------------------

QweakSimPMTOnly::QweakSimPMTOnly(QweakSimUserInformation* userInfo)
{
    //--- Initialize Pointers
    myUserInfo		= userInfo;

    PMTOnlySD         	= NULL;
    PMTOnly_PMTSD	= NULL;
	
    PMTOnlyMessenger   	= NULL;
	
    pMaterial           = NULL;
    
    Mother_Solid 	= NULL;
    Mother_Logical	= NULL;
    Mother_Physical	= NULL;
    Mother_Material 	= NULL;
    Mother_VisAtt	= NULL;

    PMTOnly_Solid     	= NULL;
    PMTOnly_Logical   	= NULL;
    PMTOnly_Physical  	= NULL;	
    PMTOnly_Material  	= NULL;
    PMTOnly_VisAtt    	= NULL;
    
    PMTQuartzOpticalFilm_Solid 		= NULL;
    PMTQuartzOpticalFilm_Logical	= NULL;
    PMTQuartzOpticalFilm_Physical	= NULL;
    PMTQuartzOpticalFilm_Material	= NULL;
    
    PMTEntranceWindow_Solid	= NULL;
    PMTEntranceWindow_Logical	= NULL;
    PMTEntranceWindow_Physical	= NULL;
    PMTEntranceWindow_Material	= NULL;
    
    Cathode_Solid	= NULL;
    Cathode_Logical	= NULL;
    Cathode_Physical	= NULL;
    Cathode_Material	= NULL;
    
    //--- Set Initial Values
    MD5_CenterPosition_X = -335.17*cm;
    MD5_CenterPosition_Y =     0.0*cm;
    MD5_CenterPosition_Z =  577.88*cm;

    Mother_FullLength_X = 20.00*cm;
    Mother_FullLength_Y = 20.00*cm;
    Mother_FullLength_Z = 20.00*cm;

    Mother_CenterPosition_X =  -320.0*cm;
    Mother_CenterPosition_Y =  -50.00*cm;
    Mother_CenterPosition_Z =  775.00*cm;

    PMTOnly_FullLength_X = 18.00*cm;
    PMTOnly_FullLength_Y = 18.00*cm;
    PMTOnly_FullLength_Z = 1.25*cm;
    
    PMTOnly_CenterPosition_X =  0.00*cm;
    PMTOnly_CenterPosition_Y =  0.00*cm;
    PMTOnly_CenterPosition_Z =  0.00*cm;

    Mother_TiltAngle_X =  0.00*degree;
    Mother_TiltAngle_Y =  0.00*degree;
    Mother_TiltAngle_Z =  0.00*degree;
    
    PMTQuartzOpticalFilm_Diameter = 12.70*cm;
    PMTQuartzOpticalFilm_Thickness = 0.10*mm;

    PMTEntranceWindow_Diameter = 12.70*cm;
    PMTEntranceWindow_Thickness = 1.00*mm;

    G4double ReductionInPhotocathodeDiameter = 5*mm;
    
    Cathode_Thickness   = 1.0*mm;
    Cathode_Diameter    = PMTEntranceWindow_Diameter - ReductionInPhotocathodeDiameter; 

    PMTOnlyMessenger = new QweakSimPMTOnlyMessenger(this);
	
    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();  
	
}


/////// --------------------------------------------------------------------

QweakSimPMTOnly::~QweakSimPMTOnly()
{
    /* --- Delete Pointers	
    if (PMTOnlySD)		delete PMTOnlySD;

    if (pMaterial)		delete pMaterial;
    if (PMTOnlyMessenger)	delete PMTOnlyMessenger;
    
    if (Mother_Solid)		delete Mother_Solid; 		
    if (Mother_Logical)		delete Mother_Logical;
    if (Mother_Physical)	delete Mother_Physical;
    if (Mother_Material)	delete Mother_Material;
    if (Mother_VisAtt)		delete Mother_VisAtt;
    
    if (PMTOnly_VisAtt)		delete PMTOnly_VisAtt;
    if (PMTOnly_Material)	delete PMTOnly_Material;	
    if (PMTOnly_Physical)	delete PMTOnly_Physical;
    if (PMTOnly_Logical)	delete PMTOnly_Logical;
    if (PMTOnly_Solid)		delete PMTOnly_Solid;
    
    if (PMTQuartzOpticalFilm_Material)	delete PMTQuartzOpticalFilm_Material;	
    if (PMTQuartzOpticalFilm_Physical)	delete PMTQuartzOpticalFilm_Physical;
    if (PMTQuartzOpticalFilm_Logical)	delete PMTQuartzOpticalFilm_Logical;
    if (PMTQuartzOpticalFilm_Solid)	delete PMTQuartzOpticalFilm_Solid;
    
    if (PMTEntranceWindow_Material)	delete PMTEntranceWindow_Material;	
    if (PMTEntranceWindow_Physical)	delete PMTEntranceWindow_Physical;
    if (PMTEntranceWindow_Logical)	delete PMTEntranceWindow_Logical;
    if (PMTEntranceWindow_Solid)	delete PMTEntranceWindow_Solid;
    
    if (Cathode_Material)	delete Cathode_Material;	
    if (Cathode_Physical)	delete Cathode_Physical;
    if (Cathode_Logical)	delete Cathode_Logical;
    if (Cathode_Solid)		delete Cathode_Solid;
    */	
}


/////// --------------------------------------------------------------------

void QweakSimPMTOnly::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
	
    //--- Materials
    Mother_Material = pMaterial->GetMaterial("Air");    
    PMTOnly_Material = pMaterial->GetMaterial("Scintillator");
    PMTQuartzOpticalFilm_Material = pMaterial->GetMaterial("SiElast_Glue");
    PMTEntranceWindow_Material = pMaterial->GetMaterial("LimeGlass");
    Cathode_Material = pMaterial->GetMaterial("Photocathode");

    //--- Define Mother Solid Volume;
    Mother_Solid = new G4Box("Mother_Solid",
    				0.5*Mother_FullLength_X,
    				0.5*Mother_FullLength_Y,
    				0.5*Mother_FullLength_Z);
    				
    //--- Define Mother Logical Volume;
    Mother_Logical = new G4LogicalVolume(Mother_Solid,
                                            Mother_Material,
                                            "Mother_Logical",
                                             0,0,0);
    
    //--- Define Mother Placement and Physical Volume
    Mother_CenterPosition = G4ThreeVector(Mother_CenterPosition_X,
                                             Mother_CenterPosition_Y,
                                             Mother_CenterPosition_Z);
    Mother_RotationMatrix = new G4RotationMatrix();
    Mother_RotationMatrix -> rotateX(Mother_TiltAngle_X);
	
    Mother_Physical = new G4PVPlacement(Mother_RotationMatrix,
                                           Mother_CenterPosition,
                                           "Mother_Phyical",
                                           Mother_Logical,
                                           MotherVolume,
                                           false,
                                           0);
	
    //--- Define PMTOnly Solid Volume	
    PMTOnly_Solid = new G4Box("PMTOnly_Solid",
                              0.5*PMTOnly_FullLength_X,     // X Length
                              0.5*PMTOnly_FullLength_Y,     // Y Length
                              0.5*PMTOnly_FullLength_Z);    // Z Length
	
    //--- Define PMTOnly Logical Volume	
    PMTOnly_Logical = new G4LogicalVolume(PMTOnly_Solid,
                                          PMTOnly_Material,
                                          "PMTOnly_Logical",
                                          0,0,0);
	
    //--- Define PMTOnly Physical Volume
    PMTOnly_CenterPosition = G4ThreeVector(PMTOnly_CenterPosition_X,
                                           PMTOnly_CenterPosition_Y,
                                           PMTOnly_CenterPosition_Z);

    PMTOnly_Physical = new G4PVPlacement(0,
                                         PMTOnly_CenterPosition,
                                         "PMTOnly_Phyical",
                                         PMTOnly_Logical,
                                         Mother_Physical,
                                         false,
                                         0);

    
    //--- Define PMTQuartzOpticalFilm Solid
    PMTQuartzOpticalFilm_Solid = new G4Tubs("PMTQuartzOpticalFilm_Solid", 
                                            0.00*cm,
                                            0.5*PMTQuartzOpticalFilm_Diameter,
                                            0.5*PMTQuartzOpticalFilm_Thickness,
                                            0.0*degree,360.0*degree);

    //--- Define PMTQuartzOpticaFilm Logical
    PMTQuartzOpticalFilm_Logical = new G4LogicalVolume(PMTQuartzOpticalFilm_Solid,
    						       PMTQuartzOpticalFilm_Material,
    						       "PMTQuartzOpticalFilm_Logical");
    
    //--- Define PMTQuartzOpticalFilm Physical Volume & Placement.
    G4double PMTQuartzOpticalFilm_Z = 0.5*(PMTOnly_FullLength_Z + PMTQuartzOpticalFilm_Thickness);
    G4ThreeVector PMTQuartzOpticalFilm_Position(0.0, 0.0, PMTQuartzOpticalFilm_Z); 
    
    PMTQuartzOpticalFilm_Physical = new G4PVPlacement(0,
    						      PMTQuartzOpticalFilm_Position,
    						      "PMTQuartzOpticalFilm_Physical",
    						      PMTQuartzOpticalFilm_Logical,    						   
    						      Mother_Physical,
    						      false, 
    						      0);

    //--- Define PMTEntranceWindow Solid
    PMTEntranceWindow_Solid = new G4Tubs("PMTEntranceWindow_Solid",
    					 0.00*cm,
    					 0.5*PMTEntranceWindow_Diameter,
    					 0.5*PMTEntranceWindow_Thickness,
    					 0.0*degree, 360.0*degree);

    //--- Define PMTEntranceWindow Logical
    PMTEntranceWindow_Logical = new G4LogicalVolume(PMTEntranceWindow_Solid,
    						    PMTEntranceWindow_Material,
    						    "PMTEntranceWindow_Logical");

    //--- Define PMTEntranceWindow Physical Volume & Placement
    G4double PMTEntranceWindow_Z = PMTQuartzOpticalFilm_Z + 0.5*(PMTQuartzOpticalFilm_Thickness + PMTEntranceWindow_Thickness);
    G4ThreeVector PMTEntranceWindow_Position(0.0, 0.0, PMTEntranceWindow_Z);

    PMTEntranceWindow_Physical = new G4PVPlacement(0,
    						   PMTEntranceWindow_Position,
    						   "PMTEntranceWindow_Physical",
    						   PMTEntranceWindow_Logical,
    						   Mother_Physical,
    						   false,
    						   0);

    //--- Define Cathode Solid
    Cathode_Solid = new G4Tubs("Cathode_Solid",
			       0.00*cm,
			       0.5*Cathode_Diameter,
			       0.5*Cathode_Thickness,
			       0.0*degree, 360.0*degree);

    //--- Define Cathode Logical
    Cathode_Logical = new G4LogicalVolume(Cathode_Solid,
    					  Cathode_Material,
    					  "Cathode_Logical");

    //--- Define Cathode Placement & Physical Volume
    G4double Cathode_Z = PMTEntranceWindow_Z + 0.5*(PMTEntranceWindow_Thickness + Cathode_Thickness);
    G4ThreeVector Cathode_Position(0.0, 0.0, Cathode_Z);
    
    Cathode_Physical = new G4PVPlacement(0,
    					Cathode_Position,
    					"Cathode_Physical",
    					Cathode_Logical,
    					Mother_Physical,
    					false,
    					0);

    ////////////////////////////
    //	Optical Photon Stuff  //
    ////////////////////////////
    
    // All code below copied from QweakSimCerenkov.cc
    const G4int nEntries = 11;
    G4double PhotonEnergy[nEntries] = {
        1.54986*eV,  //800.59 nm
        1.77127*eV,  //700.51 nm
        2.06648*eV,  //600.44 nm
        2.47978*eV,  //500.37 nm
        2.8178*eV,   //440.34 nm
        3.09973*eV,  //400.29 nm
        3.5424*eV,   //350.27 nm
        4.13297*eV,  //300.22 nm
        4.95956*eV,  //250.18 nm
        5.51063*eV,  //225.16 nm
        5.90424*eV   //210.15 nm
    };

    G4double Photocathode_Efficiency[nEntries] = {
        0.0080,      //800.59 nm
        0.0298,      //700.51 nm
        0.0638,      //600.44 nm
        0.1240,      //500.37 nm
        0.1670,      //440.34 nm
        0.1770,      //400.29 nm
        0.1800,      //350.27 nm
        0.2110,      //300.22 nm
        0.1780,      //250.18 nm
        0.0890,      //225.16 nm
        0.0355       //210.15 nm
    };
    
    G4double Photocathode_Reflectivity[nEntries] = {
        0.25, 	//800 nm
        0.25, 	//700 nm
        0.25, 	//600 nm
        0.25, 	//500 nm
        0.25,	//440 nm
        0.25,	//400 nm
        0.25,	//350 nm
        0.25,	//300 nm
        0.25,	//250 nm
        0.25,	//225 nm
        0.25 	//210 nm
    };

    G4double Reflectivity[nEntries];
    for (G4int kk= 0; kk < nEntries; kk++) {
        G4double mylambda = (h_Planck*c_light/PhotonEnergy[kk])/nanometer;

        // Nevens empiric formular for the reflectivity
        Reflectivity[kk] =  1.0 - 0.027*exp(-0.004608*mylambda);	        
    };
    
    G4OpticalSurface* LightGuide_OpticalSurface = new G4OpticalSurface("LightGuideOpticalSurface");
    LightGuide_OpticalSurface->SetType(dielectric_dielectric);
    LightGuide_OpticalSurface->SetFinish(polished);
    LightGuide_OpticalSurface->SetPolish(0.997);
    LightGuide_OpticalSurface->SetModel(glisur);

    G4MaterialPropertiesTable *quartzST = new G4MaterialPropertiesTable();
    quartzST->AddProperty("REFLECTIVITY",  PhotonEnergy , Reflectivity, nEntries);

    G4OpticalSurface* Photocathode_OpticalSurface =  new G4OpticalSurface("Photocathode_OS");
    Photocathode_OpticalSurface ->SetType(dielectric_metal); 
    Photocathode_OpticalSurface ->SetFinish(polished); 
    Photocathode_OpticalSurface ->SetModel(glisur);

    G4MaterialPropertiesTable* Photocathode_MPT = new G4MaterialPropertiesTable();
    Photocathode_MPT->AddProperty("REFLECTIVITY", PhotonEnergy, Photocathode_Reflectivity,nEntries);
    Photocathode_MPT->AddProperty("EFFICIENCY", PhotonEnergy, Photocathode_Efficiency,nEntries);
    Photocathode_OpticalSurface ->SetMaterialPropertiesTable(Photocathode_MPT);

    new G4LogicalBorderSurface("PMT_BorderSurface",
                               PMTEntranceWindow_Physical,
                               Cathode_Physical,
                               Photocathode_OpticalSurface);

    					
    ////////////////////////////////////
    // Define Visulization Attributes //
    ////////////////////////////////////
    
    Mother_VisAtt = new G4VisAttributes(G4Colour::White());
    Mother_VisAtt->SetVisibility(false);
    Mother_Logical->SetVisAttributes(Mother_VisAtt);

    PMTOnly_VisAtt = new G4VisAttributes(G4Colour::Blue());
    PMTOnly_VisAtt->SetVisibility(true);
    PMTOnly_Logical->SetVisAttributes(PMTOnly_VisAtt);

    G4VisAttributes* QuartzGlueFilm_VisAtt = new G4VisAttributes(G4Colour::White());
    QuartzGlueFilm_VisAtt->SetVisibility(true);
    PMTQuartzOpticalFilm_Logical->SetVisAttributes(QuartzGlueFilm_VisAtt);
    
    G4VisAttributes* PMTEntranceWindow_VisAtt = new G4VisAttributes(G4Colour::Grey());
    PMTEntranceWindow_VisAtt->SetVisibility(true);
    PMTEntranceWindow_Logical->SetVisAttributes(PMTEntranceWindow_VisAtt);
    
    G4VisAttributes* Cathode_VisAtt = new G4VisAttributes(G4Colour::Magenta());
    Cathode_VisAtt->SetVisibility(true);
    Cathode_Logical->SetVisAttributes(Cathode_VisAtt);

    ///////////////////////////////////////////
    // Define Sensitive Detectors to PMTOnly //
    ///////////////////////////////////////////
    
    G4SDManager* SDman = G4SDManager::GetSDMpointer();

    PMTOnlySD = new QweakSimPMTOnly_DetectorSD("PMTOnlySD");
    SDman -> AddNewDetector(PMTOnlySD);
    PMTOnly_Logical -> SetSensitiveDetector(PMTOnlySD);

    PMTOnly_PMTSD = new QweakSimPMTOnly_PMTSD("PMTOnly_PMTSD", myUserInfo);
    SDman -> AddNewDetector(PMTOnly_PMTSD);
    Cathode_Logical -> SetSensitiveDetector(PMTOnly_PMTSD);

}


/////// --------------------------------------------------------------------

void QweakSimPMTOnly::DestroyComponent()
{
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_Material(G4String materialName)
{
    //--- Set PMTOnly Material
	
    G4Material* pttoMaterial = G4Material::GetMaterial(materialName);
    
    if (pttoMaterial)
    {
        G4cout << "=== Changing PMTOnly material: Look up material " << G4endl;
        PMTOnly_Logical -> SetMaterial(pttoMaterial);
        G4cout << "=== Changing PMTOnly material: Now the material is " << materialName << G4endl;
    }
    else 
        G4cerr << "=== Error: Changing PMTOnly material FAILED! " << G4endl << G4endl;

}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_CenterPositionInX(G4double xPos)
{
    //--- Set PMTOnly X Position
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_CenterPositionInX() " << G4endl;
    Mother_CenterPosition_X = xPos;	 
    PMTOnly_Physical->SetTranslation(G4ThreeVector(Mother_CenterPosition_X,
                                                     Mother_CenterPosition_Y, 
                                                     Mother_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_CenterPositionInX() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_CenterPositionInY(G4double yPos)
{    
    //--- Set PMTOnly Y Position
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_CenterPositionInY() " << G4endl;
    Mother_CenterPosition_Y = yPos;	 
    PMTOnly_Physical->SetTranslation(G4ThreeVector(Mother_CenterPosition_X,
                                                     Mother_CenterPosition_Y, 
                                                     Mother_CenterPosition_Z));	
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_CenterPositionInY() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_CenterPositionInZ(G4double zPos)
{
    //--- Set PMTOnly Z Position
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_CenterPositionInZ() " << G4endl;
    Mother_CenterPosition_Z = zPos;	 	
    PMTOnly_Physical->SetTranslation(G4ThreeVector(Mother_CenterPosition_X,
                                                     Mother_CenterPosition_Y, 
                                                     Mother_CenterPosition_Z));	
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_CenterPositionInZ() " << G4endl << G4endl;
}




/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_TiltAngleInX(G4double xTiltAngle)
{
    //--- Set PMTOnly New X Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimPMTOnly::SetPMTOnly_TiltAngleInX() " << G4endl;
	
    //--- rotate back with old angle
    Mother_RotationMatrix->rotateX(-1.0*Mother_TiltAngle_X);
    Mother_Physical->SetRotation(Mother_RotationMatrix);
	
    //--- assign new tilting angle
    Mother_TiltAngle_X = xTiltAngle;
	
    //--- rotate to new angle
    Mother_RotationMatrix->rotateX(Mother_TiltAngle_X);
    Mother_Physical->SetRotation(Mother_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimPMTOnly::SetPMTOnly_TiltAngleInX() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_TiltAngleInY(G4double yTiltAngle)
{
    //--- Set PMTOnly New Y Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimPMTOnly::SetPMTOnly_TiltAngleInY() " << G4endl;
	
    //--- rotate back with old angle
    Mother_RotationMatrix->rotateY(-1.0*Mother_TiltAngle_Y);
    Mother_Physical->SetRotation(Mother_RotationMatrix);
	
    //--- assign new tilting angle
    Mother_TiltAngle_Y = yTiltAngle;
	
    //--- rotate to new angle
    Mother_RotationMatrix->rotateY(Mother_TiltAngle_Y);
    Mother_Physical->SetRotation(Mother_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimPMTOnly::SetPMTOnly_TiltAngleInY() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_TiltAngleInZ(G4double zTiltAngle)
{
    //--- Set PMTOnly New Z Tilting Angle
	
    G4cout << G4endl << "=== Calling QweakSimPMTOnly::SetPMTOnly_TiltAngleInZ() " << G4endl;
	
    //--- rotate back with old angle
    Mother_RotationMatrix->rotateZ(-1.0*Mother_TiltAngle_Z);
    Mother_Physical->SetRotation(Mother_RotationMatrix);
	
    //--- assign new tilting angle
    Mother_TiltAngle_Z = zTiltAngle;
	
    //--- rotate to new angle
    Mother_RotationMatrix->rotateZ(Mother_TiltAngle_Z);
    Mother_Physical->SetRotation(Mother_RotationMatrix);
	
    G4cout << G4endl << "=== Leaving QweakSimPMTOnly::SetPMTOnly_TiltAngleInZ() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_Enabled()
{
    //--- Enable the PMTOnly
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_Enabled() " << G4endl;
    PMTOnly_VisAtt -> SetVisibility(true);
    SetPMTOnly_Material(PMTOnly_Material -> GetName());
    Mother_Physical->SetTranslation(G4ThreeVector(Mother_CenterPosition_X,
                                                     Mother_CenterPosition_Y, 
                                                     Mother_CenterPosition_Z));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_Enabled() " << G4endl << G4endl;
}



/////// --------------------------------------------------------------------

void QweakSimPMTOnly::SetPMTOnly_Disabled()
{
    //--- Disable the PMTOnly
	
    G4cout << "=== Calling QweakSimPMTOnly::SetPMTOnly_Disabled() " << G4endl;
    PMTOnly_VisAtt -> SetVisibility(false);
    SetPMTOnly_Material("Air");
    Mother_Physical->SetTranslation(G4ThreeVector(Mother_CenterPosition_X,
                                                     Mother_CenterPosition_Y, 
                                                     Mother_CenterPosition_Z + 400.00*cm));
    G4cout << "=== Leaving QweakSimPMTOnly::SetPMTOnly_Disabled() " << G4endl << G4endl;
}


/////// --------------------------------------------------------------------

