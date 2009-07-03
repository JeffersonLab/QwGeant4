
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserGEM_SingleGEMEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:29:40 $
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
   \class QweakSimUserGEM_SingleGEMEvent
    
   \brief ROOT Subtree structure for SingleGEMEvent

   Placeholder for a long explaination
    
 */
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserGEM_SingleGEMEvent_h
#define QweakSimUserGEM_SingleGEMEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "cpp_include.h"
#include "Root_include.h"

#ifndef __CINT__
#endif

// user includes
#include "QweakSimUserGEM_WirePlaneEvent.hh"

// user classes
class QweakSimUserGEM_WirePlaneEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserGEM_SingleGEMEvent 
{

private:


public:

  QweakSimUserGEM_WirePlaneEvent  WirePlane;

public:
    
  // Constructor
  QweakSimUserGEM_SingleGEMEvent();
  // Destructor 
  virtual ~QweakSimUserGEM_SingleGEMEvent();
  
  void Initialize();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserGEM_SingleGEMEvent,1)
    
};  // end class QweakSimGEM_SingleGEMEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

