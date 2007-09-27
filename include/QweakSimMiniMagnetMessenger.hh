//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimMiniMagnetMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:25:57 $
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
   \class QweakSimMiniMagnetMessenger
    
   \brief Scans input file for /MiniMagnet/xyz commands

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
//  Update Date:      $Date: 2005/12/27 19:25:57 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#ifndef QweakSimMiniMagnetMessenger_h
#define QweakSimMiniMagnetMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimMiniMagnet.hh"

// user classes
class QweakSimMiniMagnet;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class QweakSimMiniMagnetMessenger: public G4UImessenger
{
public:
  QweakSimMiniMagnetMessenger(QweakSimMiniMagnet* );
  ~QweakSimMiniMagnetMessenger();
  
  void SetNewValue(G4UIcommand*, G4String);
  
private:
  
  QweakSimMiniMagnet*        myMiniMagnet;

  G4UIdirectory*             MiniMagnetDir;
  G4UIcmdWithADoubleAndUnit* CenterPosInZCmd;

  G4UIdirectory*             SingleCoilDir;
  G4UIcmdWithADoubleAndUnit* MinDiameterCmd;
  G4UIcmdWithADoubleAndUnit* MaxDiameterCmd;
  G4UIcmdWithADoubleAndUnit* RadialDistanceCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimMiniMagnetMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:25:57  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//

