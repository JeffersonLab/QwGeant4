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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimCerenkovDetectorMessenger_h
#define QweakSimCerenkovDetectorMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// user includes
#include "QweakSimMessengerDeclaration.hh"

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
  G4UIcmdWithAString*        PreRadiatorMatCmd;

  G4UIcmdWithADoubleAndUnit* ContainerXPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerYPositionCmd;
  G4UIcmdWithADoubleAndUnit* ContainerZPositionCmd;

  G4UIcmdWithADoubleAndUnit* ContainerThicknessCmd;

  G4UIcmdWithADoubleAndUnit* TiltingAngleCmd;
  G4UIcmdWithADoubleAndUnit* KinkAngleCmd;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

