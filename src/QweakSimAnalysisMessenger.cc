/*
 * QweakSimAnalysisMessenger.cc
 *
 *  Created on: May 19, 2011
 *      Author: wdconinc
 */

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimAnalysisMessenger.hh"

// user includes
#include "QweakSimAnalysis.hh"
#include "QweakSimMessengerDefinition.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

QweakSimAnalysisMessenger::QweakSimAnalysisMessenger()
{
  G4cout << "###### Calling QweakSimAnalysisMessenger::QweakSimAnalysisMessenger() " << G4endl;

  fAnalysisDir = new G4UIdirectory("/Analysis/");
  fAnalysisDir->SetGuidance("Analysis control");

  fRootFileNameCmd = new G4UIcmdWithAString("/Analysis/RootFileName",this);
  fRootFileNameCmd->SetGuidance("set output ROOT file");
  fRootFileNameCmd->SetParameterName("RootFileName",true);
  fRootFileNameCmd->SetDefaultValue("QweakSim.root");
  fRootFileNameCmd->SetRange("verbose>=0");
  fRootFileNameCmd->AvailableForStates(G4State_PreInit);

  G4cout << "###### Leaving QweakSimAnalysisMessenger::QweakSimAnalysisMessenger() " << G4endl;
}

QweakSimAnalysisMessenger::~QweakSimAnalysisMessenger()
{
  G4cout << "###### Calling QweakSimAnalysisMessenger::~QweakSimAnalysisMessenger () " << G4endl;

  delete fRootFileNameCmd;
  delete fAnalysisDir;

  G4cout << "###### Leavinging QweakSimAnalysisMessenger::~QweakSimAnalysisMessenger () " << G4endl;
}

void QweakSimAnalysisMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == fRootFileNameCmd)
    {
      pQweakSimAnalysis->SetRootFileName(newValue);
    }
}
