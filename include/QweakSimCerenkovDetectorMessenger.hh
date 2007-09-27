//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimCerenkovDetectorMessenger.hh
   $Revision: 1.2 $	
   $Date: 2005/12/27 19:23:04 $
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
   \class QweakSimCerenkovDetectorMessenger
    
   \brief Scans the input file for /Cerenkov/xyz commands

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
//  Update Date:      $Date: 2005/12/27 19:23:04 $
//  CVS/RCS Revision: $Revision: 1.2 $
//  Status:           $State: Exp $
// 
// ===================================
//  CVS Revision Log at end of file !!
// ===================================
// 
//=============================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimCerenkovDetectorMessenger_h
#define QweakSimCerenkovDetectorMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "cpp_include.h"
#include "Root_include.h"
#include "Geant4_include.hh" 

// user includes
#include "QweakSimCerenkovDetector.hh"


// system classes
// class G4UIdirectory;
// class G4UIcmdWithAString;
// class G4UIcmdWithAnInteger;
// class G4UIcmdWithADoubleAndUnit;
// class G4UIcmdWithoutParameter;

//user classes
class QweakSimCerenkovDetector;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimCerenkovDetectorMessenger: public G4UImessenger
{
  public:
    QweakSimCerenkovDetectorMessenger(QweakSimCerenkovDetector*);
   ~QweakSimCerenkovDetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
private:
  QweakSimCerenkovDetector*            myCerenkovDetector;
  
  G4UIdirectory*             Dir;

  G4UIcmdWithAString*        ContainerMatCmd;
  G4UIcmdWithAString*        DetectorMatCmd;

  G4UIcmdWithADoubleAndUnit* ContainerXPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerYPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerZPositionCmd;

  G4UIcmdWithADoubleAndUnit* ContainerThicknessCmd;

  G4UIcmdWithADoubleAndUnit* TiltingAngleCmd;
  G4UIcmdWithADoubleAndUnit* KinkAngleCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

//=======================================================================================
//   -----------------------
//  | CVS File Information |
//  -----------------------
// 
//      $Revisions$  
//      $Log: QweakSimCerenkovDetectorMessenger.hh,v $
//      Revision 1.2  2005/12/27 19:23:04  grimm
//      - Redesign of Doxygen header containing CVS info like revision and date
//      - Added CVS revision log at the end of file
//
//
