
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_MainEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:28 $
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
   \class QweakSimUserVDC_MainEvent
    
   \brief Defines the Top Root tree structure for storing VDC events.

    A VDC Event contains the information of the DriftCell geometry, and stores
    events for the Front VDC and Back VDC:

    Region3.Config. 

    Region3.ChamberFront.

    Region3.ChamberBack.
   
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
//  Update Date:      $Date: 2005/12/27 19:31:28 $
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
   \class QweakSimUserVDC_MainEvent
    
   \brief Defines the Top Root tree structure for storing VDC events.

    A VDC Event contains the information of the DriftCell geometry, and stores
    events for the Front VDC and Back VDC:

    Region3.Config. 

    Region3.ChamberFront.

    Region3.ChamberBack.
   
   Placeholder for a long explaination
    
 */
//=============================================================================
// 



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_MainEvent_h
#define QweakSimUserVDC_MainEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


#ifndef __CINT__
#endif

// user includes
#include "QweakSimUserVDC_Config.hh"
#include "QweakSimUserVDC_SingleVDCEvent.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_SingleVDCEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//class QweakSimUserMainEvent : public TObject
class QweakSimUserVDC_MainEvent 
{

private:


public:

  QweakSimUserVDC_Config          Config;
  QweakSimUserVDC_SingleVDCEvent  ChamberFront;
  QweakSimUserVDC_SingleVDCEvent  ChamberBack;

public:
    
  // Constructor
  QweakSimUserVDC_MainEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_MainEvent();
  
  void Clear();
  
  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_MainEvent,1)

};  // end class QweakSimUserVDC_MainEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_MainEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:28  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
