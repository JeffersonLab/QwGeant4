//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimG3Ntuple.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:23:41 $
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
   \class QweakSimG3Ntuple
    
   \brief Contains the elements of a primary event. 
   
   The primary events will be extracted from the Geant3 Ntuple and their properties will be stored in this class.

    
 */
//=============================================================================
// 
//
//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:23:41 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ==============================
//  CVS/RCS Log at end of file !!
// ==============================
//
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimG3Ntuple_h
#define QweakSimG3Ntuple_h
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// my custom class containing the elements of a primary event.
// The primary events will be extracted from the Geant3 Ntuple
// and their properties will be stored in this class

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
class QweakSimG3Ntuple
{

 public:    
  // Constructor
  QweakSimG3Ntuple();
  // Destructor 
  ~QweakSimG3Ntuple();

  void     SetQ2(Float_t _q2) {Q2 = _q2;}
  Float_t  GetQ2() const {return Q2;}


  Float_t Vertex[3];
  Float_t Momentum[3];

  Float_t Theta;
  Float_t Phi;

  Float_t KineticEnergy;
  Float_t TotalEnergy;

  Float_t Q2;
  Float_t Weight;

  Int_t   ParticleID;

 private:

};  // end class QweakSimG3Ntuple 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#endif 

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimG3Ntuple.hh,v $
//      Revision 1.2  2005/12/27 19:23:41  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
