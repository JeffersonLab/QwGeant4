//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimRunAction.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:14:28 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "QweakSimRunAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimRunAction::QweakSimRunAction(QweakSimAnalysis* AN)
  :runID(0), analysis(AN)
{
  G4cout << G4endl << "###### Calling/Leaving QweakSimRunAction::QweakSimRunAction()" << G4endl << G4endl;

  //  start analysis at begin of run
  analysis->BeginOfRun();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
QweakSimRunAction::~QweakSimRunAction()
{
  G4cout << G4endl << "###### Calling/Leaving QweakSimRunAction::~QweakSimRunAction()" << G4endl << G4endl;

  // End analysis procedure at end of run
  analysis->EndOfRun();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << G4endl << "###### Calling QweakSimRunAction::BeginOfRunAction()" << G4endl << G4endl;

  runID =   aRun->GetRunID();
  G4cout << "### Run " << runID <<  " start." << G4endl;


  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer();
      UI->ApplyCommand("/vis/scene/notifyHandlers");
    } 

  G4cout << G4endl << "###### Leaving QweakSimRunAction::BeginOfRunAction()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void QweakSimRunAction::EndOfRunAction(const G4Run* /*aRun*/)
{ 

  G4cout << G4endl << "###### Calling QweakSimRunAction::EndOfRunAction()" << G4endl << G4endl;
  if (G4VVisManager::GetConcreteInstance())
    {
     G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
    }



  G4cout << G4endl << "###### Leaving QweakSimRunAction::EndOfRunAction()" << G4endl << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int QweakSimRunAction::getRunID()
{
  return runID;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


