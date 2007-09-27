
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
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:29:40 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
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

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserGEM_SingleGEMEvent.hh,v $
//      Revision 1.2  2005/12/27 19:29:40  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
