//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimPrimaryGeneratorActionMessenger.cc

   $Revision: 1.3 $	
   $Date: 2006/05/05 21:33:44 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/05/05 21:33:44 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimPrimaryGeneratorActionMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorActionMessenger::QweakSimPrimaryGeneratorActionMessenger(QweakSimPrimaryGeneratorAction* pPhys)
:pPrimaryGeneratorAction(pPhys)
{
  Dir = new G4UIdirectory("/PrimaryEvent/");
  Dir->SetGuidance("UI commands of this example");
 
  verboseCmd = new G4UIcmdWithAnInteger("/PrimaryEvent/verbose",this);  
  verboseCmd->SetGuidance("set verbose for primary generator");
  verboseCmd->SetParameterName("verbose",true);
  verboseCmd->SetDefaultValue(1);
  verboseCmd->SetRange("verbose>=0");
  verboseCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  resetCmd = new G4UIcmdWithoutParameter("/PrimaryEvent/ResetNtupleEventCounter",this);  
  resetCmd->SetGuidance("resets Neven's Ntuple Event Counter");
  //resetCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
  resetCmd->AvailableForStates(G4State_Idle);  

  InitEventCounterCmd = new G4UIcmdWithAnInteger("/PrimaryEvent/StartingEvent",this);
  InitEventCounterCmd->SetGuidance("set starting event count for primary generator");
  InitEventCounterCmd->SetParameterName("StartingEvent",true);
  InitEventCounterCmd->SetDefaultValue(1);
  InitEventCounterCmd->SetRange("StartingEvent>=0");
  InitEventCounterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  SelectOctant_Cmd = new G4UIcmdWithAnInteger("/PrimaryEvent/SelectOctant",this);
  SelectOctant_Cmd->SetGuidance("Select octant for primaries");
  SelectOctant_Cmd->SetParameterName("SelectOctant",true);
  SelectOctant_Cmd->SetDefaultValue(1);
  SelectOctant_Cmd->SetRange("SelectOctant>=0");
  SelectOctant_Cmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimPrimaryGeneratorActionMessenger::~QweakSimPrimaryGeneratorActionMessenger()
{
  delete SelectOctant_Cmd;
  delete InitEventCounterCmd;
  delete verboseCmd;
  delete resetCmd;
  delete Dir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimPrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{       
  //if( command == verboseCmd )
    //{ pPrimaryGeneratorAction->SetVerbose(verboseCmd->GetNewIntValue(newValue));}
   
  if( command == resetCmd )
    {pPrimaryGeneratorAction->ResetNtupleEventCounter(); }

  if( command == InitEventCounterCmd )
    { pPrimaryGeneratorAction->SetNtupleEventCounter(InitEventCounterCmd->GetNewIntValue(newValue)); }

  if( command == SelectOctant_Cmd )
    { 
      pPrimaryGeneratorAction->SetActiveOctant(SelectOctant_Cmd->GetNewIntValue(newValue)); 
      //QweakSimPrimaryGeneratorAction::SetActiveOctant(SelectOctant_Cmd->GetNewIntValue(newValue)); 
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimPrimaryGeneratorActionMessenger.cc,v $
//      Revision 1.3  2006/05/05 21:33:44  grimm
//      Added /PrimaryEvent/SelectOctant  #octant . This defines the octant of the generated tracks.
//
//      Revision 1.2  2005/12/27 19:14:20  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
