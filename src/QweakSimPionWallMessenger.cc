//=============================================================================
//
//  File     QweakSimPionWallMessenger.cc
//  Revision 1.0
//  Date     07/23/2012
//  Author   James Dowd
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimPionWallMessenger.hh"

//  user includes
#include "QweakSimPionWall.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

QweakSimPionWallMessenger::QweakSimPionWallMessenger(QweakSimPionWall* thePionWall)
:myPionWall(thePionWall)
{
  PionWallDir = new G4UIdirectory("/PionWall/");
  PionWallDir -> SetGuidance("Pion Wall control.");
  
  //--------------------------------------------------
  
  PionWall_SetThicknessInZ_Cmd = new G4UIcmdWithADoubleAndUnit("/PionWall/SetThicknessInZ",this);
  PionWall_SetThicknessInZ_Cmd->SetGuidance("Set the thickness of the Pion Wall in the Z direction");
  PionWall_SetThicknessInZ_Cmd->SetParameterName("Size",true);
  PionWall_SetThicknessInZ_Cmd->SetUnitCategory("Length");
  PionWall_SetThicknessInZ_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //-------------------------------------------------
  
  PionWall_SetEnabled_Cmd = new G4UIcmdWithoutParameter("/PionWall/Enable",this);
  PionWall_SetEnabled_Cmd->SetGuidance("Enables the Pion Wall");
  PionWall_SetEnabled_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  //-------------------------------------------------
  
  PionWall_SetDisabled_Cmd = new G4UIcmdWithoutParameter("/PionWall/Disable",this);
  PionWall_SetDisabled_Cmd->SetGuidance("Disables the Pion Wall");
  PionWall_SetDisabled_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  
}

QweakSimPionWallMessenger::~QweakSimPionWallMessenger()
{

  if (PionWall_SetThicknessInZ_Cmd)  delete PionWall_SetThicknessInZ_Cmd;
  if (PionWall_SetEnabled_Cmd)       delete PionWall_SetEnabled_Cmd;
  if (PionWall_SetDisabled_Cmd)      delete PionWall_SetDisabled_Cmd;
  
  if (PionWallDir)                   delete PionWallDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void QweakSimPionWallMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  G4cout << "#### Messenger:  QweakSimPionWallMessenger::SetNewValue() " << newValue << G4endl;

  if ( command == PionWall_SetThicknessInZ_Cmd )
  {
    G4cout << "#### Messenger: Setting Pion Wall Z thickness to " << newValue << G4endl;
    
    myPionWall->SetPionWall_LengthInZ(PionWall_SetThicknessInZ_Cmd->GetNewDoubleValue(newValue));
  }
  
  //---------------------------------------------------------------
  
  if ( command == PionWall_SetEnabled_Cmd )
  {
    G4cout << "#### Messenger:  Pion Wall ENABLED" << G4endl;

    myPionWall->SetEnabled();
  }

    if ( command == PionWall_SetDisabled_Cmd )
  {
    G4cout << "#### Messenger:  Pion Wall DISABLED" << G4endl;

    myPionWall->SetDisabled();
  }

  //---------------------------------------------------------------
}

