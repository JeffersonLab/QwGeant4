//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_OctantEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:28:38 $
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
   \class QweakSimUserCerenkov_OctantEvent
    
   \brief ROOT Subtree structure for Cerenkov OctantEvent

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
//  Update Date:      $Date: 2005/12/27 19:28:38 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserCerenkov_OctantEvent_h
#define QweakSimUserCerenkov_OctantEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root includes
#include "Rtypes.h"

// user includes
#include "QweakSimUserCerenkov_DetectorEvent.hh"
#include "QweakSimUserCerenkov_PMTEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//class QweakSimUserOctantEvent : public TObject
class QweakSimUserCerenkov_OctantEvent 
{

private:

public:

//jpan@nuclear.uwinnipeg.ca
  QweakSimUserCerenkov_DetectorEvent  Detector;
  QweakSimUserCerenkov_PMTEvent       PMT;

public:
    
  // Constructor
  QweakSimUserCerenkov_OctantEvent();
  // Destructor 
  virtual ~QweakSimUserCerenkov_OctantEvent();
  

  //void SetTree(TTree *data){  Detector.SetTree(data); };
  
  // define a new Class known to ROOT  

//jpan@nuclear.uwinnipeg.ca
  ClassDef(QweakSimUserCerenkov_OctantEvent,1)

};  // end class QweakSimCerenkov_OctantEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserCerenkov_OctantEvent.hh,v $
//      Revision 1.2  2005/12/27 19:28:38  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

