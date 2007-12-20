//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimGlobalMagnetField.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:10:21 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:10:21 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
              
#include "QweakSimGlobalMagnetField.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimGlobalMagnetField::QweakSimGlobalMagnetField() 
{	
    
  G4cout << G4endl << "###### Calling QweakSimGlobalMagnetField::QweakSimGlobalMagnetField() " << G4endl << G4endl;

    fMagneticField_MainMagnet = NULL;
    //fMagneticField_MiniMagnet = NULL;
    
     //=======================================================
    //    configuration values of the QTOR field map
    //=======================================================

    BFieldScalingFactor_MainMagnet =   0.0;    // according to Juliette Mammei
    fMagneticField_MainMagnet = new QweakSimMagnetFieldMap();

    if(fMagneticField_MainMagnet){
//       BFieldScalingFactor_MainMagnet = 0.52; //4He target with 600 MeV incident electron energy
//       BFieldScalingFactor_MainMagnet = 0.34;
      BFieldScalingFactor_MainMagnet = 1.0;
//    fMagneticField_MainMagnet->SetFieldMap_RMin(2.0);
//    fMagneticField_MainMagnet->SetFieldMap_RMax(300.0);
//    fMagneticField_MainMagnet->SetFieldMap_RStepsize(2.0);
//
//    fMagneticField_MainMagnet->SetFieldMap_ZMin(-250.0);
//    fMagneticField_MainMagnet->SetFieldMap_ZMax( 250.0);
//    fMagneticField_MainMagnet->SetFieldMap_ZStepsize(2.0);
//
//    fMagneticField_MainMagnet->SetFieldMap_PhiMin(1.0);
//    fMagneticField_MainMagnet->SetFieldMap_PhiMax(360.0);
//    fMagneticField_MainMagnet->SetFieldMap_PhiStepsize(1.0);!
    
      fMagneticField_MainMagnet->InitializeGrid();
    
      fMagneticField_MainMagnet->ReadFieldMap("MainMagnet_FieldMap.dat");
    }
    //=======================================================
    //    configuration values of the MiniTorus field map
    //=======================================================
        
//    BFieldScalingFactor_MiniMagnet =  0.0;
//     fMagneticField_MiniMagnet = new QweakSimMagnetFieldMap();

//  if(fMagneticField_MiniMagnet){
//
//    BFieldScalingFactor_MiniMagnet =  -0.078175;//-0.15434; // according to Juliette Mammei
//
//    fMagneticField_MiniMagnet->SetFieldMap_RMin(20.0*mm);
//    fMagneticField_MiniMagnet->SetFieldMap_RMax(1100.0*mm);
//    fMagneticField_MiniMagnet->SetFieldMap_RStepsize(20.0*mm);
//
//    fMagneticField_MiniMagnet->SetFieldMap_ZMin(-2040.0*mm);
//    fMagneticField_MiniMagnet->SetFieldMap_ZMax( 2040.0*mm);
//    fMagneticField_MiniMagnet->SetFieldMap_ZStepsize(20.0*mm);
//
//    fMagneticField_MiniMagnet->SetFieldMap_PhiMin(1.0*degree);
//    fMagneticField_MiniMagnet->SetFieldMap_PhiMax(43.0*degree);
//    fMagneticField_MiniMagnet->SetFieldMap_PhiStepsize(1.0*degree);
//
//    fMagneticField_MiniMagnet->InitializeGrid();
//
//    fMagneticField_MiniMagnet->ReadFieldMap("MiniTorus_FieldMap.dat");
//  }

    G4cout << G4endl << "###### Leaving QweakSimGlobalMagnetField::QweakSimGlobalMagnetField " << G4endl << G4endl;
}		
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimGlobalMagnetField::~QweakSimGlobalMagnetField()
{  
    G4cout << G4endl << "###### Calling QweakSimGlobalMagnetField::~QweakSimGlobalMagnetField() " << G4endl << G4endl;

    if (fMagneticField_MainMagnet) delete fMagneticField_MainMagnet;	
    // if (fMagneticField_MiniMagnet) delete fMagneticField_MiniMagnet;	
    
    G4cout << G4endl << "###### Leaving QweakSimGlobalMagnetField::~QweakSimGlobalMagnetField() " << G4endl << G4endl;
}	
    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimGlobalMagnetField::GetFieldValue(const G4double Point[4], G4double *Bfield ) const
{

  //G4cout << G4endl << "###### Calling QweakSimGlobalMagnetField::GetFieldValue() " << G4endl << G4endl;

  G4double myLocalPointInMainMagnet[4];
  G4double myLocalPointInMiniMagnet[4];
  
  G4double myLocalBfieldInMainMagnet[3];
  G4double myLocalBfieldInMiniMagnet[3];
  
  //---------------------------------------------------------------
  // translation from global Point[4] into local magnet coordinates
  //---------------------------------------------------------------
  //
  // (1) transformation into local MainMagnet coordinate is trivial
  //     since MainMagnet is located in origin
  myLocalPointInMainMagnet[0] = Point[0];             // x-pos
  myLocalPointInMainMagnet[1] = Point[1];             // y-pos
  myLocalPointInMainMagnet[2] = Point[2];             // z-pos
  myLocalPointInMainMagnet[3] = Point[3];             // time
  //
  // (2) transformation into local MiniMagnet coordinate is easy
  //     since MiniMagnet is shifted by 505*cm in z
  myLocalPointInMiniMagnet[0] = Point[0];             // x-pos
  myLocalPointInMiniMagnet[1] = Point[1];             // y-pos
  myLocalPointInMiniMagnet[2] = Point[2] + 465.31*cm;  // z-pos
  myLocalPointInMiniMagnet[3] = Point[3];             // time


//     G4cout << " X pos [cm] = " << Point[0]/cm << " ,Y pos [cm] = " << Point[1]/cm << " ,Z pos [cm] = " << Point[2]/cm << G4endl;


//if(fMagneticField_MiniMagnet && fMagneticField_MainMagnet){
//  fMagneticField_MiniMagnet->GetFieldValue( myLocalPointInMiniMagnet, myLocalBfieldInMiniMagnet );
//  fMagneticField_MainMagnet->GetFieldValue( myLocalPointInMainMagnet, myLocalBfieldInMainMagnet );
//
//  Bfield[0] = myLocalBfieldInMainMagnet[0]*BFieldScalingFactor_MainMagnet + myLocalBfieldInMiniMagnet[0]*BFieldScalingFactor_MiniMagnet;
//  Bfield[1] = myLocalBfieldInMainMagnet[1]*BFieldScalingFactor_MainMagnet + myLocalBfieldInMiniMagnet[1]*BFieldScalingFactor_MiniMagnet;
//  Bfield[2] = myLocalBfieldInMainMagnet[2]*BFieldScalingFactor_MainMagnet + myLocalBfieldInMiniMagnet[2]*BFieldScalingFactor_MiniMagnet;
//}
//else if(fMagneticField_MainMagnet && !fMagneticField_MiniMagnet){

  if(fMagneticField_MainMagnet){
      
      fMagneticField_MainMagnet->GetFieldValue( myLocalPointInMainMagnet, myLocalBfieldInMainMagnet );
      
      Bfield[0] = myLocalBfieldInMainMagnet[0]*BFieldScalingFactor_MainMagnet;
      Bfield[1] = myLocalBfieldInMainMagnet[1]*BFieldScalingFactor_MainMagnet;
      Bfield[2] = myLocalBfieldInMainMagnet[2]*BFieldScalingFactor_MainMagnet;

  }
  //else if(!fMagneticField_MainMagnet && fMagneticField_MiniMagnet){
  //  fMagneticField_MiniMagnet->GetFieldValue( myLocalPointInMiniMagnet, myLocalBfieldInMiniMagnet );
  //
  //  Bfield[0] =  myLocalBfieldInMiniMagnet[0]*BFieldScalingFactor_MiniMagnet;
  //  Bfield[1] =  myLocalBfieldInMiniMagnet[1]*BFieldScalingFactor_MiniMagnet;
  //  Bfield[2] =  myLocalBfieldInMiniMagnet[2]*BFieldScalingFactor_MiniMagnet;
  //}
  else{
      
      Bfield[0] = 0.0*kilogauss;
      Bfield[1] = 0.0*kilogauss;
      Bfield[2] = 0.0*kilogauss;

  }
  
  //   G4cout << "------------------------------------------------------------------------" << G4endl;
//   G4cout << " X pos [cm] = " << Point[0]/cm << "  , with X BField [kG] = " << Bfield[0] << G4endl;
//   G4cout << " Y pos [cm] = " << Point[1]/cm << "  , with Y BField [kG] = " << Bfield[1] << G4endl;
//   G4cout << " Z pos [cm] = " << Point[2]/cm << "  , with Z BField [kG] = " << Bfield[2] << G4endl;

//G4cout << G4endl << "###### Leaving QweakSimGlobalMagnetField::GetFieldValue() " << G4endl << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimGlobalMagnetField.cc,v $
//      Revision 1.2  2005/12/27 19:10:21  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
