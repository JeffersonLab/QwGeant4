//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTargetMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:15:20 $

   \author Klaus Hans Grimm   

*/
//=============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTargetMessenger.hh"

// user includes
#include "QweakSimTarget.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTargetMessenger::QweakSimTargetMessenger(QweakSimTarget* myTar)
:myTarget(myTar)
{ 
 // Target related
  TargetDir = new G4UIdirectory("/Target/");
  TargetDir -> SetGuidance("target control.");
       
  TargZPosCmd =  new G4UIcmdWithADoubleAndUnit("/Target/SetCenterPositionInZ",this);
  TargZPosCmd->SetGuidance("Set the Z position of the target center"); 
  TargZPosCmd->SetParameterName("Size",true);
  //TargZPosCmd->SetRange("Size>=0.");
  TargZPosCmd->SetUnitCategory("Length");
  TargZPosCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TargMatCmd = new G4UIcmdWithAString("/Target/SetTargetMaterial",this);
  TargMatCmd->SetGuidance("Select Material of the Target.");
  TargMatCmd->SetParameterName("choice",false);
  TargMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TargCellMatCmd = new G4UIcmdWithAString("/Target/SetTargetCellMaterial",this);
  TargCellMatCmd->SetGuidance("Select Material of the Target Cell.");
  TargCellMatCmd->SetParameterName("choice",false);
  TargCellMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TargEntWinMatCmd = new G4UIcmdWithAString("/Target/SetTargetEntranceWindowMaterial",this);
  TargEntWinMatCmd->SetGuidance("Select Material of the Target Entrance Window.");
  TargEntWinMatCmd->SetParameterName("choice",false);
  TargEntWinMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TargExtWinMatCmd = new G4UIcmdWithAString("/Target/SetTargetExitWindowMaterial",this);
  TargExtWinMatCmd->SetGuidance("Select Material of the Target Exit Window.");
  TargExtWinMatCmd->SetParameterName("choice",false);
  TargExtWinMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTargetMessenger::~QweakSimTargetMessenger()
{
  delete TargZPosCmd;
  delete TargMatCmd;
  delete TargCellMatCmd;
  delete TargEntWinMatCmd;
  delete TargExtWinMatCmd;
  delete TargetDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTargetMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimTargetMessenger::SetNewValue() " << newValue << G4endl;

  if( command == TargZPosCmd )
   {
     G4cout << "#### Messenger: Setting Target Z position to " << newValue << G4endl;

     myTarget->SetTargetCenterPositionInZ(TargZPosCmd->GetNewDoubleValue(newValue));
   }

  if( command == TargMatCmd )
  { 
      G4cout << "#### Messenger: Setting Target Material to " << newValue << G4endl;
      
      myTarget->SetTargetMaterial(newValue);
  }

  
  if( command == TargCellMatCmd )
  { 
     G4cout << "#### Messenger: Setting Target Cell Material to " << newValue << G4endl;
     
     myTarget->SetTargetCellMaterial(newValue);
  }

  if( command == TargEntWinMatCmd )
  {
     G4cout << "#### Messenger: Setting Target Entrance Window Material to " << newValue << G4endl;
    
     myTarget->SetTargetEntranceWindowMaterial(newValue);
  }

  if( command == TargExtWinMatCmd )
  {
     G4cout << "#### Messenger: Setting Target Exit Window Material to " << newValue << G4endl;

     myTarget->SetTargetExitWindowMaterial(newValue);
  }

  G4cout << "#### Leaving QweakSimTargetMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

