//=============================================================================
// 
//   ---------------------------
//  | Doxygen File Information |
//  ---------------------------
/**
 
   \file QweakSimPrimaryGeneratorActionMessenger.hh
   $Revision: 1.3 $	
   $Date: 2006/05/05 21:33:13 $
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
   \class QweakSimPrimaryGeneratorActionMessenger
    
   \brief Scans the input file for ...

   Placeholder for a long explaination
    
 */


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef QweakSimPrimaryGeneratorActionMessenger_h
#define QweakSimPrimaryGeneratorActionMessenger_h 1
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// system includes
#include "Geant4_include.hh" 

// user includes
#include "QweakSimPrimaryGeneratorAction.hh"

// system classes
// class G4UIdirectory;
// class G4UIcmdWithAnInteger;
// class G4UIcmdWithoutParameter;

// user classes
class QweakSimPrimaryGeneratorAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class QweakSimPrimaryGeneratorActionMessenger: public G4UImessenger
{
public:  
   QweakSimPrimaryGeneratorActionMessenger(QweakSimPrimaryGeneratorAction* );
  ~QweakSimPrimaryGeneratorActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:  
  
  QweakSimPrimaryGeneratorAction*     pPrimaryGeneratorAction;
  
  G4UIdirectory*           Dir;
  G4UIcmdWithAnInteger*    verboseCmd;
  G4UIcmdWithoutParameter* resetCmd;
  G4UIcmdWithAnInteger*    InitEventCounterCmd;
  G4UIcmdWithAnInteger*    SelectOctant_Cmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


