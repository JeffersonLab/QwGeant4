//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMagnetFieldMapMessenger.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:12:59 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:12:59 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "QweakSimMagnetFieldMapMessenger.hh"

// user includes
#include "QweakSimMagnetFieldMap.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimMagnetFieldMapMessenger::QweakSimMagnetFieldMapMessenger(QweakSimMagnetFieldMap* pMfield)
  : fMfieldSetup(pMfield)
{ 
  MainMagnetDir = new G4UIdirectory("/MagnetField/");
  MainMagnetDir->SetGuidance("Main Magnetcontrol.");

  StepperCmd = new G4UIcmdWithAnInteger("/MagnetField/SetStepperType",this);
  StepperCmd->SetGuidance("Select stepper type for magnetic field");
  StepperCmd->SetParameterName("choice",true);
  StepperCmd->SetDefaultValue(4);
  StepperCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  MinStepCmd = new G4UIcmdWithADoubleAndUnit("/MagnetField/SetMinStep",this);  
  MinStepCmd->SetGuidance("Define minimal step");
  MinStepCmd->SetParameterName("min step",false,false);
  MinStepCmd->SetDefaultUnit("mm");
  MinStepCmd->AvailableForStates(G4State_Idle);  

  UpdateCmd = new G4UIcmdWithoutParameter("/MagnetField/Update",this);
  UpdateCmd->SetGuidance("Update Main Magnet geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimMagnetFieldMapMessenger::~QweakSimMagnetFieldMapMessenger()
{
  delete StepperCmd;
  delete MagFieldCmd;
  delete MinStepCmd;
  delete MainMagnetDir;
  delete UpdateCmd;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagnetFieldMapMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:12:59  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
