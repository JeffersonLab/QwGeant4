
//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimDetectorMessenger.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:28:39 $
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
   \class QweakSimDetectorMessenger
    
   \brief Scans the input file for /QweakSim/xyz commands.

    Up to now it is not used.
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
//  Update Date:      $Date: 2006/05/05 21:28:39 $
//  CVS/RCS Revision: $Revision: 1.3 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimDetectorMessenger_h
#define QweakSimDetectorMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
//#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimDetectorConstruction.hh"

// system classes
// class G4UIdirectory;
// class G4UIcmdWithAString;
// class G4UIcmdWithADoubleAndUnit;
// class G4UIcmdWithoutParameter;

// user classes
class QweakSimDetectorConstruction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimDetectorMessenger: public G4UImessenger
{
  public:
    QweakSimDetectorMessenger(QweakSimDetectorConstruction*);
   ~QweakSimDetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);

  private:
    QweakSimDetectorConstruction* myDetector;
    
    G4UIdirectory*             QweakSimDir;
    G4UIdirectory*             VisibilityDir;

    G4UIcmdWithoutParameter*   UpdateCmd;
    G4UIcmdWithoutParameter*   ShowHallFloor_Cmd;
    G4UIcmdWithoutParameter*   HideHallFloor_Cmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimDetectorMessenger.hh,v $
//      Revision 1.3  2006/05/05 21:28:39  grimm
//      Added /HallC/Visibility/ShowHallFloor and /HallC/Visibility/HideHallFloor
//
//      Revision 1.2  2005/12/27 19:23:27  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
