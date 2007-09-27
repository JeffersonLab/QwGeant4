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

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:15:20 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimTargetMessenger.hh"

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

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimTargetMessenger::~QweakSimTargetMessenger()
{
  delete TargZPosCmd;
  delete TargMatCmd;
  delete TargCellMatCmd;
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



  G4cout << "#### Leaving QweakSimTargetMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimTargetMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:15:20  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
