//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimG3NtupleReader.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:23:50 $
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
    \class QweakSimG3NtupleReader
    
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
//  Update Date:      $Date: 2005/12/27 19:23:50 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ==============================
//  CVS/RCS Log at end of file !!
// ==============================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimG3NtupleReader_h
#define QweakSimG3NtupleReader_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//#define HitsPerPrimaryEvent 1500

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimG3Ntuple.hh"

// user classes
class QweakSimG3Ntuple;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimG3NtupleReader
{

 private:

  Int_t   debug;               // debug flag, print out all infos

  // needed elements of Neven's Geant3 ntuple
  Int_t   my_gt_numhits;

  Float_t my_gt_q__2;
  Float_t my_gt_weight_n; // weight in ub (micro barn)

  Int_t   my_gt_ipart_det[1500];
  Float_t my_gt_ptot_o[1500];

  Float_t my_gt_px_o[1500];
  Float_t my_gt_py_o[1500];
  Float_t my_gt_pz_o[1500];

  Float_t my_gt_vertx_o[1500];
  Float_t my_gt_verty_o[1500];
  Float_t my_gt_vertz_o[1500];

  Float_t my_gt_theta_o[1500];
  Float_t my_gt_phi_o[1500];

  Float_t my_gt_en_o[1500];

  TString fInputFileNumber;
  TString fInputFileName;
  TFile  *fInputRootFile;

  // for appending trees from rootfile
  TTree  *InputTree;

  TRandom* myrand; 

  // private methods

  Int_t  Initialize();
  Int_t  LoadInputRootFile(TString FileName);
  void   check_events_to_be_read(Int_t &lastevent,Int_t &firstevent, TTree *tree);
 
public :    
  // public methods

  // Constructor
  QweakSimG3NtupleReader(TString FileName);
  // Destructor 
  ~QweakSimG3NtupleReader();
  
  void   InitInputTree();
  void   SetDebugLevel(Int_t debuglevel);
  void   LoopEvents(Int_t firstevent, Int_t lastevent);
  void   GetRandomEvent(QweakSimG3Ntuple  *primaryEvent);
  void   GetPrimaryEvent(int myNumber, QweakSimG3Ntuple  *primaryEvent);

  Int_t   NumberOfEntries;    // number of triggerevents, normally number of MPS 

private:

  G4ThreeVector* RotatedVertex;
  G4ThreeVector* RotatedMomentum;

}; // end class QweakSimG3NtupleReader

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimG3NtupleReader.hh,v $
//      Revision 1.2  2005/12/27 19:23:50  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
