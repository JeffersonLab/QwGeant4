
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserHDC_SingleHDCEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:30:04 $
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
   \class QweakSimUserHDC_SingleHDCEvent
    
   \brief ROOT Subtree structure for HDC SingleHDCEvent

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
//  Update Date:      $Date: 2005/12/27 19:30:04 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserHDC_SingleHDCEvent_h
#define QweakSimUserHDC_SingleHDCEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "cpp_include.h"
#include "Root_include.h"

#ifndef __CINT__
#endif

// user includes
#include "QweakSimUserHDC_WirePlaneEvent.hh"

// user classes
class QweakSimUserHDC_WirePlaneEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserHDC_SingleHDCEvent 
{

private:


public:

  QweakSimUserHDC_WirePlaneEvent  WirePlane1;
  //QweakSimUserHDC_WirePlaneEvent  WirePlane2;
  //QweakSimUserHDC_WirePlaneEvent  WirePlane3;
  //QweakSimUserHDC_WirePlaneEvent  WirePlane4;
  //QweakSimUserHDC_WirePlaneEvent  WirePlane5;
  //QweakSimUserHDC_WirePlaneEvent  WirePlane6;

public:
    
  // Constructor
  QweakSimUserHDC_SingleHDCEvent();
  // Destructor 
  virtual ~QweakSimUserHDC_SingleHDCEvent();
  
  void Initialize();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserHDC_SingleHDCEvent,1)
    
};  // end class QweakSimHDC_SingleHDCEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserHDC_SingleHDCEvent.hh,v $
//      Revision 1.2  2005/12/27 19:30:04  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

