
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_SingleVDCEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:36 $
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
   \class QweakSimUserVDC_SingleVDCEvent
    
   \brief tores the data structure related to a VDC Hit into the ROOT file for each event.
    A VDC Hit contains the information of a WirePlane Hit and/or a DriftCell Hit
  
   Placeholder for a long explaination

   Region3.ChamberFront.WirePlane

   Region3.ChamberFront.DriftCell	

   Region3.ChamberBack.WirePlane

   Region3.ChamberBack.DriftCell	

    
 */
//=============================================================================
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:31:36 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================
//=============================================================================
/**
   \class QweakSimUserVDC_SingleVDCEvent
    
   \brief Stores the data structure related to a VDC Hit into the ROOT file for each event.
    A VDC Hit contains the information of a WirePlane Hit and/or a DriftCell Hit   
   
   Placeholder for a long explaination

   Region3.ChamberFront.WirePlane

   Region3.ChamberFront.DriftCell	

   Region3.ChamberBack.WirePlane

   Region3.ChamberBack.DriftCell	
    
 */
//=============================================================================
// 


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_SingleVDCEvent_h
#define QweakSimUserVDC_SingleVDCEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "cpp_include.h"
#include "Root_include.h"

#ifndef __CINT__
#endif

// user includes
#include "QweakSimUserVDC_WirePlaneEvent.hh"
#include "QweakSimUserVDC_DriftCellEvent.hh"

// user classes
class QweakSimUserVDC_WirePlaneEvent;
class QweakSimUserVDC_DriftCellEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_SingleVDCEvent 
{

private:


public:

  QweakSimUserVDC_WirePlaneEvent  WirePlane;
  QweakSimUserVDC_DriftCellEvent  DriftCell;

public:
    
  // Constructor
  QweakSimUserVDC_SingleVDCEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_SingleVDCEvent();
  
  void Initialize();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_SingleVDCEvent,1)
    
};  // end class QweakSimUserVDC_SingleVDCEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_SingleVDCEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:36  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

