//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
// 
/**
 
   \file QweakSimG3Ntuple.cc

   $Revision: 1.2 $	
   $Date: 2005/12/27 19:08:09 $

   \author Klaus Hans Grimm   

*/
//=============================================================================

//=============================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//  Last Update:      $Author: grimm $
//  Update Date:      $Date: 2005/12/27 19:08:09 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
//
//============================================================================
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...

#include "QweakSimG3Ntuple.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimG3Ntuple::QweakSimG3Ntuple()
{
  // initialize variables
  Vertex[0]     = 0.0;
  Vertex[1]     = 0.0;
  Vertex[2]     = 0.0;
  Momentum[0]   = 0.0;
  Momentum[1]   = 0.0;
  Momentum[2]   = 0.0;
  Theta         = 0.0;
  Phi           = 0.0;
  KineticEnergy = 0.0;
  TotalEnergy   = 0.0;
  Q2            = 0.0;
  Weight        = 0.0;
  ParticleID    = 0;
 

} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
QweakSimG3Ntuple::~QweakSimG3Ntuple()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

//=======================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimG3Ntuple.cc,v $
//      Revision 1.2  2005/12/27 19:08:09  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
// 
