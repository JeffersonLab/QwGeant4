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
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:29:34 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

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
  

  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserGEM_MainEvent,1)

};  // end class QweakSimGEM_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserGEM_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:29:34  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
