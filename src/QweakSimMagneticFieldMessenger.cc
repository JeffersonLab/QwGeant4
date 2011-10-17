//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimMagneticFieldMessenger.cc

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

#include "QweakSimMagneticFieldMessenger.hh"

// user includes
#include "QweakSimMessengerDefinition.hh"
#include "QweakSimMagneticField.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimMagneticFieldMessenger::QweakSimMagneticFieldMessenger(QweakSimMagneticField* magneticfield)
  : fMagneticField(magneticfield)
{
  MagneticFieldDir = new G4UIdirectory("/MagneticField/");
  MagneticFieldDir->SetGuidance("Main Magnet control.");

  ReadCmd = new G4UIcmdWithAString("/MagneticField/Read",this);
  ReadCmd->SetGuidance("Read the specified magnetic field");
  ReadCmd->SetParameterName("file",true);
  ReadCmd->SetDefaultValue("MainMagnet_FieldMap.dat");
  ReadCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  ScaleCmd = new G4UIcmdWithADouble("/MagneticField/SetScale",this);
  ScaleCmd->SetGuidance("Set scale of the magnetic field");
  ScaleCmd->SetParameterName("bfil",false);
  ScaleCmd->SetDefaultValue(1.0);
  ScaleCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  StepperCmd = new G4UIcmdWithAnInteger("/MagneticField/SetStepperType",this);
  StepperCmd->SetGuidance("Select stepper type for magnetic field");
  StepperCmd->SetParameterName("choice",true);
  StepperCmd->SetDefaultValue(4);
  StepperCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  MinStepCmd = new G4UIcmdWithADoubleAndUnit("/MagneticField/SetMinStep",this);
  MinStepCmd->SetGuidance("Define minimal step");
  MinStepCmd->SetParameterName("min step",false,false);
  MinStepCmd->SetDefaultUnit("mm");
  MinStepCmd->AvailableForStates(G4State_Idle);

  UpdateCmd = new G4UIcmdWithoutParameter("/MagneticField/Update",this);
  UpdateCmd->SetGuidance("Update Main Magnet geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimMagneticFieldMessenger::~QweakSimMagneticFieldMessenger()
{
  delete StepperCmd;
  delete ScaleCmd;
  delete MinStepCmd;
  delete MagneticFieldDir;
  delete UpdateCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
void QweakSimMagneticFieldMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  G4cout << "#### Calling QweakSimMagneticFieldMessenger::SetNewValue() " << newValue << G4endl;

  if (command == ScaleCmd) {
    fMagneticField->SetScaleFactor(ScaleCmd->GetNewDoubleValue(newValue));
  } else if (command == ReadCmd) {
    fMagneticField->ReadFieldMap(newValue);
  }

  G4cout << "#### Leaving QweakSimMagneticFieldMessenger::SetNewValue() " << newValue << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMagneticFieldMessenger.cc,v $
//      Revision 1.2  2005/12/27 19:12:59  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
