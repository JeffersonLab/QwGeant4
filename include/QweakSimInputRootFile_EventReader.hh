//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimInputRootFile_EventReader.hh
   $Revision: 1.1 $	
   $Date: 2006/01/31 20:22:41 $
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
    \class QweakSimInputRootFile_EventReader
    
    \brief Reads the event root file ep_elastics.root.
	This file is generated externally by converting the Geant3 output Ntuple into a root file using h2root

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
//  Update Date:      $Date: 2006/01/31 20:22:41 $
//  CVS/RCS Revision: $Revision: 1.1 $
//  Status:           $State: Exp $
// 
// ==============================
//  CVS/RCS Log at end of file !!
// ==============================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimInputRootFile_EventReader_h
#define QweakSimInputRootFile_EventReader_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//#define HitsPerPrimaryEvent 1500

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimG3Ntuple.hh"	
//#include "QweakSimInputRootTree_CurrentEvent.hh"
#include "EPEvent.hh"

// user classes
class QweakSimG3Ntuple;
//class QweakSimInputRootTree_CurrentEvent;
class EPEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimInputRootFile_EventReader
{

 private:

  Int_t   debug;               // debug flag, print out all infos
  Int_t   eventcounter;

  // needed elements of Neven's Geant3 ntuple
  Int_t   my_gt_numhits;

  Double_t my_gt_q__2;
  Double_t my_gt_weight_n; // weight in ub (micro barn)

  Int_t   my_gt_ipart_det;
  Double_t my_gt_ptot_o;

  Double_t my_gt_px_o;
  Double_t my_gt_py_o;
  Double_t my_gt_pz_o;

  Double_t my_gt_vertx_o;
  Double_t my_gt_verty_o;
  Double_t my_gt_vertz_o;

  Double_t my_gt_theta_o;
  Double_t my_gt_phi_o;

  Double_t my_gt_en_o;

  TString fInputFileNumber;
  TString fInputFileName;
  TFile  *fInputRootFile;

  // for appending trees from rootfile
  TTree*  InputTree;

  TBranch* branch;
 //QweakSimInputRootTree_CurrentEvent* theCurrentEvent;
  EPEvent* event;


  TRandom* myrand; 

  // private methods

  Int_t  Initialize();
  Int_t  LoadInputRootFile(TString FileName);
  void   check_events_to_be_read(Int_t &lastevent,Int_t &firstevent, TBranch* branch);
  void   FillLeavesFromCurrentEvent(EPEvent* currentevent);
  void   PrintLeavesFromCurrentEvent();
 
public :    
  // public methods

  // Constructor
  QweakSimInputRootFile_EventReader(TString FileName);
  // Destructor 
  ~QweakSimInputRootFile_EventReader();
  
  void   InitInputTree();
  void   SetDebugLevel(Int_t debuglevel);
  void   LoopEvents(Int_t firstevent, Int_t lastevent);
  void   GetRandomEvent(QweakSimG3Ntuple  *primaryEvent);
  void   GetPrimaryEvent(int myNumber, QweakSimG3Ntuple  *primaryEvent);

  Int_t   NumberOfEntries;    // number of triggerevents, normally number of MPS 

private:

  G4ThreeVector* RotatedVertex;
  G4ThreeVector* RotatedMomentum;

 

}; // end class QweakSimInputRootFile_EventReader

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimInputRootFile_EventReader.hh,v $
//      Revision 1.1  2006/01/31 20:22:41  grimm
//      Reads the output root file of Michael's event generator.
//
//      Revision 1.2  2005/12/27 19:23:50  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
