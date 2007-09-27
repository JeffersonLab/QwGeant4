
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMiniMagnet.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:13:37 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:13:37 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimMiniMagnet.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimMiniMagnet::QweakSimMiniMagnet() 
{	
    
    G4cout << G4endl << "###### Calling QweakSimMiniMagnet::QweakSimMiniMagnet() " << G4endl << G4endl;
    
    
    //  Initialize Pointers		
    pMaterial                           = NULL;
    
//     MiniMagnet_MasterContainer_Logical  = NULL;
//     MiniMagnet_MasterContainer_Physical = NULL;
//     MiniMagnet_MasterContainer_Material = NULL;

    SingleCoil_MasterContainer_Logical  = NULL;
    SingleCoil_MasterContainer_Material = NULL;

    // clear vector containing the physical coil
    SingleCoil_MasterContainer_Physical.clear();
    SingleCoil_MasterContainer_Physical.resize(8);

    Angle_SingleCoil.clear();
    Angle_SingleCoil.resize(8);

    Translation_SingleCoil.clear();
    Translation_SingleCoil.resize(8);

    Rotation_SingleCoil.clear();
    Rotation_SingleCoil.resize(8);

    // Input File Reader
    MiniMagnet_Messenger = new QweakSimMiniMagnetMessenger(this);

    // get access to material definition
    pMaterial = new QweakSimMaterial();
    pMaterial->DefineMaterials();

 
  // define MiniMagnet_MasterContainer geometry values
  // The MiniMagnet_MasterContainer contains everything related to the MiniTorus
  //
  //MiniMagnet_MasterContainer_FullLength_X = 220.0*cm;    // Full X length 
  //MiniMagnet_MasterContainer_FullLength_Y = 220.0*cm;    // Full Y length 
  //MiniMagnet_MasterContainer_FullLength_Z =  95.0*cm;    // Full Z length , Coil_diameter= 52.50*cm

//   MiniMagnet_MasterContainer_FullLength_X = 300.0*cm;    // Full X length
//   MiniMagnet_MasterContainer_FullLength_Y = 300.0*cm;    // Full Y length
//   MiniMagnet_MasterContainer_FullLength_Z = 2*230.0*cm;    // Full Z length

  // get material
  //MiniMagnet_MasterContainer_Material = pMaterial->GetMaterial("HeGas"); 

  // set default for origin (taken from Juliette's euclid file) in MotherVolume
  MiniMagnet_CenterPositionInZ = -465.31*cm;

  // define a single coil
//   SingleCoil_MasterContainer_DiameterMin   =  175*mm;
//   SingleCoil_MasterContainer_DiameterMax   =  525*mm;
//   SingleCoil_MasterContainer_FullThickness =  14*mm;
//   SingleCoil_MasterContainer_PhiAngleStart =   0.0*degree;
//   SingleCoil_MasterContainer_PhiAngleEnd   = 360.0*degree;
  // 
  SingleCoil_MasterContainer_DiameterMin   =  175*mm;
  SingleCoil_MasterContainer_DiameterMax   =  875*mm;
  SingleCoil_MasterContainer_FullThickness =  28*mm;
  SingleCoil_MasterContainer_PhiAngleStart =   0.0*degree;
  SingleCoil_MasterContainer_PhiAngleEnd   = 360.0*degree;
 
  // get material
  SingleCoil_MasterContainer_Material = pMaterial->GetMaterial("Copper"); 
  
  // Distance of a Single Copper Coil Center to BeamLine : See SolidWorks
//   SingleCoil_CenterPositionInR = 362.50*mm;
  SingleCoil_CenterPositionInR = 537.5*mm;


  G4cout << G4endl << "###### Leaving QweakSimMiniMagnet::QweakSimMiniMagnet " << G4endl << G4endl;
}	

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimMiniMagnet::~QweakSimMiniMagnet()
{  
G4cout << G4endl << "###### Calling QweakSimMiniMagnet::~QweakSimMiniMagnet() " << G4endl << G4endl;


//     delete MiniMagnet_MasterContainer_Logical;
//     delete MiniMagnet_MasterContainer_Physical;
//
//     delete SingleCoil_MasterContainer_Logical;
//     delete SingleCoil_MasterContainer_Physical;
  if (MiniMagnet_Messenger)   delete MiniMagnet_Messenger;   	
  if (pMaterial)              delete pMaterial;

G4cout << G4endl << "###### Leaving QweakSimMiniMagnet::~QweakSimMiniMagnet() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......SingleCoil_CenterPositionInR
void QweakSimMiniMagnet::ConstructComponent(G4VPhysicalVolume* MotherVolume)
{
G4cout << G4endl << "###### Calling QweakSimMiniMagnet::ConstructComponent() " << G4endl << G4endl;


   // define center position of SingleCoil_MasterContainer inside the MiniMagnet_MasterContainer
    G4ThreeVector positionSingleCoilContainer = G4ThreeVector(0,0, MiniMagnet_CenterPositionInZ);

    // define MiniMagnet SingleCoil Container solid volume
    G4cout << G4endl << "###### QweakSimMiniMagnet: Define MiniMagnet_MasterContainer_Solid " << G4endl << G4endl;

    G4Tubs* SingleCoil_MasterContainer_Solid    = new G4Tubs("SingleCoil_MasterContainer_Sol",
							     0.5*SingleCoil_MasterContainer_DiameterMin ,
							     0.5*SingleCoil_MasterContainer_DiameterMax ,
							     0.5*SingleCoil_MasterContainer_FullThickness,
							         SingleCoil_MasterContainer_PhiAngleStart,
							         SingleCoil_MasterContainer_PhiAngleEnd
							     ); 

    // define SingleCoil_MasterContainer logical volume
     G4cout << G4endl << "###### QweakSimMiniMagnet: Define SingleCoil_MasterContainer_Logical " << G4endl << G4endl;

     SingleCoil_MasterContainer_Logical  = new G4LogicalVolume(  SingleCoil_MasterContainer_Solid,
								 SingleCoil_MasterContainer_Material,
								 "SingleCoil_MasterContainer_Log",
								 0,
								 0,0);

//**************** does NOT work !!! ************************************************
//      // arange the SingleCoil using a Parameterisation:
//      G4VPVParameterisation* singleCoilParam = new QweakSimMagnet_MiniTorusCoilParameterisation( SingleCoil_CenterPositionInR );
//
//      SingleCoil_MasterContainer_Physical =
//          new G4PVParameterised("SingleCoil_MasterContainer_Physical",    // their physical name
//                                SingleCoil_MasterContainer_Logical,       // their logical volume
//                                MotherVolume,                             // Mother physical volume
//                                kZAxis,                                   // Are placed along this axis
//                                8,                                        // Number of coils
//                                singleCoilParam);                         // The parametrisation
//


     

     // place 8 SingleCoil_MasterContainer_Logical plates into the MotherVolume (around the global Z axis)
     for (G4int n=0; n<8; n++) {

	 Angle_SingleCoil[n] = n*45.0*degree + 22.5*degree;

	 Translation_SingleCoil[n].setX(sin(Angle_SingleCoil[n])*SingleCoil_CenterPositionInR);
	 Translation_SingleCoil[n].setY(cos(Angle_SingleCoil[n])*SingleCoil_CenterPositionInR);
	 Translation_SingleCoil[n].setZ(MiniMagnet_CenterPositionInZ);

	 // since the SingleCoil_MasterContainer_Logical is defined for a vertical orientation
	 // but the translation assumes a horizontal orinetation, we have to subtract 90*deg
	 Rotation_SingleCoil[n] = new G4RotationMatrix();
	 Rotation_SingleCoil[n]->rotateY(90.0*degree);
	 Rotation_SingleCoil[n]->rotateX(Angle_SingleCoil[n]);

   
	 SingleCoil_MasterContainer_Physical[n]   = new G4PVPlacement(Rotation_SingleCoil[n],
								      Translation_SingleCoil[n],
								      "MiniMagnet_MasterContainer_Physical",
								      SingleCoil_MasterContainer_Logical,
								      MotherVolume,
								      false,
								      n);

     } // end of  for (G4int n=0; n<8; n++)

 G4cout << G4endl << "###### QweakSimMiniMagnet: Setting Attributes " << G4endl << G4endl;


 G4Colour copper ( 184/255., 115/255., 51/255.);

 G4VisAttributes* SingleCoil_MasterContainer_VisAtt = new G4VisAttributes(copper); 
 SingleCoil_MasterContainer_VisAtt->SetVisibility(true);
 //SingleCoil_MasterContainer_VisAtt->SetForceWireframe(true); 
 //SingleCoil_MasterContainer_VisAtt->SetForceSolid(true); 
 SingleCoil_MasterContainer_Logical->SetVisAttributes(SingleCoil_MasterContainer_VisAtt); 

 G4cout << G4endl << "###### Leaving QweakSimMiniMagnet::ConstructComponent() " << G4endl << G4endl;
 
}    // end 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimMiniMagnet::DestroyComponent()
{
G4cout << G4endl << "###### Calling QweakSimMiniMagnet::DestroyComponent() " << G4endl << G4endl;

G4cout << G4endl << "###### Leaving QweakSimMiniMagnet::DestroyComponent() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........

void QweakSimMiniMagnet::SetCenterPositionInZ(G4double myCenterPositionInZ)
{
G4cout << G4endl << "###### Calling QweakSimMiniMagnet::SetCenterPositionInZ() " << G4endl << G4endl;

 //MiniMagnet_MasterContainer_Physical->SetTranslation(G4ThreeVector(0.,0., myCenterPositionInZ));

     for (G4int n=0; n<8; n++) {

	 SingleCoil_MasterContainer_Physical[n]->SetTranslation(
	     G4ThreeVector( Translation_SingleCoil[n].x() ,
			    Translation_SingleCoil[n].y() , 
			    myCenterPositionInZ));
     }

G4cout << G4endl << "###### Leaving QweakSimMiniMagnet::SetCenterPositionInZ() " << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMiniMagnet.cc,v $
//      Revision 1.2  2005/12/27 19:13:37  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

