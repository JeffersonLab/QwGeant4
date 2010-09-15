//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserCerenkov_MainEvent.hh
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
   \class QweakSimUserCerenkov_MainEvent
    
   \brief ROOT Subtree structure for Cerenkov MainEvent

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
#ifndef QweakSimUserCerenkov_MainEvent_h
#define QweakSimUserCerenkov_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include <vector>
using std::vector;


#include "Rtypes.h"

#ifndef __CINT__
#include "Geant4_include.hh" 
#endif

// user include
#include "QweakSimUserCerenkov_OctantEvent.hh"

// user classes
class QweakSimUserCerenkov_OctantEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//class QweakSimUserMainEvent : public TObject
class QweakSimUserCerenkov_MainEvent 
{

private:

public:

//jpan@nuclear.uwinnipeg.ca
//  vector <QweakSimUserCerenkov_OctantEvent> Octant;
  QweakSimUserCerenkov_DetectorEvent  Detector;
  QweakSimUserCerenkov_PMTEvent       PMT;

public:
    
  // Constructor
  QweakSimUserCerenkov_MainEvent();
  // Destructor 
 virtual ~QweakSimUserCerenkov_MainEvent();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserCerenkov_MainEvent,1)

};  // end class QweakSimCerenkov_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserCerenkov_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:28:38  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

