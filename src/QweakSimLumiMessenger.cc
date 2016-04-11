/*

   \file QweakSimLumiMessenger.cc
   \author Wade Duvall

*/

#include "QweakSimLumiMessenger.hh"
#include "QweakSimLumiDetector.hh"
#include "QweakSimMessengerDefinition.hh"

QweakSimLumiMessenger::QweakSimLumiMessenger(QweakSimLumiDetector* theLumi, G4String tag):myLumi(theLumi) {
    /* Set directory for lumi control. */
    LumiDir = new G4UIdirectory("/Lumi/");
    LumiDir->SetGuidance("Lumi detector control");

    G4String DirPerTag_name = "/" + tag + "/Lumi";
    
    /* Change position of lumi. */
    Lumi_SetPositionInX_Cmd = new G4UIcmdWithADoubleAndUnit(G4String(DirPerTag_name + "/SetPositionInX"), this);
    Lumi_SetPositionInX_Cmd->SetGuidance("Set the X positiion of the Lumi");
    Lumi_SetPositionInX_Cmd->SetParameterName("Size", true);
    Lumi_SetPositionInX_Cmd->SetUnitCategory("Length");
    Lumi_SetPositionInX_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    Lumi_SetPositionInY_Cmd = new G4UIcmdWithADoubleAndUnit(G4String(DirPerTag_name + "/SetPositionInY"), this);
    Lumi_SetPositionInY_Cmd->SetGuidance("Set the Y positiion of the Lumi");
    Lumi_SetPositionInY_Cmd->SetParameterName("Size", true);
    Lumi_SetPositionInY_Cmd->SetUnitCategory("Length");
    Lumi_SetPositionInY_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    Lumi_SetPositionInZ_Cmd = new G4UIcmdWithADoubleAndUnit(G4String(DirPerTag_name + "/SetPositionInZ"), this);
    Lumi_SetPositionInZ_Cmd->SetGuidance("Set the Z positiion of the Lumi");
    Lumi_SetPositionInZ_Cmd->SetParameterName("Size", true);
    Lumi_SetPositionInZ_Cmd->SetUnitCategory("Length");
    Lumi_SetPositionInZ_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    /* Enable Lumis. */
    Lumi_SetEnabled_Cmd = new G4UIcmdWithoutParameter(G4String(DirPerTag_name + "/Enable"), this);
    Lumi_SetEnabled_Cmd->SetGuidance("Enables the Lumis");
    Lumi_SetEnabled_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    /* Disable Lumis. */
    Lumi_SetDisabled_Cmd = new G4UIcmdWithoutParameter(G4String(DirPerTag_name + "/Disable"), this);
    Lumi_SetDisabled_Cmd->SetGuidance("Disables the Lumis");
    Lumi_SetDisabled_Cmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

QweakSimLumiMessenger::~QweakSimLumiMessenger() {
    if(Lumi_SetPositionInX_Cmd) delete Lumi_SetPositionInX_Cmd;
    if(Lumi_SetPositionInY_Cmd) delete Lumi_SetPositionInY_Cmd;
    if(Lumi_SetPositionInZ_Cmd) delete Lumi_SetPositionInZ_Cmd;

    if(Lumi_SetEnabled_Cmd) delete Lumi_SetEnabled_Cmd;
    if(Lumi_SetDisabled_Cmd) delete Lumi_SetDisabled_Cmd;

    if(LumiDir) delete LumiDir;
}

void QweakSimLumiMessenger::SetNewValue(G4UIcommand* command, G4String newValue) {
    G4cout << "=== Calling QweakSimLumiMessenger::SetNewValue() " << newValue << G4endl;

    if(command == Lumi_SetPositionInX_Cmd) {
        G4cout << "=== Messenger: Setting Lumi X position to " << newValue << G4endl;
        myLumi->SetLumi_PositionInX(Lumi_SetPositionInX_Cmd->GetNewDoubleValue(newValue));
    }

    if(command == Lumi_SetPositionInY_Cmd) {
        G4cout << "=== Messenger: Setting Lumi Y position to " << newValue << G4endl;
        myLumi->SetLumi_PositionInY(Lumi_SetPositionInY_Cmd->GetNewDoubleValue(newValue));
    }

    if(command == Lumi_SetPositionInZ_Cmd) {
        G4cout << "=== Messenger: Setting Lumi Z position to " << newValue << G4endl;
        myLumi->SetLumi_PositionInZ(Lumi_SetPositionInZ_Cmd->GetNewDoubleValue(newValue));
    }

    if(command == Lumi_SetEnabled_Cmd) {
        G4cout << "=== Messenger: ENABLE the Lumi" << G4endl;
        myLumi->SetLumi_Enabled();
    }
    
    if(command == Lumi_SetDisabled_Cmd) {
        G4cout << "=== Messenger: DISABLE the Lumi" << G4endl;
        myLumi->SetLumi_Disabled();
    }
    
    G4cout << "=== Leaving QweakSimLumiMessenger::SetNewValue() " << newValue << G4endl;
}
