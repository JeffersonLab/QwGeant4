//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimTrackingActionMessenger.cc

   $Revision: 1.1 $	
   $Date: 2006/01/06 04:46:45 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2006/01/06 04:46:45 $
//  CVS/RCS Revision: $Revision: 1.1 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTrackingActionMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTrackingActionMessenger::QweakSimTrackingActionMessenger(QweakSimTrackingAction* myTA)
:myTrackingAction(myTA)
{ 
 // TrackingAction related
  TrackingActionDir = new G4UIdirectory("/TrackingAction/");
  TrackingActionDir -> SetGuidance("TrackingAction control.");

  PrimaryOnly_Cmd =  new G4UIcmdWithAnInteger("/TrackingAction/PrimaryElectronsOnly",this);
  PrimaryOnly_Cmd->SetGuidance("Track only primary target electrons"); 
  PrimaryOnly_Cmd->SetGuidance(" 1 : Track Primary only"); 
  PrimaryOnly_Cmd->SetGuidance(" 0 : Track Primary and Secondaries"); 
  PrimaryOnly_Cmd->SetParameterName("Store",true);
  PrimaryOnly_Cmd->SetDefaultValue(0);
  PrimaryOnly_Cmd->SetRange("Store >=0 && Store <= 1");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTrackingActionMessenger::~QweakSimTrackingActionMessenger()
{
  delete PrimaryOnly_Cmd;
  delete TrackingActionDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void QweakSimTrackingActionMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  G4cout << "#### Calling QweakSimTrackingActionMessenger::SetNewValue() " << newValue << G4endl;

  if( command == PrimaryOnly_Cmd )
   {
     G4cout << "#### Messenger: Setting Tracking PrimaryOnly Flag to " << newValue << G4endl;

     myTrackingAction->SetTrackingPrimaryOnlyFlag(PrimaryOnly_Cmd->ConvertToBool(newValue));
   }

  G4cout << "#### Leaving QweakSimTrackingActionMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTrackingActionMessenger.cc,v $
//      Revision 1.1  2006/01/06 04:46:45  grimm
//      Initial version. Allows to set a flag for the tracking of primary electrons.
//

