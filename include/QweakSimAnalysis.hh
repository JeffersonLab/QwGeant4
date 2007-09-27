//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimAnalysis.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:22:16 $
   \author Klaus Hans Grimm
     
*/
//=============================================================================
// 
//=============================================================================
// 
//   ---------------------------
//  | Doxygen Class Information |
//  ---------------------------
/**
   \class QweakSimAnalysis
    
   \brief Handling of the output ROOT file

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:22:16 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimAnalysis_h 
#define QweakSimAnalysis_h 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimUserMainEvent.hh"

// user classes
class QweakSimUserMainEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimAnalysis {
public:
  QweakSimAnalysis();
  virtual ~QweakSimAnalysis();
  
public:

  void BeginOfRun();
  void EndOfRun();
  void EndOfEvent(G4int flag);

  void Init();
  void Finish();

  void Fill_RootNtuple() {QweakSimG4_RootNtuple->Fill();}
  void AutoSaveRootNtuple();

  QweakSimUserMainEvent* QweakSimG4_RootEvent;


private:

  void ConstructRootNtuple(); 

  TTree*   QweakSimG4_RootNtuple;
  TBranch* QweakSimG4_RootBranch;
  TFile*   QweakSimG4_RootFile;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimAnalysis.hh,v $
//      Revision 1.2  2005/12/27 19:22:16  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
