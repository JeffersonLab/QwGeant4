
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserTriggerScintillator_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:00 $
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
   \class QweakSimUserTriggerScintillator_MainEvent
    
   \brief ROOT Subtree structure for Trigger Scintillator MainEvent

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
//  Update Date:      $Date: 2005/12/27 19:31:00 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserTriggerScintillator_MainEvent_h
#define QweakSimUserTriggerScintillator_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include "cpp_include.h"
#include "Root_include.h"

#ifndef __CINT__
#include "Geant4_include.hh" 
#endif

// user include
#include "QweakSimUserTriggerScintillator_DetectorEvent.hh"
#include "QweakSimUserTriggerScintillator_PMTEvent.hh"

// user classes
class QweakSimUserTriggerScintillator_DetectorEvent;
class QweakSimUserTriggerScintillator_PMTEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//class QweakSimUserMainEvent : public TObject
class QweakSimUserTriggerScintillator_MainEvent 
{

private:

public:

  vector <QweakSimUserTriggerScintillator_DetectorEvent>  Detector;
//  QweakSimUserTriggerScintillator_PMTEvent       PMT;

public:
    
  // Constructor
  QweakSimUserTriggerScintillator_MainEvent();
  // Destructor 
 virtual ~QweakSimUserTriggerScintillator_MainEvent();
  

  //void SetTree(TTree *data){  Detector.SetTree(data); };
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserTriggerScintillator_MainEvent,1)

};  // end class QweakSimTriggerScintillator_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserTriggerScintillator_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:00  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
