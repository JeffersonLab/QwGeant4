//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTriggerScintillatorMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:16:32 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:16:32 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTriggerScintillatorMessenger.hh"

// user includes
#include "QweakSimTriggerScintillator.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTriggerScintillatorMessenger::QweakSimTriggerScintillatorMessenger(QweakSimTriggerScintillator* theTriggerScintillator)
:myTriggerScintillator(theTriggerScintillator)
{ 

  Dir = new G4UIdirectory("/TriggerScintillator/");
  Dir -> SetGuidance("Trigger Scintillator Detector control.");
       
  ContainerThicknessCmd =  new G4UIcmdWithADoubleAndUnit("/TriggerScintillator/SetThickness",this);
  ContainerThicknessCmd->SetGuidance("Set the thickness (length in Z) of the TriggerScintillator container"); 
  ContainerThicknessCmd->SetParameterName("Size",true);
  ContainerThicknessCmd->SetUnitCategory("Length");
  ContainerThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerZPositionCmd =  new G4UIcmdWithADoubleAndUnit("/TriggerScintillator/SetCenterPositionInZ",this);
  ContainerZPositionCmd->SetGuidance("Set the Z position of the TriggerScintillator container center"); 
  ContainerZPositionCmd->SetParameterName("Size",true);
  ContainerZPositionCmd->SetUnitCategory("Length");
  ContainerZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerYPositionCmd =  new G4UIcmdWithADoubleAndUnit("/TriggerScintillator/SetCenterPositionInY",this);
  ContainerYPositionCmd->SetGuidance("Set the Y position of the TriggerScintillator container center"); 
  ContainerYPositionCmd->SetParameterName("Size",true);
  ContainerYPositionCmd->SetUnitCategory("Length");
  ContainerYPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerXPositionCmd =  new G4UIcmdWithADoubleAndUnit("/TriggerScintillator/SetCenterPositionInX",this);
  ContainerXPositionCmd->SetGuidance("Set the X position of the TriggerScintillator container center"); 
  ContainerXPositionCmd->SetParameterName("Size",true);
  ContainerXPositionCmd->SetUnitCategory("Length");
  ContainerXPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TiltingAngleCmd =  new G4UIcmdWithADoubleAndUnit("/TriggerScintillator/SetTiltingAngle",this);
  TiltingAngleCmd->SetGuidance("Set the tilting angle of the TriggerScintillator Detector"); 
  TiltingAngleCmd->SetParameterName("Angle",true);
  TiltingAngleCmd->SetDefaultUnit("degree");
  TiltingAngleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ContainerMatCmd = new G4UIcmdWithAString("/TriggerScintillator/SetContainerMaterial",this);
  ContainerMatCmd->SetGuidance("Select Material of the TriggerScintillator Container.");
  ContainerMatCmd->SetParameterName("choice",false);
  ContainerMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  DetectorMatCmd = new G4UIcmdWithAString("/TriggerScintillator/SetScintillatorMaterial",this);
  DetectorMatCmd->SetGuidance("Select Material of the TriggerScintillator Detector.");
  DetectorMatCmd->SetParameterName("choice",false);
  DetectorMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTriggerScintillatorMessenger::~QweakSimTriggerScintillatorMessenger()
{
  if (ContainerXPositionCmd)      delete ContainerXPositionCmd;
  if (ContainerYPositionCmd)      delete ContainerYPositionCmd;
  if (ContainerZPositionCmd)      delete ContainerZPositionCmd;

  if (ContainerThicknessCmd)      delete ContainerThicknessCmd;
  if (DetectorMatCmd)             delete DetectorMatCmd;  
  if (ContainerMatCmd)            delete ContainerMatCmd;
  if (TiltingAngleCmd)            delete TiltingAngleCmd;
  if (Dir)                        delete Dir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTriggerScintillatorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimTriggerScintillatorMessenger::SetNewValue() " << newValue << G4endl;

  if( command == ContainerThicknessCmd )
   {
     G4cout << "#### Messenger: Setting TriggerScintillator Container Thickness to " << newValue << G4endl;

     myTriggerScintillator->SetTriggerScintillatorThickness(ContainerThicknessCmd->GetNewDoubleValue(newValue));
   }

  if( command == ContainerXPositionCmd )
   {
     G4cout << "#### Messenger: Setting TriggerScintillator Container X position to " << newValue << G4endl;

     myTriggerScintillator->SetTriggerScintillatorCenterPositionInX(ContainerXPositionCmd->GetNewDoubleValue(newValue));
   }

  if( command == ContainerYPositionCmd )
  {
      G4cout << "#### Messenger: Setting TriggerScintillator Container Y position to " << newValue << G4endl;
      
      myTriggerScintillator->SetTriggerScintillatorCenterPositionInY(ContainerYPositionCmd->GetNewDoubleValue(newValue));
   }
  
  if( command == ContainerZPositionCmd )
  {
      G4cout << "#### Messenger: Setting TriggerScintillator Container Z position to " << newValue << G4endl;

      myTriggerScintillator->SetTriggerScintillatorCenterPositionInZ(ContainerZPositionCmd->GetNewDoubleValue(newValue));
  }
  
  
  if( command == ContainerMatCmd )
   { 
     G4cout << "#### Messenger: Setting TriggerScintillator Container Material to " << newValue << G4endl;

     //myTriggerScintillator->SetContainerMaterial(newValue);
   }

  if( command == DetectorMatCmd )
   { 
     G4cout << "#### Messenger: Setting Scintillator Detector Material to " << newValue << G4endl;

     myTriggerScintillator->SetTriggerScintillatorMaterial(newValue);
   }

  if( command == TiltingAngleCmd )
   { 
     G4cout << "#### Messenger: Setting Scintillator Detector Tilting Angle to " << newValue << G4endl;

     myTriggerScintillator->SetTriggerScintillatorTiltAngle(TiltingAngleCmd->GetNewDoubleValue(newValue));
   }

  G4cout << "#### Leaving QweakSimTriggerScintillator Messenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTriggerScintillatorMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:16:32  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
