//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserGEM_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:29:34 $
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
   \class QweakSimUserGEM_MainEvent
    
   \brief ROOT Subtree structure for GEM MainEvent

   Placeholder for a long explaination
    
 */
//=============================================================================
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserGEM_MainEvent_h
#define QweakSimUserGEM_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "cpp_include.h"
#include "Root_include.h"

#ifndef __CINT__
#endif

// user includes
#include "QweakSimUserGEM_SingleGEMEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserGEM_SingleGEMEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//class QweakSimUserMainEvent : public TObject
class QweakSimUserGEM_MainEvent 
{

private:


public:

  QweakSimUserGEM_SingleGEMEvent  ChamberFront;
  QweakSimUserGEM_SingleGEMEvent  ChamberBack;

public:
    
  // Constructor
  QweakSimUserGEM_MainEvent();
  // Destructor 
  virtual ~QweakSimUserGEM_MainEvent();
  
  void Clear();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserGEM_MainEvent,1)

};  // end class QweakSimGEM_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

