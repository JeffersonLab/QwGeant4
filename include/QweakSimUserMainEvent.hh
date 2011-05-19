//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserMainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:30:33 $
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
   \class QweakSimUserMainEvent
    
   \brief Defines Top ROOT Tree structure of the ROOT file for each event.

          Primary.

	  Region1.

	  Region2.

	  Region3.

	  Cerenkov.

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserMainEvent_h
#define QweakSimUserMainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// root include
#include "TObject.h"

// user includes
#include "QweakSimUserPrimaryEvent.hh"
#include "QweakSimUserGEM_MainEvent.hh"
#include "QweakSimUserHDC_MainEvent.hh"
#include "QweakSimUserVDC_MainEvent.hh"
#include "QweakSimUserTriggerScintillator_MainEvent.hh"
#include "QweakSimUserCerenkov_MainEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserMainEvent : public TObject
// class QweakSimUserMainEvent 
{

private:

public:

  // top directoty of Root output tree:
    
  QweakSimUserPrimaryEvent                     Primary;              // tree containing primary particle info

  QweakSimUserGEM_MainEvent                    Region1;              // tree containing HDC info
  QweakSimUserHDC_MainEvent                    Region2;              // tree containing HDC info
  QweakSimUserVDC_MainEvent                    Region3;              // tree containing VDC info

  QweakSimUserTriggerScintillator_MainEvent    TriggerScintillator;  // tree containing TriggerScintilliator info

  QweakSimUserCerenkov_MainEvent               Cerenkov;             // tree containing Cdetector info

public:
    
  // Constructor
  QweakSimUserMainEvent();
  // Destructor 
  virtual ~QweakSimUserMainEvent();
  
  //void SetTree(TTree *data){Cerenkov.SetTree(data);};

  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserMainEvent,1)

};  // end class QweakSimMainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 



