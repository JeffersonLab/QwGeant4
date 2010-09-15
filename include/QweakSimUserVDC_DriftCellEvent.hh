//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimUserVDC_DriftCellEvent.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:31:22 $
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
   \class QweakSimUserVDC_DriftCellEvent
    
   \brief Stores the data structure related to a VDC DriftCell Hit into the ROOT file for each event

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
//  Update Date:      $Date: 2005/12/27 19:31:22 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimUserVDC_DriftCellEvent_h
#define QweakSimUserVDC_DriftCellEvent_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


#include "Rtypes.h"

#ifndef __CINT__
#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimUserVDC_DriftCellEvent 
{

private:

  Int_t UDriftCellHasBeenHit;
  Int_t VDriftCellHasBeenHit;

  Int_t UDriftCellNbOfHits;
  Int_t VDriftCellNbOfHits;

public:
  
  // Constructor
  QweakSimUserVDC_DriftCellEvent();
  // Destructor 
  virtual ~QweakSimUserVDC_DriftCellEvent();

  void     Initialize();

  void     StoreUDriftCellHasBeenHit(Int_t nudc)   { UDriftCellHasBeenHit = nudc; }
  Int_t      GetUDriftCellHasBeenHit() const {return UDriftCellHasBeenHit;}

  void     StoreVDriftCellHasBeenHit(Int_t nvdc)   { VDriftCellHasBeenHit = nvdc; }
  Int_t      GetVDriftCellHasBeenHit() const {return VDriftCellHasBeenHit;}


  void     StoreUDriftCellNbOfHits(Int_t nu)     { UDriftCellNbOfHits = nu; }
  Int_t      GetUDriftCellNbOfHits() const {return UDriftCellNbOfHits;}

  void     StoreVDriftCellNbOfHits(Int_t nv)     { VDriftCellNbOfHits = nv; }
  Int_t      GetVDriftCellNbOfHits() const {return VDriftCellNbOfHits;}

  //-----------------

  // define a new Class known to ROOT  
  ClassDef(QweakSimUserVDC_DriftCellEvent,1)

};  // end class QweakSimUserVDC_DriftCellEvent 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimUserVDC_DriftCellEvent.hh,v $
//      Revision 1.2  2005/12/27 19:31:22  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 

