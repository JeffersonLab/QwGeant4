//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimG4.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:09:32 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

#include "QweakSimDetectorConstruction.hh"
#include "QweakSimPhysicsList.hh"
#include "QweakSimPrimaryGeneratorAction.hh"
#include "QweakSimRunAction.hh"
#include "QweakSimEventAction.hh"
#include "QweakSimStackingAction.hh"		
//#include "QweakSimSteppingAction.hh"
//#include "QweakSimSteppingVerbose.hh"
//#include "QweakSimAnalysis.hh"
#include "QweakSimTrackingAction.hh"
//#include "QweakSimTrackInformation.hh"
//#include "QweakSimUserInformation.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4UI_USE_XM
    #include "G4UIXm.hh"
#endif

#ifdef G4VIS_USE
    #include "G4VisExecutive.hh"
#endif




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv) {

  //my Verbose output class
  G4VSteppingVerbose::SetInstance( new QweakSimSteppingVerbose() ); 
  
  // Run manager
  G4RunManager * runManager = new G4RunManager();

  // UserInitialization classes (mandatory)
  QweakSimUserInformation*       myQweakSimUserInformation  = new QweakSimUserInformation();
  QweakSimDetectorConstruction*  myQweakSimExperiment       = new QweakSimDetectorConstruction(myQweakSimUserInformation);
  QweakSimAnalysis*              myQweakSimAnalysis         = new QweakSimAnalysis();

//jpan@nuclear.uwinnipeg.ca
  QweakSimEPEvent*               myEPEvent                  = new QweakSimEPEvent();


  runManager->SetUserInitialization(myQweakSimExperiment);
  runManager->SetUserInitialization(new QweakSimPhysicsList() );
   






  // UserAction classes
  //runManager->SetUserAction( new QweakSimPrimaryGeneratorAction(myQweakSimUserInformation) );
  runManager->SetUserAction( new QweakSimPrimaryGeneratorAction( ) );
  runManager->SetUserAction( new QweakSimSteppingAction(myQweakSimUserInformation, myEPEvent));
  runManager->SetUserAction( new QweakSimStackingAction() );
  runManager->SetUserAction( new QweakSimTrackingAction(myQweakSimUserInformation) );
  runManager->SetUserAction( new QweakSimEventAction(myQweakSimAnalysis, myQweakSimUserInformation) );
  runManager->SetUserAction( new QweakSimRunAction(myQweakSimAnalysis) );  



  //Initialize G4 kernel
  runManager->Initialize();

  G4UIsession* session = 0;

 if (argc==1)   // Define UI session for interactive mode.
 {
     // G4UIterminal is a (dumb) terminal.
    #if defined(G4UI_USE_XM)
     session = new G4UIXm(argc,argv);
    #elif defined(G4UI_USE_WIN32)
     session = new G4UIWin32();
    #elif defined(G4UI_USE_TCSH)
     session = new G4UIterminal(new G4UItcsh);
    #else
      session = new G4UIterminal();
    #endif

 }


#ifdef G4VIS_USE
  // Visualization, if you choose to have it!
  // 
  // Simple graded message scheme - give first letter or a digit:
  //  0) quiet,         // Nothing is printed.
  //  1) startup,       // Startup and endup messages are printed...
  //  2) errors,        // ...and errors...
  //  3) warnings,      // ...and warnings...
  //  4) confirmations, // ...and confirming messages...
  //  5) parameters,    // ...and parameters of scenes and views...
  //  6) all            // ...and everything available.

  G4VisManager* visManager = new G4VisExecutive;
  //visManager -> SetVerboseLevel (1);
  visManager ->Initialize();
#endif


  //get the pointer to the User Interface manager 
  G4UImanager * UI = G4UImanager::GetUIpointer();  

 if (session)   // Define UI session for interactive mode.
    {
      // G4UIterminal is a (dumb) terminal.
      //UI->ApplyCommand("/control/execute myVis.mac");

#if defined(G4UI_USE_XM) || defined(G4UI_USE_WIN32)
      // Customize the G4UIXm,Win32 menubar with a macro file :
      UI->ApplyCommand("/control/execute gui.mac");
#endif

      session->SessionStart();
      delete session;
    }
  else           // Batch mode
    {
#ifdef G4VIS_USE
      visManager->SetVerboseLevel("quiet");
#endif
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }



#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;

  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


