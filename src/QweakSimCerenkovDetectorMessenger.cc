//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimCerenkovDetectorMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:07:14 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:07:14 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimCerenkovDetectorMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimCerenkovDetectorMessenger::QweakSimCerenkovDetectorMessenger(QweakSimCerenkovDetector* theCerenkovDetector)
:myCerenkovDetector(theCerenkovDetector)
{ 

  Dir = new G4UIdirectory("/Cerenkov/");
  Dir -> SetGuidance("Cerenkov Detector control.");
       
  ContainerThicknessCmd =  new G4UIcmdWithADoubleAndUnit("/Cerenkov/SetThickness",this);
  ContainerThicknessCmd->SetGuidance("Set the thickness (length in Z) of the Cherenkov container"); 
  ContainerThicknessCmd->SetParameterName("Size",true);
  ContainerThicknessCmd->SetUnitCategory("Length");
  ContainerThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerZPositionCmd =  new G4UIcmdWithADoubleAndUnit("/Cerenkov/SetCenterPositionInZ",this);
  ContainerZPositionCmd->SetGuidance("Set the Z position of the Cerenkov container center"); 
  ContainerZPositionCmd->SetParameterName("Size",true);
  ContainerZPositionCmd->SetUnitCategory("Length");
  ContainerZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerYPositionCmd =  new G4UIcmdWithADoubleAndUnit("/Cerenkov/SetCenterPositionInY",this);
  ContainerYPositionCmd->SetGuidance("Set the Y position of the Cerenkov container center"); 
  ContainerYPositionCmd->SetParameterName("Size",true);
  ContainerYPositionCmd->SetUnitCategory("Length");
  ContainerYPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerXPositionCmd =  new G4UIcmdWithADoubleAndUnit("/Cerenkov/SetCenterPositionInX",this);
  ContainerXPositionCmd->SetGuidance("Set the X position of the Cerenkov container center"); 
  ContainerXPositionCmd->SetParameterName("Size",true);
  ContainerXPositionCmd->SetUnitCategory("Length");
  ContainerXPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TiltingAngleCmd =  new G4UIcmdWithADoubleAndUnit("/Cerenkov/SetTiltingAngle",this);
  TiltingAngleCmd->SetGuidance("Set the tilting angle of the Cerenkov Detector"); 
  TiltingAngleCmd->SetParameterName("Angle",true);
  TiltingAngleCmd->SetDefaultUnit("degree");
  TiltingAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  KinkAngleCmd =  new G4UIcmdWithADoubleAndUnit("/Cerenkov/SetKinkAngle",this);
  KinkAngleCmd->SetGuidance("Set the kink angle for the V-shape "); 
  KinkAngleCmd->SetParameterName("Angle",true);
  KinkAngleCmd->SetDefaultUnit("degree");
  KinkAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerMatCmd = new G4UIcmdWithAString("/Cerenkov/SetContainerMaterial",this);
  ContainerMatCmd->SetGuidance("Select Material of the Cerenkov Container.");
  ContainerMatCmd->SetParameterName("choice",false);
  ContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DetectorMatCmd = new G4UIcmdWithAString("/Cerenkov/SetCerenkovMaterial",this);
  DetectorMatCmd->SetGuidance("Select Material of the Cerenkov Detector.");
  DetectorMatCmd->SetParameterName("choice",false);
  DetectorMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimCerenkovDetectorMessenger::~QweakSimCerenkovDetectorMessenger()
{
  if (ContainerXPositionCmd)      delete ContainerXPositionCmd;
  if (ContainerYPositionCmd)      delete ContainerYPositionCmd;
  if (ContainerZPositionCmd)      delete ContainerZPositionCmd;

  if (ContainerThicknessCmd)      delete ContainerThicknessCmd;
  if (DetectorMatCmd)             delete DetectorMatCmd;  
  if (ContainerMatCmd)            delete ContainerMatCmd;
  if (TiltingAngleCmd)            delete TiltingAngleCmd;
  if (KinkAngleCmd)               delete KinkAngleCmd;
  if (Dir)                        delete Dir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimCerenkovDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimCerenkovDetectorMessenger::SetNewValue() " << newValue << G4endl;

  if( command == ContainerThicknessCmd )
   {
     G4cout << "#### Messenger: Setting CerenkovDetector Container Thickness to " << newValue << G4endl;

     myCerenkovDetector->SetCerenkovDetectorThickness(ContainerThicknessCmd->GetNewDoubleValue(newValue));
   }

  if( command == ContainerXPositionCmd )
   {
     G4cout << "#### Messenger: Setting CerenkovDetector Container X position to " << newValue << G4endl;

     myCerenkovDetector->SetCerenkovDetectorCenterPositionInX(ContainerXPositionCmd->GetNewDoubleValue(newValue));
   }

  if( command == ContainerYPositionCmd )
  {
      G4cout << "#### Messenger: Setting CerenkovDetector Container Y position to " << newValue << G4endl;
      
      myCerenkovDetector->SetCerenkovDetectorCenterPositionInY(ContainerYPositionCmd->GetNewDoubleValue(newValue));
   }
  
  if( command == ContainerZPositionCmd )
  {
      G4cout << "#### Messenger: Setting CerenkovDetector Container Z position to " << newValue << G4endl;

      myCerenkovDetector->SetCerenkovDetectorCenterPositionInZ(ContainerZPositionCmd->GetNewDoubleValue(newValue));
  }
  
  
  if( command == ContainerMatCmd )
   { 
     G4cout << "#### Messenger: Setting CerenkovDetector Container Material to " << newValue << G4endl;

     //myCerenkovDetector->SetContainerMaterial(newValue);
   }

  if( command == DetectorMatCmd )
   { 
     G4cout << "#### Messenger: Setting Cerenkov Detector Material to " << newValue << G4endl;

     myCerenkovDetector->SetCerenkovDetectorMaterial(newValue);
   }

  if( command == TiltingAngleCmd )
   { 
     G4cout << "#### Messenger: Setting Cerenkov Detector Tilting Angle to " << newValue << G4endl;

     myCerenkovDetector->SetCerenkovDetectorTiltAngle(TiltingAngleCmd->GetNewDoubleValue(newValue));
   }

  if( command == KinkAngleCmd )
   { 
     G4cout << "#### Messenger: Setting Cerenkov Detector Kink Angle to " << newValue << G4endl;

     // myCerenkovDetector->SetKinkAngle(newValue);
   }


  G4cout << "#### Leaving QweakSimCerenkovDetector Messenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimCerenkovDetectorMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:07:14  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
